// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Logic/BaseGameMode.h"

int ABaseGameMode::UpdateEnemyInFight(int Amount)
{
	EnemyInFightAmount += Amount;
	return EnemyInFightAmount;
}

int ABaseGameMode::GetEnemiesInFight() const
{
	return EnemyInFightAmount;
}


