#include "Plan.h"
#include <iostream>

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions) : plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), status(PlanStatus::AVALIABLE), facilities(vector<Facility *>()),
                                                                                                                                            underConstruction(vector<Facility *>()), facilityOptions(facilityOptions),
                                                                                                                                            life_quality_score(0), economy_score(0), environment_score(0) {}
// get another plan and a new settlement
Plan::Plan(const Plan &other, const Settlement &newS) : plan_id(other.plan_id), settlement(newS),selectionPolicy(other.selectionPolicy->clone()), status(other.status),
      facilities(vector<Facility *>()), underConstruction(vector<Facility *>()), facilityOptions(other.facilityOptions),
      life_quality_score(other.life_quality_score), economy_score(other.economy_score), environment_score(other.environment_score)
{
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
    delete Plan::selectionPolicy;
    Plan::selectionPolicy = selectionPolicy;
    selectionPolicy = nullptr;
}

void Plan::step()
{
    // Check which facilty to build
    while (status == PlanStatus::AVALIABLE)
    {
        FacilityType selectedFacilityType = selectionPolicy->selectFacility(facilityOptions);
        Facility *fac = new Facility(selectedFacilityType, settlement.getName());
        underConstruction.push_back(fac);
        if (underConstruction.size() >= limit(settlement))
        {
            status = PlanStatus::BUSY;
        }
    }
    vector<int> forDelete;
    // Do step on the facilities under construction
    for (std::size_t i = 0; i < underConstruction.size(); i++)
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
        for (std::size_t i = f; i < forDelete.size(); i++)
        {
            forDelete[i]--;
        }
    }
    if (forDelete.size() > 0)
    {
        status = PlanStatus::AVALIABLE;
    }
}

// return the limit to construction facility
std::size_t Plan::limit(const Settlement &settle)
{
    if (settle.getType() == SettlementType::VILLAGE)
    {
        return 1;
    }
    else if (settle.getType() == SettlementType::CITY)
    {
        return 2;
    }
    else
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

const string Plan::getSettlementName() const {
    return settlement.getName();
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
    environment_score += facility->getEnvironmentScore();
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

const string Plan::closeToString() const {
    return "Plan ID: " + std::to_string(plan_id) + "\n" +
           "SettlementName: " + settlement.getName() + "\n" +
           "LifeQualityScore: " + std::to_string(life_quality_score) + "\n" +
           "EconomyScore: " + std::to_string(economy_score) + "\n" +
           "EnvironmentScore: " + std::to_string(environment_score);
}

Plan::~Plan()
{
    // Clean up dynamically allocated memory for facilities under construction
    for (Facility *facility : underConstruction)
    {
        delete facility;
    }
    underConstruction.clear();
    // Clean up dynamically allocated memory for opersions facilities
    for (Facility *facility : facilities)
    {
        delete facility;
    }
    facilities.clear();
    // Delete the Selected Policy object
    delete selectionPolicy;
}

const int Plan::getID() const
{
    return plan_id;
}

Plan::Plan(const Plan &other)
    : plan_id(other.plan_id), settlement(other.settlement), selectionPolicy(other.selectionPolicy->clone()), status(other.status),
      facilities(vector<Facility *>()), underConstruction(vector<Facility *>()), facilityOptions(other.facilityOptions),
      life_quality_score(other.life_quality_score), economy_score(other.economy_score), environment_score(other.environment_score)
{
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
      status(other.status),
      facilities(std::move(other.facilities)),
      underConstruction(std::move(other.underConstruction)),
      facilityOptions(std::move(other.facilityOptions)),
      life_quality_score(other.life_quality_score),
      economy_score(other.economy_score),
      environment_score(other.environment_score)
{
    // Reset the source object
    other.underConstruction.clear();
    other.facilities.clear();
    selectionPolicy = nullptr;
}
