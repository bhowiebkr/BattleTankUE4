// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


class AProjectile;


// Enum for the aiming states
UENUM()
enum class EFireingState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
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

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void Fire();

	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = "Fire")
	int GetRoundsLeft() const;

	EFireingState GetFiringState() const;


protected:

	// The current state of firing based on the enum state
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFireingState FiringState = EFireingState::Reloading;

private:
	UTankAimingComponent();

	void MoveBarrelTowards(FVector AimDirection)const;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	FVector AimDirection;

	int RoundsLeft = 3;
};
