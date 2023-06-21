// Fill out your copyright notice in the Description page of Project Settings.
#include "Interaction/InteractionBaseComponent.h"
#include "Interaction/Interactable.h"
#include "Interaction/InteractionsManagerComponent.h"
#include "Agent/AgentBase.h"



// Sets default values for this component's properties
UInteractionBaseComponent::UInteractionBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UInteractionBaseComponent::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	IInteractable* const Interactable = Cast<IInteractable>(GetOwner());
	if (!ensureMsgf(Interactable, TEXT("UInteractionBaseComponent: Attached to %s which isn't an interactable!"), *GetOwner()->GetName()))
	{
		return;
	}
#endif

	RegisterInteraction();
}

UInteractionsManagerComponent* UInteractionBaseComponent::GetOwnerInteractionsManager() const
{
	IInteractable* const Interactable = Cast<IInteractable>(GetOwner());
	return Interactable->GetInteractionsManager();
}

void UInteractionBaseComponent::RegisterInteraction()
{
	UInteractionsManagerComponent* InteractionsManager = GetOwnerInteractionsManager();
	InteractionsManager->RegisterInteraction(this);
}

void UInteractionBaseComponent::UnregisterInteraction()
{
	UInteractionsManagerComponent* InteractionsManager = GetOwnerInteractionsManager();
	InteractionsManager->UnregisterInteraction(this);
}

void UInteractionBaseComponent::BeginInteractionProcess(AAgentBase* InteractingAgent)
{
	if (!IsValid(InteractingAgent))
	{
		return;
	}

	ensureMsgf(!InteractingAgent->IsBusy(), TEXT("UInteractionBaseComponent: Starting interaction with an already busy agent!"));

	OccupyingAgent = InteractingAgent;

	OccupyingAgent->SetIsBusy(true);

	BeginInteraction_Implementation();
}

void UInteractionBaseComponent::BreakInteractionProcess()
{
	if (IsValid(OccupyingAgent))
	{
		OccupyingAgent->SetIsBusy(false);
	}

	BreakInteraction_Implementation(OccupyingAgent);

	OccupyingAgent = nullptr;
}

void UInteractionBaseComponent::EndInteractionProcess()
{
	if (MaxUses > 0)
	{
		--MaxUses;
	}

	if (IsValid(OccupyingAgent))
	{
		OccupyingAgent->SetIsBusy(false);
	}

	EndInteraction_Implementation(OccupyingAgent);

	OccupyingAgent = nullptr;
}

bool UInteractionBaseComponent::IsOccupied() const
{
	return IsValid(OccupyingAgent);
}