// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	ARogueExplosiveBarrel();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

};
