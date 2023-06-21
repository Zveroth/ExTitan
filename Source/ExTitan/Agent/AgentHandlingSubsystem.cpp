// Fill out your copyright notice in the Description page of Project Settings.
#include "Agent/AgentHandlingSubsystem.h"
#include "Agent/AgentBase.h"



bool UAgentHandlingSubsystem::AnyAgentAvailable() const
{
	return AvailableAgents.Num() > 0;
}

AAgentBase* UAgentHandlingSubsystem::GetFirstAvailableAgent() const
{
	for (AAgentBase* Agent : AvailableAgents)
	{
		ensure(IsValid(Agent));

		return Agent;
	}

	return nullptr;
}

void UAgentHandlingSubsystem::RegisterAgent(AAgentBase* InAgent)
{
	InAgent->OnAgentBusyStateChanged.BindUObject(this, &UAgentHandlingSubsystem::OnAgentBusyStateChanged);

	if (InAgent->IsBusy())
	{
		BusyAgents.Add(InAgent);
	}
	else
	{
		AvailableAgents.Add(InAgent);
	}
}

void UAgentHandlingSubsystem::UnregisterAgent(AAgentBase* InAgent)
{
	InAgent->OnAgentBusyStateChanged.Unbind();
}

void UAgentHandlingSubsystem::OnAgentBusyStateChanged(AAgentBase* InAgent)
{
	if (InAgent->IsBusy())
	{
		AvailableAgents.Remove(InAgent);
		BusyAgents.Add(InAgent);
	}
	else
	{
		AvailableAgents.Add(InAgent);
		BusyAgents.Remove(InAgent);
	}
}