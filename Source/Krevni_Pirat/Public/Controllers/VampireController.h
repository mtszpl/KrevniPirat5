// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VampireController.generated.h"

class AVampire;
class UBehaviorTree;

/**
 * 
 */
UCLASS()
class KREVNI_PIRAT_API AVampireController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccesss = "true"))
	float AttackCooldownTime = 3;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccesss = "true"))
	TObjectPtr<UBehaviorTree > VampBT;

	UPROPERTY()
	TObjectPtr<AVampire> Vamp;
	
protected:
	void BeginPlay() override;

public:

	void Attack();
};
