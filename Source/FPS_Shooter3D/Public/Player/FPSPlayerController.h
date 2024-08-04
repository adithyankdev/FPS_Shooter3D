// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "FPSPlayerController.generated.h"

class AFPSPlayer;

/**
 * 
 */
UCLASS()
class FPS_SHOOTER3D_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

private: 

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;
	
	void BeginPlay() override;

};
