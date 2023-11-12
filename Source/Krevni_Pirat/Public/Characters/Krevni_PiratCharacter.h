// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Krevni_PiratCharacter.generated.h"

class ASword;
class AGun;

UCLASS(config=Game)
class AKrevni_PiratCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		FVector CameraAimingOffset;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

#pragma region Weapons

	UPROPERTY(EditAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASword> SwordClass;

	UPROPERTY(EditAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AGun> GunClass;

	UPROPERTY(VisibleAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
		USceneComponent* SwordAttach;

	UPROPERTY(VisibleAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
		USceneComponent* SwordHand;

	UPROPERTY(VisibleAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
		USceneComponent* GunAttach;

	UPROPERTY(VisibleAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
		USceneComponent* GunHand;

	UPROPERTY()
		ASword* Sword;

	UPROPERTY()
		AGun* Gun;

#pragma endregion

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsArmed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsAiming = false;

	bool bIsAttacking = false;

#pragma region Animations
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* SheathSwordMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* DrawSwordMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> SwordAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* DrawGunMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* SheathGunMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* GunFireMontage;

#pragma endregion


	FTimerHandle SwordMoveHandle;
	FTimerHandle GunMoveHandle;
	FTimerHandle AttackHandle;

	float SwordAnimTime = 0;
	float GunAnimTime = 0;

	UFUNCTION()
		void SwordGrab();

	UFUNCTION()
		void SwordLeave();

	UFUNCTION()
		void GunGrab();

	UFUNCTION()
		void GunLeave();

	UFUNCTION()
		void AfterSwordAttack();

	UFUNCTION()
		void AfterGunFire();

public:
	AKrevni_PiratCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	void ToggleArmed();

	void StartAiming();

	void StopAiming();

	void Attack();

#pragma region Getters
	bool GetIsArmed();

	bool GetIsAiming();
#pragma endregion


protected:

	void BeginPlay() override;

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

