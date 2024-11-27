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
        /*int BalancedSelection::getLifeQualityScore() const
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
        */
        const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions)
        {    
            FacilityType toReturn = facilitiesOptions[0];
            int a=INT32_MAX;
            int tempA, tempB, tempC, tempD;
            for (int i=0; i<facilitiesOptions.size(); i++)
            {   
                int lqs, ecos, envs;
                lqs = LifeQualityScore + facilitiesOptions[i].getLifeQualityScore();
                ecos=EconomyScore + facilitiesOptions[i].getEconomyScore();
                envs=EnvironmentScore + facilitiesOptions[i].getEnvironmentScore();
                tempA=std::abs(lqs-ecos); tempB=std::abs(ecos-envs); tempC=std::abs(envs-lqs);
                if (tempA+tempB+tempC==0)
                        return facilitiesOptions[i];
                if (tempA+tempB+tempC<a)
                {
                        a=tempA+tempB+tempC;
                        tempD=i;
                }
                
                
            }
            return facilitiesOptions[tempD];

        }
        const string BalancedSelection::toString() const 
        {
                return "life quality score is: " +std::to_string(LifeQualityScore) + "/n" +
                "ecomony score is: " +std::to_string(EconomyScore) + "/n" +
                "environment score is: " +std::to_string(EnvironmentScore);
        }
        BalancedSelection* BalancedSelection::clone() const {
        return new BalancedSelection(LifeQualityScore, EconomyScore, EnvironmentScore);  
        }
        BalancedSelection::~BalancedSelection() = default;