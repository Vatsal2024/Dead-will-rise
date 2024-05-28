// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FireBall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fire Ball"));
	RootComponent=FireBall;
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->MaxSpeed = 1300.f;
	MovementComponent->InitialSpeed = 1300.f;

	FireTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Component"));
	FireTrail->SetupAttachment(RootComponent);
	//UE_LOG(LogTemp, Display, TEXT("Projectile is working"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	FireBall->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	UGameplayStatics::PlaySoundAtLocation(this, Fire, GetActorLocation());
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Display, TEXT("Other Actor is : %s"), *OtherActor->GetName());
	AActor* owner = GetOwner();
	//UE_LOG(LogTemp, Warning, TEXT("Owner is : %s"), *this->GetName());
	if (owner == nullptr) { 
		Destroy();
		return; 
	}
	auto InstigatorController = owner->GetInstigatorController();

	auto Damagetype = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != owner) {
		//UE_LOG(LogTemp, Display, TEXT("Other Actor is : %s"), *OtherActor->GetName());
		UGameplayStatics::ApplyDamage(OtherActor, Damage, InstigatorController,this, Damagetype);
		UGameplayStatics::SpawnEmitterAtLocation(this, fireanime, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(this, HitObject, GetActorLocation());
		
		
	}
	Destroy();
	

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

