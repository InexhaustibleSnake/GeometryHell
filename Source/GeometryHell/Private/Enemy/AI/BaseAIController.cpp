// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/AI/BaseAIController.h"
#include "Enemy/Components/BaseAIPerceptionComponent.h"
#include "Enemy/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MainCharacter.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include "Logic/BaseGameMode.h"

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

void ABaseAIController::BeginPlay()
{
    Super::BeginPlay();

    GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ABaseAIController::ActorsUpdated);

    const auto EnemyOwner = Cast<ABaseEnemy>(GetPawn());
    EnemyOwner->OnTakeAnyDamage.AddDynamic(this, &ABaseAIController::OnTakeDamage);
}

void ABaseAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!SpotPlayer) return;
    const auto PlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    SetFocus(PlayerCharacter);
}

void ABaseAIController::ActorsUpdated(TArray<AActor*> const& UpdatedActors)
{
    const auto PlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    for (auto PerceivedActor : UpdatedActors)
    {
        if (PerceivedActor == PlayerCharacter)
        {

            if (!SpotPlayer) 
            {
                AddEnemiesInFight();
            }

            SpotPlayer = true;
            const auto EnemyOwner = Cast<ABaseEnemy>(GetPawn());
            EnemyOwner->HasEnemy = true;
        }
    }
}

void ABaseAIController::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    if (SpotPlayer) return;
    AddEnemiesInFight();
    SpotPlayer = true;

    const auto EnemyOwner = Cast<ABaseEnemy>(GetPawn());
    EnemyOwner->HasEnemy = true;
}

void ABaseAIController::AddEnemiesInFight()
{
    auto GameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (!GameMode && SpotPlayer) return;
    GameMode->UpdateEnemyInFight(1);
}