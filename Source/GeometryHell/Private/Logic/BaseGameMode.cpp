// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Logic/BaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Engine/Engine.h"

ABaseGameMode::ABaseGameMode()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->SetSound(FightOst);
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
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Some debug message!"));
	}
	else if (EnemyInFightAmount == 0)
	{
		AudioComponent->FadeOut(6.0f, 0.01f, EAudioFaderCurve::Linear);
		
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	}
}