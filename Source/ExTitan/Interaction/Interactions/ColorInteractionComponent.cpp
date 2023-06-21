// Fill out your copyright notice in the Description page of Project Settings.
#include "Interaction/Interactions/ColorInteractionComponent.h"
#include "Agent/AgentBase.h"



UColorInteractionComponent::UColorInteractionComponent()
{
	InteractionText = FText::FromString("Color");
	MaxUses = 1;
}

void UColorInteractionComponent::OnReachLocation()
{
	if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(OccupyingAgent->GetCapsuleMesh()->GetMaterial(0)))
	{
		Material->SetVectorParameterValue(FName("Color"), Color);
	}

	EndInteractionProcess();
}