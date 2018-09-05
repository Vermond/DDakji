// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "CameraDirector.h"
#include "GameFramework/PlayerController.h"
#include "DDakjiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DDAKJI_API ADDakjiPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:	
	ADDakjiPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ChangeUI(Phase phase);
	
	UFUNCTION(BlueprintCallable)
		FVector2D GetMousePos();

	UFUNCTION()
		void GetWorldPosViaMouse();

protected:
	void SetupInputComponent() override;

private:
	void SetUI(TSubclassOf<class UUserWidget> targetWidget, bool showCuror = true);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> startUIWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> targetUIWidget;

private:	
	UUserWidget* currentUI;
	ACameraDirector* cameraDirector;

	float tickTime;
};
