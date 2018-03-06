// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), hideCategories=("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max up movement
	void ElevateBarrel(float RelativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float MaxDegreesPerSecond = 10;
	
	UPROPERTY(EditDefaultsOnly, Category ="Setup")
	float MaxElevationDegrees = 20;

	UPROPERTY(EditDefaultsOnly, Category ="Setup")
	float MinElevationDegrees = 0;
};
