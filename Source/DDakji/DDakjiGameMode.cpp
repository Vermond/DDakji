// Fill out your copyright notice in the Description page of Project Settings.

#include "DDakjiGameMode.h"

ADDakjiGameMode::ADDakjiGameMode()
{
	currentPhase = Phase::Start;
	currentPlayer = Playing::Myself;
	currentPlayMode = PlayMode::Practice;

	dicePower = 0;
	clickDistance = 0;
	guardPoint = 0;

	currentPosX = 0;
	currentPosY = 0;
	bFirstPlayerSuccess = false;
	bSecondPlayerSuccess = false;
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
void ADDakjiGameMode::SetCurrentPlayer(Playing value) { currentPlayer = value; }

PlayMode ADDakjiGameMode::GetCurrentPlayMode() { return currentPlayMode; }
void ADDakjiGameMode::SetCurrentPlayMode(PlayMode value) { currentPlayMode = value; }
#pragma endregion
