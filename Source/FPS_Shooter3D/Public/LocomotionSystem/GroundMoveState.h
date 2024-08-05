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

	void EnterState(ACharacter* Player, TVariant<FVector2D, bool>&InputValue) override;
	void CacheInterface(ACharacter* Player,UWorld* World) override;

private:

	TScriptInterface<IPlayerInterface>PlayerInterface;
    
	APlayerController* PlayerController;

	void PPrintString(FString Str);

	UWorld* GetWorld;

};
