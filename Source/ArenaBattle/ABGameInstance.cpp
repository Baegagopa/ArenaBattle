// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"



void UABGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogClass, Warning, TEXT("GameInstance Init!"));
}
