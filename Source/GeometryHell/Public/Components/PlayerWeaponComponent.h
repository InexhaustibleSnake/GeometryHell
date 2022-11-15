// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerWeaponComponent.generated.h"

class ABaseProjectile;
class UAnimMontage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYHELL_API UPlayerWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerWeaponComponent();

	void StartFire();
	void StopFire();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectiles")
		TSubclassOf<ABaseProjectile> MainProjectile;

	void ShootMainProjectile();
	void SecondaryMainProjectile();
	void MakeTrace(FHitResult& HitResult, const FVector TraceStart, const FVector TraceEnd);
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd);
	FVector GetMuzzleLocation();
	AController* GetPlayerController();
};
