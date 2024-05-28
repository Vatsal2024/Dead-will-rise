// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avator.generated.h"

UCLASS()
class CRYPTRAIDER_API AAvator : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvator();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
		float MaxHealth = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentHealth=100;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		UAnimSequence* MyAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		UAnimMontage* ShootAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
		float AmmoCount = 99;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
		float PlayerDamage = 10;

	void DestroyActor();
	int32 onceChecker = 1;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void NoAmmo();
	bool needtochange = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float axisvalue);
	void MoveRight(float axisvalue);
	void Jump1();
	void LookRight(float axisvalue);
	UFUNCTION(BlueprintCallable)
	void SetIsAttacking() { IsAttacking = false; };
	void Shoot();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsAttacking;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsDead=false;

	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<class Agun> GunClass;

	Agun* gun;

	UFUNCTION(BlueprintImplementableEvent)
		void HealthUpdated(float health);

	UFUNCTION(BlueprintImplementableEvent)
		void ActorDied();
	
	UFUNCTION(BlueprintImplementableEvent)
		void ShootTrigger();

	UFUNCTION(BlueprintImplementableEvent)
		void AmmoAdded(float Ammo);

	UFUNCTION(BlueprintImplementableEvent)
		void AmmoZero(bool AmmoLeft);

	UFUNCTION(BlueprintCallable)
		void AddHealth();

	UFUNCTION(BlueprintCallable)
		void AddAmmo();
	
	UFUNCTION(BlueprintCallable)
	bool PlayerChecker();

	UPROPERTY(EditAnywhere)
		USoundBase* Fire;
};
