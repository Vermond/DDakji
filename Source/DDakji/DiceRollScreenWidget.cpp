// Fill out your copyright notice in the Description page of Project Settings.

#include "DiceRollScreenWidget.h"

#include "DDakjiPlayerController.h"

#include "Engine/Texture2D.h"
#include "TimerManager.h"

UDiceRollScreenWidget::UDiceRollScreenWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	GetDiceImageAsync();

	totalTime = 0;
	changeTime = .1f;
}

void UDiceRollScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	totalTime += InDeltaTime;

	if (totalTime > changeTime)
	{
		totalTime = 0;

		ChangeDiceImage();
	}
}

void UDiceRollScreenWidget::SetDiceImage(UImage* image, UImage* image2, UImage* image3)
{
	diceImage1 = image;
	diceImage2 = image2;
	diceImage3 = image3;
}

void UDiceRollScreenWidget::ChangeDiceImage()
{
	//랜덤
	//https://msdn.microsoft.com/ko-kr/library/windows/desktop/398ax69y.aspx
	int r;

	if (bEnableDiceRoll1)
	{
		r = (double)rand() / (RAND_MAX + 1) * 5;
		diceImage1->SetBrush(brushes[r]);

		r = (double)rand() / (RAND_MAX + 1) * 5;
		diceImage2->SetBrush(brushes[r]);

		r = (double)rand() / (RAND_MAX + 1) * 5;
		diceImage3->SetBrush(brushes[r]);
	}

	UE_LOG(LogTemp, Warning, TEXT("ChangeDiceImage : %f"), changeTime);
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

void UDiceRollScreenWidget::SubmitPower()
{
	//버튼 클릭시 주사위 최종 값을 결정한다
	resultDice1Power = (double)rand() / (RAND_MAX + 1) * 5;

	//버튼 클릭시 주사위 변하는 속도를 조금씩 낮춘다
	//tempDelegate.BindUFunction(this, FName("SetUI"), targetWidget, showCursor);
	timerDelegate.BindUFunction(this, FName("DecreaseRollTime"));
	GetWorld()->GetTimerManager().SetTimer(timerHandle, timerDelegate, 3, true);
}

void UDiceRollScreenWidget::DecreaseRollTime()
{
	changeTime *= 2;
	UE_LOG(LogTemp, Warning, TEXT("DecreaseRollTime"));

	if (changeTime > 0.5f)
	{
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		StopAndGo();
	}
}

void UDiceRollScreenWidget::StopAndGo()
{
	bEnableDiceRoll1 = false;
	UE_LOG(LogTemp, Warning, TEXT("Result Power %d"), resultDice1Power + 1);

	//실제 값으로 멈추도록 변경해야 한다
	diceImage1->SetBrush(brushes[resultDice1Power]);
	
	//싱글에서만 동작할 것으로 예상된다. 수정 필요함
	ADDakjiPlayerController* pc = (ADDakjiPlayerController*)GWorld->GetFirstPlayerController();
	pc->ChangeUIByPhase(Phase::Result);
}
