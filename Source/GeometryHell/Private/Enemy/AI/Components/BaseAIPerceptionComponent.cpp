// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/AI/Components/BaseAIPerceptionComponent.h"
#include "Enemy/AI/BaseAIController.h"
#include "Perception/AISense_Sight.h"
#include "Character/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

AActor* UBaseAIPerceptionComponent::GetPlayer() const
{
	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
	if (PerceivedActors.Num() == 0) return nullptr;

	const auto Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player) return nullptr;

	return Player;
}
