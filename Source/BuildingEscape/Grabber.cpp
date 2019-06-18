// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	FindPhysicsHandleComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



	if (!PhysicsHandle) {
		return;
	}
	if (PhysicsHandle->GrabbedComponent) {

		PhysicsHandle->SetTargetLocation(getReachLineEnd());
	}

}

FVector UGrabber::getReachLineEnd() {
	FVector PlayerViewportLocation;
	FRotator PlayerViewportRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewportLocation,
		OUT PlayerViewportRotation
	);

	return PlayerViewportLocation + PlayerViewportRotation.Vector() * Reach;
}

FVector UGrabber::getReachLineStart() {
	FVector PlayerViewportLocation;
	FRotator PlayerViewportRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewportLocation,
		OUT PlayerViewportRotation
	);

	return PlayerViewportLocation;
}

UPhysicsHandleComponent* UGrabber::getPhisicsHendler()
{
	return  GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = getPhisicsHendler();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Phisics Handle on %s is missing!"), *(GetOwner()->GetName()));
	}

}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Input Component on %s reporting for duty!"), *(GetOwner()->GetName()));
		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Drop);
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grub!"));

	// Truy and reach any actors with physics body collisin channel set
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit) {
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true // allow rotation
		);
	}

}

void UGrabber::Drop() {
	PhysicsHandle->ReleaseComponent();
}


const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get player view point per tick
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;

	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		getReachLineStart(),
		getReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = HitResult.GetActor();
	// See what we hit
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("I see  %s"), *(ActorHit->GetName()));
	}

	return HitResult;
}
