// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseProjectile;
class USoundCue;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GEOMETRYHELL_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();
	void StartFire();
	void StopFire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<ABaseProjectile> MainProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
		float MainShootRate = 0.3f;

	FTimerHandle ShootTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* ShootAudio;


private:
	void MainShot();
	void MakeTrace(FHitResult& HitResult, const FVector TraceStart, const FVector TraceEnd);
	void GetPlayerViewPoint(FVector& TraceStart, FVector& TraceEnd);

	FVector GetMuzzleWorldLocation();
};