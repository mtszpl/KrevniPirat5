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
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		USceneComponent* FirePoint;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UParticleSystem* HitEffect;

	
public:	
	AGun();

	void Fire(UCameraComponent* Camera);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
