#pragma once
#include "SelectionPolicy.h"

        NaiveSelection::NaiveSelection(): lastSelectedIndex(0){}
        NaiveSelection::NaiveSelection(int i): lastSelectedIndex(i){}
        const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) 
        {
                return facilitiesOptions[lastSelectedIndex+1];
        }
        const string NaiveSelection::toString() const 
        {
                return "the last selected index is: " + std::to_string(lastSelectedIndex);
        }
        NaiveSelection* NaiveSelection::clone() const 
        {
                return new NaiveSelection(lastSelectedIndex);
        }

        BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
        :LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore)  {}

        const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions)
        {
        int minDif = INT32_MAX;
        int difLE = 0, difEE = 0, difEL = 0, currFacility = 0;

        // Check which facility need to be built
        for (int i = 0; i < facilitiesOptions.size(); i++)
        {   
        int lqs = LifeQualityScore + facilitiesOptions[i].getLifeQualityScore();
        int ecos = EconomyScore + facilitiesOptions[i].getEconomyScore();
        int envs = EnvironmentScore + facilitiesOptions[i].getEnvironmentScore();

        // Calculate the diff
        difLE = std::abs(lqs-ecos); 
        difEE = std::abs(ecos-envs);
        difEL = std::abs(envs-lqs);

        // if it is totaly balance return the first one to do it
        if (difLE + difEE + difEL == 0) {
                UpdateScores(*this ,facilitiesOptions[i].getLifeQualityScore(),facilitiesOptions[i].getEconomyScore(), facilitiesOptions[i].getEnvironmentScore());
                return facilitiesOptions[i];
        }
        // check if its better choice
        if (difLE + difEE + difLE < minDif)
        {
                minDif = difLE + difEE + difEL;
                currFacility = i;
        }           
        }
        // Update Scores
        UpdateScores(*this ,facilitiesOptions[currFacility].getLifeQualityScore(),facilitiesOptions[currFacility].getEconomyScore(), facilitiesOptions[currFacility].getEnvironmentScore());
        return facilitiesOptions[currFacility];

        }
        const string BalancedSelection::toString() const 
        {
                return "life quality score is: " +std::to_string(LifeQualityScore) + "\n" +
                "ecomony score is: " +std::to_string(EconomyScore) + "\n" +
                "environment score is: " +std::to_string(EnvironmentScore);
        }
        BalancedSelection* BalancedSelection::clone() const {
                return new BalancedSelection(LifeQualityScore, EconomyScore, EnvironmentScore);  
        }

        // The function add the scores to the scores fields in a given balaced policy
        void BalancedSelection::UpdateScores(BalancedSelection& pol, int quality, int economy, int environment) {
                pol.LifeQualityScore += quality;
                pol.EconomyScore += economy;
                pol.EnvironmentScore += environment;
        }