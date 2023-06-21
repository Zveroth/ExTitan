// Fill out your copyright notice in the Description page of Project Settings.
#include "Agent/AgentBase.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Agent/AgentHandlingSubsystem.h"



// Sets default values
AAgentBase::AAgentBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CapsuleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CapsuleMesh"));
	CapsuleMesh->SetupAttachment(RootComponent);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAgentBase::OverrideBehavior(UBehaviorTree* Behavior)
{
	AAIController* const AIController = GetController<AAIController>();
	if (IsValid(AIController))
	{
		AIController->RunBehaviorTree(Behavior);
	}
}

void AAgentBase::ClearBehaviorOverride()
{
	SetupBehaviorTree();
}

void AAgentBase::BeginPlay()
{
	Super::BeginPlay();

	SetupBehaviorTree();

	UAgentHandlingSubsystem* const AgentSubsystem = UWorld::GetSubsystem<UAgentHandlingSubsystem>(GetWorld());
	AgentSubsystem->RegisterAgent(this);

	CapsuleMesh->CreateDynamicMaterialInstance(0);
}

void AAgentBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UAgentHandlingSubsystem* const AgentSubsystem = UWorld::GetSubsystem<UAgentHandlingSubsystem>(GetWorld());
	AgentSubsystem->UnregisterAgent(this);
}

void AAgentBase::SetIsBusy(bool bInBusy)
{
	if (m_bBusy != bInBusy)
	{
		m_bBusy = bInBusy;

		OnAgentBusyStateChanged.ExecuteIfBound(this);
	}
}

void AAgentBase::SetupBehaviorTree()
{
	if (DefaultBehaviorTree.IsNull())
	{
		return;
	}

	AAIController* const AIController = GetController<AAIController>();
	if (IsValid(AIController))
	{
		AIController->RunBehaviorTree(DefaultBehaviorTree.LoadSynchronous());
	}
}