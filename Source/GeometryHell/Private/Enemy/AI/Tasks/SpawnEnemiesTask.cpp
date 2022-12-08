// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/AI/Tasks/SpawnEnemiesTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Enemy/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/AI/BaseAIController.h"

USpawnEnemiesTask::USpawnEnemiesTask()
{
	NodeName = "Spawn Enemies";
}

EBTNodeResult::Type USpawnEnemiesTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	FTransform SpawnTransform(FRotator::ZeroRotator, Pawn->GetActorLocation());

	for (int i = 0; i < SpawnAmount; ++i) {
		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActorDeferred<ABaseEnemy>(EnemyType, SpawnTransform);
		if (SpawnedEnemy)
		{
			SpawnedEnemy->FinishSpawning(SpawnTransform);
		}
	}

	return EBTNodeResult::Succeeded;
}
