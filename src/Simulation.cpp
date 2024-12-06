#include "Simulation.h"
#include "Auxiliary.h"
#include "Action.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <fstream>
#include <iostream>

// לבדוק האם אפשר למחוק את הפונקציה הזו!
Settlement *Simulation::find_Settlemnt(vector<Settlement *> settlement, const string &nameS)
{
    for (Settlement *s : settlement)
    {
        if (s->getName().compare(nameS) == 0)
            return s;
    }
    return nullptr;
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
    std::cout << "The simulation has started" << std::endl;
    while (isRunning)
    {
        string user_input;
        std::getline(std::cin, user_input);
        vector<string> action_Line = Auxiliary::parseArguments(user_input);
        if (action_Line.size() > 0)
        {
            BaseAction *inputAction = nullptr;
            if (action_Line[0].compare("step") == 0 && action_Line.size() == 2)
            {
                inputAction = new SimulateStep(std::stoi(action_Line[1]));
            }
            else if (action_Line[0].compare("plan") == 0 && action_Line.size() == 3)
            {
                inputAction = new AddPlan(action_Line[1], action_Line[2]);
            }
            else if (action_Line[0].compare("settlement") == 0 && action_Line.size() == 3)
            {
                inputAction = new AddSettlement(action_Line[1], Settlement::StringToSettlementType(action_Line[2]));
            }
            else if (action_Line[0].compare("facility") == 0 && action_Line.size() == 7)
            {
                inputAction = new AddFacility(action_Line[1],
                                              FacilityType::StringToFacilityCategory(action_Line[2]), std::stoi(action_Line[3]), std::stoi(action_Line[4]),
                                              std::stoi(action_Line[5]), std::stoi(action_Line[6]));
            }
            else if (action_Line[0].compare("planStatus") == 0 && action_Line.size() == 2)
            {
                inputAction = new PrintPlanStatus(std::stoi(action_Line[1]));
            }
            else if (action_Line[0].compare("changePolicy") == 0 && action_Line.size() == 3)
            {
                inputAction = new ChangePlanPolicy(std::stoi(action_Line[1]), action_Line[2]);
            }
            else if (action_Line[0].compare("log") == 0)
            {
                inputAction = new PrintActionsLog();
            }
            else if (action_Line[0].compare("close") == 0)
            {
                inputAction = new Close();
            }
            else if (action_Line[0].compare("backup") == 0)
            {
                inputAction = new BackupSimulation();
            }
            else if (action_Line[0].compare("restore") == 0)
            {
                inputAction = new RestoreSimulation();
            }
            else
            {
                std::cout << "INVALID ACTION" << std::endl;
            }
            if (inputAction != nullptr)
            {
                inputAction->act(*this);
                actionsLog.push_back(inputAction);
            }
        }
    }
}

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy)
{
    Plan p1(planCounter, settlement, selectionPolicy, facilitiesOptions);
    plans.push_back(p1);
    planCounter++;
}

