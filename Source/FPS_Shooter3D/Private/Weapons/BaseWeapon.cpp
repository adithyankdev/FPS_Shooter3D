// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"
#include "Player/FPSPlayer.h"
#include "Interfaces/PlayerInterface.h"
#include "Runtime/Engine/Public/TimerManager.h"

#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

BaseWeapon::BaseWeapon()
{
	StartPoint = FVector::ZeroVector;
	EndPoint = FVector::ZeroVector;
	ShootingRange = 3500.0f;
	BulletCount = 30;

	//Loading GunFire Animation From The ContentBrowser
	RifleGunFiringAnim = LoadObject<UAnimSequence>(nullptr, TEXT("/Game/Weapons/Rifle/Animations/Weap_Rifle_Fire.Weap_Rifle_Fire"));
	RifleGunNoBulletFiringAnim = LoadObject<UAnimSequence>(nullptr, TEXT("/Game/Weapons/Rifle/Animations/RifleWeapon_NoBulletFire.RifleWeapon_NoBulletFire"));

	GunShotImpactParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/MilitaryWeapSilver/FX/GunShotHitFloor_MediumImpact.GunShotHitFloor_MediumImpact"));

}


BaseWeapon::~BaseWeapon()
{
	OwnedPlayer = nullptr;
	GunSkeletalMesh = nullptr;
}

void BaseWeapon::CacheInformation(ACharacter* Player, USkeletalMeshComponent* GunMesh,UWorld* World)
{
	OwnedPlayer = Player;
	GunSkeletalMesh = GunMesh;
	GetWorld = World;
	PlayerInterface.SetObject(Player);
	if (IPlayerInterface* Interface = Cast<IPlayerInterface>(Player))
	{
		PlayerInterface.SetInterface(Interface);
	}

	CollisionParams.AddIgnoredActor(Player);
}

void BaseWeapon::StartShoot(EWeaponType WeaponType)
{
	GetWorld->GetTimerManager().SetTimer(ShootWeaponTimer,[this](){ Shooting();},0.12,true);
}

void BaseWeapon::Shooting()
{
	if (BulletCount > 0)
	{
		PlayerInterface->GetLocationForTrace(StartPoint, EndPoint);
		EndPoint = (EndPoint * ShootingRange) + StartPoint; //Adding Setting Up The EndLocation

		//Playing The ShootGun Animation on Weapon
		GunSkeletalMesh->PlayAnimation(RifleGunFiringAnim, false);

		if (bool IsHit = GetWorld->LineTraceSingleByChannel(TraceHitResult, StartPoint, EndPoint, ECC_Camera, CollisionParams))
		{
			EmitterSpawnTransform.SetLocation(TraceHitResult.ImpactPoint);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld, GunShotImpactParticle, EmitterSpawnTransform, true, EPSCPoolMethod::AutoRelease);
		}
		BulletCount--;
	}
	else 
	{
		GunSkeletalMesh->PlayAnimation(RifleGunNoBulletFiringAnim,false);
	}
	
	//DrawDebugLine(GetWorld, StartPoint, EndPoint,FLinearColor::Green.ToFColor(true), true, 5.0f);
}

void BaseWeapon::StopShoot()
{
	GetWorld->GetTimerManager().ClearTimer(ShootWeaponTimer);
}

void BaseWeapon::ReloadWeapon()
{
	BulletCount = 30;
}
