// Fill out your copyright notice in the Description page of Project Settings.

#include "DiceRollScreenWidget.h"

#include "DDakjiPlayerController.h"
#include "DDakjiGameModeBase.h"
#include "MyStaticLibrary.h"
#include "Engine/Texture2D.h"
#include "TimerManager.h"

UDiceRollScreenWidget::UDiceRollScreenWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	GetDiceImageAsync();

	totalTime = 0;
	changeTime = .1f;
	changeTime2 = .1f;
	changeTime3 = .1f;

	resultDice1Power = 0;
	resultDice2Power = 0;
	resultDice3Power = 0;

	bEnableDiceRoll1 = true;
	bEnableDiceRoll2 = true;
	bEnableDiceRoll3 = true;
}

void UDiceRollScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	diceRepeatTimerDelegate1.BindUFunction(this, FName("ChangeDiceImage"), 1);
	GetWorld()->GetTimerManager().SetTimer(diceRepeatTimerHandle1, diceRepeatTimerDelegate1, changeTime, true);

	diceRepeatTimerDelegate2.BindUFunction(this, FName("ChangeDiceImage"), 2);
	GetWorld()->GetTimerManager().SetTimer(diceRepeatTimerHandle2, diceRepeatTimerDelegate2, changeTime, true);

	diceRepeatTimerDelegate3.BindUFunction(this, FName("ChangeDiceImage"), 3);
	GetWorld()->GetTimerManager().SetTimer(diceRepeatTimerHandle3, diceRepeatTimerDelegate3, changeTime, true);
}

void UDiceRollScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UDiceRollScreenWidget::SetDiceImage(UImage* image, UImage* image2, UImage* image3)
{
	diceImage1 = image;
	diceImage2 = image2;
	diceImage3 = image3;
}

void UDiceRollScreenWidget::ChangeDiceImage(int32 itemNum)
{
	//랜덤
	//https://msdn.microsoft.com/ko-kr/library/windows/desktop/398ax69y.aspx
	int r;

	if (bEnableDiceRoll1 && itemNum == 1)
	{
		r = (double)rand() / (RAND_MAX + 1) * 5;
		diceImage1->SetBrush(brushes[r]);
	}
	if (bEnableDiceRoll2 && itemNum == 2)
	{
		r = (double)rand() / (RAND_MAX + 1) * 5;
		diceImage2->SetBrush(brushes[r]);
	}
	if (bEnableDiceRoll3 && itemNum == 3)
	{
		r = (double)rand() / (RAND_MAX + 1) * 5;
		diceImage3->SetBrush(brushes[r]);
	}
}

void UDiceRollScreenWidget::GetDiceImageAsync()
{
	//https://docs.unrealengine.com/ko-kr/Programming/Assets/AsyncLoading

	// 주사위 이미지 비동기로 얻기
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
			brushes.Add(brush);
		}
	}
}

void UDiceRollScreenWidget::SubmitPower(int32 itemNum)
{
	int* rp;
	FTimerDelegate* td;
	FTimerHandle* th;

	switch (itemNum)
	{
	case 1:
		rp = &resultDice1Power;
		td = &decreasePowerTimerDelegate;
		th = &decreasePowerTimerHandle;
		break;
	case 2:
		rp = &resultDice2Power;
		td = &decreasePowerTimerDelegate2;
		th = &decreasePowerTimerHandle2;
		break;
	case 3:
		rp = &resultDice3Power;
		td = &decreasePowerTimerDelegate3;
		th = &decreasePowerTimerHandle3;
		break;
	default:
		//그냥 종료해버린다.
		//로그는 임시로 넣었으니 적절한 구문으로 변경하자
		UE_LOG(LogTemp, Warning, TEXT("SubmitPower got wrong power"));
		return;
	}

	//버튼 클릭시 주사위 최종 값을 결정한다
	*rp = (double)rand() / (RAND_MAX + 1) * 5;

	//버튼 클릭시 주사위 변하는 속도를 조금씩 낮춘다
	td->BindUFunction(this, FName("DecreaseRollTime"), itemNum);
	GetWorld()->GetTimerManager().SetTimer(*th, *td, 3, true);
}

void UDiceRollScreenWidget::DecreaseRollTime(int32 itemNum)
{
	float* ct;
	FTimerHandle* th;
	FTimerHandle* repeatHandle;
	FTimerDelegate* repeatDel;


	switch (itemNum)
	{
	case 1:
		ct = &changeTime;
		th = &decreasePowerTimerHandle;
		repeatHandle = &diceRepeatTimerHandle1;
		repeatDel = &diceRepeatTimerDelegate1;
		break;
	case 2:
		ct = &changeTime2;
		th = &decreasePowerTimerHandle2;
		repeatHandle = &diceRepeatTimerHandle2;
		repeatDel = &diceRepeatTimerDelegate2;
		break;
	case 3:
		ct = &changeTime3;
		th = &decreasePowerTimerHandle3;
		repeatHandle = &diceRepeatTimerHandle3;
		repeatDel = &diceRepeatTimerDelegate3;
		break;
	default:
		//아무것도 안함
		return;
	}

	*ct *= 2;
	GetWorld()->GetTimerManager().ClearTimer(*repeatHandle);

	UE_LOG(LogTemp, Warning, TEXT("DecreaseRollTime %d %f"), itemNum, *ct);

	if (*ct > 0.5f)
	{
		GetWorld()->GetTimerManager().ClearTimer(*th);
		StopAndGo(itemNum);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(*repeatHandle, *repeatDel, *ct, true);
	}
}

void UDiceRollScreenWidget::StopAndGo(int32 itemNum)
{
	UImage* dice;
	int* dicePower;

	switch (itemNum)
	{
	case 1:
		bEnableDiceRoll1 = false;
		dicePower = &resultDice1Power;
		dice = diceImage1;
		break;
	case 2:
		bEnableDiceRoll2 = false;
		dicePower = &resultDice2Power;
		dice = diceImage2;
		break;
	case 3:
		bEnableDiceRoll3 = false;
		dicePower = &resultDice3Power;
		dice = diceImage3;
		break;
	default:
		//아무것도 안함
		return;
	}

	//실제 값으로 멈추도록 변경해야 한다
	dice->SetBrush(brushes[*dicePower]);

	//싱글에서만 동작할 것으로 예상된다. 수정 필요함
	if (!bEnableDiceRoll1 && !bEnableDiceRoll2 && !bEnableDiceRoll3)
	{
		ADDakjiGameModeBase* gamemode = UMyStaticLibrary::GetGameMode();
		ADDakjiPlayerController* pc = (ADDakjiPlayerController*)GWorld->GetFirstPlayerController();
		gamemode->SetDicePower(resultDice1Power + resultDice2Power + resultDice3Power);
		pc->ChangeUIByPhase(Phase::Result);
	}

	UE_LOG(LogTemp, Warning, TEXT("Result Power %d %d %d"), resultDice1Power + 1, resultDice2Power + 1, resultDice3Power + 1);
}
