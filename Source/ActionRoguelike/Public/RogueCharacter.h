// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

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
	
	void MoveForward(float AxisValue);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
