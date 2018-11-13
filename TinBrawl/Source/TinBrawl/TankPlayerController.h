// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // MUST be the last include

/**
 * 
 */
UCLASS()
class TINBRAWL_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();
	// Return an OUT parameter, true if hit landscape
	bool GetAimRayHitLocation(FVector& OutAimLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333f;
	UPROPERTY(EditAnywhere)
	float TraceRange = 1000000.0f;

};
