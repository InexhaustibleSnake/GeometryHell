// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Logic/SpawnInWavesEnemies.h"
#include "Enemy/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MainCharacter.h"
#include "Logic/BaseGameMode.h"

void ASpawnInWavesEnemies::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{   
	const auto GameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	const auto Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!GetWorld() && !OtherActor->IsA(AMainCharacter::StaticClass()) && !Enemy) return;

	GetWorldTimerManager().SetTimer(ActivationTimer, this, &ASpawnInWavesEnemies::SpawnEnemies, 2.0f, true, 0.0f);
}

void ASpawnInWavesEnemies::SpawnEnemies()
{
	const auto GameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode->GetEnemiesInFight() > 0) return;

	for (const auto Point : PointToSpawn)
	{
		FTransform SpawnTransform = Point->GetTransform();

		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActorDeferred<ABaseEnemy>(Enemy, SpawnTransform);
		if (SpawnedEnemy)
		{
			SpawnedEnemy->FinishSpawning(SpawnTransform);
		}
	}

	DecreaseWaves();
}

void ASpawnInWavesEnemies::DecreaseWaves()
{
	if (NumOfWaves-- == 0)
	{
		Destroy();
	}
}
