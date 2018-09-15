// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetWidget.h"
#include "MyStaticLibrary.h"
#include "DDakjiPlayerController.h"

void UTargetWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//tickTime -= InDeltaTime;

	if (tickTime < 0)
	{
		tickTime = nextAnnoyTime;
		
		ADDakjiPlayerController* controller = UMyStaticLibrary::GetPlayerController(this);

		FVector2D pos = FVector2D();
		controller->GetMousePosition(pos.X, pos.Y);

		pos.X += rand() % 20 - 10;
		pos.Y += rand() % 20 - 10;

		controller->SetMouseLocation((int)(pos.X), (int)(pos.Y));
	}
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

		controller->ChangeUIByPhase(Phase::Powering);
	}
}