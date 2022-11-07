// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Components/ReflectionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UReflectionComponent::UReflectionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UReflectionComponent::BeginPlay()
{
	Super::BeginPlay();

	ReflectionStamina = MaxReflectionStamina;
}

// When Player toggle Reflection On and Off
void UReflectionComponent::Reflection(bool Active)
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (!GetWorld() || !Owner) return;

	if (Active)
	{
		GetWorld()->GetTimerManager().SetTimer(ReflectionTimer, this, &UReflectionComponent::ReduceReflectionStamina, ReflectionReduceTimer, true, 0.0f);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), ReflectionPower);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(ReflectionTimer, this, &UReflectionComponent::RestoreReflectionStamina, ReflectionRestoreTimer, true, 0.0f);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), ReflectionPower);
	}
}

// Reduce ReflectionStamina and Set Global Time Dilation to Normal, if ReflectionStamina empty
void UReflectionComponent::ReduceReflectionStamina()
{
	if (IsReflectionStaminaEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(ReflectionTimer);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	}
	else 
	{
		ReflectionStamina -= 1;
	}
}

void UReflectionComponent::RestoreReflectionStamina()
{
	if (IsReflectionStaminaFull())
	{
		GetWorld()->GetTimerManager().ClearTimer(ReflectionTimer);
	}
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		ReflectionStamina += 1;
	}
}

bool UReflectionComponent::IsReflectionStaminaEmpty() const
{
	return FMath::IsNearlyEqual(ReflectionStamina, 0);
}

bool UReflectionComponent::IsReflectionStaminaFull() const
{
	return FMath::IsNearlyEqual(ReflectionStamina, MaxReflectionStamina);
}