#include "Settlement.h"
#include "Facility.h"
#include "SelectionPolicy.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
    string configurationFile = argv[1];
    //Check blanced policy
    Settlement *s1 = new Settlement("Tel aviv", SettlementType::CITY);
    cout << s1->toString() << endl;
    FacilityType* hospital = new FacilityType("hospital", FacilityCategory::LIFE_QUALITY, 5, 5, 3 ,2);
    FacilityType* School = new FacilityType("school", FacilityCategory::LIFE_QUALITY, 4, 4, 2, 2);
    FacilityType* Park = new FacilityType("park", FacilityCategory::LIFE_QUALITY, 3, 3, 1, 3);
    FacilityType* Factory = new FacilityType("factory", FacilityCategory::ECONOMY, 5, 2, 5, 1);
    vector<FacilityType> v;
    v.push_back(*hospital);
    v.push_back(*School);
    v.push_back(*Park);
    v.push_back(*Factory);

    BalancedSelection pol(5, 4, 3);
    cout << pol.toString() << endl;
    cout << pol.selectFacility(v).getName() << endl;
    cout << pol.toString() << endl;
    //cout << std::to_string(hospital->getCost()) << endl; */
    
    delete s1;
    delete hospital;
    delete School;
    delete Park;
    delete Factory;

    return 0;
}