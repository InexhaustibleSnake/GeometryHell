// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Enemy/UI/BaseHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UBaseHealthBarWidget::SetHealthPercent(float Percent)
{
	if (!HealthProgressBar) return;

	const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold) ? ESlateVisibility::Hidden : ESlateVisibility::Visible;

	HealthProgressBar->SetVisibility(HealthBarVisibility);

	const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

	HealthProgressBar->SetPercent(Percent);
}
