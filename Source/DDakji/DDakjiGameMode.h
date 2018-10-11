// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Common.h"
#include "DDakjiGameMode.generated.h"

DECLARE_DELEGATE_OneParam(FChangePlayerDelegate, Playing);
DECLARE_DELEGATE_OneParam(FPhaseChangeDelegate, Phase);

UCLASS()
class DDAKJI_API ADDakjiGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ADDakjiGameMode();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

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

public:
	UFUNCTION(BlueprintCallable)
	void ChangeUIByPhase(Phase phase);

public:
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


	FPhaseChangeDelegate PhaseChangeDelegate;
	FChangePlayerDelegate ChangePlayerDelegate;

private:
	Phase currentPhase;
	Playing currentPlayer;
	PlayMode currentPlayMode;

	int32 dicePower;
	float clickDistance;
	float guardPoint;

	float currentPosX;
	float currentPosY;
	bool bFirstPlayerSuccess;
	bool bSecondPlayerSuccess;
};
