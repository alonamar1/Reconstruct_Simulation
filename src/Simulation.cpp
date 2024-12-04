#include "Simulation.h"
#include "Auxiliary.h"
#include "Settlement.h"
#include <fstream>
#include <iostream>

// לבדוק האם אפשר למחוק את הפונקציה הזו!
Settlement *Simulation::find_Settlemnt(vector<Settlement *> settlement, const string &nameS)
{
    for (Settlement *s : settlement)
    {
        if (s->getName().compare(nameS) == 0)
            return s;
        return nullptr;
    }
}

SelectionPolicy *Simulation::create_Policy(const string &typeP, int lqScore, int ecoScore, int envScore)
{
    if (typeP.compare("eco") == 0)
    {
        return new EconomySelection();
    }
    else if (typeP.compare("bal") == 0)
    {
        return new BalancedSelection(lqScore, ecoScore, envScore);
    }
    else if (typeP.compare("env") == 0)
    {
        return new SustainabilitySelection();
    }
    else if (typeP.compare("nve") == 0)
    {
        return new NaiveSelection();
    }
    return nullptr;
}

Simulation::Simulation(const string &configFilePath) : isRunning(false), planCounter(0),
                                                       actionsLog(vector<BaseAction *>()), plans(vector<Plan>()), settlements(vector<Settlement *>()),
                                                       facilitiesOptions(vector<FacilityType>())
{
    std::ifstream File(configFilePath);
    string line;
    while (getline(File, line))
    {
        vector<string> config_Line = Auxiliary::parseArguments(line);
        if (config_Line[0].compare("settlement") == 0)
        {
            addSettlement(new Settlement(config_Line[1], Settlement::StringToSettlementType(config_Line[2])));
        }
        if (config_Line[0].compare("facility") == 0)
        {
            addFacility(FacilityType(config_Line[1],
                                     FacilityType::StringToFacilityCategory(config_Line[2]), std::stoi(config_Line[3]), std::stoi(config_Line[4]),
                                     std::stoi(config_Line[5]), std::stoi(config_Line[6])));
        }
        if (config_Line[0].compare("plan") == 0)
        {
            addPlan(*find_Settlemnt(settlements, config_Line[1]), create_Policy(config_Line[2], 0, 0, 0));
        }
    }
}

void Simulation::start()
{
    open();
    while (isRunning)
    {

    }
}



void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy)
{
    Plan p1(planCounter, settlement, selectionPolicy, facilitiesOptions);
    plans.push_back(p1);
    planCounter++;
}

void Simulation::addAction(BaseAction *action) {
    actionsLog.push_back(action);
}

bool Simulation::addSettlement(Settlement *settlement)
{
    if (isSettlementExists(settlement->getName()) == true)
    {
        return false;
    }
    settlements.push_back(settlement);
    return true;
}

bool Simulation::addFacility(FacilityType facility)
{
    for (const FacilityType& f : facilitiesOptions)
    {
        if (f.getName().compare(facility.getName()) == 0)
            return false;
    }
    facilitiesOptions.push_back(facility);
    return true;
}

bool Simulation::isSettlementExists(const string &settlementName)
{
    for (Settlement *s : settlements)
    {
        if (s->getName().compare(settlementName) == 0)
            return true;
    }
    return false;
}

const vector<BaseAction*> Simulation::getActionsLog() const
{
    return actionsLog;
}

const vector<Plan> Simulation::getPlans() const
{
    return plans;
}


bool Simulation::isPlanExists(int planID)
{
    for (const Plan& p : plans)
    {
        if (p.getID() == planID)
            return true;
    }
    return false;
}

Settlement &Simulation::getSettlement(const string &settlementName)
{
    for (Settlement *s : settlements)
    {
        if (s->getName().compare(settlementName) == 0)
        {
            return *s;
        }
    }
    throw std::runtime_error("Settlement with Name " + settlementName + " not found.");
}

Plan& Simulation::getPlan(const int planID)
{
    for (Plan& p : plans)
    {
        if (p.getID() == planID)
        {
            return p;
        }
    }
    throw std::runtime_error("Plan with ID " + std::to_string(planID) + " not found.");
}

void Simulation::step()
{
    for (Plan& p : plans)
    {
        p.step();
    }
}
void Simulation::open()
{
    isRunning = true;
}
void Simulation::close()
{
    isRunning = false;
    // complete
}

Simulation::Simulation(const Simulation &other): isRunning(other.isRunning), planCounter(other.planCounter),
actionsLog(vector<BaseAction*>()), plans(vector<Plan>()), settlements(vector<Settlement*>()), facilitiesOptions(vector<FacilityType>())
{
    // Coopying Acions
    for (int i = 0; i < other.actionsLog.size(); i++) {
        actionsLog.push_back(other.actionsLog[i]);
    }
    // Coopying Plans
    for (int i = 0; i < other.plans.size(); i++) {
        plans.push_back(other.plans[i]);
    }
    // Coopying Settlements
    for (int i = 0; i < other.settlements.size(); i++) {
        settlements.push_back(other.settlements[i]);
    }
    // Coopying Facilities 
    for (int i = 0; i < other.facilitiesOptions.size(); i++) {
        facilitiesOptions.push_back(other.facilitiesOptions[i]);
    }
}

