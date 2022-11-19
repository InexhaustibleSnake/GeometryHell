// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FireAtPlayerService.generated.h"

UCLASS()
class GEOMETRYHELL_API UFireAtPlayerService : public UBTService
{
	GENERATED_BODY()
	
public:
	UFireAtPlayerService();

protected:
    
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector PlayerActorKey;

};
