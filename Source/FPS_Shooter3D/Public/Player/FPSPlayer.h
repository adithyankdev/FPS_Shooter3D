// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//-------------------------------------------
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
//-------------------------------------------
#include "InputActionValue.h"
//-------------------------------------------
#include "Interfaces/PlayerInterface.h"
#include "Interfaces/PlayerAnimeInterface.h"
//-------------------------------------------
#include "Weapons/BaseWeapon.h"
#include "Player/LocomotionSystem/AbstractState.h"
//-------------------------------------------
#include "FPSPlayer.generated.h"

class AFPSPlayerController;
class UPlayerAnimInstance;


UCLASS()
class FPS_SHOOTER3D_API AFPSPlayer : public ACharacter , public IPlayerInterface
{
	GENERATED_BODY()

public:

	//Interface Function
	APlayerController* GetPlayerController() override;

	//Output Parameter Function ... Connecting From WeaponBase
	void GetLocationForTrace(FVector& StartPoint, FVector& EndPoint) override;

	bool IsReloading() override;

	AFPSPlayer();
	~AFPSPlayer();

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	UCameraComponent* FPSCamera;

	UPROPERTY()
	TScriptInterface<IPlayerAnimeInterface>AnimInstanceInterface;

private:

	//Referance For The Custom Controller
	UPROPERTY()
	AFPSPlayerController* FPSController;

	//For Storing Differnt LocomotionStates
	TMap<StateEnum, AbstractState*>StateLibrary;

	//Variable For Passing In LocomotionStates
	TVariant<FVector2D, bool>MovementValue;

	//Variable For Referencing The Current Weapon Using
	EWeaponType CurrentWeaponType;

	//WeaponClass
	BaseWeapon* WeaponBase;

	/*Timer For Reloading Weapon*/
	FTimerHandle ReloadWeaponTimer;

	//Variable For Checking Reloading
	bool IsReload;
	//Variable For Checking Firing
	bool Firing;

protected:

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	//Function To Contain Movement Logic
	void MoveFunction(const FInputActionValue& InputValue);
	void LookFunction(const FInputActionValue& InputValue);
	void SprintFunction(const FInputActionValue& InputValue);
	void StopSprintFunction();

	void CrouchToggleFunction();

	void WeaponFireStartFunction();
	void WeaponFireStopFunction();
	void WeaponReload();
	void WeaponReloaded();

	//Variable for Implementing The Toggle Functionality -- FlipFlop In The Blueprint
	bool CrouchToggleValue;

};
