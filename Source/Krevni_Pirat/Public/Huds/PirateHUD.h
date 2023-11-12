// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PirateHUD.generated.h"

class UAimingWidget;

/**
 * 
 */
UCLASS()
class KREVNI_PIRAT_API APirateHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UAimingWidget> AimWidgetClass;

	UPROPERTY()
	TObjectPtr<UAimingWidget> AimWidget;

protected:
	void BeginPlay() override;

public:
	void StartAiming();

	void StopAiming();
};
