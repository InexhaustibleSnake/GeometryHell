// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Pickups/BasePickup.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Character/MainCharacter.h"
#include "Components/StaticMeshComponent.h"

ABasePickup::ABasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	SetRootComponent(CollisionComponent);
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	StaticMeshComponent->SetupAttachment(CollisionComponent);
}

void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Player = Cast<AMainCharacter>(OtherActor);


	if (GivePickupTo(Player))
	{
		PickupWasTaken();
	}
}

bool ABasePickup::GivePickupTo(AMainCharacter* PlayerCharacter)
{
	return false;
}

void ABasePickup::PickupWasTaken()
{
	GetRootComponent()->SetHiddenInGame(true, true);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	

	GetWorldTimerManager().SetTimer(PickupTimer, this, &ABasePickup::Respawn, RespawnTime);
}

void ABasePickup::Respawn()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	GetRootComponent()->SetHiddenInGame(false, true);
}

