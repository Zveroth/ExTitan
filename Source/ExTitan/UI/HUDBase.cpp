// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/HUDBase.h"
#include "UI/Widgets/ListWidget.h"



void AHUDBase::DisplayListWidget(const TArray<FListWidgetEntryData>& InOptions, const TFunction<void(int32, UObject*)>& InCallback)
{
	UListWidget* const ListWidget = CreateWidget<UListWidget>(GetOwningPlayerController(), ListWidgetClass);

	ListWidget->SetSelectionCallback(InCallback);
	ListWidget->SetOptions(InOptions);

	ListWidget->AddToViewport();
}