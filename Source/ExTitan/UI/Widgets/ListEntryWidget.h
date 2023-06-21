// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ListEntryWidget.generated.h"



class UButton;
class UTextBlock;

UCLASS()
class EXTITAN_API UListEntryWidget : public UUserWidget
{
	GENERATED_BODY()


	DECLARE_DELEGATE_OneParam(FListEntryEvent, UListEntryWidget*);

public:

	void SetOptionText(const FText& InText);
	void SetPayload(UObject* InPayload) { m_Payload  = InPayload; }

	UObject* GetPayload() const { return m_Payload; }

protected:

	virtual void NativeOnInitialized() override;

private:

	UFUNCTION()
	void OnButtonClicked();

public:

	FListEntryEvent OnEntryClicked;

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OptionText;

private:

	UPROPERTY()
	UObject* m_Payload;
};