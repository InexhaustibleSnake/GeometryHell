// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class GEOMETRYHELL_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseProjectile();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }
	void SetDamage(float NewDamage) { Damage = NewDamage; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properities")
		float Damage = 10.0f;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properities")
		float LifeSpan = 5.0f;

	FVector ShotDirection;
    
	UFUNCTION()
		virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
};
