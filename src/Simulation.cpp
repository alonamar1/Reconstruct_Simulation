#pragma once
#include "Simulation.h"
#include "Auxiliary.h"
#include "Settlement.h"
#include <fstream>
#include <iostream>

Simulation::Simulation(const string &configFilePath): isRunning(false), planCounter(0),
actionsLog(vector<BaseAction*>()), plans(vector<Plan>()), settlements(vector<Settlement*>()),
facilitiesOptions(vector<FacilityType>()) {
    std::ifstream File(configFilePath);
    string line;
    while (getline(File, line)) {
        vector<string> config_Line = Auxiliary::parseArguments(line);
        if (config_Line[0] == "settlement") {
            settlements.push_back(new Settlement(config_Line[1], Settlement::StringToSettlementType(config_Line[1])));
        }
        if (config_Line[0] == "facility") {
            facilitiesOptions.push_back(FacilityType(config_Line[1],
            FacilityType::StringToFacilityCategory(config_Line[2]), std::stoi(config_Line[3]), std::stoi(config_Line[4]),
            std::stoi(config_Line[5]), std::stoi(config_Line[6])));
        }
        
    }
}
