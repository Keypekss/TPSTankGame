// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If the PlayerPawn reference isn't valid or it's out of range, return. 
	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}
	// If we have a PlayerPawn in range then rotate the turret to follow. 
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	// If Player == null || is Dead THEN BAIL!!
	if (!PlayerPawn || !PlayerPawn->GetPlayerAlive()) {
		return;
	}

	// IF Player IS in range THEN FIRE!! 
	if (ReturnDistanceToPlayer() <= FireRange) {
		Fire();
	}	
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn) {
		return 0.0f;
	}

	return ((PlayerPawn->GetActorLocation() - GetActorLocation()).Size());
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

