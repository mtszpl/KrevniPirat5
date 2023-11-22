// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Krevni_PiratCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ASword;
class AGun;

UCLASS(config=Game)
class AKrevni_PiratCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FVector CameraAimingOffset;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

#pragma region Weapons

	UPROPERTY(EditAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASword> SwordClass;

	UPROPERTY(EditAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGun> GunClass;

	UPROPERTY(VisibleAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SwordAttach;

	UPROPERTY(VisibleAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SwordHand;

	UPROPERTY(VisibleAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> GunAttach;

	UPROPERTY(VisibleAnywhere, Category = Weapons, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> GunHand;

	UPROPERTY()
	TObjectPtr<ASword> Sword;

	UPROPERTY()
	TObjectPtr<AGun> Gun;

#pragma endregion

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsArmed = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsAiming = false;

	bool bIsAttacking = false;

#pragma region Animations
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> SheathSwordMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DrawSwordMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> SwordAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DrawGunMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> SheathGunMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animations, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> GunFireMontage;

#pragma endregion


	FTimerHandle SwordMoveHandle;
	FTimerHandle GunMoveHandle;
	FTimerHandle AttackHandle;

	float SwordDrawTime = 0;
	float GunDrawTime = 0;
	float SwordSheathTime = 0;
	float GunSheathTime = 0;

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

