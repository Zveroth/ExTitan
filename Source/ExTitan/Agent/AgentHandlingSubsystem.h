// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AgentHandlingSubsystem.generated.h"



class AAgentBase;

UCLASS()
class EXTITAN_API UAgentHandlingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	

public:

	bool AnyAgentAvailable() const;
	AAgentBase* GetFirstAvailableAgent() const;

	void RegisterAgent(AAgentBase* InAgent);
	void UnregisterAgent(AAgentBase* InAgent);

private:

	void OnAgentBusyStateChanged(AAgentBase* InAgent);

private:

	UPROPERTY()
	TSet<AAgentBase*> AvailableAgents;
	UPROPERTY()
	TSet<AAgentBase*> BusyAgents;
};