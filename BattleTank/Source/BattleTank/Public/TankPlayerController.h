// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

// Responsible for helping the player aim

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ScreenAimingPosition")
		float AimX = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ScreenAimingPosition")
		float AimY = 0.333f;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponint(UTankAimingComponent* AimCompRef);

private:

	// Start the tank moving the barrel so that a shot would hit where
	// the cross hair intersects the world
	void AimTowardsCrosshair();

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

	UFUNCTION()
	void OnPossedTankDeath();

	virtual void SetPawn(APawn* InPawn) override;

};
