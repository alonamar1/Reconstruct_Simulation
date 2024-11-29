#include "Plan.h"

        Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
        plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), facilityOptions(facilityOptions), status(?????), underConstruction(???), 
        life_quality_score(0), economy_score(0), environment_score(0){} //??????

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
        void setSelectionPolicy(SelectionPolicy *selectionPolicy)
        {
            selectionPolicy=selectionPolicy; //??????
        }

        void step();

        void Plan::printStatus()
        {
            if (status == PlanStatus::AVALIABLE)
                std::cout << "AVAILABLE" << std::endl;
            if (status == PlanStatus::BUSY)
                cout << "BUSY" << endl; 
        }

        const vector<Facility*>& Plan::getFacilities() const
        {
            return facilities;
        }

        void addFacility(Facility* facility);
        const string toString() const;


