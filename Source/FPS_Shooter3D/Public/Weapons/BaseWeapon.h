// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class IPlayerInterface;

enum class EWeaponType : int
{
	Rifile,
};

/**
 * 
 */
class FPS_SHOOTER3D_API BaseWeapon
{
public:
	BaseWeapon();
	~BaseWeapon();

	EWeaponType CurrentWeapon;

	float ShootingRange;

	/*Cache Variables */
	ACharacter* OwnedPlayer;
	USkeletalMeshComponent* GunSkeletalMesh;
	UWorld* GetWorld;

	void CacheInformation(ACharacter* Player, USkeletalMeshComponent* GunMesh,UWorld* World);

	TScriptInterface<IPlayerInterface>PlayerInterface;

	FTimerHandle ShootWeaponTimer;

	void StartShoot(EWeaponType WeaponType);
	void Shooting();
	void StopShoot();

	/*Pre Declaraton Of Line Trace Parameters*/
	FVector StartPoint;
	FVector EndPoint;
	FHitResult TraceHitResult;
	ECollisionChannel TraceChannel;
	FCollisionQueryParams CollisionParams;
};
