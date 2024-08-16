// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimSequence.h"

class IPlayerInterface;

class ParticleSystem;
class ParticleSystemComponent;

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
protected:

	EWeaponType CurrentWeapon;

	float ShootingRange;

	/*Cache Variables */
	ACharacter* OwnedPlayer;
	USkeletalMeshComponent* GunSkeletalMesh;
	UWorld* GetWorld;

	TScriptInterface<IPlayerInterface>PlayerInterface;

	FTimerHandle ShootWeaponTimer;

public:

	void CacheInformation(ACharacter* Player, USkeletalMeshComponent* GunMesh, UWorld* World);

	void StartShoot(EWeaponType WeaponType);
	void Shooting();
	void StopShoot();

private:

	UAnimSequence* FireGunAnimSequence;

	UParticleSystem* GunImpactParticle;
	FTransform EmitterSpawnTransform;

	/*Pre Declaraton Of Line Trace Parameters*/
	FVector StartPoint;
	FVector EndPoint;
	FHitResult TraceHitResult;
	ECollisionChannel TraceChannel;
	FCollisionQueryParams CollisionParams;
};
