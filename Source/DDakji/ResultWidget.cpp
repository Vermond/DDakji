// Fill out your copyright notice in the Description page of Project Settings.

#include "ResultWidget.h"
#include "DDakjiPlayerController.h"

float UResultWidget::GetPowerResult()
{
	ADDakjiPlayerController* pc = (ADDakjiPlayerController*)GWorld->GetFirstPlayerController();
	
	float guardPoint = pc->guardPoint; //변수명 변경해야 함
	float distance = pc->clickDistance;
	int32 dicePower = pc->dicePower;

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