void Simulation::addAction(BaseAction *action)
{
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
    for (const FacilityType &f : facilitiesOptions)
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

const vector<BaseAction *> Simulation::getActionsLog() const
{
    return actionsLog;
}

const vector<Plan> Simulation::getPlans() const
{
    return plans;
}

bool Simulation::isPlanExists(int planID)
{
    for (const Plan &p : plans)
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

Plan &Simulation::getPlan(const int planID)
{
    for (Plan &p : plans)
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
    for (Plan &p : plans)
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
}

Simulation::Simulation(const Simulation &other) : isRunning(other.isRunning), planCounter(other.planCounter),
                                                  actionsLog(vector<BaseAction *>()), plans(vector<Plan>()), settlements(vector<Settlement *>()), facilitiesOptions(vector<FacilityType>())
{
    // Coopying Acions
    for (std::size_t i = 0; i < other.actionsLog.size(); i++)
    {
        actionsLog.push_back(other.actionsLog[i]->clone());
    }
    // Coopying Settlements
    for (std::size_t i = 0; i < other.settlements.size(); i++)
    {
        settlements.push_back(new Settlement(*other.settlements[i]));
    }
    // Coopying Facilities
    for (std::size_t i = 0; i < other.facilitiesOptions.size(); i++)
    {
        facilitiesOptions.push_back(other.facilitiesOptions[i]);
    }
    // Coopying Plans
    for (std::size_t i = 0; i < other.plans.size(); i++)
    {
        Settlement *s = Simulation::find_Settlemnt(settlements, other.plans[i].getSettlementName());
        Plan p = Plan(other.plans[i], *s);
        plans.push_back(p);
    }
}

Simulation::~Simulation()
{
    for (BaseAction *ba : actionsLog)
    {
        delete ba;
    }
    actionsLog.clear();
    for (Settlement *s : settlements)
    {
        delete s;
    }
    settlements.clear();
    plans.clear();
    facilitiesOptions.clear();
}

// Move constructor
Simulation::Simulation(Simulation &&other) : isRunning(other.isRunning), planCounter(other.planCounter), actionsLog(std::move(other.actionsLog)),
                                             plans(std::move(other.plans)), settlements(std::move(other.settlements)), facilitiesOptions(std::move(other.facilitiesOptions))
{
    // Clears the moved stolen data beacuse rvalue, In order to prevent double deletion
    other.settlements.clear();
    other.actionsLog.clear();
}

Simulation &Simulation::operator=(const Simulation &other)
{
    isRunning = other.isRunning;
    planCounter = other.planCounter;
    if (&other != this)
    {
        // delete corrent files
        for (BaseAction *ba : actionsLog)
        {
            delete ba;
        }
        actionsLog.clear();
        for (Settlement *s : settlements)
        {
            delete s;
        }
        settlements.clear();
        plans.clear();
        facilitiesOptions.clear();

        // Put things inside | Deep copy
        for (BaseAction *ba : other.actionsLog)
        {
            actionsLog.push_back(ba->clone());
        }
        for (Settlement *s : other.settlements)
        {
            settlements.push_back(new Settlement(*s));
        }

        for (std::size_t i = 0; i < other.facilitiesOptions.size(); i++)
        {
            facilitiesOptions.push_back(other.facilitiesOptions[i]);
        }

        for (std::size_t i = 0; i < other.plans.size(); i++)
        {
            Settlement *s = Simulation::find_Settlemnt(settlements, other.plans[i].getSettlementName());
            Plan p = Plan(other.plans[i], *s);
            plans.push_back(p);
        }
    }
    return *this;
}

Simulation &Simulation::operator=(Simulation &&other)
{
    if (&other != this)
    {

        // clear this
        for (BaseAction *ba : actionsLog)
        {
            delete ba;
        }
        for (Settlement *s : settlements)
        {
            delete s;
        }
        plans.clear();
        facilitiesOptions.clear();
        actionsLog.clear();
        settlements.clear();

        // copy other's data
        isRunning = other.isRunning;
        planCounter = other.planCounter;
        for (BaseAction *ba : other.actionsLog)
        {
            actionsLog.push_back(ba);
        }
        for (Settlement *s : other.settlements)
        {
            settlements.push_back(s);
        }
        for (std::size_t i = 0; i < other.plans.size(); i++)
        {
            plans.push_back(other.plans[i]);
        }
        for (std::size_t i = 0; i < other.facilitiesOptions.size(); i++)
        {
            facilitiesOptions.push_back(other.facilitiesOptions[i]);
        }

        // clear other
        for (std::size_t i = 0; i < other.actionsLog.size(); i++)
        {
            other.actionsLog[i] = nullptr;
        }
        for (std::size_t i = 0; i < other.settlements.size(); i++)
        {
            other.settlements[i] = nullptr;
        }
        other.settlements.clear();
        other.actionsLog.clear();
        other.plans.clear();
        other.facilitiesOptions.clear();
    }
    return *this;
}
