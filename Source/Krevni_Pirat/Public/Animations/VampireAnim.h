// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VampireAnim.generated.h"

class AVampireController;
class AVampire;

/**
 * 
 */
UCLASS()
class KREVNI_PIRAT_API UVampireAnim : public UAnimInstance
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsDead;

	UPROPERTY()
	TObjectPtr<AVampireController> Controller;

	UPROPERTY()
	TObjectPtr<AVampire> Vamp;

protected:

	void NativeBeginPlay() override;

	void NativeUpdateAnimation(float deltaSeconds) override;

	UFUNCTION()
	void Die();
};
