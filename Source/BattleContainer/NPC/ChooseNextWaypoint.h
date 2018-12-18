// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECONTAINER_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		FBlackboardKeySelector IndexKey;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		FBlackboardKeySelector WaypointKey;
private:
	UBlackboardComponent* BlackboardComp=nullptr;
	TArray<AActor*> PatrolPoints;
	void GetPatrolPoints(UBehaviorTreeComponent& OwnerComp);//Get patrol points
	int32 SetNextWaypoint();
	void CycleIndex(int32 index);
};
