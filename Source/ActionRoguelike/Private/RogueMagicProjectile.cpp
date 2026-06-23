// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ARogueMagicProjectile::ARogueMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(SphereComp);
	SphereComp->SetCollisionProfileName("Projectile");
	

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->InitialSpeed = 1000.f;
	ProjectileMovementComp->MaxSpeed = 1000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(RootComponent);
}

void ARogueMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARogueMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

