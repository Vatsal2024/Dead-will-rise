// Fill out your copyright notice in the Description page of Project Settings.


#include "Avator.h"
#include "gun.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AAvator::AAvator()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float AAvator::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied=Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth = CurrentHealth - DamageApplied;
	HealthUpdated(CurrentHealth);
	if (CurrentHealth <= 0) {
		if (onceChecker == 1) {
			GetMesh()->PlayAnimation(MyAnimation, false);
			if (PlayerChecker()) {
				ActorDied();
			}
			
		}
		onceChecker = 2;
		FTimerHandle TimerHandle;
		float DelayInSeconds = 2.0f; // Change this value to adjust the delay
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AAvator::DestroyActor, DelayInSeconds, false);

	}	
	return DamageApplied;
}

void AAvator::DestroyActor()
{
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Destroy();
}

// Called when the game starts or when spawned
void AAvator::BeginPlay()
{
	Super::BeginPlay();
	gun = GetWorld()->SpawnActor<Agun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon"), EPhysBodyOp::PBO_None);
	gun->DamageAmmount = PlayerDamage;
	gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
	gun->SetOwner(this);
	CurrentHealth = MaxHealth;
	
}

void AAvator::NoAmmo()
{
	if (needtochange) {
		if (AmmoCount <= 0) {
			AmmoZero(false);
			needtochange = false;
		}
	}
}

// Called every frame
void AAvator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	NoAmmo();

}

// Called to bind functionality to input
void AAvator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AAvator::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AAvator::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AAvator::LookRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AAvator::Jump1);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AAvator::Shoot);

}

void AAvator::MoveForward(float axisvalue) {
	AddMovementInput(GetActorForwardVector() * axisvalue);
}

void AAvator::MoveRight(float axisvalue)
{
	AddMovementInput(GetActorRightVector() * axisvalue);
}

void AAvator::Jump1()
{
	Jump();
}

void AAvator::LookRight(float axisvalue)
{
	AddControllerYawInput(axisvalue);
}

void AAvator::Shoot()
{
	gun->PullTrigger();
	UGameplayStatics::PlaySoundAtLocation(this, Fire, GetActorLocation());
	//GetMesh()->PlayAnimation(ShootAnimation,false);
	GetMesh()->GetAnimInstance()->Montage_Play(ShootAnimation);
	if (PlayerChecker()) {
		ShootTrigger();
	}

}

void AAvator::AddHealth()
{
	CurrentHealth = CurrentHealth + 20;
	HealthUpdated(CurrentHealth);
}

void AAvator::AddAmmo()
{
	AmmoCount = AmmoCount + 10;
	if (PlayerChecker()) {
		AmmoAdded(AmmoCount);
	}
	
}

bool AAvator::PlayerChecker()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) {
		APawn* ControllerPawn = PlayerController->GetPawn();
		if (ControllerPawn == this) {
			return true;
		}
	}
	return false;
}



