// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	

private:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float ReloadTimeInSeconds = 3.f;
	double LastFireTime = 0.f;

	// How close can the AI tank get to the player
	float AcceptanceRadius = 3000;



};
