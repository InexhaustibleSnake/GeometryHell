// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/AI/Services/FireAtPlayerService.h"
#include "Enemy/BaseEnemy.h"
#include "Enemy/Components/BaseAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UFireAtPlayerService::UFireAtPlayerService()
{
	NodeName = "Fire At Player";
}

void UFireAtPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	auto Blackboard = Controller->GetBlackboardComponent();

	const auto EnemyOwner = Cast<ABaseEnemy>(OwnerComp.GetAIOwner());

//	EnemyOwner->StartFire();

	/*bool HasAim = Blackboard && Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName);

	if (Controller)
	{
		const auto EnemyOwner = Cast<ABaseEnemy>(OwnerComp.GetAIOwner());
		
		if (HasAim) EnemyOwner->StartFire();
	}*/

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
