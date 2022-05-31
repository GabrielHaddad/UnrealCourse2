// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = (PlatformVelocity * DeltaTime) + CurrentLocation;
	SetActorLocation(NewLocation);

	double DistanceFromStart = FVector::Distance(StartLocation, NewLocation);
	DistanceMoved = DistanceFromStart;

	if (DistanceFromStart > MaxMoveDistance)
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + (MoveDirection * MaxMoveDistance);
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;

	}
}

