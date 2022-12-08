// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseEnemy.h"
#include "FinalBoss.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeStop, bool, IsActive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSecondPhase, bool, IsActive);

class AMainCharacter;

UCLASS()
class GEOMETRYHELL_API AFinalBoss : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	AFinalBoss();

	UFUNCTION(BlueprintCallable)
		float GetHealthPercent() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USceneComponent* LaserShootPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<ABaseProjectile> LaserProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TimeStop")
		float TimeStopDuration = 7.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TimeStop")
		float TimeStopRate = 14.0f;

	UPROPERTY(BlueprintAssignable, Category = "Custom")
		FOnTimeStop TimeStop;

	FOnSecondPhase SecondPhase;

private:
	void StopTime();
	void RestoreTime();
	void LaserAttack();

	AMainCharacter* GetPlayer();

	FTimerHandle TimeStopTimer;
	FTimerHandle RestoreTimeTimer;
};
