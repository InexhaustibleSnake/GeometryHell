// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Logic/BaseSetPlayingOst.h"
#include "Logic/BaseGameMode.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

ABaseSetPlayingOst::ABaseSetPlayingOst()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
}

void ABaseSetPlayingOst::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseSetPlayingOst::OnPlayerOverlap);
}

void ABaseSetPlayingOst::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto GameMode = Cast<ABaseGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	GameMode->AudioComponent->SetSound(NewOst);
	Destroy();
}