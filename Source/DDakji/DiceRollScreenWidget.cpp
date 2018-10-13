// Fill out your copyright notice in the Description page of Project Settings.

#include "DiceRollScreenWidget.h"

#include "DDakjiPlayerController.h"
#include "DDakjiGameMode.h"
#include "MyStaticLibrary.h"
#include "Engine/Texture2D.h"

/////////////////////////////////////////
//DiceRepeat 클래스 구현
/////////////////////////////////////////
DiceRepeat::DiceRepeat() : DiceRepeat(.1f, 3, true)
{
}

DiceRepeat::DiceRepeat(float diceRoll, float rollSlow, bool bEnableRoll = true)
	: diceRollTime(diceRoll), rollSlowTime(rollSlow), bEnableDiceRoll(bEnableRoll), resultDiceNum(0)
{
}

void DiceRepeat::SetTimer(const UObject* object, FTimerHandle& timerHandle, FTimerDelegate& timerDelegate, float changeTime)
{
	GEngine->GetWorldFromContextObjectChecked(object)->GetTimerManager().SetTimer(timerHandle, timerDelegate, changeTime, true);
}

void DiceRepeat::ClearTimer(const UObject* object, FTimerHandle& timerHandle)
{
	GEngine->GetWorldFromContextObjectChecked(object)->GetTimerManager().PauseTimer(timerHandle);
}


///////////////////////////////////////////
//UDiceRollScreenWidget 클래스 구현
///////////////////////////////////////////
UDiceRollScreenWidget::UDiceRollScreenWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	GetDiceImageAsync();

	diceRepeats.Add(DiceRepeat(.1f, 3));
	diceRepeats.Add(DiceRepeat(.1f, 3));
	diceRepeats.Add(DiceRepeat(.1f, 3));

	rollSlowTimerDelegates.Add(FTimerDelegate());
	rollSlowTimerDelegates.Add(FTimerDelegate());
	rollSlowTimerDelegates.Add(FTimerDelegate());

	diceRollDelegates.Add(FTimerDelegate());
	diceRollDelegates.Add(FTimerDelegate());
	diceRollDelegates.Add(FTimerDelegate());
	
	startBrush.TintColor = FLinearColor::White;
	decreasingBrush.TintColor = FLinearColor::Yellow;
	stopBrush.TintColor = FLinearColor::Black;
}

void UDiceRollScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < diceRepeats.Num(); ++i)
	{
		diceRollDelegates[i].BindUFunction(this, FName("ChangeDiceImage"), i);
		diceRepeats[i].SetTimer(this, diceRepeats[i].GetDiceRollHandle(), diceRollDelegates[i], diceRepeats[i].GetDiceRollTime());
	}	
}

void UDiceRollScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UDiceRollScreenWidget::SetDiceImage(UImage* image, UImage* image2, UImage* image3)
{
	diceRepeats[0].SetDiceImage(image);
	diceRepeats[1].SetDiceImage(image2);
	diceRepeats[2].SetDiceImage(image3);
}

void UDiceRollScreenWidget::SetBorder(UBorder* val1, UBorder* val2, UBorder* val3)
{
	val1->SetBrush(startBrush);
	val2->SetBrush(startBrush);
	val3->SetBrush(startBrush);

	diceRepeats[0].SetBorder(val1);
	diceRepeats[1].SetBorder(val2);
	diceRepeats[2].SetBorder(val3);
}

void UDiceRollScreenWidget::ChangeDiceImage(int32 itemNum)
{
	//랜덤
	//https://msdn.microsoft.com/ko-kr/library/windows/desktop/398ax69y.aspx

	//배열 길이 넘어가면 체크하는거 넣어놓자
	
	if (diceRepeats[itemNum].GetEnableRoll())
	{
		int r = (double)rand() / (RAND_MAX + 1) * 5;
		diceRepeats[itemNum].GetDiceImage()->SetBrush(diceBrushes[r]);
	}
}

