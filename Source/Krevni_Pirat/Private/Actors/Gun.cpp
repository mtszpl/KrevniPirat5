// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gun.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "../../Public/Characters/Vampire.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	FirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(Mesh);
}

void AGun::Fire(UCameraComponent* Camera)
{
	FHitResult Hit;
	if(GetWorld()->LineTraceSingleByChannel(Hit, Camera->GetComponentLocation(), Camera->GetComponentLocation() + Camera->GetForwardVector() * Range, ECollisionChannel::ECC_Visibility))
	{
		if(IsValid(HitEffect))
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.ImpactPoint);
		AVampire* Vamp = Cast<AVampire>(Hit.GetActor());
		if (IsValid(Vamp))
			Vamp->GetHit(Damage);
	}
	RemainingReload = ReloadTime;
	bIsReloading = true;
}

float AGun::GetReloadTime()
{
	return ReloadTime;
}
