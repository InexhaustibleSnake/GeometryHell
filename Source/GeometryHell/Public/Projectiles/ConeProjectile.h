// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/BaseProjectile.h"
#include "ConeProjectile.generated.h"

UCLASS()
class GEOMETRYHELL_API AConeProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
		int32 MaxHittedEnemies = 25;

	virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;
};
