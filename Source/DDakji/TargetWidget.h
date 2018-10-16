// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "TargetWidget.generated.h"

/**
 * 
 */
UCLASS()
class DDAKJI_API UTargetWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void GetWorldPosViaMouse();
	
	void SetMousePosToTarget();
	void MoveTarget(float posX, float posY);

	void SimulateClick(int32 x, int32 y);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		class UTextBlock* targetWidget;

private:
	float tickTime = 0;
	const float nextAnnoyTime = .05f;
	FVector2D prevMousePos;
};
