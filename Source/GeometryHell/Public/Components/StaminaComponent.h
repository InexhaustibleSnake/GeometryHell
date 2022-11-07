// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYHELL_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStaminaComponent();

	void Sprint();
	void StopSprinting();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float SprintSpeed = 1200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float WalkSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float StaminaRecoverRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float StaminaReduceRate = 0.1f;

	FTimerHandle StaminaTimer;

	void StaminaReduce();
	void StaminaRecover();
	bool IsStaminaFull() const;
	bool IsStaminaEmpty() const;


};
