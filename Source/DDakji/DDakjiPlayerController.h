// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "CameraDirector.h"
#include "GameFramework/PlayerController.h"
#include "DDakjiPlayerController.generated.h"

UCLASS()
class DDAKJI_API ADDakjiPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:	
	ADDakjiPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable)
	//void ChangeUIByPhase(Phase phase);
	
	UFUNCTION(BlueprintCallable)
		FVector2D GetMousePos();

	void ChangeCamera(Phase phase);
	void SetInputByPlayer(Playing player);

protected:
	void SetupInputComponent() override;

private:
	ACameraDirector* cameraDirector;
};
