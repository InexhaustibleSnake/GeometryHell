// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

class UCameraShakeBase;
class USoundCue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYHELL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	float GetHealthPercentage() const;

	bool TryToAddHealth(float Amount);
	bool IsHealthFull() const;

	UPROPERTY(BlueprintAssignable)
		FOnDeath OnDeath;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* HittedSound;

	UFUNCTION()
		void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

private:
	void PlayCameraShake();
	void SetHealth(float Amount);

};
