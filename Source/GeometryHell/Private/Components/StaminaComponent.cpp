// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Components/StaminaComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/MainCharacter.h"

UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	Stamina = MaxStamina;
}

void UStaminaComponent::Sprint()
{
	const auto MainCharacter = Cast<AMainCharacter>(GetOwner());
	if (!MainCharacter || !GetWorld() || !CanRun) return;

	MainCharacter->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	GetWorld()->GetTimerManager().SetTimer(StaminaTimer, this, &UStaminaComponent::StaminaReduce, StaminaReduceRate, true, 0.0f);
}

void UStaminaComponent::StopSprinting()
{
	const auto MainCharacter = Cast<AMainCharacter>(GetOwner());
	if (!MainCharacter || !GetWorld() || !CanRun) return;

	MainCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetWorld()->GetTimerManager().SetTimer(StaminaTimer, this, &UStaminaComponent::StaminaRecover, StaminaRecoverRate, true, 0.0f);
}

void UStaminaComponent::StaminaReduce()
{
	const auto MainCharacter = Cast<AMainCharacter>(GetOwner());
	if (!MainCharacter || !GetWorld()) return;

	if (IsStaminaEmpty() || MainCharacter->GetVelocity().IsZero())
	{
		StopSprinting();
	}
	else
	{
		Stamina -= 1;
	}
}

void UStaminaComponent::StaminaRecover()
{
	if (IsStaminaFull())
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaTimer);
	}
	else
	{
		Stamina += 1;
	}
}

bool UStaminaComponent::IsStaminaFull() const
{
	return FMath::IsNearlyEqual(Stamina, MaxStamina);
}

bool UStaminaComponent::IsStaminaEmpty() const
{
	return FMath::IsNearlyEqual(Stamina, 0);
}
