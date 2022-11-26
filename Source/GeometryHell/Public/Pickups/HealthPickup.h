// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "HealthPickup.generated.h"


 
UCLASS()
class GEOMETRYHELL_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float HealAmount = 30.0f;

private:
      virtual bool GivePickupTo(AMainCharacter* PlayerCharacter) override;
};
