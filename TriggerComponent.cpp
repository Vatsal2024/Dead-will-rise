// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent(){
	PrimaryComponentTick.bCanEverTick = true;
    // UE_LOG(LogTemp, Error, TEXT("cONSTRUCTOR"));
}


void UTriggerComponent:: BeginPlay(){
    Super::BeginPlay();
    // UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* Actor=GetAcceptableActor();
    if(Actor==nullptr){
        // UE_LOG(LogTemp, Display, TEXT("Realocating"));
        Mover->ShouldMove=false;
    }
    else{
        // FString ActorName = Actor->GetActorNameOrLabel();
        // UE_LOG(LogTemp, Display, TEXT("Allocating"));
        // Cast is used to check whether the Root Component is Primitive if not it will have null ptr
        UPrimitiveComponent* RootComponent=Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if(RootComponent!=nullptr){
            RootComponent->SetSimulatePhysics(false);
        }
        Actor->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform);
        Mover->ShouldMove=true;
        
        
    }

}


void UTriggerComponent::SetTriggerMover(UMover* NewMover){
    Mover=NewMover;

}

AActor* UTriggerComponent::GetAcceptableActor(){
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    
    for (AActor* Actor: Actors){
        if(Actor->ActorHasTag(TriggerByTag) && !(Actor->ActorHasTag("Grabbed"))){
            // FString ActorName = Actor->GetActorNameOrLabel();
            // UE_LOG(LogTemp, Display, TEXT("Actors are : %s"),*ActorName);
            return Actor;
        }
    }
    return nullptr;
}