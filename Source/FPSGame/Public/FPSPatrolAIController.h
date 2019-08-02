// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "FPSPatrolAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSPatrolAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFPSPatrolAIController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
protected:

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void MoveToNextLocation();

	int CurrentTargetPoint;
};
