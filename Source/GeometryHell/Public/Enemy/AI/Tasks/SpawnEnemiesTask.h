// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SpawnEnemiesTask.generated.h"

class ABaseEnemy;

UCLASS()
class GEOMETRYHELL_API USpawnEnemiesTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	USpawnEnemiesTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		int SpawnAmount = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float SpawnRadius = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TSubclassOf<ABaseEnemy> EnemyType;
};
