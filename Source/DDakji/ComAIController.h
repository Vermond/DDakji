// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Common.h"
#include "ComAIController.generated.h"

/**
 * 
 */
UCLASS()
class DDAKJI_API AComAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	AComAIController();

	virtual void PostInitializeComponents() override;

	void StartGame();
	
	void PhaseChanged(Phase phase);

	void SimulateClick();
	void SimulateDiceRoll();

private:
	int finalX;
	int finalY;
	int currentX;
	int currentY;
};
