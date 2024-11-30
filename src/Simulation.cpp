#pragma once
#include "Simulation.h"
#include "Auxiliary.h"
#include "Settlement.h"
#include <fstream>
#include <iostream>

Settlement* Simulation::find_Settlemnt(vector<Settlement*> settlement, const string& nameS) {
    for (Settlement* s : settlement) {
        if (s->getName().compare(nameS) == 0)
            return s;
    return nullptr;
    }
}

SelectionPolicy* Simulation::create_Policy(const string& typeP) {
    if (typeP.compare("eco") == 0) {
        return new EconomySelection(); 
        }
    else if (typeP.compare("bal") == 0) {
        return new BalancedSelection(0, 0, 0);
        }
    else if (typeP.compare("env") == 0) {
        return new SustainabilitySelection();
        }
    else if (typeP.compare("nve") == 0) {
        return new NaiveSelection();
    }
    return nullptr;
}

Simulation::Simulation(const string &configFilePath): isRunning(false), planCounter(0),
actionsLog(vector<BaseAction*>()), plans(vector<Plan>()), settlements(vector<Settlement*>()),
facilitiesOptions(vector<FacilityType>()) {
    std::ifstream File(configFilePath);
    string line;
    while (getline(File, line)) {
        vector<string> config_Line = Auxiliary::parseArguments(line);
        if (config_Line[0].compare("settlement") == 0) {
            settlements.push_back(new Settlement(config_Line[1], Settlement::StringToSettlementType(config_Line[2])));
        }
        if (config_Line[0].compare("facility") == 0) {
            facilitiesOptions.push_back(FacilityType(config_Line[1],
            FacilityType::StringToFacilityCategory(config_Line[2]), std::stoi(config_Line[3]), std::stoi(config_Line[4]),
            std::stoi(config_Line[5]), std::stoi(config_Line[6])));
        }
        if (config_Line[0].compare("plan") == 0) {
            Plan p1(planCounter, *find_Settlemnt(settlements, config_Line[1]), create_Policy(config_Line[2]), facilitiesOptions);
            plans.push_back(p1);
            planCounter++;  
        }
        
    }
}
