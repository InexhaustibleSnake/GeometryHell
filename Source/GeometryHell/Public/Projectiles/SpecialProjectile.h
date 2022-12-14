// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/BaseProjectile.h"
#include "SpecialProjectile.generated.h"



UCLASS()
class GEOMETRYHELL_API ASpecialProjectile : public ABaseProjectile
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
		int32 MaxHittedEnemies = 6;

	AActor* HittedActor = nullptr;
	virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;

};
