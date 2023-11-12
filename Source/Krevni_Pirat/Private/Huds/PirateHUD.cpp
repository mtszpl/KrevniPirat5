// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDs/PirateHUD.h"
#include "../../Public/Widgets/AimingWidget.h"
#include "Blueprint/UserWidget.h"

void APirateHUD::BeginPlay()
{
	if (IsValid(AimWidgetClass))
	{
		AimWidget = CreateWidget<UAimingWidget>(GetWorld(), AimWidgetClass);
		AimWidget->AddToViewport();
		AimWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APirateHUD::StartAiming()
{
	AimWidget->SetVisibility(ESlateVisibility::Visible);
}

void APirateHUD::StopAiming()
{
	AimWidget->SetVisibility(ESlateVisibility::Hidden);
}
