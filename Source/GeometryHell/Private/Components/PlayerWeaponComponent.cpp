// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Components/PlayerWeaponComponent.h"
#include "Character/MainCharacter.h"
#include "DrawDebugHelpers.h"
#include "Projectiles/BaseProjectile.h"
#include "GameFramework/Character.h"

UPlayerWeaponComponent::UPlayerWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UPlayerWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UPlayerWeaponComponent::StartFire()
{
	ShootMainProjectile();
}

void UPlayerWeaponComponent::StopFire()
{
}

void UPlayerWeaponComponent::ShootMainProjectile()
{
	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;

	if (!GetTraceData(TraceStart, TraceEnd)) return;
	

	FHitResult HitResult;
	MakeTrace(HitResult, TraceStart, TraceEnd);

	FVector ProjectileEndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	FVector ProjectileDirection = (ProjectileEndPoint - GetMuzzleLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleLocation());
	ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(MainProjectile, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShootDirection(ProjectileDirection);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
	const auto MainCharacter = Cast<AMainCharacter>(GetOwner());
	MainCharacter->PlayShotAnimaton();
}

void UPlayerWeaponComponent::SecondaryMainProjectile()
{
}

bool UPlayerWeaponComponent::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
	const auto Controller = GetPlayerController();
	if (!Controller) return true;

	FVector ViewLocation, ShootDirection;
	FRotator ViewRotation;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	ShootDirection = ViewRotation.Vector();

	TraceStart = ViewLocation;
	TraceEnd = ViewLocation + ShootDirection * 6000.0f;

	return true;
}

void UPlayerWeaponComponent::MakeTrace(FHitResult& HitResult, const FVector TraceStart, const FVector TraceEnd)
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

FVector UPlayerWeaponComponent::GetMuzzleLocation()
{
	const auto MainCharacter = Cast<AMainCharacter>(GetOwner());
	return MainCharacter->GetMuzzleLocation();
}

AController* UPlayerWeaponComponent::GetPlayerController()
{
	const auto Player = Cast<AMainCharacter>(GetOwner());
	return Player->GetController();
}