// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Vampire.generated.h"

class UCapsuleComponent;
class UFloatingPawnMovement;

UCLASS()
class KREVNI_PIRAT_API AVampire : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> Collider;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> Movement;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 Hp = 50;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 AttackPower = 10;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 CorpseRemainTime = 10;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> AttackMontages;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;

	DECLARE_MULTICAST_DELEGATE(OnDeathDelegate);

public:
	// Sets default values for this pawn's properties
	AVampire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
	void Attack();

	void GetHit(int32 damage);

	void Die();

	OnDeathDelegate OnDeath;
};
