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

public:
	Phase currentPhase;
};
