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
	void ChangeUIByPhase(Phase phase);
	
	UFUNCTION(BlueprintCallable)
		FVector2D GetMousePos();

	UFUNCTION()
		void GetWorldPosViaMouse();

protected:
	void SetupInputComponent() override;

private:
	UFUNCTION()
	void SetUI(TSubclassOf<class UUserWidget> targetWidget, bool showCursor = true);
	void SetUIDelayed(TSubclassOf<class UUserWidget> targetWidget, bool showCursor = true);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> startUIWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> targetUIWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> powerUIWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> resultUIWidget;

	int32 dicePower = 0;
	float clickDistance = 0;
	float guardPoint = 0;

private:	
	UUserWidget* currentUI;
	ACameraDirector* cameraDirector;

	float tickTime;

};
