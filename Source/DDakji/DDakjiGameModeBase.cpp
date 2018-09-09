// Fill out your copyright notice in the Description page of Project Settings.

#include "DDakjiGameModeBase.h"

ADDakjiGameModeBase::ADDakjiGameModeBase()
{
	currentPhase = Phase::Start;
}


#pragma region Get/Set functions

int32 ADDakjiGameModeBase::GetDicePower() { return dicePower; }
void ADDakjiGameModeBase::SetDicePower(int32 value) { dicePower = value; }

float ADDakjiGameModeBase::GetClickDistance() { return clickDistance; }
void ADDakjiGameModeBase::SetClickDistance(float value) { clickDistance = value; }

float ADDakjiGameModeBase::GetGuardPoint() { return guardPoint; }
void ADDakjiGameModeBase::SetGuardPoint(float value) { guardPoint = value; }

#pragma endregion
