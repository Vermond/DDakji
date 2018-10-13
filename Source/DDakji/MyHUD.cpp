// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"

#include "DDakjiGameMode.h"
#include "MyStaticLibrary.h"

#include "UserWidget.h"
#include "TimerManager.h"

void AMyHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ADDakjiGameMode* gameMode = UMyStaticLibrary::GetGameMode(this);
	if (gameMode) gameMode->PhaseChangeDelegate.AddUObject(this, &AMyHUD::ChangeUI);
}

void AMyHUD::ChangeUI(Phase phase)
{
	switch (phase)
	{
	case Main:
		SetUI(mainUIWidget);
		break;
	case Select:
		SetUI(selectUIWidget);
		break;
	case Start:
		SetUI(startUIWidget);
		break;
	case Target:
		SetUIDelayed(targetUIWidget);
		break;
	case Powering:
		SetUIDelayed(powerUIWidget);
		break;
	case Result:
		SetUIDelayed(resultUIWidget);
		break;
	default:
		break;
	}
}

void AMyHUD::SetUI(TSubclassOf<class UUserWidget> targetWidget, bool showCursor)
{
	if (nullptr != currentUI)
	{
		currentUI->RemoveFromViewport();
		currentUI = nullptr;
	}

	if (nullptr != targetWidget)
	{
		//첫번째 인자로 UWorld&, APlayerController 등을 넣어줘야됨
		//자세한거는 doc 참고
		currentUI = CreateWidget<UUserWidget>(GetWorld(), targetWidget);
		currentUI->AddToViewport();
		//bShowMouseCursor = showCursor;
	}
}

void AMyHUD::SetUIDelayed(TSubclassOf<class UUserWidget> targetWidget, bool showCursor)
{
	if (nullptr != currentUI)
	{
		currentUI->RemoveFromViewport();
		currentUI = nullptr;
	}

	FTimerDelegate tempDelegate;
	FTimerHandle TimerHandle;

	//타이머를 이용해 화면 전환 시간동안 UI 출력을 지연시킨다
	tempDelegate.BindUFunction(this, FName("SetUI"), targetWidget, showCursor);

	GetWorldTimerManager().SetTimer(TimerHandle, tempDelegate, .75f, false);
}