void UDiceRollScreenWidget::GetDiceImageAsync()
{
	//https://docs.unrealengine.com/ko-kr/Programming/Assets/AsyncLoading

	// 주사위 이미지 에셋 비동기로 얻기
	if (!ObjectLibrary)
	{
		ObjectLibrary = UObjectLibrary::CreateLibrary(TSubclassOf<class UTexture2D>(), false, GIsEditor);
		ObjectLibrary->AddToRoot();
	}

	ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/Resources"));
	if (bFullyLoad)
	{
		ObjectLibrary->LoadAssetsFromAssetData();
	}
		
	//이미지 개수 충족 시에 브러시 준비
	if (ObjectLibrary->GetAssetDataCount() >= 6)
	{
		TArray<FAssetData> assetDataList;
		ObjectLibrary->GetAssetDataList(assetDataList);

		for (int i = 0; i < assetDataList.Num(); i++)
		{
			FSlateBrush brush;
			brush.SetResourceObject(assetDataList[i].GetAsset());
			brush.ImageSize = FVector2D(128, 128);
			diceBrushes.Add(brush);
		}
	}
}

void UDiceRollScreenWidget::RequestStopDice(int32 itemNum)
{	
	diceRepeats[itemNum].GetBorder()->SetBrush(decreasingBrush);
	//주사위 수는 이미 결정을 해놓는다
	diceRepeats[itemNum].SetDiceNum((double)rand() / (RAND_MAX + 1) * 5);
		
	rollSlowTimerDelegates[itemNum].BindUFunction(this, FName("SlowerRollTime"), itemNum);
	diceRepeats[itemNum].SetTimer(this, diceRepeats[itemNum].GetRollSlowHandle(), rollSlowTimerDelegates[itemNum], diceRepeats[itemNum].GetRollSlowTime());
}

void UDiceRollScreenWidget::SlowerRollTime(int32 itemNum)
{
	diceRepeats[itemNum].SetDiceRollTime(diceRepeats[itemNum].GetDiceRollTime() * 2);
	diceRepeats[itemNum].SetRollSlowTime(diceRepeats[itemNum].GetRollSlowTime() / 2);

	if (diceRepeats[itemNum].GetDiceRollTime() > 0.5f)
	{
		diceRepeats[itemNum].ClearTimer(this, diceRepeats[itemNum].GetDiceRollHandle());
		diceRepeats[itemNum].ClearTimer(this, diceRepeats[itemNum].GetRollSlowHandle());
		StopAndGo(itemNum);
	}
	else
	{
		diceRepeats[itemNum].SetTimer(this, diceRepeats[itemNum].GetDiceRollHandle(), diceRollDelegates[itemNum], diceRepeats[itemNum].GetDiceRollTime());
		diceRepeats[itemNum].SetTimer(this, diceRepeats[itemNum].GetRollSlowHandle(), rollSlowTimerDelegates[itemNum], diceRepeats[itemNum].GetRollSlowTime());
	}
}

void UDiceRollScreenWidget::StopAndGo(int32 itemNum)
{
	diceRepeats[itemNum].SetEnableRoll(false);
	diceRepeats[itemNum].GetBorder()->SetBrush(stopBrush);
	diceRepeats[itemNum].GetDiceImage()->SetBrush(diceBrushes[diceRepeats[itemNum].GetDiceNum()]);

	bool bResult = true;
	int32 diceSum = 0;

	for(DiceRepeat item : diceRepeats)
	{
		bResult = bResult && !item.GetEnableRoll();
		diceSum += item.GetDiceNum();
	}

	if (bResult)
	{
		//결과를 볼 시간을 제공하기 위해 타이머로 딜레이를 만듬
		screenWaitTimerDelegate.BindUFunction(this, FName("ChangeScreen"), diceSum);
		GetWorld()->GetTimerManager().SetTimer(screenWaitTimerHandle, screenWaitTimerDelegate, 1, false);
	}
}

void UDiceRollScreenWidget::ChangeScreen(int32 diceSum)
{
	ADDakjiGameMode* gamemode = UMyStaticLibrary::GetGameMode(this);
	ADDakjiPlayerController* pc = (ADDakjiPlayerController*)GWorld->GetFirstPlayerController();
	gamemode->SetDicePower(diceSum);
	gamemode->ChangePhase(Phase::Result);
}