// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h" // So we can implement OnDeath
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get the player tank and exit if we can't find it
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFireingState::Locked)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::OnPossedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}
