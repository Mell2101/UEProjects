// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsComponent.h"

// Sets default values for this component's properties
UPhysicsComponent::UPhysicsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPhysicsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPhysicsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FVector> UPhysicsComponent::GenerateTrajectory(FVector StartPos, FVector Velocity,
	float MaxTime,float TimeStep ,float MinZValue /*= 0*/)
{
	float t = 0;
	TArray<FVector> trajectory;
	FVector gravityVector(0, 0, Graviti);
	for ( t; t < MaxTime; t = t + TimeStep);
	{
		FVector position = StartPos + Velocity * t + gravityVector * t * t /2;
		
		if (position.Z <= MinZValue)
		{
			switch (1)
			{
			case (1):
				{
					break;
				}
			
			}
		} 
				
		trajectory.Add(position);
	}

	return trajectory;
}

