// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;

	Turret->GetName();

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) const
{
	// Work out difference between current barrel rotation, and aim direction
	// move the barrel the right amount this frame
	// given a max elevation speed, and the frame time

	// rotate the turret into position over time
	// rotate the barrel into position over time

	if (!ensure(Barrel) || !ensure(Turret)) { return; }


	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->ElevateBarrel(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
	else
	{
		Turret->RotateTurret(-DeltaRotator.Yaw);
	}
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFireingState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFireingState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFireingState::Aiming;
	}
	else
	{
		FiringState = EFireingState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.05);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		UE_LOG(LogTemp, Warning, TEXT("missing barrel or turret"));

		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHanveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHanveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(OutLaunchVelocity);
		FString TankName = GetOwner()->GetName();
	}
}


void UTankAimingComponent::Fire()
{
	if (FiringState == EFireingState::Locked || FiringState == EFireingState::Aiming)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		// Spawn a projectile at the socket location on the barrel
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

void UTankAimingComponent::BeginPlay()
{
	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

EFireingState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}
