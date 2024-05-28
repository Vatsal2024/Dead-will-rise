// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gun.generated.h"

UCLASS()
class CRYPTRAIDER_API Agun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Agun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleFlash;
	
	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleAtHit;
	UPROPERTY(EditAnywhere)
		float MaxRange = 50000.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DamageAmmount=10;
};
