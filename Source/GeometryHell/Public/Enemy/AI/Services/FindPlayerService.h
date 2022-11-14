// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindPlayerService.generated.h"



UCLASS()
class GEOMETRYHELL_API UFindPlayerService : public UBTService
{
	GENERATED_BODY()
	
public:
	UFindPlayerService();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector EnemyActorKey;

};
