// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes


#include "Enemy/BaseEnemy.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

