// Fill out your copyright notice in the Description page of Project Settings.


#include "tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

Atank::Atank() {
	PrimaryActorTick.bCanEverTick = true;
	Belica = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Belica"));
	Belica->SetupAttachment(BaseMesh);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void Atank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());

}


// Called every frame
void Atank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PlayerControllerRef) {
		FHitResult HitResult;
		HasHit = PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		//if (HasHit) {
			//RotateTop(HitResult.ImpactPoint);
			//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 50.f, 12, FColor::Red, false);

		//}
	}
}

void Atank::HandleDestruction() {
	Super::HandleDestruction();
	UE_LOG(LogTemp, Display, TEXT("Handle Destruction is Working"));
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}



void Atank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &Atank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &Atank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &Atank::Fire);

}

void Atank::Move(float Value) {
	//UE_LOG(LogTemp, Display, TEXT("Value :: %f"),Value);
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector DeltaDistance=FVector::ZeroVector;
	DeltaDistance.X = Value*speed*DeltaTime;
	UE_LOG(LogTemp, Display, TEXT("DeltaDistance : %f"), DeltaDistance.X);
	AddActorLocalOffset(DeltaDistance, true);
}

void Atank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaRotation.Yaw = Value * turnrate * DeltaTime;
	AddActorLocalRotation(DeltaRotation);
}
