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
	GenerateRotationYaw();
}

void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (!OtherActor->IsA(AMainCharacter::StaticClass())) return;

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
	
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PickupTakenSound, GetActorLocation());
	
	GetWorldTimerManager().SetTimer(PickupTimer, this, &ABasePickup::Respawn, RespawnTime);
}

void ABasePickup::Respawn()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	GetRootComponent()->SetHiddenInGame(false, true);
}

void ABasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}