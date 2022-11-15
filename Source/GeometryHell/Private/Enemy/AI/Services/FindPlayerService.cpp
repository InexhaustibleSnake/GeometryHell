// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/AI/Services/FindPlayerService.h"
#include "Enemy/BaseEnemy.h"
#include "Enemy/AI/Components/BaseAIPerceptionComponent.h"
#include "Enemy/AI/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindPlayerService::UFindPlayerService()
{
	NodeName = "Find Player";
}

void UFindPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
		const auto PerceptionComponent = Cast<UBaseAIPerceptionComponent>(AIController);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetPlayer());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
