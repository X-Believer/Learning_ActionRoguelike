// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ARogueCharacter::ARogueCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARogueCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARogueCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &ARogueCharacter::AddControllerYawInput);
}

