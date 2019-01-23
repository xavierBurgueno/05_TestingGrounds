// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint2.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UChooseNextWaypoint2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	

	//Get Patrol Route
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	//Warn about empty patrol routes
	auto PatrollingPoints = PatrolRoute->GetPatrolPoints();
	if (PatrollingPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Guard is missing Patrol Points"));
		return EBTNodeResult::Failed;
	}


	//Set Next Waypoint
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackBoardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrollingPoints[Index]);

	//Cycle the index
	auto NextIndex = (Index + 1) % PatrollingPoints.Num();
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	
	return EBTNodeResult::Succeeded;
}

