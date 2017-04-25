// Fill out your copyright notice in the Description page of Project Settings.

#include "WebService.h"
#include "WebConnect.h"


UWebConnect::UWebConnect()
{
	UE_LOG(LogClass, Warning, TEXT("WebConnect Constructor Call!"));

	Host = TEXT("localhost:8000");
	URI = TEXT("/");
}


void UWebConnect::RequestToken(const FString& UserID)
{
	UE_LOG(LogClass, Warning, TEXT("Request Token Call!"));
//	TokenCompleteDelegate.ExecuteIfBound(TEXT("0LCJydGkiOiI2a3NjVE9pTUNESVZWM05qVTIyUnlTIn0.VJyMOicM"));
	TokenCompleteDelegate.Broadcast(TEXT("0LCJydGkiOiI2a3NjVE9pTUNESVZWM05qVTIyUnlTIn0.VJyMOicM"));

}