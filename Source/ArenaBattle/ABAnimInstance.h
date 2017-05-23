// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "ABPawn.h"
#include "ABAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UABAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
		void AnimNotify_AttackEnd(UAnimNotify* Notify) { AB_LOG_CALLONLY(Warning); }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	float VelocityAnim;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	EPlayerState CurrentState;
};
