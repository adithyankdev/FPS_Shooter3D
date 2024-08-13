// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/PlayerInterface.h"
#include "Interfaces/PlayerAnimeInterface.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Player/LocomotionSystem/AbstractState.h"
#include "FPSPlayer.generated.h"

class AFPSPlayerController;
class UPlayerAnimInstance;

UCLASS()
class FPS_SHOOTER3D_API AFPSPlayer : public ACharacter , public IPlayerInterface
{
	GENERATED_BODY()

public:

	//Interface Function
	APlayerController* GetPlayerController() override;

	AFPSPlayer();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UCameraComponent* FPSCamera;

	UPROPERTY()
	TScriptInterface<IPlayerAnimeInterface>AnimInstanceInterface;

private:

	//Referance For The Custom Controller
	AFPSPlayerController* FPSController;

	//For Storing Differnt LocomotionStates
	TMap<StateEnum, AbstractState*>StateLibrary;

	//Variable For Passing In LocomotionStates
	TVariant<FVector2D, bool>MovementValue;

protected:

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	//Function To Contain Movement Logic
	void MoveFunction(const FInputActionValue& InputValue);
	void LookFunction(const FInputActionValue& InputValue);
	void CrouchToggleFunction();

	//Variable for Implementing The Toggle Functionality -- FlipFlop In The Blueprint
	bool CrouchToggleValue;



};
