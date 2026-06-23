// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueItemChest : public AActor, public IRogueGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ARogueItemChest();
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
	UPROPERTY(EditAnywhere)
	float TargetPitch = 110.f;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

public:	
	virtual void Tick(float DeltaTime) override;

};
