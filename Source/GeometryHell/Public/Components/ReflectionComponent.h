// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ReflectionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYHELL_API UReflectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UReflectionComponent();

	void Reflection(bool Active);

protected:
	virtual void BeginPlay() override;

	FTimerHandle ReflectionTimer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Reflection")
	    float ReflectionStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Reflection")
	    float MaxReflectionStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Reflection")
	    float ReflectionPower = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Reflection")
		float ReflectionRestoreTimer = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Reflection")
		float ReflectionReduceTimer = 0.1f;


	void ReduceReflectionStamina();
	void RestoreReflectionStamina();
	bool IsReflectionStaminaEmpty() const;
	bool IsReflectionStaminaFull() const;

private:
		
};
