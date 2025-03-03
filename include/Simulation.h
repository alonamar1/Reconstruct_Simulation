#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation
{
public:
    Simulation(const string &configFilePath);
    void start();
    void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
    void addAction(BaseAction *action);
    bool addSettlement(Settlement *settlement);
    bool addFacility(FacilityType facility);
    bool isSettlementExists(const string &settlementName);
    Settlement &getSettlement(const string &settlementName);
    Plan &getPlan(const int planID);
    void step();
    void close();
    void open();

    //---------funcions we've added-----------// 
    static Settlement *find_Settlemnt(vector<Settlement *> settlement, const string &nameS); // returns the settlement from a vector
    static SelectionPolicy *create_Policy(const string &typeP, int lqScore, int ecoScore, int envScore); //create a policy with specific parameters
    const vector<BaseAction*> getActionsLog() const; //returns actionslog vector
    const vector<Plan> getPlans()const ; //return plans vector
    bool isPlanExists(int planID); //checks if there is a plan with the same id

    // Rule of 5:
    Simulation(const Simulation &other);
    ~Simulation();
    Simulation(Simulation &&other); 
    Simulation &operator=(const Simulation &other);
    Simulation &operator=(Simulation &&other);
    


private:
    bool isRunning;
    int planCounter; // For assigning unique plan IDs
    vector<BaseAction *> actionsLog;
    vector<Plan> plans;
    vector<Settlement *> settlements;
    vector<FacilityType> facilitiesOptions;
};