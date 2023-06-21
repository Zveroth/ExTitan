// Fill out your copyright notice in the Description page of Project Settings.
#include "Interaction/InteractionsManagerComponent.h"
#include "Interaction/InteractionBaseComponent.h"
#include "UI/HUDBase.h"
#include "UI/Widgets/ListWidget.h"
#include "Agent/AgentHandlingSubsystem.h"



// Sets default values for this component's properties
UInteractionsManagerComponent::UInteractionsManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInteractionsManagerComponent::RegisterInteraction(UInteractionBaseComponent* Interaction)
{
	m_Interactions.Add(Interaction);
}

void UInteractionsManagerComponent::UnregisterInteraction(UInteractionBaseComponent* Interaction)
{
	m_Interactions.Remove(Interaction);
}

void UInteractionsManagerComponent::OnClicked()
{
	APlayerController* const  PlayerController = GetWorld()->GetFirstPlayerController();
	if (!IsValid(PlayerController))
	{
		return;
	}

	AHUDBase* const HUD = PlayerController->GetHUD<AHUDBase>();
	if (!IsValid(HUD))
	{
		return;
	}

	TArray<FListWidgetEntryData> Options = GetInteractionUIOptions();
	if (Options.Num() <= 0)
	{
		return;
	}

	HUD->DisplayListWidget(Options, [](int32 SelectedOption, UObject* Payload)
		{
			UInteractionBaseComponent* const Interaction = Cast<UInteractionBaseComponent>(Payload);
			if (!IsValid(Interaction))
			{
				return;
			}

			if (Interaction->IsOccupied())
			{
				Interaction->BreakInteractionProcess();
				return;
			}

			UAgentHandlingSubsystem* const AgentSubsystem = UWorld::GetSubsystem<UAgentHandlingSubsystem>(Interaction->GetWorld());

			Interaction->BeginInteractionProcess(AgentSubsystem->GetFirstAvailableAgent());
		});
}

TArray<FListWidgetEntryData> UInteractionsManagerComponent::GetInteractionUIOptions() const
{
	TArray<FListWidgetEntryData> InteractionTexts;
	InteractionTexts.Reserve(m_Interactions.Num());

	UAgentHandlingSubsystem* const AgentSubsystem = UWorld::GetSubsystem<UAgentHandlingSubsystem>(GetWorld());
	if (AgentSubsystem->AnyAgentAvailable())
	{
		for (UInteractionBaseComponent* const Interaction : m_Interactions)
		{
			if (Interaction->CanBeUsed())
			{
				InteractionTexts.Add({ Interaction->GetInteractionText(), Interaction });
			}
		}
	}
	else
	{
		for (UInteractionBaseComponent* const Interaction : m_Interactions)
		{
			if (Interaction->IsOccupied())
			{
				InteractionTexts.Add({ Interaction->GetInteractionText(), Interaction });
			}
		}
	}

	return InteractionTexts;
}