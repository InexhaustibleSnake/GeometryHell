// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Projectiles/ConeProjectile.h"

void AConeProjectile::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	OtherActor->TakeDamage(Damage, FDamageEvent{}, nullptr, this);

	if ((MaxHittedEnemies -= 1) == 0)
	{
		Destroy();
	}
}