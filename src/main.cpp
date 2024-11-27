//#include "Simulation.h"
#include <iostream>
#include "Settlement.h"
#include "Facility.h"
#include "SelectionPolicy.h"

using namespace std;

//Simulation* backup = nullptr;

int main(int argc, char** argv){
    if(argc!=2){
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    //Simulation simulation(configurationFile);
    //simulation.start();

    //Check blanced policy
    Settlement *s1 = new Settlement("Tel aviv", SettlementType::CITY);
    //cout << s1->toString() << endl;
    FacilityType* hospital = new FacilityType("Hospital", (FacilityCategory)0, 5, 5, 3 ,2);
    FacilityType* School = new FacilityType("School", (FacilityCategory)0, 4, 4, 2, 2);
    FacilityType* Park = new FacilityType("Park", (FacilityCategory)0, 3, 3, 1, 3);
    FacilityType* Factory = new FacilityType("Factory", (FacilityCategory)1, 5, 2, 5, 1);
    vector<FacilityType> v;
    v.push_back(*hospital);
    v.push_back(*School);
    v.push_back(*Park);
    v.push_back(*Factory);
    
    BalancedSelection pol(5, 4, 3);
    cout << pol.toString() << endl;
    cout << pol.selectFacility(v).getName() << endl;
    cout << pol.toString() << endl;
    //cout << std::to_string(hospital->getCost()) << endl;

    delete s1;
    
//    if(backup!=nullptr){
//    	delete backup;
//    	backup = nullptr;
//    }
    return 0;
}