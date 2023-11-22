// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UCameraComponent;

UCLASS()
class KREVNI_PIRAT_API AGun : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> FirePoint;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> HitEffect;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 Range = 1000;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 Damage = 50;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float ReloadTime;

	float RemainingReload;

	bool bIsReloading = false;
	
public:	
	AGun();

	void Fire(UCameraComponent* Camera);

	float GetReloadTime();
};
