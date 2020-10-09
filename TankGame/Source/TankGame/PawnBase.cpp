// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h" 
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	// Find Rotation value to look at. 
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z));

	// Rotate Turret.
	TurretMesh->SetWorldRotation(TurretRotation);

}

void APawnBase::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE!!"));
}

void APawnBase::HandleDestruction()
{

}