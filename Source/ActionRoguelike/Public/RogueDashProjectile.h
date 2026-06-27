// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectileBase.h"
#include "RogueDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ARogueDashProjectile : public ARogueProjectileBase
{
	GENERATED_BODY()
public:
	ARogueDashProjectile();
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Teleport")
	float TeleportDelay;
	
	UPROPERTY(EditDefaultsOnly, Category="Teleport")
	float DetonateDelay;
	
	FTimerHandle DelayDetonateTimer;
	
	virtual void Explode_Implementation() override;
	
	void TeleportInstigator();
};
