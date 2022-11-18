// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class UBehaviorTree;
class UBaseHealthBarWidget;
class UTextRenderComponent;
class UStaticMeshComponent;

UCLASS()
class GEOMETRYHELL_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseEnemy();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* CannonCube;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBaseHealthBarWidget* BaseHealthBarWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* HealthTextRender;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properities")
		float Health = 100.0f;

   UFUNCTION()
	  void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
