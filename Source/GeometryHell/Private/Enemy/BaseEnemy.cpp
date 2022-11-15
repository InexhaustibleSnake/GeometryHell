// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/BaseEnemy.h"
#include "Enemy/UI/BaseHealthBarWidget.h"
#include "Components/TextRenderComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	
	HealthTextRender = CreateDefaultSubobject<UTextRenderComponent>("HealthTextRender");
	HealthTextRender->SetupAttachment(GetRootComponent());
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &ABaseEnemy::OnTakeDamage);
	HealthTextRender->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
	
}

void ABaseEnemy::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	HealthTextRender->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
	if (Health == 0) Destroy();
}