// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/AI/BaseAIController.h"
#include "Enemy/BaseEnemy.h"
#include "Enemy/AI/Components/BaseAIPerceptionComponent.h"

ABaseAIController::ABaseAIController()
{
	BaseAIPerceptionComponent = CreateDefaultSubobject<UBaseAIPerceptionComponent>("BaseAIPerceptionComponent");
	SetPerceptionComponent(*BaseAIPerceptionComponent);
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto BaseEnemy = Cast<ABaseEnemy>(InPawn);
	if (BaseEnemy)
	{
		RunBehaviorTree(BaseEnemy->BehaviorTreeAsset);
	}
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto PlayerActor = BaseAIPerceptionComponent->GetPlayer();
	SetFocus(PlayerActor);
}
