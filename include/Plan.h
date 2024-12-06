#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

enum class PlanStatus
{
    AVALIABLE,
    BUSY,
};

class Plan
{
public:
    Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
    Plan(const Plan &other, const Settlement &newS);  // get another plan and a new settlement
    const int getlifeQualityScore() const;
    const int getEconomyScore() const;
    const int getEnvironmentScore() const;
    void setSelectionPolicy(SelectionPolicy *selectionPolicy);
    void step();
    void printStatus();
    const vector<Facility *> &getFacilities() const;
    void addFacility(Facility *facility);
    const string toString() const;
    
    //---------funcions we've added-----------//
    std::size_t limit(const Settlement &settle); // return the limit to construction facility
    const string getStatus(); //returns status
    const string closeToString() const; //returns a string that surrerize the relevant information for close action
    const int getID() const; // returns the plan's ID
    const string getSettlementName() const;  //returns settlement's name from the plan
    const SelectionPolicy *getSelectionPolicy() const; //returns the current selectionPolicy
    const vector<Facility *> getUnderConstruction() const; //return the vector of under construction facilities
    
    //---------rule of 5-----------//
    Plan &operator=(const Plan &other) = delete;  
    Plan &operator=(const Plan &&other) = delete;
    Plan(const Plan &other); //copy constructor
    Plan(Plan &&other); // move constructor
    ~Plan(); //destructor
    
   

private:
    int plan_id;
    const Settlement &settlement;
    SelectionPolicy *selectionPolicy;
    PlanStatus status;
    vector<Facility *> facilities;
    vector<Facility *> underConstruction;
    const vector<FacilityType> &facilityOptions;
    int life_quality_score, economy_score, environment_score;
};