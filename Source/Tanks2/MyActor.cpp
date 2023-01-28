// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshFirst = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshFirst"));
	RootComponent = MeshFirst;

	MeshSecond = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshSecond"));
	MeshSecond->AttachToComponent(MeshFirst, FAttachmentTransformRules::KeepRelativeTransform);

	SetupSomething = CreateDefaultSubobject<UArrowComponent>(TEXT("SetupSomething"));
	SetupSomething->AttachToComponent(MeshSecond, FAttachmentTransformRules::KeepRelativeTransform);

	BoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColl"));
	BoxColl->SetupAttachment(MeshSecond);

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Health->OnDie.AddUObject(this, &AMyActor::Die);
	Health->OnDamaged.AddUObject(this, &AMyActor::DamageTaked);



}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyActor::Die()
{
	Destroy();
}

void AMyActor::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(),
		DamageValue, Health->GetHealth());
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::TakeDamage(FDamageData DamageData)
{
	Health->TakeDamage(DamageData);
}

void AMyActor::Fire()
{
	if(Cannon) Cannon->Fire();
}

