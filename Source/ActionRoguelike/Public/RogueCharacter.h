// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

class ARogueProjectileBase;
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
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	
	void SpawnProjectile(TSubclassOf<ARogueProjectileBase> ProjectileClass);
	
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	
	void BlackHoleAttack();
	void BlackHoleAttack_TimeElapsed();
	
	void Dash();
	void Dash_TimeElapsed();
	
	void PrimaryInteract();
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, URogueAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere)
	URogueInteractionComponent* InteractionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URogueAttributeComponent* AttributeComp;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<ARogueProjectileBase> NormalProjectileClass;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<ARogueProjectileBase> BlackHoleProjectileClass;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<ARogueProjectileBase> DashProjectileClass;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	UAnimMontage* AttackAnim;
	
	FTimerHandle PrimaryAttackTimer;
	FTimerHandle BlackHoleAttackTimer;
	FTimerHandle DashTimer;
	float AttackAnimDelay = 0.2f;
	
};
