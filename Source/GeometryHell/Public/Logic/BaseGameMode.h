// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

class USoundCue;
class USoundBase;

UCLASS()
class GEOMETRYHELL_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	ABaseGameMode();

	UFUNCTION(BlueprintCallable)
		int UpdateEnemyInFight(int Amount);
	UFUNCTION(BlueprintCallable)
		int GetEnemiesInFight() const;

	void PlayFightOst();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* FightOst;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* GameOverOst;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		UAudioComponent* AudioComponent;

	UFUNCTION()
	void OnPlayerDeath();

protected:

	int EnemyInFightAmount = 0;
};
