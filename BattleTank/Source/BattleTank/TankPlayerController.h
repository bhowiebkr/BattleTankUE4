// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

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

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
