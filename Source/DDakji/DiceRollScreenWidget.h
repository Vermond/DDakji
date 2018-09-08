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
	virtual void NativeConstruct();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Widget")
		void SetDiceImage(UImage* image, UImage* image2, UImage* image3);
	UFUNCTION(BlueprintCallable, Category = "Widget")
		void ChangeDiceImage(int32 itemNum);
	UFUNCTION(BlueprintCallable, Category = "Widget")
		void SubmitPower(int32 itemNum);

private:
	UFUNCTION()
		void DecreaseRollTime(int32 itemNum);

	void GetDiceImageAsync();
	void StopAndGo(int32 itemNum);

protected:
	UImage* diceImage1;
	UImage* diceImage2;
	UImage* diceImage3;


private:
	float totalTime;
	float changeTime;
	float changeTime2;
	float changeTime3;

	TArray<FSlateBrush> brushes;

	UObjectLibrary* ObjectLibrary = nullptr;
	bool bFullyLoad = false;

	FTimerHandle decreasePowerTimerHandle;
	FTimerHandle decreasePowerTimerHandle2;
	FTimerHandle decreasePowerTimerHandle3;
	FTimerDelegate decreasePowerTimerDelegate;
	FTimerDelegate decreasePowerTimerDelegate2;
	FTimerDelegate decreasePowerTimerDelegate3;

	FTimerHandle diceRepeatTimerHandle1;
	FTimerHandle diceRepeatTimerHandle2;
	FTimerHandle diceRepeatTimerHandle3;
	FTimerDelegate diceRepeatTimerDelegate1;
	FTimerDelegate diceRepeatTimerDelegate2;
	FTimerDelegate diceRepeatTimerDelegate3;

	bool bEnableDiceRoll1 = true;
	bool bEnableDiceRoll2 = true;
	bool bEnableDiceRoll3 = true;
	int resultDice1Power;
	int resultDice2Power;
	int resultDice3Power;
};
