// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "tank.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API Atank : public ABasePawn
{
	GENERATED_BODY()
	


public:
	Atank();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move(float Value);
	void Turn(float Value);

	UPROPERTY(EditAnywhere, Category="Movements")
		float speed=50;

	UPROPERTY(EditAnywhere, Category = "Movements")
		float turnrate = 50;

	bool HasHit;

	void HandleDestruction();

	APlayerController* GetPlayerController() const { return PlayerControllerRef; }

private:
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* Belica;

	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

	APlayerController* PlayerControllerRef;

protected:
	// Called when the game starts or when spawned

};