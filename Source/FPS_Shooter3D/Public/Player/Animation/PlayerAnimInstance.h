// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/PlayerAnimeInterface.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_SHOOTER3D_API UPlayerAnimInstance : public UAnimInstance , public IPlayerAnimeInterface
{
	GENERATED_BODY()

public:

	void ChangeLocomotionState(ELocomotionState NewState) override;

protected:

	//Caching The chracter Interface
	UPROPERTY(BlueprintReadOnly)
	class ACharacter* OwnerCharacter;

	//Variable For Storing The Speed For Character
	UPROPERTY(BlueprintReadOnly)
	float Speed;

	//Variable For Storing The Current Direction Of The  Character
	UPROPERTY(BlueprintReadOnly)
	float Direction;;

	//Varibale For Storing The Pitch Rotation 
	UPROPERTY(BlueprintReadOnly)
	float PitchRotation;

	UPROPERTY(BlueprintReadOnly)
	FVector CharacterVelocity;

	UPROPERTY(BlueprintReadOnly)
	bool Falling;

	//Variable For Storing The Current Locomotion State
	UPROPERTY(BlueprintReadOnly)
	ELocomotionState CurrentState;

public:

	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaTime) override;
	
};
