// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpawnEnemies.generated.h"

class UBoxComponent;
class ABaseEnemy;

UCLASS()
class GEOMETRYHELL_API ABaseSpawnEnemies : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseSpawnEnemies();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		TSubclassOf<ABaseEnemy> Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		TArray<AActor*> PointToSpawn;

	UFUNCTION()
		virtual void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
