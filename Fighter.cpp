// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter.h"
#include "tank.h"
#include "Avator.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"



AFighter::AFighter(){ 
	PrimaryActorTick.bCanEverTick = true;
}

void AFighter::BeginPlay() {
	Super::BeginPlay();
	Tank = Cast<Atank>(UGameplayStatics::GetPlayerPawn(this, 0));
	Avator= Cast<AAvator>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AFighter::CheckFireCondition, FireRate, true);
	//if (Belica) {
		//TArray<AActor*> FoundActors;
		//UGameplayStatics::GetAllActorsOfClass(this, Belica, FoundActors);
		//BelicaActor = FoundActors[0];
	//}

}

void AFighter::CheckFireCondition()
{
	if (FireInRange()) {
		Fire();
	}
	
}

void AFighter::HandleDestruction() {
	Super::HandleDestruction();
	Destroy();
}


// Called every frame
void AFighter::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	if (FireInRange()) {
		//UE_LOG(LogTemp, Display, TEXT("Actor location is : %s"), Avator->GetActorLocation().ToString());
		RotateTop(Avator->GetActorLocation());
		
	}
	//UE_LOG(LogTemp, Warning, TEXT("Distance is : %f"), Distance);
	//RotateTop(TopMesh)
}


bool AFighter::FireInRange(){
	
	float Dist = FVector::Dist(GetActorLocation(), Avator->GetActorLocation());
	if (Dist < Distance) {
		return true;
	}
	
	return false;
	
}