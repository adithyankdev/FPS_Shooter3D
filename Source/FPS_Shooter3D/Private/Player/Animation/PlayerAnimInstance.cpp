// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Animation/PlayerAnimInstance.h"
#include "GameFramework/Character.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast <ACharacter>(TryGetPawnOwner());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (OwnerCharacter)
	{
		FVector CharacterVelocity = OwnerCharacter->GetVelocity();

		Speed = CharacterVelocity.Size();
		Direction = CalculateDirection(CharacterVelocity, OwnerCharacter->GetActorRotation());

		float YawRotation = OwnerCharacter->GetBaseAimRotation().Pitch;
		if (YawRotation >= 180.0f)
		{
			PitchRotation = YawRotation - 360.0f;
		}
		else
		{
			PitchRotation = YawRotation;
		}

	}
	

}
