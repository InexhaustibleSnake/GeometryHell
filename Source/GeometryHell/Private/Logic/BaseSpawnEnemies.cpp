// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Logic/BaseSpawnEnemies.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MainCharacter.h"
#include "Enemy/BaseEnemy.h"
#include "GameFramework/Actor.h"


ABaseSpawnEnemies::ABaseSpawnEnemies()
{
	PrimaryActorTick.bCanEverTick = false;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
}

void ABaseSpawnEnemies::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseSpawnEnemies::OnPlayerOverlap);
}

void ABaseSpawnEnemies::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!GetWorld() && !OtherActor->IsA(AMainCharacter::StaticClass())) return;

	for (const TPair<AActor*, TSubclassOf<ABaseEnemy>>& Pair : SpawnData)
	{
		FTransform SpawnTransForm = Pair.Key->GetTransform();

		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActorDeferred<ABaseEnemy>(Pair.Value, SpawnTransForm);

		if (SpawnedEnemy)
		{
			SpawnedEnemy->FinishSpawning(SpawnTransForm);
		}
	}
	Destroy();
}

//void ABaseSpawnEnemies::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	const auto Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//	if (!GetWorld() && !OtherActor->IsA(AMainCharacter::StaticClass()) && !Enemy) return;
//
//	for (const auto Point : PointToSpawn)
//	{
//		FTransform SpawnTransform = Point->GetTransform();
//		auto Point = SpawnData.Find(AActor::StaticClass());
//
//		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActorDeferred<ABaseEnemy>(Enemy, SpawnTransform);
//		if (SpawnedEnemy)
//		{
//			SpawnedEnemy->FinishSpawning(SpawnTransform);
//		}
//	}
//	Destroy();
//}
