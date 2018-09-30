// Fill out your copyright notice in the Description page of Project Settings.

#include "ComAIController.h"

#include "DDakjiGameMode.h"
#include "MyStaticLibrary.h"
#include "TargetWidget.h"

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

void AComAIController::SimulateClick()
{
	//랜덤 지점을 구한다
	const FVector2D &ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	int rx, ry;

	//r = (double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min;
	rx = (double)rand() / (RAND_MAX + 1) * ViewportSize.X;
	ry = (double)rand() / (RAND_MAX + 1) * ViewportSize.Y;

	//이동 없이 클릭만 우선 구현해보자
	ADDakjiGameMode* gameMode = UMyStaticLibrary::GetGameMode(this);
//	UTargetWidget* targetWidget = gameMode->testTargetUIWidget.Get();	

}

void AComAIController::SimulateDiceRoll()
{
	int r1 = (double)rand() / (RAND_MAX + 1) * 5;
	int r2 = (double)rand() / (RAND_MAX + 1) * 5;
	int r3 = (double)rand() / (RAND_MAX + 1) * 5;
}

