// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Pickups/HealthPickup.h"
#include "Character/MainCharacter.h"
#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

bool AHealthPickup::GivePickupTo(AMainCharacter* PlayerCharacter)
{
	auto MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	auto HealthComponent = MainCharacter->FindComponentByClass<UHealthComponent>();
	
	if (!HealthComponent) return false;
	
	return HealthComponent->TryToAddHealth(HealAmount);
}
