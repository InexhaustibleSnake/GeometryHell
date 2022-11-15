// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Components/ReflectionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Character/MainCharacter.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"

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
		GetWorld()->GetTimerManager().SetTimer(ReflectionTimer, this, &UReflectionComponent::ReduceReflectionStamina, ReflectionReduceRate, true, 0.0f);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), ReflectionPower);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(ReflectionTimer, this, &UReflectionComponent::RestoreReflectionStamina, ReflectionRestoreRate, true, 0.0f);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), ReflectionPower);
	}
}

void UReflectionComponent::UltraReflectionOn()
{
	const auto PlayerActor = GetPlayerActor();
	PlayerActor->CustomTimeDilation = PlayerDilationOnUltra;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), UltraReflectionPower);
}

void UReflectionComponent::UltraReflectionOff()
{
	const auto PlayerActor = GetPlayerActor();
	PlayerActor->CustomTimeDilation = 1.0f;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
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

void UReflectionComponent::ReduceUltraReflectionStamina()
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

AActor* UReflectionComponent::GetPlayerActor() const
{
	const auto PlayerActor = Cast<AActor>(GetOwner());
	return PlayerActor;
}