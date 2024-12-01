#pragma once
#include <vector>
#include "Facility.h"
using std::vector;

class SelectionPolicy {
    public:
        virtual const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) = 0;
        virtual const string toString() const = 0;
        virtual SelectionPolicy* clone() const = 0;
        virtual ~SelectionPolicy() = default;
        virtual SelectionPolicy& operator=(const SelectionPolicy& other) = default;
        static bool isTrueSelectionPolicy(const string &Selectionpolicy);
};

class NaiveSelection: public SelectionPolicy {
    public:
        NaiveSelection();
        NaiveSelection(int i);
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        NaiveSelection *clone() const override;
        ~NaiveSelection() override = default;
        NaiveSelection& operator=(const NaiveSelection& other) = default;
    private:
        int lastSelectedIndex;
};

class BalancedSelection: public SelectionPolicy {
    public:
        BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore);
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        BalancedSelection *clone() const override;
        ~BalancedSelection() override = default;
        static void UpdateScores(BalancedSelection& pol, int quality, int economy, int environment); // update scores in all classes
        BalancedSelection& operator=(const BalancedSelection& other) = default;
    private:
        int LifeQualityScore;
        int EconomyScore;
        int EnvironmentScore;
};

class EconomySelection: public SelectionPolicy {
    public:
        EconomySelection();
        EconomySelection(int i);
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        EconomySelection *clone() const override;
        ~EconomySelection() override = default;
        EconomySelection& operator=(const EconomySelection& other) = default;
    private:
        int lastSelectedIndex;

};

class SustainabilitySelection: public SelectionPolicy {
    public:
        SustainabilitySelection();
        SustainabilitySelection(int i);
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        SustainabilitySelection *clone() const override;
        ~SustainabilitySelection() override = default;
        SustainabilitySelection& operator=(const SustainabilitySelection& other) = default;
    private:
        int lastSelectedIndex;
};