// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr; 

	// Find attached Physics Handle
	void FindPhysicsHandleComponent();

	// Setup (assumed) input comonent
	void SetupInputComponent();

	// Return hit for first physics component
	const FHitResult GetFirstPhysicsBodyInReach();

	// Ray-cast and grab what's in reach
	void Grab();
	void Drop();

	UPROPERTY(EditAnywhere)
		float Reach = 80.f;

	// getters

	UPhysicsHandleComponent* getPhisicsHendler();

	// Return current end of reach line
	FVector getReachLineEnd();

	FVector getReachLineStart();

};
