// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "Cannon.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "HealthComponent.h"
#include "MyActor.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class UBoxComponent;
class ACannon;
class UHealthComponent;

UCLASS()
class TANKS2_API AMyActor : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* MeshFirst;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* MeshSecond;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
		UArrowComponent* SetupSomething;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
		UBoxComponent* BoxColl;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
		UHealthComponent* Health;

	UPROPERTY()
		ACannon* Cannon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		TSubclassOf<ACannon> CannonClass;
	

	UFUNCTION()
		void Die();
	UFUNCTION()
		void DamageTaked(float DamageValue);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void TakeDamage(FDamageData DamageData);
	
	void Fire();

};
