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

void UReflectionComponent::ReflectionOn()
{
	if (IsUltraReflectionActive) return;

	GetWorld()->GetTimerManager().SetTimer(ReflectionTimer, this, &UReflectionComponent::ReduceReflectionStamina, ReflectionStaminaReduceRate, true, 0.0f);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), ReflectionPower);
	IsReflectionActive = true;
}

void UReflectionComponent::ReduceReflectionStamina()
{
	if (!IsReflectionStaminaEmpty())
	{
		ReflectionStamina -= ReflectionStaminaReduceAmount;
	}
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		GetWorld()->GetTimerManager().ClearTimer(ReflectionTimer);
	}
}

void UReflectionComponent::ReflectionOff()
{
	GetWorld()->GetTimerManager().SetTimer(ReflectionTimer, this, &UReflectionComponent::RestoreReflectionStamina, ReflectionStaminaRestoreRate, true, 0.0f);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	IsReflectionActive = false;
}

void UReflectionComponent::RestoreReflectionStamina()
{
	if (IsReflectionStaminaFull())
	{
		GetWorld()->GetTimerManager().ClearTimer(ReflectionTimer);
		ReflectionStamina = MaxReflectionStamina;
	}
	else
	{
		ReflectionStamina += 1;
	}
}

void UReflectionComponent::UltraReflectionOn()
{
	if (IsReflectionActive) return;

	GetWorld()->GetTimerManager().SetTimer(ReflectionTimer, this, &UReflectionComponent::ReduceUltraReflectionStamina, UltraReflectionStaminaReduceRate, true, 0.0f);

	AActor* Player = GetPlayerActor();
	Player->CustomTimeDilation = PlayerDilationOnUltra;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), UltraReflectionPower);

	IsUltraReflectionActive = true;
}

void UReflectionComponent::ReduceUltraReflectionStamina()
{
	if (!IsReflectionStaminaEmpty())
	{
		ReflectionStamina -= UltraReflectionStaminaReduceAmount;
	}
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		GetWorld()->GetTimerManager().ClearTimer(ReflectionTimer);
	}
}

void UReflectionComponent::UltraReflectionOff()
{
	GetWorld()->GetTimerManager().SetTimer(ReflectionTimer, this, &UReflectionComponent::RestoreReflectionStamina, ReflectionStaminaRestoreRate, true, 0.0f);

	AActor* Player = GetPlayerActor();
	Player->CustomTimeDilation = 1.0f;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);

	IsUltraReflectionActive = false;
}

bool UReflectionComponent::IsReflectionStaminaEmpty() const
{
	return FMath::IsNearlyEqual(ReflectionStamina, 0);
}

bool UReflectionComponent::IsReflectionStaminaFull() const
{
	return FMath::IsNearlyEqual(ReflectionStamina, MaxReflectionStamina) || ReflectionStamina >= MaxReflectionStamina;
}

AActor* UReflectionComponent::GetPlayerActor() const
{
	return Cast<AActor>(GetOwner());
}