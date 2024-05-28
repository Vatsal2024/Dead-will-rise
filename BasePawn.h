// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned

	void RotateTop(FVector LookAtTarget);
	void Fire();

	void HandleDestruction();
	

public:
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TopMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	UParticleSystem* Blast;

	UPROPERTY(EditAnywhere)
		USoundBase* Death;

};
