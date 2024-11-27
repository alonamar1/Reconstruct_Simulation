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
        NaiveSelection::~NaiveSelection() = default;


        BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore){
        LifeQualityScore=LifeQualityScore;
        EconomyScore=EconomyScore;
        EnvironmentScore=EnvironmentScore;
        }
        int BalancedSelection::getLifeQualityScore() const
        {
                return LifeQualityScore;
        }
        int BalancedSelection::getEconomyScore() const
        {
                return EconomyScore;
        }
        int BalancedSelection::getEnvironmentScore() const
        {
                return EnvironmentScore;
        }
        const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions)
        {
            int a=INT32_MAX;
            for (FacilityType f:facilitiesOptions)
            {   
                int lqs=0;
                int ecos=0, envs=0;
                lqs = f.getLifeQualityScore();
            }
        
        }
        //const string toString() const override;
        //BalancedSelection *clone() const override;
        //~BalancedSelection() override = default;