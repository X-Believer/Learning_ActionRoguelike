// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

class URogueAttributeComponent;
class URogueInteractionComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARogueCharacter();
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere)
	URogueInteractionComponent* InteractionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URogueAttributeComponent* AttributeComp;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<AActor> ProjectileClass;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	UAnimMontage* AttackAnim;
	
	FTimerHandle FTimerHandle_PrimaryAttack;
	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	
	void PrimaryAttack();
	void PrimaryInteract();
	
	void PrimaryAttack_TimeElapsed();
	

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
