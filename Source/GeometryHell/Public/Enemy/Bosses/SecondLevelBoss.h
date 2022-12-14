// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseEnemy.h"
#include "SecondLevelBoss.generated.h"

UCLASS()
class GEOMETRYHELL_API ASecondLevelBoss : public ABaseEnemy
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const;
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* CannonCubeTR;
};
