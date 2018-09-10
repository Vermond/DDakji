// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class.h"

UENUM(BlueprintType)
enum Phase
{
	Main,
	Select,
	Start,
	Target,
	Powering,
	Result
};