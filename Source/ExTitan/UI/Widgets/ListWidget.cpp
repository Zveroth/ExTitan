// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/Widgets/ListWidget.h"
#include "UI/Widgets/ListEntryWidget.h"

#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Input/Reply.h"



void UListWidget::SetOptions(const TArray<FListWidgetEntryData>& InOptions)
{
	if (!ensure(EntryClass))
	{
		return;
	}

	OptionsBox->ClearChildren();

	for (const FListWidgetEntryData& Option : InOptions)
	{
		UListEntryWidget* Entry = CreateWidget<UListEntryWidget>(this, EntryClass);
		Entry->SetOptionText(Option.Text);
		Entry->SetPayload(Option.Payload);
		Entry->OnEntryClicked.BindUObject(this, &UListWidget::OnEntryClicked);

		OptionsBox->AddChildToVerticalBox(Entry)->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	}
}

void UListWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RefreshLocation();
}

FReply UListWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent).IsEventHandled())
	{
		return FReply::Handled();
	}

	RemoveFromParent();

	return FReply::Handled();
}

void UListWidget::OnEntryClicked(UListEntryWidget* Entry)
{
	const int32 ChildIndex = OptionsBox->GetChildIndex(Entry);

	SelectionCallback(ChildIndex, Entry->GetPayload());

	RemoveFromParent();
}

void UListWidget::RefreshLocation()
{
	APlayerController* const PlayerController = GetWorld()->GetFirstPlayerController();
	if (!IsValid(PlayerController))
	{
		return;
	}

	UCanvasPanelSlot* const CanvasSlot = Cast<UCanvasPanelSlot>(OptionsBox->Slot);
	if (!ensureMsgf(IsValid(CanvasSlot), TEXT("UListWidget: OptionsBox has to be directly attached to a canvas")))
	{
		return;
	}

	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

	FIntPoint ViewportSize;
	PlayerController->GetViewportSize(ViewportSize.X, ViewportSize.Y);

	const FVector2D MousePositionNormalized(MousePosition.X / ViewportSize.X, MousePosition.Y / ViewportSize.Y);

	CanvasSlot->SetAnchors(FAnchors(MousePositionNormalized.X, MousePositionNormalized.Y));
}