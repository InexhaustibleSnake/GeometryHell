// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSetPlayingOst.generated.h"

class UBoxComponent;
class USoundCue;

UCLASS()
class GEOMETRYHELL_API ABaseSetPlayingOst : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseSetPlayingOst();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USoundCue* NewOst;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxComponent;

	UFUNCTION()
		virtual void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
