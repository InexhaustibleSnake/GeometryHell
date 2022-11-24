// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/MainCharacter.h"
#include "BasePickup.generated.h"


class USphereComponent;
class USoundCue;
class UStaticMeshComponent;

UCLASS()
class GEOMETRYHELL_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePickup();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
		USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Pickup")
		float RespawnTime = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundCue* PickupTakenSound;

private:
	virtual bool GivePickupTo(AMainCharacter* PlayerCharacter);
	void PickupWasTaken();
	void Respawn();

	FTimerHandle PickupTimer;
	float RotationYaw;


};

