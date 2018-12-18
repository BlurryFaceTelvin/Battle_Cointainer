// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "PatrolRoute.h"


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
	UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return; }
	PatrolPoints = PatrolRoute->GetPatrolPoints();
	if(PatrolPoints.Num()==0){UE_LOG(LogTemp,Warning,TEXT("A guard is missing patrol points")) }
}

int32 UChooseNextWaypoint::SetNextWaypoint()
{
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	return Index;
}

void UChooseNextWaypoint::CycleIndex(int32 index)
{
	index++;
	int value = (index%PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, value);
}
