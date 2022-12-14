// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

class UBaseAIPerceptionComponent;

UCLASS()
class GEOMETRYHELL_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController();

	void OnOwnerDamaged();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBaseAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FName FocusOnKeyName = "PlayerActor";

	UFUNCTION()
	void ActorsUpdated(TArray<AActor*> const & UpdatedActors);

	bool SpotPlayer = false;

	UFUNCTION()
	void AddEnemiesInFight();
};
