// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueTargetDummy.generated.h"

class URogueAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	ARogueTargetDummy();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	URogueAttributeComponent* AttributeComp;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, URogueAttributeComponent* OwningComp, float NewHealth, float Delta);

};
