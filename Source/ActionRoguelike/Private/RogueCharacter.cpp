// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueCharacter.h"

#include "RogueAttributeComponent.h"
#include "RogueInteractionComponent.h"
#include "RogueProjectileBase.h"
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
	
	AttributeComp = CreateDefaultSubobject<URogueAttributeComponent>(TEXT("AttributeComp"));
}

void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARogueCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	AttributeComp->OnHealthChanged.AddDynamic(this, &ARogueCharacter::OnHealthChanged);
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
	PlayerInputComponent->BindAction("BlackHoleAttack", IE_Pressed, this, &ARogueCharacter::BlackHoleAttack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ARogueCharacter::Dash);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ARogueCharacter::PrimaryInteract);
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
		PrimaryAttackTimer,
		this,
		&ARogueCharacter::PrimaryAttack_TimeElapsed,
		0.2f,
		false
	);
}

void ARogueCharacter::SpawnProjectile(TSubclassOf<ARogueProjectileBase> ClassToSpawn)
{
	if (ensure(ClassToSpawn))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		
		FCollisionShape Shape;
		Shape.SetSphere(20.f);
		
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
		
		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = TraceStart + (GetControlRotation().Vector() * 5000.f);
		
		FHitResult Hit;
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, Shape, QueryParams))
		{
			TraceEnd = Hit.ImpactPoint;
		}
		
		FRotator ProjectileRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		
		FTransform SpawnTransform = FTransform(ProjectileRotation, HandLocation);
		
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTransform, SpawnParams);
	}
}

void ARogueCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(NormalProjectileClass);
}

void ARogueCharacter::BlackHoleAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(BlackHoleAttackTimer, this, &ARogueCharacter::BlackHoleAttack_TimeElapsed, AttackAnimDelay);
}

void ARogueCharacter::BlackHoleAttack_TimeElapsed()
{
	SpawnProjectile(BlackHoleProjectileClass);
}

void ARogueCharacter::Dash()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(DashTimer, this, &ARogueCharacter::Dash_TimeElapsed, AttackAnimDelay);
}

void ARogueCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}

void ARogueCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ARogueCharacter::OnHealthChanged(AActor* InstigatorActor, URogueAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

