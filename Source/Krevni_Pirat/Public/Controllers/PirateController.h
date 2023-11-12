// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "PirateController.generated.h"

class APirateHUD;

/**
 * 
 */
UCLASS()
class KREVNI_PIRAT_API APirateController : public APlayerController
{
	GENERATED_BODY()

#pragma region InputActions
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UInputAction* LookAction;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UInputAction* RotateAction;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UInputAction* DrawWeaponAction;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UInputAction* AimAction;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UInputAction* AttackAction;

#pragma endregion

#pragma region InputSignals



	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsJumping = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsFalling = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsShooting = false;
#pragma endregion

	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = "true"))
		float MouseXSensitivity = 10;

	UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowPrivateAccess = "true"))
		float MouseYSensitivity = 10;

	UPROPERTY()
		APirateHUD* HUD;
		
	void SetupInput();

#pragma region Inputs

	UFUNCTION()
		void Move(const FInputActionValue& Value);

	UFUNCTION()
		void Look(const FInputActionValue& Value);

	UFUNCTION()
		void Rotate(const FInputActionValue& Value);

	UFUNCTION()
		void Jump();

	UFUNCTION()
		void StartFalling();

	UFUNCTION()
		void OnCharacterFallDown(const FHitResult& Hit);
#pragma endregion

	UFUNCTION()
		void Attack();

	UFUNCTION()
		void ToggleArmed();

	UFUNCTION()
		void StartAiming();

	UFUNCTION()
		void StopAiming();
protected:
	void BeginPlay() override;

public:

#pragma region Getters
	bool GetIsJumping();

	bool GetIsFalling();
#pragma endregion

};
