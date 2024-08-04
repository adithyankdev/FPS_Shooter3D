// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Player/FPSPlayer.h"
#include "EnhancedInputSubsystems.h"

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(PlayerMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInput = Cast <UEnhancedInputComponent>(this->InputComponent))
	{
	    if (AFPSPlayer* FPSPlayer = Cast<AFPSPlayer>(GetPawn()))
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, FPSPlayer, &AFPSPlayer::MoveFunction);
		}
	}

}
