// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class ACharacter;

enum class StateEnum
{
	Walking,
	Jumping,
	Crouching,
};


/**
 * 
 */
class FPS_SHOOTER3D_API AbstractState
{
public:
	AbstractState();
	virtual ~AbstractState();

	virtual void EnterState(ACharacter* Player,TVariant<FVector2D,bool>&InputValue)=0;
	virtual void CacheInterface(ACharacter* Player,UWorld* World)=0;
};
