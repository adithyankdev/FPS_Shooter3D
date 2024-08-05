// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/LocomotionSystem/AbstractState.h"
#include "Interfaces/PlayerInterface.h"



/**
 * 
 */
class FPS_SHOOTER3D_API LookState : public AbstractState
{
public:
	LookState();
	~LookState();

	 void EnterState(ACharacter* Player, TVariant<FVector2D, bool>& InputValue)override;
	 void CacheInterface(ACharacter* Player, UWorld* World) override;

	 //Caching PlayerInterface And Controller
	 TScriptInterface<IPlayerInterface>PlayerInterface;
	 APlayerController* PlayerController;

	 //For Avoid Repeated Declaration Of Variable In The EnterState Function
	 FVector2D AxisValue;
};
