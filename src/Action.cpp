
#pragma once
#include "Action.h"

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
    return "settlement name: " + settlementName + "/n" + "selection policy: " + selectionPolicy;
}

AddPlan *AddPlan::clone() const
{
    return new AddPlan(settlementName, selectionPolicy);
}

// class addsettlement
AddSettlement::AddSettlement(const string &settlementName, SettlementType settlementType);
void AddSettlement::act(Simulation &simulation) override;
AddSettlement *AddSettlement::clone() const override;
const string AddSettlement::toString() const override;

const string settlementName;
const SettlementType settlementType;
