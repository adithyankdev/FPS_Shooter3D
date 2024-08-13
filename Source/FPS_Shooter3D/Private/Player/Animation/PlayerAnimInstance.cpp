// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Animation/PlayerAnimInstance.h"
#include "GameFramework/Character.h"

//Assiging The Latest State
void UPlayerAnimInstance::ChangeLocomotionState(ELocomotionState NewState)
{
	CurrentState = NewState;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast <ACharacter>(TryGetPawnOwner());
	//Setting Default State To GroundLocomotion++

	CurrentState = ELocomotionState::GroundLocomotion;
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
			PitchRotation = YawRotation - 360.0f;    //Decrementing The Pitch  , Preventing Unexpected Behaviour (Scope Of 90 to -90)
		}
		else
		{
			PitchRotation = YawRotation;
		}

	}
	

}
