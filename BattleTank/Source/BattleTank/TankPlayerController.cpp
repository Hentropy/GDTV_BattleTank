// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
//#include "GameFramework/Actor.h"

void ATankPlayerController::BeginPlay() {
        Super::BeginPlay();

        auto ControlledTank = GetControlledTank();
        if (!ControlledTank) {
            UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank."))
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(ControlledTank->GetName()))
        }
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) { return; }

	//linetrace through crosshair
	//if linetrace hits something, aim tank turret at that point
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		ControlledTank->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);

	FVector _Location, LookDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, _Location, LookDirection)) {
		FHitResult HitResult;
		FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
		FVector EndLocation = CameraLocation + LineTraceRange * LookDirection;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndLocation, ECC_Visibility)) {
			OutHitLocation = HitResult.Location;
			return true;
		}
	}

	return false;
}
