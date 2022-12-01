// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Logic/BaseSpawnEnemies.h"
#include "Containers/Array.h"
#include "SpawnInWavesEnemies.generated.h"


UCLASS()
class GEOMETRYHELL_API ASpawnInWavesEnemies : public ABaseSpawnEnemies
{
	GENERATED_BODY()

protected:
	virtual void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		int32 NumOfWaves = 1;

private:
	void SpawnEnemies();
	void DecreaseWaves();

	FTimerHandle ActivationTimer;
};
