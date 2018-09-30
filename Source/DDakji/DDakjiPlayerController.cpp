// Fill out your copyright notice in the Description page of Project Settings.

#include "DDakjiPlayerController.h"

#include "DDakjiGameMode.h"
#include "MyStaticLibrary.h"

#include "UserWidget.h"
#include "EngineUtils.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UnrealString.h"
#include "TimerManager.h"

#include "DrawDebugHelpers.h"

ADDakjiPlayerController::ADDakjiPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADDakjiPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//변수 이동으로 인한 임시조치
	ADDakjiGameMode* gameMode = UMyStaticLibrary::GetGameMode(this);
	mainUIWidget = gameMode->mainUIWidget;
	selectUIWidget = gameMode->selectUIWidget;
	startUIWidget = gameMode->startUIWidget;
	targetUIWidget = gameMode->targetUIWidget;
	powerUIWidget = gameMode->powerUIWidget;
	resultUIWidget = gameMode->resultUIWidget;

	//SetUI(mainUIWidget);

	gameMode->testDelegate.BindUObject(this, &ADDakjiPlayerController::TestReceive);
}

void ADDakjiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	for (TActorIterator<ACameraDirector> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		cameraDirector = *ActorItr;
		break;
	}
}

void ADDakjiPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADDakjiPlayerController::TestReceive(Phase phase)
{
	UE_LOG(LogTemp, Warning, TEXT("ADDakjiPlayerController TestReceive"));

	switch (phase)
	{
	case Main:
		SetUI(mainUIWidget);
		break;
	case Select:
		SetUI(selectUIWidget);
		break;
	case Start:
		//카메라 원위치
		cameraDirector->ChangeCamera(1);

		SetUI(startUIWidget);
		break;
	case Target:
		//딱지치기를 위한 상단으로 카메라 이동
		cameraDirector->ChangeCamera(2);

		SetUIDelayed(targetUIWidget);
		break;
	case Powering:
		cameraDirector->ChangeCamera(3);

		SetUIDelayed(powerUIWidget);
		break;
	case Result:
		cameraDirector->ChangeCamera(4);

		SetUIDelayed(resultUIWidget);
		break;
	default:
		break;
	}
}

/*
void ADDakjiPlayerController::ChangeUIByPhase(Phase phase)
{
	//페이즈 변경 처리를 임시로 이 함수에서 수행한다
	//적절한 위치 결정하면 꼭 옮기자
	ADDakjiGameMode* gameMode = UMyStaticLibrary::GetGameMode(this);
	gameMode->SetCurrentPhase(phase);
	
	switch (phase)
	{
	case Main:
		SetUI(mainUIWidget);
		break;
	case Select:
		SetUI(selectUIWidget);
		break;
	case Start:
		//카메라 원위치
		cameraDirector->ChangeCamera(1);

		SetUI(startUIWidget);
		break;
	case Target:
		//딱지치기를 위한 상단으로 카메라 이동
		cameraDirector->ChangeCamera(2);
		
		SetUIDelayed(targetUIWidget);
		break;
	case Powering:
		cameraDirector->ChangeCamera(3);

		SetUIDelayed(powerUIWidget);
		break;
	case Result:
		cameraDirector->ChangeCamera(4);

		SetUIDelayed(resultUIWidget);
		break;
	default:
		break;
	}
}*/

void ADDakjiPlayerController::SetUI(TSubclassOf<class UUserWidget> targetWidget, bool showCursor)
{
	if (nullptr != currentUI)
	{
		currentUI->RemoveFromViewport();
		currentUI = nullptr;
	}

	if (nullptr != targetWidget)
	{		
		currentUI = CreateWidget<UUserWidget>(this, targetWidget);
		currentUI->AddToViewport();
		bShowMouseCursor = showCursor;
	}
}

void ADDakjiPlayerController::SetUIDelayed(TSubclassOf<class UUserWidget> targetWidget, bool showCursor)
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

//이 함수 사용하는지 확인하고 지워도 되면 지우기
//쓸거면 GetMousePosition에 맞춰서 bool 반환시키고 FVector2D 인자로 넣기
FVector2D ADDakjiPlayerController::GetMousePos()
{
	FVector2D pos = FVector2D();
	GetMousePosition(pos.X, pos.Y);

	return pos;
}

void ADDakjiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}