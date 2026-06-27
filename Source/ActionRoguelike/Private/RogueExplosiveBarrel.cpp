// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueExplosiveBarrel.h"

#include "DrawDebugHelpers.h"
#include "PhysicsEngine/RadialForceComponent.h"

ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;
	
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(MeshComp);
	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->Radius = 750.f;
	RadialForceComp->ImpulseStrength = 300.f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void ARogueExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARogueExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARogueExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	MeshComp->OnComponentHit.AddDynamic(this, &ARogueExplosiveBarrel::OnActorHit);
}

void ARogueExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
	
	DrawDebugString(GetWorld(), GetActorLocation() + FVector(0, 0, 100), "BOOM!", nullptr, FColor::White, 2.f, true);
}