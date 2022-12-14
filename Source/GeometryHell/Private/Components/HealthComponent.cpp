// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Components/HealthComponent.h"
#include "Character/MainCharacter.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShakeBase.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	Health = MaxHealth;
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;

	if (Health <= 0) 
	{
		OnDeath.Broadcast();
		GetOwner()->Destroy();
		return;
	}

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HittedSound, GetOwner()->GetActorLocation());
	PlayCameraShake();
}

void UHealthComponent::PlayCameraShake()
{
	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Cast<APlayerController>(Player->GetController());
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

float UHealthComponent::GetHealthPercentage() const
{
	return Health / MaxHealth;
}

bool UHealthComponent::TryToAddHealth(float Amount)
{
	if (IsHealthFull()) return false;
	
	SetHealth(Health + Amount);
	return true;
}

bool UHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UHealthComponent::SetHealth(float Amount)
{
	const auto NewHealth = FMath::Clamp(Amount, 0.0f, MaxHealth);

	Health = NewHealth;
}
