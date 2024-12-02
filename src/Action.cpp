
#pragma once
#include "Action.h"
#include <iostream>

BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::ERROR) {}

ActionStatus BaseAction::getStatus() const
{
    return status;
}

string BaseAction::getStringStatus() const
{
    if (status == ActionStatus::ERROR)
        return "ERROR";
    if (status == ActionStatus::COMPLETED)
        return "COMPLETED";
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
    return "step " + std::to_string(numOfSteps)+ " " + BaseAction::getStringStatus();;
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
        simulation.addPlan(simulation.getSettlement(settlementName), simulation.create_Policy(selectionPolicy, 0, 0, 0));
        complete();
    }
    else
        error("cannot create this plan");
}

const string AddPlan::toString() const
{
    return  "Plan " + settlementName + " " + selectionPolicy + " " + BaseAction::getStringStatus();
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
    return "settlement" + settlementName + " " + Settlement::settlementTypeToString(settlementType) +" "+ BaseAction::getStringStatus();;
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
        cat = "0";
    if (facilityCategory == FacilityCategory::ECONOMY)
        cat = "1";
    if (facilityCategory == FacilityCategory::ENVIRONMENT)
        cat = "2";

    return "Facility " + facilityName +
           " " + cat +
           " " + std::to_string(price) +
           " " + std::to_string(lifeQualityScore) +
           " " + std::to_string(economyScore) +
           " " + std::to_string(environmentScore) + " " + BaseAction::getStringStatus();;
}

// print plan status
PrintPlanStatus::PrintPlanStatus(int planId) : BaseAction(), planId(planId) {}
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

PrintPlanStatus *PrintPlanStatus::clone() const
{
    return new PrintPlanStatus(planId);
}

const string PrintPlanStatus::toString() const
{
    return "planStatus " + std::to_string(planId) + " " + BaseAction::getStringStatus();
}

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy): BaseAction(), planId(planId), newPolicy(newPolicy) {}
void ChangePlanPolicy::act(Simulation &simulation) {
    Plan currPlan = simulation.getPlan(planId);
    // just if there is a plan with the same name and the policy is diffrent the the prvious one
    if (simulation.isPlanExists(planId) && currPlan.getSelectionPolicy()->getPolicyType().compare(newPolicy) != 0) {
        int ecoScore = currPlan.getEconomyScore(), envScore = currPlan.getEnvironmentScore(), lqScore = currPlan.getlifeQualityScore();
        // include the scores of the underConstruction
        for (Facility* f : currPlan.getUnderConstruction()) {
            ecoScore += f->getEconomyScore();
            envScore += f->getEnvironmentScore();
            lqScore += f->getLifeQualityScore();
        }
        currPlan.setSelectionPolicy(Simulation::create_Policy(newPolicy, lqScore, ecoScore, envScore));
        complete();
    }
    else {
        error("Cannot change selection policy");
    }
}
ChangePlanPolicy* ChangePlanPolicy::clone() const {
    return new ChangePlanPolicy(planId, newPolicy);
}
const string ChangePlanPolicy::toString() const {
    return "changePolicy " + std::to_string(planId) + " " + newPolicy + " " + BaseAction::getStringStatus();

}

//print action log
    PrintActionsLog::PrintActionsLog(): BaseAction() {}
    void PrintActionsLog::act(Simulation &simulation)
    {
        for (BaseAction* a: simulation.getActionsLog())
        {
            std::cout << a->toString() << "\n" << std::endl;
        }
        complete();
    }
    PrintActionsLog* PrintActionsLog::clone() const
    {
        return new PrintActionsLog();
    }
    const string PrintActionsLog::toString() const
    {
        return "log " + BaseAction::getStringStatus();
    }


    //close
    Close::Close(): BaseAction() {}
    void Close::act(Simulation &simulation)
    {
        for (Plan p : simulation.getPlans())
        {
            std::cout << p.toString() << std::endl;
        }
        complete();
        simulation.close();
    }
    Close* Close::clone() const
    {
        return new Close();
    }
    const string Close::toString() const
    {
        return "close " + BaseAction::getStringStatus();
    }

    BackupSimulation::BackupSimulation(): BaseAction() {}
    void BackupSimulation::act(Simulation &simulation)
    {
        
    }
    BackupSimulation* BackupSimulation::clone() const
    {
        return new BackupSimulation();
    }
    const string BackupSimulation::toString() const
    {
        return "backup " + BaseAction::getStringStatus();
    }

    class RestoreSimulation : public BaseAction
{

    RestoreSimulation::RestoreSimulation(): BaseAction() {}
    void RestoreSimulation::act(Simulation &simulation) 
    {

    }  
    RestoreSimulation* RestoreSimulation::clone() const
    {
        return new RestoreSimulation();
    }
    const string RestoreSimulation::toString() const
    {
        return "restore "+ BaseAction::getStringStatus();;
    }

private:
};
