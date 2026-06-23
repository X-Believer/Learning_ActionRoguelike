// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueItemChest.h"

ARogueItemChest::ARogueItemChest()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
	
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(RootComponent);
}

void ARogueItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	IRogueGameplayInterface::Interact_Implementation(InstigatorPawn);
}

void ARogueItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

