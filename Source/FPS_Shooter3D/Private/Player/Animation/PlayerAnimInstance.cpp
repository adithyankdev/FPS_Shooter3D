// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Animation/PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"



//Assiging The Latest State
void UPlayerAnimInstance::ChangeLocomotionState(ELocomotionState NewState)
{
	CurrentState = NewState;
}


void UPlayerAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast <ACharacter>(TryGetPawnOwner());
	//Setting Default State To GroundLocomotion++

	if (IPlayerInterface* Interface = Cast<IPlayerInterface>(OwnerCharacter))
	{
		OwnerInterface.SetObject(OwnerCharacter);
		OwnerInterface.SetInterface(Interface);
	}

	CurrentState = ELocomotionState::GroundLocomotion;


}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (OwnerCharacter)
	{
		CharacterVelocity = OwnerCharacter->GetVelocity();

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

		Falling = OwnerCharacter->GetCharacterMovement()->IsFalling();

	}
	

}
