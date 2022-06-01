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

	FString ActorName = GetName();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *ActorName);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{

	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + (MoveDirection * MaxMoveDistance);
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;

	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = (PlatformVelocity * DeltaTime) + CurrentLocation;
		SetActorLocation(NewLocation);
	}
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MaxMoveDistance;
}

double AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Distance(StartLocation, GetActorLocation());
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = (RotationVelocity * DeltaTime) + CurrentRotation;
	SetActorRotation(NewRotation);
}

