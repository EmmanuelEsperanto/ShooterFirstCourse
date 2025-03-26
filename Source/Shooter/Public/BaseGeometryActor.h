// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Amplitude = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	EMovementType MoveType = EMovementType::Sin;

	UPROPERTY(EditAnywhere)
	float TimerRate = 1.0f;

	UPROPERTY(EditAnywhere)
	FLinearColor Color = FLinearColor::MakeRandomColor();
	
};


/**
 * 
 */
UCLASS()
class SHOOTER_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
public:
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; }
	
protected:
	virtual void BeginPlay() override;
	void HandleMovement();

	UPROPERTY(EditAnywhere, Category = "Movement")
	FGeometryData GeometryData;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponsNum = 4;
	
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 1;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health = 32.12521f;

	UPROPERTY(EditAnywhere, Category = "Health")
	bool IsDead = false;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool HasWeapon = true;

	UPROPERTY(EditAnywhere)
	FLinearColor MeshColor = GeometryData.Color;
public:
	virtual void Tick(float DeltaTime) override;

private:
	void PrintTypes();

	FVector InitialLocation;

	FVector CurrentLocation;

	void SetColor(FLinearColor NewColor);

	FTimerHandle MyTimerHandle;

	void OnTimerFired();

	const int32 MaxTimerCount = 10;

	int32 CurrentTimerCount = 0;
};
