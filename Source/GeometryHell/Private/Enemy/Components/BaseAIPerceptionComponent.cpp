// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/Components/BaseAIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MainCharacter.h"

AActor* UBaseAIPerceptionComponent::GetPlayer() const
{
	TArray<AActor*> PerceivedActors;

	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);

	if (PerceivedActors.Num() == 0) return nullptr;

	const auto PlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	
	return PlayerCharacter;
}
