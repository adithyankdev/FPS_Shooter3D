// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayer.h"
#include "Player/FPSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AFPSPlayer::AFPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	FPSController = Cast<AFPSPlayerController>(GetController());
	
}

// Called every frame
void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Movement Logic 
void AFPSPlayer::MoveFunction(const FInputActionValue& InputValue)
{
	FVector2D MovementValue = InputValue.Get<FVector2D>();

	FRotator CtrlRotation = FPSController->GetControlRotation();                   //Implementation Needs To Change on a  Separate class
	FRotator YawRotation = FRotator(0, CtrlRotation.Yaw, 0);

	FVector XDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector YDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(XDirection, MovementValue.X);
	AddMovementInput(YDirection, MovementValue.Y);
}

