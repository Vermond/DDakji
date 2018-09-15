// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ComAIController.generated.h"

/**
 * 
 */
UCLASS()
class DDAKJI_API AComAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	void StartGame();
	
	void SimulateClick();
	void SimulateDiceRoll();
};
