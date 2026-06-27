// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAttributeComponent.h"

URogueAttributeComponent::URogueAttributeComponent()
{
	Health = 100.0f;
}

bool URogueAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	
	return true;
}

