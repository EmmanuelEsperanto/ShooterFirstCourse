// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor, Color, const FString&, Name);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementType MoveType = EMovementType::Sin;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TimerRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
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
	
	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const { return GeometryData; }



	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;


	FOnTimerFinished OnTimerFinished;

protected:
	virtual void BeginPlay() override;
	void HandleMovement();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
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
