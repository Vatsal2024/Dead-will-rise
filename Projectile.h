// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class CRYPTRAIDER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FireBall;

	UPROPERTY(VisibleAnywhere);
	UParticleSystemComponent* FireTrail;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere)
		float Damage = 25.f;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	UParticleSystem* fireanime;

	UPROPERTY(EditAnywhere)
		USoundBase* Fire;
	
	UPROPERTY(EditAnywhere)
		USoundBase* HitObject;

};
