// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Tank controlled by TankPlayerController"));
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing %s"), *(ControlledTank->GetName()));
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController ticking"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutAimLocation;

	if (GetAimRayHitLocation(OutAimLocation))
	{
		GetControlledTank()->AimAt(OutAimLocation);
	}
	// Aim barrel towards point in world where crosshair trace intersects.
}

bool ATankPlayerController::GetAimRayHitLocation(FVector& OutAimLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto CrosshairScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector StartLocation;
	FHitResult HitResult;
	if (DeprojectScreenPositionToWorld(CrosshairScreenLocation.X, CrosshairScreenLocation.Y, StartLocation, OutAimLocation))
	{
		if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			OutAimLocation * TraceRange,
			ECollisionChannel::ECC_Visibility))
		{
			OutAimLocation = HitResult.Location;
			return true;
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("AI Tank Aim Location: %s"), *OutAimLocation.ToString());
	OutAimLocation = FVector(0);
	return false;
}