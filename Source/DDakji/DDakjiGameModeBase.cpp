// Fill out your copyright notice in the Description page of Project Settings.

#include "DDakjiGameModeBase.h"

ADDakjiGameModeBase::ADDakjiGameModeBase()
{
	currentPhase = Phase::Start;
	currentPlayer = Playing::Myself;
	currentPlayMode = PlayMode::Practice;
}


#pragma region Get/Set functions

int32 ADDakjiGameModeBase::GetDicePower() { return dicePower; }
void ADDakjiGameModeBase::SetDicePower(int32 value) { dicePower = value; }

float ADDakjiGameModeBase::GetClickDistance() { return clickDistance; }
void ADDakjiGameModeBase::SetClickDistance(float value) { clickDistance = value; }

float ADDakjiGameModeBase::GetGuardPoint() { return guardPoint; }
void ADDakjiGameModeBase::SetGuardPoint(float value) { guardPoint = value; }

Phase ADDakjiGameModeBase::GetCurrentPhase() { return currentPhase; }
void ADDakjiGameModeBase::SetCurrentPhase(Phase value) { currentPhase = value; }

Playing ADDakjiGameModeBase::GetCurrentPlayer() { return currentPlayer; }
void ADDakjiGameModeBase::SetCurrentPlayer(Playing value) { currentPlayer = value; }

PlayMode ADDakjiGameModeBase::GetCurrentPlayMode() { return currentPlayMode; }
void ADDakjiGameModeBase::SetCurrentPlayMode(PlayMode value) { currentPlayMode = value; }
#pragma endregion
