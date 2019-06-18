// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Pool the triggerVolume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) { 
		OnOpen.Broadcast();
	} else {
		OnClose.Broadcast();
	}
	// If the ActorThatOpen in the Volume				
	
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate) {
		return TotalMass;
	}

	// Find all owerlapping actors
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto* Actor : OverlappingActors) {
		// TotalMass += Actor->
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(Actor->GetName()));
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		// Ite
	}
		UE_LOG(LogTemp, Warning, TEXT("%f"), TotalMass);
	return TotalMass;
	
}

