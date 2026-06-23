// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueMagicProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ARogueMagicProjectile();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovementComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* EffectComp;

public:	
	virtual void Tick(float DeltaTime) override;

};
