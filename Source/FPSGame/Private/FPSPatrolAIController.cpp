// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPatrolAIController.h"

#include "FPSAIGuard.h"

AFPSPatrolAIController::AFPSPatrolAIController()
{
	CurrentTargetPoint = -1;
}

void AFPSPatrolAIController::BeginPlay()
{
	Super::BeginPlay();

	MoveToNextLocation();
}

void AFPSPatrolAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	MoveToNextLocation();
}

void AFPSPatrolAIController::MoveToNextLocation()
{
	AFPSAIGuard* AIGuardPawn = Cast<AFPSAIGuard>(GetPawn());

	if (!AIGuardPawn)
	{
		return;
	}

	if (AIGuardPawn->TargetPoints.Num() == 0)
	{
		return;
	}

	CurrentTargetPoint++;

	if (CurrentTargetPoint == AIGuardPawn->TargetPoints.Num())
	{
		CurrentTargetPoint = 0;
	}

	MoveToActor(AIGuardPawn->TargetPoints[CurrentTargetPoint]);
}