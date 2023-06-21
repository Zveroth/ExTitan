// Fill out your copyright notice in the Description page of Project Settings.
#include "Interaction/Interactions/BehaviorInteractionComponent.h"
#include "Agent/AgentBase.h"

#include "BehaviorTree/BehaviorTree.h"



UBehaviorInteractionComponent::UBehaviorInteractionComponent()
{
	InteractionText = FText::FromString("Behavior");
}

void UBehaviorInteractionComponent::OnReachLocation()
{
	OccupyingAgent->OverrideBehavior(Behavior.LoadSynchronous());
}

void UBehaviorInteractionComponent::BreakInteraction_Implementation(AAgentBase* InAgent)
{
	Super::BreakInteraction_Implementation(InAgent);

	InAgent->ClearBehaviorOverride();
}