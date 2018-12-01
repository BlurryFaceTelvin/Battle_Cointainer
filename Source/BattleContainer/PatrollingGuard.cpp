// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrollingGuard.h"

TArray<AActor*> APatrollingGuard::GetPatrolPointsCPP()
{
	return PatrolPointsCPP;
}

void APatrollingGuard::setPatrolPointsCPP(TArray<AActor*> InPatrolPointsCPP)
{
	PatrolPointsCPP = InPatrolPointsCPP;
}
