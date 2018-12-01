// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PatrollingGuard.h"//TODO Remove coupling

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//get a blackboard component
	BlackboardComp = OwnerComp.GetBlackboardComponent();
	GetPatrolPoints(OwnerComp);
	int32 myIndex = SetNextWaypoint();
	CycleIndex(myIndex);
	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypoint::GetPatrolPoints(UBehaviorTreeComponent & OwnerComp)
{
	AAIController* AIOwner =OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIOwner->GetPawn();
	APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	PatrolPoints = PatrollingGuard->GetPatrolPointsCPP();
}

int32 UChooseNextWaypoint::SetNextWaypoint()
{
	
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	UE_LOG(LogTemp, Warning, TEXT("Index: %i"), Index)
	return Index;
}

void UChooseNextWaypoint::CycleIndex(int32 index)
{
	index++;
	int value = (index%PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, value);
}
