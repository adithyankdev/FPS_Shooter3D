// Fill out your copyright notice in the Description page of Project Settings.


#include "LocomotionSystem/LookState.h"
#include "Player/FPSPlayer.h"


LookState::LookState()
{
}

LookState::~LookState()
{
}

void LookState::EnterState(ACharacter* Player, TVariant<FVector2D, bool>& InputValue)
{
	AxisValue = InputValue.Get<FVector2D>();

	if (PlayerController)
	{
		Player->AddControllerYawInput(AxisValue.X);
		Player->AddControllerPitchInput(AxisValue.Y);
	}
}

void LookState::CacheInterface(ACharacter* Player, UWorld* World)
{
	if (IPlayerInterface* Interface = Cast <IPlayerInterface>(Player))
	{
		//Setting Value Into The Interfaces
		PlayerInterface.SetObject(Player);
		PlayerInterface.SetInterface(Interface);

		PlayerController = PlayerInterface->GetPlayerController();
	}
}
