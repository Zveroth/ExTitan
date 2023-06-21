// Fill out your copyright notice in the Description page of Project Settings.
#include "Interaction/Interactions/MoveToInteractionComponent.h"
#include "Agent/AgentBase.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"



void UMoveToInteractionComponent::BeginInteraction_Implementation()
{
	AAIController* const AIController = OccupyingAgent->GetController<AAIController>();

	if (!IsValid(AIController))
	{
		EndInteractionProcess();
		return;
	}

	UBlackboardComponent* const Blackboard = AIController->GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		EndInteractionProcess();
		return;
	}

	AIController->ReceiveMoveCompleted.AddDynamic(this, &UMoveToInteractionComponent::OnMoveCompleted);
	Blackboard->SetValueAsObject(FName("TargetActor"), GetOwner());
}

void UMoveToInteractionComponent::BreakInteraction_Implementation(AAgentBase* InAgent)
{
	AAIController* const AIController = InAgent->GetController<AAIController>();

	if (!IsValid(AIController))
	{
		return;
	}

	AIController->ReceiveMoveCompleted.RemoveDynamic(this, &UMoveToInteractionComponent::OnMoveCompleted);
	AIController->StopMovement();

	UBlackboardComponent* const Blackboard = AIController->GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		return;
	}

	Blackboard->ClearValue(FName("TargetActor"));
}

void UMoveToInteractionComponent::EndInteraction_Implementation(AAgentBase* InAgent)
{
	AAIController* const AIController = InAgent->GetController<AAIController>();

	if (!IsValid(AIController))
	{
		return;
	}

	UBlackboardComponent* const Blackboard = AIController->GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		return;
	}

	Blackboard->ClearValue(FName("TargetActor"));
}

void UMoveToInteractionComponent::OnReachLocation()
{
	EndInteractionProcess();
}

void UMoveToInteractionComponent::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (Result != EPathFollowingResult::Success)
	{
		return;
	}

	if (AAIController* const AIController = OccupyingAgent->GetController<AAIController>())
	{
		AIController->ReceiveMoveCompleted.RemoveDynamic(this, &UMoveToInteractionComponent::OnMoveCompleted);
	}

	OnReachLocation();
}