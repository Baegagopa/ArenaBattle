// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(ArenaBattle, Log, All);

#define AB_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define AB_LOG_CALLONLY(Verbosity) UE_LOG(ArenaBattle, Verbosity, TEXT("%s"), *AB_LOG_CALLINFO)
#define AB_LOG(Verbosity, Format, ...) UE_LOG(ArenaBattle, Verbosity, TEXT("%s %s"), *AB_LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__)) 