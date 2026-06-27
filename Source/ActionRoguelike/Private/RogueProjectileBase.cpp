// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ARogueProjectileBase::ARogueProjectileBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(SphereComp);
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->SetNotifyRigidBodyCollision(true);
	SphereComp->OnComponentHit.AddDynamic(this, &ThisClass::OnActorHit);
	

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->InitialSpeed = 1000.f;
	ProjectileMovementComp->MaxSpeed = 1000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(RootComponent);
}

void ARogueProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARogueProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARogueProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ARogueProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherHitComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ARogueProjectileBase::Explode_Implementation()
{
	if (ensure(IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}

