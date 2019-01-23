// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint2.h"
#include "AIController.h"
#include "PatrollingGuard.h" //TODO Remove coupling
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UChooseNextWaypoint2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//TODO : protect for empty patrol units

	//Get Patrol Points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrollingPoints = PatrollingGuard->PatrolPointsCPP;

	//Set Next Waypoint
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackBoardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrollingPoints[Index]);

	//Cycle the index
	auto NextIndex = (Index + 1) % PatrollingPoints.Num();
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	
	return EBTNodeResult::Succeeded;
}

