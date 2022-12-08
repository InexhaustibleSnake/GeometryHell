// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/Bosses/FinalBoss.h"
#include "Projectiles/BaseProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Enemy/Components/BaseAIPerceptionComponent.h"
#include "Character/MainCharacter.h"
#include "EngineUtils.h"

AFinalBoss::AFinalBoss()
{
	LaserShootPoint = CreateDefaultSubobject<USceneComponent>("LaserShootPoint");
	LaserShootPoint->SetupAttachment(GetRootComponent());
}

void AFinalBoss::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimeStopTimer, this, &AFinalBoss::StopTime, TimeStopRate, true, 2.0f);
}

void AFinalBoss::LaserAttack()
{
	const auto AIPerception = Cast<UBaseAIPerceptionComponent>(GetController());
	if (!HasEnemy) return;

	const FTransform SpawnTransform(FRotator::ZeroRotator, LaserShootPoint->GetComponentLocation());

	ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(LaserProjectile, SpawnTransform);

	if (Projectile)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ShootAudio, GetActorLocation());
		Projectile->SetShotDirection(LaserShootPoint->GetForwardVector());
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
}

float AFinalBoss::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void AFinalBoss::StopTime()
{
	auto Player = GetPlayer();
	if (!Player) return;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	for (auto FoundActor : FoundActors)
	{
		if (FoundActor == this) continue;

		FoundActor->CustomTimeDilation = 0.001f;

		TimeStop.Broadcast(true);
		GetWorldTimerManager().SetTimer(RestoreTimeTimer, this, &AFinalBoss::RestoreTime, TimeStopDuration, false, TimeStopDuration);
		Player->InBossTimeStop = true;
	}
}

void AFinalBoss::RestoreTime()
{
	auto Player = GetPlayer();
	if (!Player) return;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	for (auto FoundActor : FoundActors)
	{
		if (FoundActor == this) continue;

		FoundActor->CustomTimeDilation = 1.0f;
	}

	LaserAttack();
	TimeStop.Broadcast(false);
	Player->InBossTimeStop = false;
}

AMainCharacter* AFinalBoss::GetPlayer()
{
	return Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}