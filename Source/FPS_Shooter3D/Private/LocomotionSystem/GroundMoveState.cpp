// Fill out your copyright notice in the Description page of Project Settings.


#include "LocomotionSystem/GroundMoveState.h"
#include "Kismet/KismetSystemLibrary.h"

GroundMoveState::GroundMoveState()
{
}

GroundMoveState::~GroundMoveState()
{
	PlayerInterface = nullptr;
}

void GroundMoveState::EnterState(ACharacter* Player, TVariant<FVector2D, bool>&InputValue)
{
	if (PlayerController)
	{
		FVector2D AxisValue = InputValue.Get<FVector2D>();

		Player->AddMovementInput(Player->GetActorForwardVector(),AxisValue.X);
		Player->AddMovementInput(Player->GetActorRightVector(), AxisValue.Y);
		PPrintString("MovementValue");
	}
}

void GroundMoveState::CacheInterface(ACharacter* Player,UWorld* World)
{
	if (IPlayerInterface* Interface = Cast <IPlayerInterface>(Player))
	{
		PlayerInterface.SetObject(Player);
		PlayerInterface.SetInterface(Interface);
		
		PlayerController =  PlayerInterface->GetPlayerController();
	}
	GetWorld = World;
}

void GroundMoveState::PPrintString(FString Str)
{
	UKismetSystemLibrary::PrintString(GetWorld, Str);
}
