// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
        Super::BeginPlay();

        ATank* ControlledTank = GetControlledTank();
        if (!ControlledTank) {
            UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank."))
        }

        ATank* PlayerTank = GetPlayerTank();
        if (!PlayerTank) {
            UE_LOG(LogTemp, Warning, TEXT("AIController could not get player tank."))
        }
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();
	if (!ControlledTank || !PlayerTank) { return; }
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
