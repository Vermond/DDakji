// Fill out your copyright notice in the Description page of Project Settings.

#include "DDakjiGameMode.h"
#include "DDakjiPlayerController.h"

ADDakjiGameMode::ADDakjiGameMode()
{

	currentPhase = Phase::Start;
	currentPlayer = Playing::Player1;
	currentPlayMode = PlayMode::Practice;

	dicePower = 0;
	clickDistance = 0;
	guardPoint = 0;

	currentPosX = 0;
	currentPosY = 0;
	bFirstPlayerSuccess = false;
	bSecondPlayerSuccess = false;
}

void ADDakjiGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADDakjiGameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangePhase(Phase::Main);
	SetCurrentPlayer(Playing::Computer);
}

#pragma region Get/Set functions

int32 ADDakjiGameMode::GetDicePower() { return dicePower; }
void ADDakjiGameMode::SetDicePower(int32 value) { dicePower = value; }

float ADDakjiGameMode::GetClickDistance() { return clickDistance; }
void ADDakjiGameMode::SetClickDistance(float value) { clickDistance = value; }

float ADDakjiGameMode::GetGuardPoint() { return guardPoint; }
void ADDakjiGameMode::SetGuardPoint(float value) { guardPoint = value; }

Phase ADDakjiGameMode::GetCurrentPhase() { return currentPhase; }
void ADDakjiGameMode::SetCurrentPhase(Phase value) { currentPhase = value; }

Playing ADDakjiGameMode::GetCurrentPlayer() { return currentPlayer; }
void ADDakjiGameMode::SetCurrentPlayer(Playing value)
{
	currentPlayer = value;

	//상태 변경 알림
	ChangePlayerDelegate.ExecuteIfBound(value);
}

PlayMode ADDakjiGameMode::GetCurrentPlayMode() { return currentPlayMode; }
void ADDakjiGameMode::SetCurrentPlayMode(PlayMode value) { currentPlayMode = value; }
#pragma endregion

void ADDakjiGameMode::ChangePhase(Phase phase)
{
	SetCurrentPhase(phase);

	//상태 변경 알림
	if (PhaseChangeDelegate.IsBound())
	{
		PhaseChangeDelegate.Broadcast(phase);
	}
}