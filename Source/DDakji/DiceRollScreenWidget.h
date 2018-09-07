// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateBrush.h"
#include "Image.h"
#include "Engine/ObjectLibrary.h"
#include "DiceRollScreenWidget.generated.h"

/**
 *
 */
UCLASS()
class DDAKJI_API UDiceRollScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDiceRollScreenWidget(const FObjectInitializer& objectInitializer);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Widget")
		void SetDiceImage(UImage* image, UImage* image2, UImage* image3);
	UFUNCTION(BlueprintCallable, Category = "Widget")
		void ChangeDiceImage();
	UFUNCTION(BlueprintCallable, Category = "Widget")
		void SubmitPower();

private:
	UFUNCTION()
		void DecreaseRollTime();

	void GetDiceImageAsync();
	void StopAndGo();

protected:
	UImage* diceImage1;
	UImage* diceImage2;
	UImage* diceImage3;

private:
	float totalTime;
	float changeTime;

	TArray<FSlateBrush> brushes;

	UObjectLibrary* ObjectLibrary = nullptr;
	bool bFullyLoad = false;

	FTimerDelegate timerDelegate;
	FTimerHandle timerHandle;

	bool bEnableDiceRoll1 = true;
	int resultDice1Power;
};
