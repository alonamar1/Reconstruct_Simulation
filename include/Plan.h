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
    Plan(const Plan &other, const Settlement &newS);
    const int getlifeQualityScore() const;
    const int getEconomyScore() const;
    const int getEnvironmentScore() const;
    void setSelectionPolicy(SelectionPolicy *selectionPolicy);
    void step();
    void printStatus();
    const vector<Facility *> &getFacilities() const;
    void addFacility(Facility *facility);
    const string toString() const;
    const std::string getStatus();

    //---------funcions we've added-----------//
    const int getID() const; // returns the plan's ID
    const string getSettlementName() const;
    std::size_t limit(const Settlement &settle); // return the limit to construction facility
    Plan &operator=(const Plan &other) = delete;
    Plan &operator=(const Plan &&other) = delete;
    ~Plan();
    Plan(const Plan &other);
    Plan(Plan &&other); // move func
    const SelectionPolicy *getSelectionPolicy() const;
    const vector<Facility *> getUnderConstruction() const;

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