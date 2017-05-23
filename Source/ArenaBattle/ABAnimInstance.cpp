// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	VelocityAnim = 0.0F;
	CurrentState = EPlayerState::BATTLE;
}
void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	APawn* OwnerPawn = TryGetPawnOwner();
	if (OwnerPawn != nullptr)
	{
		if (OwnerPawn->IsValidLowLevel())
		{
			VelocityAnim = OwnerPawn->GetVelocity().Size();
			AABPawn * ABPawn = Cast<AABPawn>(OwnerPawn);
			if (ABPawn)
			{
				CurrentState = ABPawn->CurrentState;
			}
		}
	}
}


