// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"



UCLASS()
class GEOMETRYHELL_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		int UpdateEnemyInFight(int Amount);
	UFUNCTION(BlueprintCallable)
		int GetEnemiesInFight() const;

protected:

	int EnemyInFightAmount = 0;
};
