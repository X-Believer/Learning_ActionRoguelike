// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueDashProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ARogueDashProjectile::ARogueDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;
	
	ProjectileMovementComp->InitialSpeed = 2000.f;
}

void ARogueDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DelayDetonateTimer, this, &ARogueDashProjectile::Explode, DetonateDelay);
}

void ARogueDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(DelayDetonateTimer);
	
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	
	EffectComp->DeactivateSystem();
	
	ProjectileMovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);
	
	FTimerHandle DelayTeleportTimer;
	GetWorldTimerManager().SetTimer(DelayTeleportTimer, this, &ARogueDashProjectile::TeleportInstigator, TeleportDelay);
}

void ARogueDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}
