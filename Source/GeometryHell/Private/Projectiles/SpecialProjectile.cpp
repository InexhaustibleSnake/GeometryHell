// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Projectiles/SpecialProjectile.h"

void ASpecialProjectile::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

	if (HittedActor == OtherActor) return;

	OtherActor->TakeDamage(Damage, FDamageEvent{}, nullptr, this);

	if ((MaxHittedEnemies -= 1) == 0)
	{
		Destroy();
	}
	HittedActor = OtherActor;
}
