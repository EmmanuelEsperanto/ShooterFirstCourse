// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

void AGeometryHubActor::DoActorsSpawn()
{
	UWorld* World = GetWorld();
	if (World)
	{

		if (GeometryClass)
		{
			for (int32 i = 0; i < 10; ++i)
			{

				const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f * i));
				ABaseGeometryActor* SpawnedGeometry = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);
				if (SpawnedGeometry)
				{
					FGeometryData Data;
					Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
					SpawnedGeometry->SetGeometryData(Data);
				}
			}
		}
	}

}

void AGeometryHubActor::DoActorsSpawnZ()
{
	UWorld* World = GetWorld();
	if (World)
	{
		if (GeometryClass)
		{

			for (int32 i2 = 0; i2 < 10; ++i2)
			{

				const FTransform GeometryTransform2 = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i2, 700.0f * i2));
				ABaseGeometryActor* SpawnedGeometry2 = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform2);
				if (SpawnedGeometry2)
				{
					FGeometryData Data2;
					Data2.Color = FLinearColor::MakeRandomColor();
					SpawnedGeometry2->SetGeometryData(Data2);
					SpawnedGeometry2->FinishSpawning(GeometryTransform2);
				}
			}
		}
	}
}

void AGeometryHubActor::DoActorsSpawnArray()
{
	UWorld* World = GetWorld();
	if (World)
	{
			for (const FGeometryPayload Payload : GeometryPayloads)

			{
				ABaseGeometryActor* SpawnedGeometry3 = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);
				if (SpawnedGeometry3)
				{
					SpawnedGeometry3->SetGeometryData(Payload.Data);
					SpawnedGeometry3->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
					SpawnedGeometry3->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
					SpawnedGeometry3->FinishSpawning(Payload.InitialTransform);
				}
			}
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor Color, const FString& Name)
{
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor name: %s Color %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if (!Actor) return;
	
	UE_LOG(LogGeometryHub, Error, TEXT("Timer Finished --- %s"), *Actor->GetName());

	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);

	if (!Geometry) return;

	UE_LOG(LogGeometryHub, Display, TEXT("Cast is success, amplitude %f"), Geometry->GetGeometryData().Amplitude);

	Geometry->Destroy();
	//Geometry->SetLifeSpan(1.0f);
}


// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();
	
	//DoActorsSpawn();
	//DoActorsSpawnZ();
	DoActorsSpawnArray();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

