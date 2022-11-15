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

	void UltraReflectionOn();
	void UltraReflectionOff();

protected:
	virtual void BeginPlay() override;

	FTimerHandle ReflectionTimer;

	FTimerHandle UltraReflectionTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Reflection")
	    float ReflectionStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Reflection")
	    float MaxReflectionStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Reflection")
	    float ReflectionPower = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Reflection")
		float ReflectionRestoreRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Reflection")
		float ReflectionReduceRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UltraReflection")
		float UltraReflectionPower = 0.05f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UltraReflection")
		float UltraReflectionReduceRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UltraReflection")
		float PlayerDilationOnUltra = 2.0f;

	void ReduceReflectionStamina();
	void ReduceUltraReflectionStamina();
	void RestoreReflectionStamina();

	bool IsReflectionStaminaEmpty() const;
	bool IsReflectionStaminaFull() const;

	AActor* GetPlayerActor() const;
};
