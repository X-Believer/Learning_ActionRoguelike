// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueMagicProjectile.h"
#include "RogueAttributeComponent.h"

ARogueMagicProjectile::ARogueMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARogueMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARogueMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherHitComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherHitComponent, NormalImpulse, Hit);
	if (OtherActor && OtherActor != GetInstigator())
	{
		URogueAttributeComponent* AttributeComp = Cast<URogueAttributeComponent>(OtherActor->GetComponentByClass(URogueAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.f);
			Destroy();
		}
	}
}