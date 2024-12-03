#include "Plan.h"
#include <iostream>

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions) : plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), facilityOptions(facilityOptions), status(PlanStatus::AVALIABLE), underConstruction(vector<Facility *>()),
                                                                                                                                            facilities(vector<Facility *>()), life_quality_score(0), economy_score(0), environment_score(0) {}

const int Plan::getlifeQualityScore() const
{
    return life_quality_score;
}

const int Plan::getEconomyScore() const
{
    return economy_score;
}
const int Plan::getEnvironmentScore() const
{
    return environment_score;
}
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy)
{
    delete Plan::selectionPolicy; //  האם צריך למחוק את כל מה שיש פה ??? או למחוק את זה בchagnepolicy
    Plan::selectionPolicy = selectionPolicy;
}

void Plan::step()
{
    // Check which facilty to build
    while (status == PlanStatus::AVALIABLE)
    {
        FacilityType selectedFacilityType = selectionPolicy->selectFacility(facilityOptions);
        underConstruction.push_back(new Facility(selectedFacilityType, settlement.getName()));
        if (underConstruction.size() >= limit(settlement))
        {
            status = PlanStatus::BUSY;
        }
    }
    vector<int> forDelete;
    // Do step on the facilities under construction
    for (int i = 0; i < underConstruction.size(); i++)
    {
        underConstruction[i]->step();
        if (underConstruction[i]->getStatus() == FacilityStatus::OPERATIONAL)
        {
            addFacility(underConstruction[i]);
            forDelete.push_back(i);
        }
    }
    // Delete the item
    for (int f : forDelete)
    {
        underConstruction.erase(underConstruction.begin() + f);
    }
    if (forDelete.size() > 0)
    {
        status = PlanStatus::AVALIABLE;
    }
}

// return the limit to construction facility
int Plan::limit(const Settlement &settle)
{
    if (settle.getType() == SettlementType::VILLAGE)
    {
        return 1;
    }
    if (settle.getType() == SettlementType::CITY)
    {
        return 2;
    }
    if (settle.getType() == SettlementType::METROPOLIS)
    {
        return 3;
    }
}

void Plan::printStatus()
{
    if (status == PlanStatus::AVALIABLE)
        std::cout << "AVAILABLE" << std::endl;
    if (status == PlanStatus::BUSY)
        std::cout << "BUSY" << std::endl;
}

const vector<Facility *> &Plan::getFacilities() const
{
    return facilities;
}

void Plan::addFacility(Facility *facility)
{
    facilities.push_back(facility);
    life_quality_score += facility->getLifeQualityScore();
    economy_score += facility->getEconomyScore();
    environment_score += facility->getEconomyScore();
}
const SelectionPolicy *Plan::getSelectionPolicy() const
{
    return selectionPolicy;
}

const vector<Facility *> Plan::getUnderConstruction() const
{
    return underConstruction;
}

const string Plan::toString() const
{
    string s = "", facilitiesString = "";
    if (status == PlanStatus::AVALIABLE)
        s = "AVAILABLE";
    if (status == PlanStatus::BUSY)
        s = "BUSY";
    for (Facility *f : facilities)
    {
        facilitiesString += "FacilityName: " + f->getName() + "\n" +
                            "FacilityStatus: " + f->getStringStatus() + "\n";
    }
    for (Facility *f : underConstruction)
    {
        facilitiesString += "FacilityName: " + f->getName() + "\n" +
                            "FacilityStatus: " + f->getStringStatus() + "\n";
    }
    return "Plan ID: " + std::to_string(plan_id) + "\n" +
           "SettlementName: " + settlement.getName() + "\n" +
           "PlanStatus: " + s + "\n" +
           "SelectionPolicy: " + selectionPolicy->getPolicyType() + "\n" +
           "LifeQualityScore: " + std::to_string(life_quality_score) + "\n" +
           "EconomyScore: " + std::to_string(economy_score) + "\n" +
           "EnvironmentScore: " + std::to_string(environment_score) + "\n" +
           facilitiesString;
}
Plan::~Plan()
{
    // Clean up dynamically allocated memory for facilities under construction
    for (Facility *facility : underConstruction)
    {
        delete facility;
    }
    // Clean up dynamically allocated memory for opersions facilities
    for (Facility *facility : facilities)
    {
        delete facility;
    }
    // Delete the Selected Policy object
    delete selectionPolicy;
}

const int Plan::getID() const
{
    return plan_id;
}

Plan::Plan(const Plan &other)
    : plan_id(other.plan_id), settlement(other.settlement), facilityOptions(other.facilityOptions),
      status(other.status), life_quality_score(other.life_quality_score), economy_score(other.economy_score), environment_score(other.environment_score)
{
    selectionPolicy = other.selectionPolicy->clone();
    // Deep copy the 'underConstruction' vector
    for (Facility *f : other.underConstruction)
    {
        underConstruction.push_back(new Facility(*f)); // Create a copy of each Facility
    }

    // Deep copy the 'facilities' vector
    for (Facility *f : other.facilities)
    {
        facilities.push_back(new Facility(*f)); // Create a copy of each Facility
    }
}

Plan::Plan(Plan &&other) // noexcept
    : plan_id(other.plan_id),
      settlement(std::move(other.settlement)),
      selectionPolicy(other.selectionPolicy),
      facilityOptions(std::move(other.facilityOptions)),
      status(other.status),
      life_quality_score(other.life_quality_score),
      economy_score(other.economy_score),
      environment_score(other.environment_score),
      underConstruction(std::move(other.underConstruction)),
      facilities(std::move(other.facilities))
{
    // Reset the source object
    other.underConstruction = vector<Facility *>();
    other.facilities = vector<Facility *>();
    selectionPolicy = nullptr;
}
