// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bIsMissionSuccessful)
{
	if (!InstigatorPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AFPSGameMode::CompleteMission - No InstigatorPawn"))
		return;
	}

	OnMissionCompleted(InstigatorPawn, bIsMissionSuccessful);
	InstigatorPawn->DisableInput(nullptr);

	if (!SpectatingViewpointClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AFPSGameMode::CompleteMission - No SpectatingViewpointClass"))
		return;
	}
		
	AActor* NewViewTarget;
	TArray<AActor*> ReturnedActors;
	UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

	if (ReturnedActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AFPSGameMode::CompleteMission - No SpectatingViewpoints Found"))
		return;
	}
	NewViewTarget = ReturnedActors[0];

	APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
	if (!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("AFPSGameMode::CompleteMission - No PlayerController"))
		return;
	}
	PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
}
