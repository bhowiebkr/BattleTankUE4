// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScreenAimingPosition)
		float AimX = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScreenAimingPosition)
		float AimY = 0.333f;

private:
	ATank* GetControlledTank() const;

	// Start the tank moving the barrel so that a shot would hit where
	// the cross hair intersects the world
	void AimTowardsCrosshair();

	// Return an out parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;


	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

	//bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	//bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
