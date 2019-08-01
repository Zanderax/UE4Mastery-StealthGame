// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* ArrowMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, Category = "Force")
	float CharacterHorizontalForceScale = 400;

	UPROPERTY(EditAnywhere, Category = "Force")
	float CharacterVerticalForceScale = 1000;

	UPROPERTY(EditAnywhere, Category = "Force")
	float StaticMeshHorizontalForceScale = 50000;

	UPROPERTY(EditAnywhere, Category = "Force")
	float StaticMeshVerticalForceScale = 200000;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* JumpFX;
};
