// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Player/FPSPlayer.h"
#include "EnhancedInputSubsystems.h"

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			//Setting Up The Mapping Context
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
	

	if (UEnhancedInputComponent* EnhancedInput = Cast <UEnhancedInputComponent>(this->InputComponent))
	{
	    if (AFPSPlayer* FPSPlayer = Cast<AFPSPlayer>(GetPawn()))
		{
			//Binding InputAction And The Correspoding Functions
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, FPSPlayer, &AFPSPlayer::MoveFunction);
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, FPSPlayer, &AFPSPlayer::LookFunction);
			EnhancedInput->BindAction(CrouchToggleAction, ETriggerEvent::Completed, FPSPlayer, &AFPSPlayer::CrouchToggleFunction);

			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, FPSPlayer,&AFPSPlayer::Jump);
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, FPSPlayer, &AFPSPlayer::StopJumping);

			EnhancedInput->BindAction(FireGunAction, ETriggerEvent::Started, FPSPlayer, &AFPSPlayer::WeaponFireStartFunction);
			EnhancedInput->BindAction(FireGunAction, ETriggerEvent::Completed, FPSPlayer, &AFPSPlayer::WeaponFireStopFunction);
		}
	}

}
