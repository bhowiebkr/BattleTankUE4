// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	// Returns health as a percentage between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

private:
	ATank();

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	int32 StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Initialized in begin play
};
