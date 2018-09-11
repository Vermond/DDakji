// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Common.h"
#include "DDakjiGameModeBase.generated.h"

UCLASS()
class DDAKJI_API ADDakjiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ADDakjiGameModeBase();

#pragma region Get/Set functions
public:
	int32 GetDicePower();
	void SetDicePower(int32 value);

	float GetClickDistance();
	void SetClickDistance(float value);

	float GetGuardPoint();
	void SetGuardPoint(float value);

	Phase GetCurrentPhase();
	void SetCurrentPhase(Phase value);

	Playing GetCurrentPlayer();
	UFUNCTION(BlueprintCallable)
	void SetCurrentPlayer(Playing value);

	PlayMode GetCurrentPlayMode();
	UFUNCTION(BlueprintCallable)
	void SetCurrentPlayMode(PlayMode value);
#pragma endregion
	
private:
	Phase currentPhase;
	Playing currentPlayer;
	PlayMode currentPlayMode;

	int32 dicePower = 0;
	float clickDistance = 0;
	float guardPoint = 0;
};
