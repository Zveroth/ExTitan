// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ListWidget.generated.h"



class UVerticalBox;
class UListEntryWidget;

struct FListWidgetEntryData
{
	FListWidgetEntryData(const FText& InText, UObject* InPayload) : Text(InText), Payload(InPayload) {}

	FText Text;
	UObject* Payload;
};

UCLASS()
class EXTITAN_API UListWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void SetSelectionCallback(const TFunction<void(int32, UObject*)>& InCallback) { SelectionCallback = InCallback; }
	void SetOptions(const TArray<FListWidgetEntryData>& InOptions);

protected:

	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:

	void OnEntryClicked(UListEntryWidget* Entry);

	void RefreshLocation();

protected:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* OptionsBox;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UListEntryWidget> EntryClass;

private:

	TFunction<void(int32, UObject*)> SelectionCallback;
};