// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RougeBTTask_RangedAttack.h"

#include "AIController.h"
#include "RogueProjectileBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type URougeBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		ACharacter* Character = AIController->GetCharacter();
		if (Character == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		FVector MuzzleLocation = Character->GetMesh()->GetSocketLocation(FName("Muzzle_01"));
		
		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator Rotation = Direction.Rotation();
		
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		ARogueProjectileBase* Projectile = Cast<ARogueProjectileBase>(Character->GetWorld()->SpawnActor<ARogueProjectileBase>(ProjectileClass, MuzzleLocation, Rotation, Params));
		
		return Projectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Failed;
}
