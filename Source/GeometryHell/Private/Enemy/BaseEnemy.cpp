// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/BaseEnemy.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectiles/BaseProjectile.h"
#include "Components/SceneComponent.h"
#include "Enemy/Components/BaseAIPerceptionComponent.h"
#include "AIController.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Logic/BaseGameMode.h"
#include "Enemy/AI/BaseAIController.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CannonCube = CreateDefaultSubobject<UStaticMeshComponent>("CannonCube");
	CannonCube->SetupAttachment(GetRootComponent());
	
	ShootPoint = CreateDefaultSubobject<USceneComponent>("ShootPoint");
	ShootPoint->SetupAttachment(CannonCube);

	HealthTextRender = CreateDefaultSubobject<UTextRenderComponent>("HealthTextRender");
	HealthTextRender->SetupAttachment(GetRootComponent());

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ABaseEnemy::StartFire, FireRate, true, 0.0f);

	OnTakeAnyDamage.AddDynamic(this, &ABaseEnemy::OnTakeDamage);
	HealthTextRender->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ABaseEnemy::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	HealthTextRender->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
	if (Health <= 0)
	{
		auto GameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		GameMode->UpdateEnemyInFight(-1);

		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DeathSound, GetOwner()->GetActorLocation());
		Destroy();
		return;
	}
	HasEnemy = true;
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DamagedSound, GetOwner()->GetActorLocation());
	UpdateControllerInfo();
}

void ABaseEnemy::StartFire()
{
	const auto AIPerception = Cast<UBaseAIPerceptionComponent>(GetController());
	if (!HasEnemy) return;

	const FTransform SpawnTransform(FRotator::ZeroRotator, ShootPoint->GetComponentLocation());

	ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(MainProjectile, SpawnTransform);

	if (Projectile)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ShootAudio, GetActorLocation());
		Projectile->SetShotDirection(ShootPoint->GetForwardVector());
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}


}

void ABaseEnemy::UpdateControllerInfo()
{
	ABaseAIController* AIController = Cast<ABaseAIController>(GetController());

	AIController->OnOwnerDamaged();
}