// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter/Public/BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)



void ABaseGeometryActor::SetColor(FLinearColor NewColor)
{
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if(DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("MyColor", NewColor);
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if(++CurrentTimerCount <= MaxTimerCount)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
	
		SetColor(NewColor);
	} else
	{
		GetWorldTimerManager().ClearTimer(MyTimerHandle);
	}
}


ABaseGeometryActor::ABaseGeometryActor()
{
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyBaseMesh");
	SetRootComponent(BaseMesh);

	InitialLocation = GetActorLocation();
	const FLinearColor NewColor2 = FLinearColor::MakeRandomColor();
	
	SetColor(NewColor2);
}

void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	PrintTypes();

	FTransform Transform = GetActorTransform();

	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Transform %s"), *Transform.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Location %s"), *Location.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Rotation %s"), *Rotation.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Scale %s"), *Scale.ToString());


	UE_LOG(LogBaseGeometry, Warning, TEXT("Human transform is : %s"), *Transform.ToHumanReadableString());



	SetColor(FLinearColor::Blue);

	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
	

}



void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
		{
			float time = GetWorld()->GetTimeSeconds();
			CurrentLocation = GetActorLocation();
			CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * time);
			SetActorLocation(CurrentLocation);
		}
		break;
	case EMovementType::Static: break;
	default: break;
	}
}

void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
	
}

void ABaseGeometryActor::PrintTypes()
{
	
	FString Name = "John Connor";
	
	UE_LOG(LogTemp, Display, TEXT("Weapons num: %d, kills num: %i"), WeaponsNum, KillsNum);
	UE_LOG(LogTemp, Display, TEXT("Health: %f"), Health);
	UE_LOG(LogTemp, Display, TEXT("Health: %.2f"), Health);
	UE_LOG(LogTemp, Display, TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogTemp, Display, TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));

	FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr= "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is dead = " + FString(IsDead ? "true" : "false");
	FString Stat = FString::Printf(TEXT(" \n == All Stat == \n %s \n %s \n %s "), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, Stat, true, FVector2D(1.5f, 1.5f));
}