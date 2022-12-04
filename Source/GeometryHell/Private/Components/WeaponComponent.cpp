// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Components/WeaponComponent.h"
#include "Character/MainCharacter.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectiles/BaseProjectile.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/BaseProjectile.h"
#include "Components/ReflectionComponent.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	NumOfSpecialShots = MaxSpecialShots;
}

void UWeaponComponent::StartFire()
{
	GetWorld()->GetTimerManager().SetTimer(ShootTimer, this, &UWeaponComponent::MainShot, MainShootRate, true, 0.0f);
}

void UWeaponComponent::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootTimer);
}

void UWeaponComponent::MainShot()
{
	FVector TraceStart, TraceEnd;

	GetPlayerViewPoint(TraceStart, TraceEnd);

	FHitResult HitResult;
	MakeTrace(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	ABaseProjectile* BaseProjectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(MainProjectile, SpawnTransform);
	if (BaseProjectile)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ShootAudio, GetOwner()->GetActorLocation());

		const auto MainCharacter = Cast<AMainCharacter>(GetOwner());
		if (MainCharacter->CustomTimeDilation > 1) 
		{
			BaseProjectile->SetDamage(BaseProjectile->Damage * 1.5);
		}

		BaseProjectile->SetShotDirection(Direction);
		BaseProjectile->FinishSpawning(SpawnTransform);
	}
}

void UWeaponComponent::SpecialShot()
{
	if (NumOfSpecialShots == 0) return;
	FVector TraceStart, TraceEnd;

	GetPlayerViewPoint(TraceStart, TraceEnd);

	FHitResult HitResult;
	MakeTrace(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	ABaseProjectile* SpecialShot = GetWorld()->SpawnActorDeferred<ABaseProjectile>(SpecialProjectile, SpawnTransform);
	if (SpecialShot)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SpecialShotAudio, GetOwner()->GetActorLocation());
		NumOfSpecialShots -= 1;

		const auto MainCharacter = Cast<AMainCharacter>(GetOwner());
		if (MainCharacter->CustomTimeDilation > 1)
		{
			SpecialShot->SetDamage(SpecialShot->Damage * 1.5);
		}

		SpecialShot->SetShotDirection(Direction);
		SpecialShot->FinishSpawning(SpawnTransform);

		if (!GetWorld()->GetTimerManager().IsTimerActive(SpecialShotTimer))
		{
			GetWorld()->GetTimerManager().SetTimer(SpecialShotTimer, this, &UWeaponComponent::SpecialShotRestore, SpecialRestoreRate, true, 0.0f);
		}
	}
}

void UWeaponComponent::SpecialShotRestore()
{
	if (NumOfSpecialShots != MaxSpecialShots)
	{
		NumOfSpecialShots += 1;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SpecialShotTimer);
	}
}

void UWeaponComponent::GetPlayerViewPoint(FVector& TraceStart, FVector& TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;

	const auto PlayerCharacter = Cast<AMainCharacter>(GetOwner());
	PlayerCharacter->GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

	TraceStart = ViewLocation;
	TraceEnd = ViewLocation + ViewRotation.Vector() * 16000.0f;
}

void UWeaponComponent::MakeTrace(FHitResult& HitResult, const FVector TraceStart, const FVector TraceEnd)
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

FVector UWeaponComponent::GetMuzzleWorldLocation()
{
	const auto PlayerCharacter = Cast<AMainCharacter>(GetOwner());
	return PlayerCharacter->GunMesh->GetSocketLocation("Muzzle");
}
