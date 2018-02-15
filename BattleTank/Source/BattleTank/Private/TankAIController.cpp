// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	// Get the player tank and exit if we can't find it
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	ATank* AITank = Cast<ATank>(GetPawn());
	AITank->AimAt(PlayerTank->GetActorLocation());

	if (PlayerTank && isReloaded)
	{
		// Move towards the player
		MoveToActor(
			PlayerTank,
			AcceptanceRadius
			);

		AITank->Fire();
		LastFireTime = FPlatformTime::Seconds();
	}
}
