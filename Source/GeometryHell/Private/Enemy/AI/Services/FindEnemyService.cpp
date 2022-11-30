// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/AI/Services/FindEnemyService.h"
#include "Character/MainCharacter.h"
#include "Enemy/BaseEnemy.h"
#include "Enemy/Components/BaseAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UFindEnemyService::UFindEnemyService()
{
	NodeName = "Find Player";
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	/*const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto OwnerEnemyController = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = Cast<UBaseAIPerceptionComponent>(OwnerEnemyController);

		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetPlayer());
		}
	}*/
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
