// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/Widgets/ListEntryWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"



void UListEntryWidget::SetOptionText(const FText& InText) 
{
	OptionText->SetText(InText); 
}

void UListEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OptionButton->OnClicked.AddDynamic(this, &UListEntryWidget::OnButtonClicked);
}

void UListEntryWidget::OnButtonClicked()
{
	OnEntryClicked.ExecuteIfBound(this);
}