// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetWidget.h"
#include "MyStaticLibrary.h"
#include "DDakjiPlayerController.h"
#include "PanelSlot.h"
#include "CanvasPanelSlot.h"
#include "PanelWidget.h"
#include "CanvasPanel.h"
#include "Engine/Engine.h"

void UTargetWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ADDakjiPlayerController* controller = UMyStaticLibrary::GetPlayerController(this);
	prevMousePos = controller->GetMousePos();

	SetMousePosToTarget();
}

void UTargetWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	tickTime -= InDeltaTime;

	if (tickTime < 0)
	{
		tickTime = nextAnnoyTime;
		
		//임시로 진동기능 빼놓음
		float x = 0;// rand() % 20 - 10;
		float y = 0;// rand() % 20 - 10;

		ADDakjiPlayerController* controller = UMyStaticLibrary::GetPlayerController(this);
		
		FVector2D mousePos;
		//마우스 이동과 위젯 이동이 동기화되지 않음
		//이동 단위 또는 비율 문제같음. 변환 필요한듯
		mousePos = controller->GetMousePos(); //실제 화면의 마우스 위치, 게임 화면 크게랑 상관없음

		x += mousePos.X - prevMousePos.X;
		y += mousePos.Y - prevMousePos.Y;

		prevMousePos = mousePos;

		MoveTarget(x, y);
	}
}

void UTargetWidget::SetMousePosToTarget()
{
	
	ADDakjiPlayerController* controller = UMyStaticLibrary::GetPlayerController(this);

	//UCanvasPanelSlot* slot = (UCanvasPanelSlot*)targetWidget->Slot;
	//해당 아이템의 몇몇 정보를 얻기 위해 슬롯으로 변환
	//slot->GetSize()
	//umg 기준에서의 해당 아이템 크기
	//targetWidget->RenderTransform.Translation
	//umg 기준에서의 초기 위치
	//GEngine->GameViewport->Viewport->GetSizeXY()
	//현재 뷰포트 크기
	//targetWidget->RenderTransformPivot
	//피봇 위치
	//slot->GetAnchors()
	//앵커; 퍼센트로 출력된다

	UCanvasPanelSlot* slot = (UCanvasPanelSlot*)targetWidget->Slot;

	const FVector2D &viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D &size = slot->GetSize();
	const FVector2D &pos = slot->GetPosition();
	const FAnchors &anchor = slot->GetAnchors();
	const FVector2D &pivot = targetWidget->RenderTransformPivot;

	int x, y;

	if (slot != nullptr)
	{
		//무조건 아이템 중간에 마우스가 오도록 하자
		//앵커가 영역이 아닌 포인트라고 가정한다 (이 경우 Maximum = minimum)
		//식 미완성
		x = viewportSize.X * anchor.Maximum.X + pos.X + size.X / 2;// *((pivot.X * -1) + 0.5);
		y = viewportSize.Y * anchor.Maximum.Y + pos.Y + size.Y / 2;// *((pivot.Y * -1) + 0.5);

		controller->SetMouseLocation(x, y);
	}
}

void UTargetWidget::MoveTarget(float posX, float posY)
{
	FVector2D pos = targetWidget->RenderTransform.Translation;
	pos.X += posX;
	pos.Y += posY;

	targetWidget->SetRenderTranslation(pos);
}

void UTargetWidget::GetWorldPosViaMouse()
{
	ADDakjiGameMode* gamemode = UMyStaticLibrary::GetGameMode(this);
	ADDakjiPlayerController* controller = UMyStaticLibrary::GetPlayerController(this);

	if (gamemode->GetCurrentPhase() == Phase::Target)
	{
		FHitResult HitData(ForceInit);

		FVector worldLocation;
		FVector worldDirection;

		//카메라 위치와 마우스 클릭을 기준으로 한다
		controller->DeprojectMousePositionToWorld(worldLocation, worldDirection);

		const FVector Start = worldLocation;
		const FVector End = Start + worldDirection * 512;
				
		if (UMyStaticLibrary::Trace(controller->GetWorld(), controller->GetPawn(), Start, End, HitData))
		{
			//클릭 위치가 오브젝트 중심에서 떨어진 길이를 구한다.
			//상단 평면에서만 계산하는 것으로 가정하므로 높이는 무시한다.
			FVector actorLoc = HitData.Actor->GetActorLocation();
			FVector clickLoc = HitData.Location;

			gamemode->SetClickDistance(sqrtf(powf(actorLoc.X - clickLoc.X, 2) + pow(actorLoc.Y - clickLoc.Y, 2)));

			//충격 효과가 최소화가 되는 지점과의 길이를 구한다
			//원형으로 가정하며 아래 식은 임시로 구현한다 (15% 위치를 기준으로 함)
			FVector origin, boxExtend;
			HitData.Actor->GetActorBounds(true, origin, boxExtend);
			gamemode->SetGuardPoint(sqrtf(powf(boxExtend.X * 0.15, 2) + pow(boxExtend.Y * 0.15, 2)));
		}

		gamemode->ChangePhase(Phase::Powering);
	}
}

void UTargetWidget::SimulateClick(int32 x, int32 y)
{
	//우선 호출되는지 확인하기
	UE_LOG(LogTemp, Warning, TEXT("UTargetWidget SimulateClick"));


}