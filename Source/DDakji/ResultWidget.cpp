// Fill out your copyright notice in the Description page of Project Settings.

#include "ResultWidget.h"
#include "DDakjiPlayerController.h"
#include "MyStaticLibrary.h"

float UResultWidget::GetPowerResult()
{
	ADDakjiGameMode* gamemode = UMyStaticLibrary::GetGameMode(this);
	
	float guardPoint = gamemode->GetGuardPoint();
	float distance = gamemode->GetClickDistance();
	int32 dicePower = gamemode->GetDicePower();

	//타격이 제일 효과적인 범위를 나타내는 길이
	//적절한 위치로 옮겨야 함
	float guardRange = 10;

	if (guardPoint > (distance - guardRange) && guardPoint < (distance + guardRange))
	{
		//식 실수했으므로 변경해야 한다
		return 1 * 0.5 * dicePower;
	}
	else
	{
		//0.5는 임시로 넣은 보정값으로 필요시 값을 변경하거나 다른 변수로 교체한다.
		//식 실수했으므로 변경해야 한다
		return (distance - guardPoint) * 0.5 * dicePower;
	}
}

bool UResultWidget::GetResult()
{
	//임시로 정한 딱지 HP
	float ddakjiHp = 200;

	//계산된 파워가 HP를 넘을 경우에만 성공을 반환한다.
	return ddakjiHp < GetPowerResult();
}