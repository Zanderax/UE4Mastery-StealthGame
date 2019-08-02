// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "FPSGameState.h"
#include "UObject/ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bIsMissionSuccessful)
{
	if (!InstigatorPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AFPSGameMode::CompleteMission - No InstigatorPawn"))
		return;
	}

	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if (GS)
	{
		GS->MulticastOnMissionComplete(InstigatorPawn, bIsMissionSuccessful);
	}

	OnMissionCompleted(InstigatorPawn, bIsMissionSuccessful);

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

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		APlayerController* PC = It->Get();
		if (!PC)
		{
			UE_LOG(LogTemp, Warning, TEXT("AFPSGameMode::CompleteMission - No PlayerController"))
			continue;
		}
		PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
	}
	
}
