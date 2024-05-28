// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	TopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top Mesh"));
	TopMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Point"));
	ProjectileSpawnPoint->SetupAttachment(TopMesh);
}

void ABasePawn::RotateTop(FVector LookAtTarget)
{
	FVector Target = LookAtTarget - TopMesh->GetComponentLocation();
	FRotator RotateBy = FRotator(0.f, Target.Rotation().Yaw, 0.f);
	TopMesh->SetWorldRotation(FMath::RInterpTo(TopMesh->GetComponentRotation(), RotateBy, UGameplayStatics::GetWorldDeltaSeconds(this), 25.f));


}

void ABasePawn::HandleDestruction() {
	//ToDo Add Destroy Animation and sound effects
	UGameplayStatics::SpawnEmitterAtLocation(this, Blast, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, Death, GetActorLocation());
}

void ABasePawn::Fire()
{
	//DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 20.f, 10, FColor::Red,true,3.f);
	auto projectile=GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	projectile->SetOwner(this);
}





// Called to bind functionality to input

