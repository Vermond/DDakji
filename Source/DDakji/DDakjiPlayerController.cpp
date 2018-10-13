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

	if (gameMode)
	{
		gameMode->PhaseChangeDelegate.AddUObject(this, &ADDakjiPlayerController::ChangeCamera);
		gameMode->ChangePlayerDelegate.BindUObject(this, &ADDakjiPlayerController::SetInputByPlayer);
	}
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

void ADDakjiPlayerController::ChangeCamera(Phase phase)
{
	switch (phase)
	{
	case Main:
		break;
	case Select:
		break;
	case Start:
		//카메라 원위치
		cameraDirector->ChangeCamera(1);
		break;
	case Target:
		//딱지치기를 위한 상단으로 카메라 이동
		cameraDirector->ChangeCamera(2);
		break;
	case Powering:
		cameraDirector->ChangeCamera(3);
		break;
	case Result:
		cameraDirector->ChangeCamera(4);
		break;
	default:
		break;
	}
}

void ADDakjiPlayerController::SetInputByPlayer(Playing player)
{
	UE_LOG(LogTemp, Warning, TEXT("ADDakjiPlayerController SetInputByPlayer"));
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