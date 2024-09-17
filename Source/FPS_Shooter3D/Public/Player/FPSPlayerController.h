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

	//InputAction For Ground Movement --WSAD
	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;

	//InputAction For Look Movement --MouseXY
	UPROPERTY(EditDefaultsOnly)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* SprintAction;

	//InputAction For Crouch Movement - C
	UPROPERTY(EditDefaultsOnly)
	UInputAction* CrouchToggleAction;

	//InputAction For Jump Movment - SpaceBar
	UPROPERTY(EditDefaultsOnly)
	UInputAction* JumpAction;

	//InputAction For Firing Gun - LeftMouseButton
	UPROPERTY(EditDefaultsOnly)
	UInputAction* FireGunAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* ReloadGunAction;

	void BeginPlay() override;

};
