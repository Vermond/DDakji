// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Common.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class DDAKJI_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void PostInitializeComponents() override;

public:
	//HUD 만들어서 옮겨야됨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> mainUIWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> selectUIWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> startUIWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> targetUIWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> powerUIWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> resultUIWidget;

	void ChangeUI(Phase phase);
	UUserWidget* GetCurrentUI();
	

private:
	UFUNCTION()
	void SetUI(TSubclassOf<class UUserWidget> targetWidget, bool showCursor = true);
	void SetUIDelayed(TSubclassOf<class UUserWidget> targetWidget, bool showCursor = true);

private:
	UUserWidget* currentUI;	
};
