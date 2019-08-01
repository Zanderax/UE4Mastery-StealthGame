// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"

#include "FPSCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "Engine/StaticMeshActor.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	RootComponent = BaseMeshComp;

	ArrowMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMeshComp"));
	ArrowMeshComp->SetupAttachment(BaseMeshComp);

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetupAttachment(BaseMeshComp);

	
}

void AFPSLaunchPad::NotifyActorBeginOverlap(AActor* OtherActor)
{
	FRotator CurrentRotation = GetActorRotation();
	FVector Roll, Pitch, Yaw;
	UKismetMathLibrary::BreakRotIntoAxes(CurrentRotation, Roll, Pitch, Yaw);

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if(MyCharacter)
	{
		float LaunchX = Roll.X * CharacterHorizontalForceScale;
		float LaunchY = Roll.Y * CharacterHorizontalForceScale;
		MyCharacter->LaunchCharacter({ LaunchX, LaunchY, CharacterVerticalForceScale }, false, false);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), JumpFX, GetActorLocation());
		return;
	}

	AStaticMeshActor* MyStaticMeshActor = Cast<AStaticMeshActor>(OtherActor);
	if (MyStaticMeshActor)
	{
		float LaunchX = Roll.X * StaticMeshHorizontalForceScale;
		float LaunchY = Roll.Y * StaticMeshHorizontalForceScale;
		MyStaticMeshActor->GetStaticMeshComponent()->AddForce({ LaunchX, LaunchY, StaticMeshVerticalForceScale }, "None", true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), JumpFX, GetActorLocation());
		return;
	}
}
