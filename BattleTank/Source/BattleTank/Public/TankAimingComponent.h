// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// Enum for the aiming states
UENUM()
enum class EFireingState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;


// Holds barrel properties
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Initialize the with the barrel and the turret
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	
	// Aim at the hit location use launch speed for velocity
	void AimAt(FVector HitLocation);


protected:

	// The current state of firing based on the enum state
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFireingState FiringState = EFireingState::Locked;

private:
	// Constructor
	UTankAimingComponent();

	// hold the barrel and turret
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;


	// TODO remove when firing is moved to the aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000.f;

	// Move the barrel towards a vector
	void MoveBarrelTowards(FVector AimDirection)const;
};
