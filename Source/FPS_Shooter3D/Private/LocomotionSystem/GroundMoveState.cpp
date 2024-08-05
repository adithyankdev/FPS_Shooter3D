// Fill out your copyright notice in the Description page of Project Settings.


#include "LocomotionSystem/GroundMoveState.h"
#include "Kismet/KismetSystemLibrary.h"

GroundMoveState::GroundMoveState()
{
}

GroundMoveState::~GroundMoveState()
{
	//Avoid Memory Leak
	PlayerInterface = nullptr;
	PlayerController = nullptr;
}

void GroundMoveState::EnterState(ACharacter* Player, TVariant<FVector2D, bool>&InputValue)
{
	if (PlayerController)
	{
	    AxisValue = InputValue.Get<FVector2D>();
		Player->AddMovementInput(Player->GetActorForwardVector(),AxisValue.X);
		Player->AddMovementInput(Player->GetActorRightVector(), AxisValue.Y);
	}
}

void GroundMoveState::CacheInterface(ACharacter* Player,UWorld* World)
{
	if (IPlayerInterface* Interface = Cast <IPlayerInterface>(Player))
	{
		//Setting Value Into The Interfaces
		PlayerInterface.SetObject(Player);
		PlayerInterface.SetInterface(Interface);
		
		PlayerController =  PlayerInterface->GetPlayerController();
	}
	
}
