
#pragma once
#include "Action.h"
#include <iostream>

BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::ERROR) {}

ActionStatus BaseAction::getStatus() const
{
    return status;
}

void BaseAction::complete()
{
    status = ActionStatus::COMPLETED;
}
void BaseAction::error(string errorMsg)
{
    status = ActionStatus::ERROR;
    BaseAction::errorMsg = errorMsg;
}

const string &BaseAction::getErrorMsg() const
{
    return errorMsg;
}

// class SimulateSte

SimulateStep::SimulateStep(const int numOfSteps) : BaseAction(), numOfSteps(numOfSteps) {}
void SimulateStep::act(Simulation &simulation)
{
    for (int i = 0; i < numOfSteps; i++)
    {
        simulation.step();
    }
    complete();
}
const string SimulateStep::toString() const
{
    return "number of steps:" + std::to_string(numOfSteps);
}
SimulateStep *SimulateStep::clone() const
{
    return new SimulateStep(numOfSteps);
}

// Class AddPlan

AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy) : BaseAction(),
                                                                                settlementName(settlementName), selectionPolicy(selectionPolicy) {}

void AddPlan::act(Simulation &simulation)
{
    if (simulation.isSettlementExists(settlementName) & SelectionPolicy::isTrueSelectionPolicy(selectionPolicy))
    {
        simulation.addPlan(simulation.getSettlement(settlementName), simulation.create_Policy(selectionPolicy));
        complete();
    }
    else
        error("cannot create this plan");
}

const string AddPlan::toString() const
{
    return "settlement name: " + settlementName + "\n" + "selection policy: " + selectionPolicy;
}

AddPlan *AddPlan::clone() const
{
    return new AddPlan(settlementName, selectionPolicy);
}

// class addsettlement
AddSettlement::AddSettlement(const string &settlementName, SettlementType settlementType) : BaseAction(), settlementName(settlementName), settlementType(settlementType) {}
void AddSettlement::act(Simulation &simulation)
{
    bool result = simulation.addSettlement(new Settlement(settlementName, settlementType));
    if (!result)
    {
        error("settlement already exist");
    }
    else
        complete();
}

AddSettlement *AddSettlement::clone() const
{
    return new AddSettlement(settlementName, settlementType);
}

const string AddSettlement::toString() const
{
    return "settlement name: " + settlementName + "\n" + "settlement type: " + Settlement::settlementTypeToString(settlementType);
}

// addfacility

AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore) : BaseAction(), facilityName(facilityName), facilityCategory(facilityCategory), price(price), lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore) {}
void AddFacility::act(Simulation &simulation)
{
    bool result = simulation.addFacility(FacilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore));
    if (!result)
    {
        error("facility already exist");
    }
    else
        complete();
}
AddFacility *AddFacility::clone() const
{
    return new AddFacility(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
}

const string AddFacility::toString() const
{
    string cat;
    if (facilityCategory == FacilityCategory::LIFE_QUALITY)
        cat = "Life Quality";
    if (facilityCategory == FacilityCategory::ECONOMY)
        cat = "Economy";
    if (facilityCategory == FacilityCategory::ENVIRONMENT)
        cat = "Environment";
    
    return "Facility: " + facilityName +
    "\nCategory: " + cat +
    "\nprice: " + std::to_string(price) +
    "\nLife Quality Score: "+ std::to_string(lifeQualityScore) +
    "\nEconomy Score: " +std::to_string(economyScore) +
    "\nEnvironment Score: " + std::to_string(environmentScore);
}

//print plan status
PrintPlanStatus::PrintPlanStatus(int planId):
BaseAction(), planId(planId){}
void PrintPlanStatus::act(Simulation &simulation)
{   
    if (simulation.isPlanExists(planId))
    {
            std::cout << simulation.getPlan(planId).toString() << std::endl;
            complete();
    }
    else 
    {
        error("plan doesn't exist");
    }
    
}

PrintPlanStatus* PrintPlanStatus::clone() const
{
    return new PrintPlanStatus(planId);
}

const string PrintPlanStatus::toString() const
{
    return "plan ID: " + planId;
}




