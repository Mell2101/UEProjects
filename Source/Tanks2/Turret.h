// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "Turret.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class ACannon;
class UBoxComponent;
class APawn;
class UHealthComponent;
class ATankPawn;

UCLASS()
class TANKS2_API ATurret : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

	UFUNCTION()
		void TakeDamage(FDamageData DamageData);
	UFUNCTION()
		void DamageTaked(float DamageValue);
	UFUNCTION()
		void Die();

	FVector GetEyesPosition();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		TSubclassOf<ACannon> CannonClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		TSubclassOf<ACannon> CannonClassSecond;
	

	UPROPERTY()
		ACannon* Cannon;
	UPROPERTY()
		ACannon* CannonSecond;
	UPROPERTY()
		APawn* PlayerPawn;
	UPROPERTY()
		ATankPawn* TankPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetSpeed = 0.1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingRate = 0.005;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float Accurency = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		float TimeForChange = 5;



	bool IsPlayerSeen();
	void SwapCannon();

	FTimerHandle TimerHandleTurret;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
