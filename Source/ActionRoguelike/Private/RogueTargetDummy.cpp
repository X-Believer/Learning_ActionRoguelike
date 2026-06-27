// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueTargetDummy.h"

#include "RogueAttributeComponent.h"

ARogueTargetDummy::ARogueTargetDummy()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
	
	AttributeComp = CreateDefaultSubobject<URogueAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &ARogueTargetDummy::OnHealthChanged);

}

void ARogueTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARogueTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARogueTargetDummy::OnHealthChanged(AActor* InstigatorActor, URogueAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}
