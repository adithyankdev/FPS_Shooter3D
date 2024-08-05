// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayer.h"
#include "Player/FPSPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LocomotionSystem/GroundMoveState.h"
#include "LocomotionSystem/LookState.h"

#include "Kismet/KismetSystemLibrary.h"

APlayerController* AFPSPlayer::GetPlayerController()
{
	return FPSController;
}

// Sets default values
AFPSPlayer::AFPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	AbstractState* State = new GroundMoveState();
	StateLibrary.Add(StateEnum::Walking, State);
	State = new LookState();
	StateLibrary.Add(StateEnum::Looking, State);
}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	FPSController = Cast<AFPSPlayerController>(GetController());
	
	StateLibrary[StateEnum::Walking]->CacheInterface(this,GetWorld());
	StateLibrary[StateEnum::Looking]->CacheInterface(this, GetWorld());
}

// Called every frame
void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Movement Logic 
void AFPSPlayer::MoveFunction(const FInputActionValue& InputValue)
{	
	//Setting InputValue To TVariant
	MovementValue.Set<FVector2D>(InputValue.Get<FVector2D>());
    
	//Calling The Function Of Locomotion State From TMap(StateLibrary)
	StateLibrary[StateEnum::Walking]->EnterState(this, MovementValue);

}

void AFPSPlayer::LookFunction(const FInputActionValue& InputValue)
{  
	MovementValue.Set<FVector2D>(InputValue.Get<FVector2D>());
	StateLibrary[StateEnum::Looking]->EnterState(this, MovementValue);
}

