// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"
#include "Player/FPSPlayer.h"
#include "Interfaces/PlayerInterface.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "DrawDebugHelpers.h"

BaseWeapon::BaseWeapon()
{
	StartPoint = FVector::ZeroVector;
	EndPoint = FVector::ZeroVector;
	ShootingRange = 3500.0f;
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
}

void BaseWeapon::StartShoot(EWeaponType WeaponType)
{
	GetWorld->GetTimerManager().SetTimer(ShootWeaponTimer,[this](){ Shooting();},0.1,true);
}

void BaseWeapon::Shooting()
{
	PlayerInterface->GetLocationForTrace(StartPoint, EndPoint);
	EndPoint = (EndPoint * ShootingRange) + StartPoint;
	GetWorld->LineTraceSingleByChannel(TraceHitResult, StartPoint, EndPoint, TraceChannel, CollisionParams);
	DrawDebugLine(GetWorld, StartPoint, EndPoint,FLinearColor::Green.ToFColor(true), true, 5.0f);
}

void BaseWeapon::StopShoot()
{
	GetWorld->GetTimerManager().ClearTimer(ShootWeaponTimer);
}
