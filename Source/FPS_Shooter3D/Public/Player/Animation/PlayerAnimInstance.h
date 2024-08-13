// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_SHOOTER3D_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	float Direction;;

	UPROPERTY(BlueprintReadOnly)
	float PitchRotation;

public:

	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaTime) override;
	
};
