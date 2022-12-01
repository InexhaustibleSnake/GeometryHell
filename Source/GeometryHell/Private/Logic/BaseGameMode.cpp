// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Logic/BaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Engine/Engine.h"
#include "Character/MainCharacter.h"
#include "Components/HealthComponent.h"

ABaseGameMode::ABaseGameMode()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->SetSound(FightOst);
	
	const auto PlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	const auto HealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>();

	HealthComponent->OnDeath.AddDynamic(this, &ABaseGameMode::OnPlayerDeath);
}

int ABaseGameMode::UpdateEnemyInFight(int Amount)
{
	EnemyInFightAmount += Amount;
	PlayFightOst();
	return EnemyInFightAmount;
}

int ABaseGameMode::GetEnemiesInFight() const
{
	return EnemyInFightAmount;
}

void ABaseGameMode::PlayFightOst()
{
	if (EnemyInFightAmount == 1 && !AudioComponent->IsPlaying())
	{
		AudioComponent->Play(0.0f);
	}
	else if (EnemyInFightAmount == 0)
	{
		GetWorldTimerManager().SetTimer(FadeOutTimer, this, &ABaseGameMode::FadeMusicOut, 4.0f, false, 4.0f);
	}
	else if (AudioComponent->bIsFadingOut)
	{
		AudioComponent->FadeIn(2.0f, 0.3f);
	}
}

void ABaseGameMode::OnPlayerDeath()
{
	UGameplayStatics::PlaySound2D(GetWorld(), GameOverOst);
}

void ABaseGameMode::FadeMusicOut()
{
	if (GetEnemiesInFight() == 0)
	{
		AudioComponent->FadeOut(4.0f, 0.05f, EAudioFaderCurve::Linear);
	}
}
