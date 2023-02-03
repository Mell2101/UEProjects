// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"
#include "DamageTaker.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawnpoint"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent >(TEXT("ShootEffect"));
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffect"));
	AudioEffect->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();

	Reload();
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACannon::Fire()
{
	
	if (ReadyToFire == false || Ammo < 0 )
	{
		return;
	}
	ShootEffect->ActivateSystem();
	AudioEffect->Play();
	
	if (Type == ECannonType::FireProjectile)
	{
		//GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, FString::Printf(TEXT("Fire -Projectile, Ammo = %f"), Ammo));

		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, FString::Printf(TEXT("Fire - trace, Ammo = %f"),Ammo));
		FHitResult hitResult;
		FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;
		FVector start = ProjectileSpawnPoint->GetComponentLocation();
		FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;
		
		if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end,	ECollisionChannel::ECC_Visibility, traceParams))
		{
			if (hitResult.Actor.Get())
			{
				IDamageTaker* damageTakerActor = Cast<IDamageTaker>(hitResult.Actor.Get());
				DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.5f, 0, 5);
				if (damageTakerActor)
				{
					//hitResult.Actor.Get()->Destroy();

					FDamageData damageData;
					damageData.DamageValue = 1;

					damageTakerActor->TakeDamage(damageData);

				}
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), start, end, FColor::Blue, false, 0.5f, 0, 5);
		}

		
	}
	ReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload,  FireRate, false);
	
}

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

void ACannon::Reload()
{
	ReadyToFire = true;
}

void ACannon::ActiveCannon(bool bIsVisible)
{
	if (bIsVisible)
	{
		Mesh->SetVisibility(true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		Mesh->SetVisibility(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACannon::AddAmmo(float value)
{
	Ammo += value;
}

void ACannon::AmmoDecrease()
{
	--Ammo;
}

