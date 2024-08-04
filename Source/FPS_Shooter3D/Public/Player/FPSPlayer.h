// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FPSPlayer.generated.h"

class AFPSPlayerController;

UCLASS()
class FPS_SHOOTER3D_API AFPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:

	AFPSPlayer();

private:

	AFPSPlayerController* FPSController;

protected:

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	//Function To Contain Movement Logic
	void MoveFunction(const FInputActionValue& InputValue);

};
