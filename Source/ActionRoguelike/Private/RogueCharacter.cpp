// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueCharacter.h"

#include "RogueInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ARogueCharacter::ARogueCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	
	InteractionComp = CreateDefaultSubobject<URogueInteractionComponent>(TEXT("InteractionComp"));
}

void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARogueCharacter::MoveForward(float AxisValue)
{
	FRotator Rotation = GetControlRotation();
	Rotation.Pitch = 0.f;
	Rotation.Roll = 0.f;
	AddMovementInput(Rotation.Vector(), AxisValue);
}

void ARogueCharacter::MoveRight(float AxisValue)
{
	FRotator Rotation = GetControlRotation();
	Rotation.Pitch = 0.f;
	Rotation.Roll = 0.f;
	FVector RightVector = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightVector, AxisValue);
}

void ARogueCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(
		FTimerHandle_PrimaryAttack,
		this,
		&ARogueCharacter::PrimaryAttack_TimeElapsed,
		0.2f,
		false
	);
	
	// GetWorldTimerManager().ClearTimer(FTimerHandle_PrimaryAttack);
}

void ARogueCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ARogueCharacter::PrimaryAttack_TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	FTransform SpawnTransform = FTransform(GetControlRotation(), HandLocation);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
}

void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARogueCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARogueCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ARogueCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ARogueCharacter::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ARogueCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ARogueCharacter::PrimaryInteract);
}

