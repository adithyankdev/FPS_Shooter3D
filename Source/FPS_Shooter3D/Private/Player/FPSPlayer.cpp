// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayer.h"
#include "Player/FPSPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LocomotionSystem/GroundMoveState.h"
#include "LocomotionSystem/LookState.h"
#include "Kismet/KismetSystemLibrary.h"

//Interface Function For Retreving Controller
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
//	FPSCamera->SetupAttachment(RootComponent);

	//Setting Attachment Of The Camera To SkelatalMesh
	if (FPSCamera && GetMesh())
	{
		FPSCamera->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale);

	}


	//Storing All Locomotion States To TMap
	AbstractState* State = new GroundMoveState();
	//Adding States With Enum Into Map
	StateLibrary.Add(StateEnum::Walking, State);
	State = new LookState();
	StateLibrary.Add(StateEnum::Looking, State);

}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();



	//Storing Ref To The Custom Controller
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
	//Setting InputValue To TVariant
	MovementValue.Set<FVector2D>(InputValue.Get<FVector2D>());

	//Calling The Function From The LookState
	StateLibrary[StateEnum::Looking]->EnterState(this, MovementValue);
}

