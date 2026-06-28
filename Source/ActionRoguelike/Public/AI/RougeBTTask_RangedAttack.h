// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RougeBTTask_RangedAttack.generated.h"

class ARogueProjectileBase;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URougeBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	UPROPERTY(EditAnywhere, Category="AI")
	TSubclassOf<ARogueProjectileBase> ProjectileClass;
};
