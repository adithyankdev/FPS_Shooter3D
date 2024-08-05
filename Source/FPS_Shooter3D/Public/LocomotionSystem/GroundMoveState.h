// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerInterface.h"
#include "Player/LocomotionSystem/AbstractState.h"

class APlayerController;

/**
 * 
 */
class FPS_SHOOTER3D_API GroundMoveState : public AbstractState
{
public:
	GroundMoveState();
	~GroundMoveState();

	//Interface Function for Trigger Movement
	void EnterState(ACharacter* Player, TVariant<FVector2D, bool>&InputValue) override;
	//Interface Function For Caching Variables
	void CacheInterface(ACharacter* Player,UWorld* World) override;

private:

	//Caching PlayerInterface And Controller
	TScriptInterface<IPlayerInterface>PlayerInterface;
	APlayerController* PlayerController;

	//For Avoid Repeated Declaration Of Variable In The EnterState Function
	FVector2D AxisValue;


};
