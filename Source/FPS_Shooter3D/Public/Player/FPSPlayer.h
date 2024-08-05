// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerInterface.h"
#include "InputActionValue.h"
#include "Player/LocomotionSystem/AbstractState.h"
#include "FPSPlayer.generated.h"

class AFPSPlayerController;

UCLASS()
class FPS_SHOOTER3D_API AFPSPlayer : public ACharacter , public IPlayerInterface
{
	GENERATED_BODY()

public:

	APlayerController* GetPlayerController() override;

	AFPSPlayer();

private:

	AFPSPlayerController* FPSController;

	TMap<StateEnum, AbstractState*>StateLibrary;

	TVariant<FVector2D, bool>MovementValue;

protected:

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	//Function To Contain Movement Logic
	void MoveFunction(const FInputActionValue& InputValue);

};
