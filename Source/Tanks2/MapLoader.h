// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "MapLoader.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UPointLightComponent;

UCLASS()
class TANKS2_API AMapLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapLoader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* GatesMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* TriggerCollider;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UPointLightComponent* ActivatedLight;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UPointLightComponent* DeactivateLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level loading params")
		FName LoadLevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level loading params")
		bool bIsActivated = false;

	UFUNCTION()
		void OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const
			FHitResult& SweepResult);

	void SetActiveLights();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetIsActivated(bool NewIsActivated);




};
