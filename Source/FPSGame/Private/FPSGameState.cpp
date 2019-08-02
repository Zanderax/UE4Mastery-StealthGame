// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"

#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bIsMissionSuccessful)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		if (PC && PC->IsLocalController())
		{
			// Complete Mission
			PC->OnMissionComplete(InstigatorPawn, bIsMissionSuccessful);

			// Disbale Input
			APawn* MyPawn = PC->GetPawn();
			if (MyPawn)
			{
				MyPawn->DisableInput(nullptr);
			}
		}
	}
}
