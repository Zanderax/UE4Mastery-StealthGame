// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackhole.h"

#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

#include "Engine/StaticMeshActor.h"

// Sets default values
AFPSBlackhole::AFPSBlackhole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GravityComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = GravityComp;

	EventHorizon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EventHorizon"));
	EventHorizon->SetupAttachment(GravityComp);
}

// Called when the game starts or when spawned
void AFPSBlackhole::BeginPlay()
{
	Super::BeginPlay();
	EventHorizon->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackhole::OnEnterEventHorizon);
}

// Called every frame
void AFPSBlackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> GravityAffectedComponents;
	GravityComp->GetOverlappingComponents(GravityAffectedComponents);
	for (UPrimitiveComponent* GravityAffectedComponent : GravityAffectedComponents)
	{
		if (GravityAffectedComponent && GravityAffectedComponent->IsSimulatingPhysics())
		{
			// Pulls actors inwards
			GravityAffectedComponent->AddRadialForce(GetActorLocation(), GravityComp->GetUnscaledSphereRadius(), -GravityStrength, ERadialImpulseFalloff::RIF_Constant, true);
			// Gets actors up off the ground and gives their paths a little wobble
			GravityAffectedComponent->AddForce({ 0,0,100 }, "None", true);
		}
	}
}

void AFPSBlackhole::OnEnterEventHorizon(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

