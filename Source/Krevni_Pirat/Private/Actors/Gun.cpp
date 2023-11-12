// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Gun.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"

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
	DrawDebugSphere(GetWorld(), Camera->GetComponentLocation() + Camera->GetForwardVector() * 10000, 10, 48, FColor::Cyan, false, 10);
	DrawDebugLine(GetWorld(), FirePoint->GetComponentLocation(), Camera->GetComponentLocation() + Camera->GetForwardVector() * 1000, FColor::Red, false, 10);
	if(GetWorld()->LineTraceSingleByChannel(Hit, FirePoint->GetComponentLocation(), Camera->GetComponentLocation() + Camera->GetForwardVector() * 1000, ECollisionChannel::ECC_Visibility))
	{
		//GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, Hit.Actor->GetName());
		if(IsValid(HitEffect))
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.ImpactPoint);
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}