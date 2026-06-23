// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "RogueGameplayInterface.h"

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void URogueInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void URogueInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams CollisionParams;
	CollisionParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	AActor* Owner = GetOwner();
	FVector Start;
	FVector End;
	
	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	
	Start = EyeLocation;
	End = Start + (EyeRotation.Vector() * 1000);
	
	TArray<FHitResult> HitResults;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(30.f);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		CollisionParams,
		CollisionShape
	);
	
	for (const FHitResult& HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<URogueGameplayInterface>())
			{
				APawn* OwnerPawn = Cast<APawn>(Owner);
				IRogueGameplayInterface::Execute_Interact(HitActor, OwnerPawn);
				break;
			}
		}
	}
}