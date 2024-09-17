// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSPlayer.h"
//---------------------------------------------------
#include "GameFramework/CharacterMovementComponent.h"
//---------------------------------------------------
#include "Player/FPSPlayerController.h"
//---------------------------------------------------
#include "LocomotionSystem/GroundMoveState.h"
#include "LocomotionSystem/LookState.h"
//---------------------------------------------------
#include "Player/Animation/PlayerAnimInstance.h"
//---------------------------------------------------
#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

APlayerController* AFPSPlayer::GetPlayerController()
{
	return FPSController;
}

void AFPSPlayer::GetLocationForTrace(FVector& StartPoint, FVector& EndPoint)
{
	StartPoint = FPSCamera->GetComponentLocation();
	EndPoint = FPSCamera->GetForwardVector();
}

bool AFPSPlayer::IsReloading()
{
	return IsReload;
}

// Sets default values
AFPSPlayer::AFPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponActor"));
	MeshComponent->SetupAttachment(GetMesh(),TEXT("WeaponHold"));

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//FPSCamera->SetupAttachment(GetMesh(),TEXT("head"));
	FPSCamera->SetupAttachment(GetMesh(),TEXT("head"));

	AbstractState* State = new GroundMoveState();
	StateLibrary.Add(StateEnum::Walking, State);
	State = new LookState();
	StateLibrary.Add(StateEnum::Looking, State);

	WeaponBase = new BaseWeapon();
	CurrentWeaponType = EWeaponType::Rifile;
}

AFPSPlayer::~AFPSPlayer()
{
	StateLibrary.Empty();
	WeaponBase = nullptr;
}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	FPSController = Cast<AFPSPlayerController>(GetController());
	
	StateLibrary[StateEnum::Walking]->CacheInterface(this,GetWorld());
	StateLibrary[StateEnum::Looking]->CacheInterface(this, GetWorld());

	if (IPlayerAnimeInterface* Interface = Cast<IPlayerAnimeInterface>(GetMesh()->GetAnimInstance()))
	{
		AnimInstanceInterface.SetObject(GetMesh()->GetAnimInstance());
		AnimInstanceInterface.SetInterface(Interface);
	}
	//Calling The Cache Function On The Weapon Class For Storing Data
	WeaponBase->CacheInformation(this, MeshComponent, GetWorld());
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

//Function Implementing With Toogle Method
void AFPSPlayer::CrouchToggleFunction()
{
	CrouchToggleValue = !CrouchToggleValue;
	if (CrouchToggleValue)
	{
		Crouch();
		AnimInstanceInterface->ChangeLocomotionState(ELocomotionState::Crouch);
		
	}
	else
	{
		UnCrouch();
		AnimInstanceInterface->ChangeLocomotionState(ELocomotionState::GroundLocomotion);
	}
	
}

void AFPSPlayer::WeaponFireStartFunction()
{
	WeaponBase->StartShoot(CurrentWeaponType);
}

void AFPSPlayer::WeaponFireStopFunction()
{
	WeaponBase->StopShoot();
}

void AFPSPlayer::WeaponReload()
{
	IsReload = true;
	GetWorld()->GetTimerManager().SetTimer(ReloadWeaponTimer, this, &AFPSPlayer::WeaponReloaded, 2.1);
	
}

void AFPSPlayer::WeaponReloaded()
{
	IsReload = false;
	WeaponBase->ReloadWeapon();
}


