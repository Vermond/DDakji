// Fill out your copyright notice in the Description page of Project Settings.

#include "ComAIController.h"

#include "DDakjiGameMode.h"
#include "MyStaticLibrary.h"
#include "TargetWidget.h"
#include "MyHUD.h"
#include "TargetWidget.h"
#include "DiceRollScreenWidget.h"

#include "Engine/Engine.h"

AComAIController::AComAIController()
{
	UE_LOG(LogTemp, Warning, TEXT("AComAIController init"));
}

void AComAIController::StartGame()
{
	//게임 단계
	//1. 클릭
	//2. 주사위
	//3. 계산 : 어디서 하는게 좋을지 확인하기

	UE_LOG(LogTemp, Warning, TEXT("AComAIController StartGame"));
}

void AComAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UE_LOG(LogTemp, Warning, TEXT("AComAIController PostInitializeComponents"));

	ADDakjiGameMode* gameMode = UMyStaticLibrary::GetGameMode(this);
	if (gameMode) gameMode->PhaseChangeDelegate.AddUObject(this, &AComAIController::PhaseChanged);	
}

void AComAIController::PhaseChanged(Phase phase)
{
	UE_LOG(LogTemp, Warning, TEXT("AComAIController PhaseChanged"));


	ADDakjiGameMode* gameMode = UMyStaticLibrary::GetGameMode(this);

	if (gameMode == nullptr || gameMode->GetCurrentPlayer() != Playing::Computer) return;

	switch (phase)
	{
	case Main:
		break;
	case Select:
		break;
	case Start:
		break;
	case Target:
		SimulateClick();
		break;
	case Powering:
		SimulateDiceRoll();
		break;
	case Result:
		break;
	default:
		break;
	}
}

void AComAIController::SimulateClick()
{
	//랜덤 지점을 구한다
	const FVector2D &ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	int32 rx, ry;

	//r = (double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min;
	rx = (double)rand() / (RAND_MAX + 1) * ViewportSize.X;
	ry = (double)rand() / (RAND_MAX + 1) * ViewportSize.Y;

	//위젯 함수를 통해 클릭한 것처럼 판정
	AMyHUD* hud = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (hud)
	{
		Cast<UTargetWidget>(hud->GetCurrentUI())->SimulateClick(rx, ry);
	}
}

void AComAIController::SimulateDiceRoll()
{
	int r1 = (double)rand() / (RAND_MAX + 1) * 5;
	int r2 = (double)rand() / (RAND_MAX + 1) * 5;
	int r3 = (double)rand() / (RAND_MAX + 1) * 5;

	//위젯 함수를 통해 클릭한 것처럼 판정
	AMyHUD* hud = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (hud)
	{
		Cast<UDiceRollScreenWidget>(hud->GetCurrentUI())->SimulateClick(r1, r2, r3);
	}
}

