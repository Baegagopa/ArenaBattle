// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "WebConnect.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FTokenCompleteSignature, const FString&);

/**
 * 
 */
UCLASS()
class WEBSERVICE_API UWebConnect : public UObject
{
	GENERATED_BODY()

public :
	UWebConnect();

	UPROPERTY()
	FString Host;

	UPROPERTY()
	FString URI;
	
	UFUNCTION()
	void RequestToken(const FString& UserID);

	FTokenCompleteSignature TokenCompleteDelegate;

};
