// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::ElevateBarrel(float DegreesPerSecond)
{
	// Move the barrel the right amount this frame
	// given a max elevation speed, and the frame time

	UE_LOG(LogTemp, Warning, TEXT("Barrel elevate called at speed: %f"), DegreesPerSecond)
}
