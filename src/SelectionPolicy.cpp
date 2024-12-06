#include "SelectionPolicy.h"
//--------------SelectionPolicy---------------------//
//---------funcions we've added-----------//

SelectionPolicy::SelectionPolicy(const string &policytype) : policyType(policytype) {}

bool SelectionPolicy::isTrueSelectionPolicy(const string &Selectionpolicy)
{
        if ((Selectionpolicy.compare("nve") == 0) || (Selectionpolicy.compare("eco") == 0) ||
            (Selectionpolicy.compare("bal") == 0) || (Selectionpolicy.compare("env") == 0))
        {
                return true;
        }
        return false;
}

const string &SelectionPolicy::getPolicyType() const
{
        return policyType;
}

//--------------NaiveSelection---------------------//
NaiveSelection::NaiveSelection() : SelectionPolicy("nve"), lastSelectedIndex(-1) {} // when we add 1 in "selectSelection" func it wil start in index 0
const FacilityType &NaiveSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
        lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size(); // Cycling on vector size
        return facilitiesOptions[lastSelectedIndex];
}
const string NaiveSelection::toString() const
{
        return "the last selected index is: " + std::to_string(lastSelectedIndex);
}
NaiveSelection *NaiveSelection::clone() const
{
        return new NaiveSelection(*this);
}

//--------------BalancedSelection---------------------//
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
    : SelectionPolicy("bal"), LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

const FacilityType &BalancedSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
        int minDif = INT32_MAX;
        int difLE = 0, difEE = 0, difEL = 0, nextFacility = 0;

        // Check which facility need to be built
        for (std::size_t i = 0; i < facilitiesOptions.size(); i++)
        {
                int lqs = LifeQualityScore + facilitiesOptions[i].getLifeQualityScore();
                int ecos = EconomyScore + facilitiesOptions[i].getEconomyScore();
                int envs = EnvironmentScore + facilitiesOptions[i].getEnvironmentScore();

                // Calculate the diff
                difLE = std::abs(lqs - ecos);
                difEE = std::abs(ecos - envs);
                difEL = std::abs(envs - lqs);

                // if it is totaly balance return the first one to do it
                if (difLE + difEE + difEL == 0)
                {
                        UpdateScores(*this, facilitiesOptions[i].getLifeQualityScore(), facilitiesOptions[i].getEconomyScore(), facilitiesOptions[i].getEnvironmentScore());
                        return facilitiesOptions[i];
                }
                // check if its better choice
                if (difLE + difEE + difLE < minDif)
                {
                        minDif = difLE + difEE + difEL;
                        nextFacility = i;
                }
        }
        // Update Scores
        UpdateScores(*this, facilitiesOptions[nextFacility].getLifeQualityScore(), facilitiesOptions[nextFacility].getEconomyScore(), facilitiesOptions[nextFacility].getEnvironmentScore());
        return facilitiesOptions[nextFacility];
}
const string BalancedSelection::toString() const
{
        return "life quality score is: " + std::to_string(LifeQualityScore) + "\n" +
               "ecomony score is: " + std::to_string(EconomyScore) + "\n" +
               "environment score is: " + std::to_string(EnvironmentScore);
}
BalancedSelection *BalancedSelection::clone() const
{
        return new BalancedSelection(*this);
}

// The function add the scores to the scores fields in a given balaced policy
void BalancedSelection::UpdateScores(BalancedSelection &pol, int quality, int economy, int environment)
{
        pol.LifeQualityScore += quality;
        pol.EconomyScore += economy;
        pol.EnvironmentScore += environment;
}

//--------------EconomySelection---------------------//
EconomySelection::EconomySelection() : SelectionPolicy("eco"), lastSelectedIndex(0) {}
const FacilityType &EconomySelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
        bool found = false;
        std::size_t i = (lastSelectedIndex + 1) % facilitiesOptions.size();
        // Assuming there is at least one economy facility in vector
        while (!found)
        {
                if (facilitiesOptions[i].getCategory() == FacilityCategory::ECONOMY)
                {
                        found = true;
                        lastSelectedIndex = i;
                }
                // Search in cycle until find next facility
                i = (i + 1) % facilitiesOptions.size();
        }
        return facilitiesOptions[lastSelectedIndex];
}
EconomySelection *EconomySelection::clone() const
{
        return new EconomySelection(*this);
}

const string EconomySelection::toString() const
{
        return "Last selected Index: " + std::to_string(lastSelectedIndex);
}

//--------------SustainabilitySelection---------------------//
SustainabilitySelection::SustainabilitySelection() : SelectionPolicy("env"), lastSelectedIndex(0) {}

const FacilityType &SustainabilitySelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
        bool found = false;
        std::size_t i = (lastSelectedIndex + 1) % facilitiesOptions.size();
        // Assuming there is at least one environment facility in vector
        while (!found)
        {
                if (facilitiesOptions[i].getCategory() == FacilityCategory::ENVIRONMENT)
                {
                        found = true;
                        lastSelectedIndex = i;
                }
                // Search in cycle until find next facility
                i = (i + 1) % facilitiesOptions.size();
        }
        return facilitiesOptions[lastSelectedIndex];
}

SustainabilitySelection *SustainabilitySelection::clone() const
{
        return new SustainabilitySelection(*this);
}

const string SustainabilitySelection::toString() const
{
        return "Last selected Index: " + std::to_string(lastSelectedIndex);
}
