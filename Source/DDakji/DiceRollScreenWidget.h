// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateBrush.h"
#include "Image.h"
#include "Engine/ObjectLibrary.h"
#include "Border.h"
#include "TimerManager.h"
#include "DiceRollScreenWidget.generated.h"

//개별 주사위 타이머를 위한 클래스
class DiceRepeat
{
public:
	DiceRepeat();
	DiceRepeat(float diceRoll, float rollSlow, bool bEnableRoll);

	void SetTimer(const UObject* object, FTimerHandle& timerHandle, FTimerDelegate& timerDelegate, float changeTime);
	void ClearTimer(const UObject* object, FTimerHandle& timerHandle);

public:
	float GetDiceRollTime() { return diceRollTime; }
	float GetRollSlowTime() { return rollSlowTime; }
	FTimerHandle& GetDiceRollHandle() { return diceRollHandle; }
	FTimerHandle& GetRollSlowHandle() { return rollSlowHandle; }
	UImage* GetDiceImage() { return diceImage; }
	UBorder* GetBorder() { return border; }
	bool GetEnableRoll() { return bEnableDiceRoll; }
	int GetDiceNum() { return resultDiceNum; }

	void SetDiceRollTime(float value) { diceRollTime = value; }
	void SetRollSlowTime(float value) { rollSlowTime = value; }
	void SetDiceImage(UImage* value) { diceImage = value; }
	void SetBorder(UBorder* value) { border = value; }
	void SetEnableRoll(bool value) { bEnableDiceRoll = value; }
	void SetDiceNum(int value) { resultDiceNum = value; }
private:
	float diceRollTime;
	float rollSlowTime;

	FTimerHandle diceRollHandle;
	FTimerHandle rollSlowHandle;

	UImage* diceImage;
	UBorder* border;

	bool bEnableDiceRoll;
	int resultDiceNum;
};


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

	//주사위 개수를 늘릴 경우에는 함수 인자를 배열로 변경하자
	UFUNCTION(BlueprintCallable, Category = "Widget")
		void SetDiceImage(UImage* image, UImage* image2, UImage* image3);
	UFUNCTION(BlueprintCallable, Category = "Widget")
		void SetBorder(UBorder* val1, UBorder* val2, UBorder* val3);

	UFUNCTION(BlueprintCallable, Category = "Widget")
		void RequestStopDice(int32 itemNum);
	UFUNCTION()
		void ChangeDiceImage(int32 itemNum);
	UFUNCTION()
		void ChangeScreen(int32 diceSum);
private:
	UFUNCTION()
		void SlowerRollTime(int32 itemNum);

	void GetDiceImageAsync();
	void StopAndGo(int32 itemNum);

private:
	TArray<FSlateBrush> diceBrushes;

	UObjectLibrary* ObjectLibrary = nullptr;
	bool bFullyLoad = false;

	FSlateBrush startBrush;
	FSlateBrush decreasingBrush;
	FSlateBrush stopBrush;
	   
	TArray<FTimerDelegate> rollSlowTimerDelegates;
	TArray<FTimerDelegate> diceRollDelegates;
	TArray<DiceRepeat> diceRepeats;

	FTimerDelegate screenWaitTimerDelegate;
	FTimerHandle screenWaitTimerHandle;
};
