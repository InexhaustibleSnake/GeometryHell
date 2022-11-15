// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/AI/BaseAIController.h"
#include "Enemy/Components/BaseAIPerceptionComponent.h"
#include "Enemy/BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MainCharacter.h"

ABaseAIController::ABaseAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UBaseAIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    const auto Enemy = Cast<ABaseEnemy>(InPawn);
    if (Enemy)
    {
        RunBehaviorTree(Enemy->BehaviorTreeAsset);
    }
}

void ABaseAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //const auto PlayerActor = GetFocusActor();
    const auto PlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    SetFocus(PlayerCharacter);
}

AActor* ABaseAIController::GetFocusOnPlayer()
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
