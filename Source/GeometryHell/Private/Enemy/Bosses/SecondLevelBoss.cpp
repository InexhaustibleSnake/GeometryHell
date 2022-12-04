// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/Bosses/SecondLevelBoss.h"

float ASecondLevelBoss::GetHealthPercent() const
{
	return Health / MaxHealth;
}
