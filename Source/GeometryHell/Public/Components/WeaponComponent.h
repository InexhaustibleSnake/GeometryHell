// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/MainCharacter.h"
#include "WeaponComponent.generated.h"

class ABaseProjectile;
class USoundCue;
//class AMainCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GEOMETRYHELL_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();
	void StartFire();
	void StopFire();

	void SpecialShot();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<ABaseProjectile> MainProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<ABaseProjectile> SpecialProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
		float MainShootRate = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpecialShot")
		float SpecialRestoreRate = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpecialShot")
		float MaxSpecialShots = 4.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpecialShot")
		float NumOfSpecialShots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* ShootAudio;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* SpecialShotAudio;

	FTimerHandle ShootTimer;
	FTimerHandle SpecialShotTimer;

private:
	void MainShot();
	void MakeTrace(FHitResult& HitResult, const FVector TraceStart, const FVector TraceEnd);
	void GetPlayerViewPoint(FVector& TraceStart, FVector& TraceEnd);
	void SpecialShotRestore();

	AMainCharacter* Player = Cast<AMainCharacter>(GetOwner());;

	FVector GetMuzzleWorldLocation();
};