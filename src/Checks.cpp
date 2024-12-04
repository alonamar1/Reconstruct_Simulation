#include "Settlement.h"
#include "Facility.h"
#include "SelectionPolicy.h"
#include "Plan.h"
#include "Auxiliary.h"
#include "Simulation.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv){
    string configurationFile = argv[1];
    Simulation simul(configurationFile);
    simul.start();
    // for (string s: config_File) {
    //     std::cout << s << std::endl;
    // }


    //Check blanced policy
    Settlement *s1 = new Settlement("Tel aviv", SettlementType::CITY);
    //cout << s1->toString() << endl;
    FacilityType* hospital = new FacilityType("hospital", FacilityCategory::LIFE_QUALITY, 5, 5, 3 ,2);
    FacilityType* School = new FacilityType("school", FacilityCategory::LIFE_QUALITY, 4, 4, 2, 2);
    FacilityType* Park = new FacilityType("park", FacilityCategory::LIFE_QUALITY, 3, 3, 1, 3);
    FacilityType* Factory = new FacilityType("factory", FacilityCategory::ECONOMY, 5, 2, 5, 1);
    FacilityType* CommunityCenter = new FacilityType("CommunityCenter", FacilityCategory::LIFE_QUALITY, 4, 5, 2, 3);
    vector<FacilityType> v;
    v.push_back(*hospital);
    v.push_back(*School);
    v.push_back(*Park);
    v.push_back(*Factory);
    v.push_back(*CommunityCenter);

    BalancedSelection *pol = new BalancedSelection(5, 4, 3);
    //cout << pol->toString() << endl;
    //cout << pol->selectFacility(v).getName() << endl;
    //cout << pol->toString() << endl;
    //cout << std::to_string(hospital->getCost()) << endl; 
    const int id = 1;

    Plan p1 = Plan(id, *s1, pol, v);
    //cout << p1.toString() << endl;
    NaiveSelection *nvePol = new NaiveSelection();
    EconomySelection *ecoPol = new EconomySelection();
    //p1.setSelectionPolicy(nvePol);
    cout << p1.toString() << endl;
    p1.step();
    p1.step();
    p1.step();
    p1.step();
    p1.step();
    p1.step();
    cout << p1.toString() << endl;
    Plan *p2 = new Plan(p1);
    p2->setSelectionPolicy(nvePol);
    cout << p2->toString() << endl;

    delete p2;
    delete s1;
    delete hospital;
    delete School;
    delete Park;
    delete CommunityCenter;
    delete Factory;
    //delete nvePol;
    delete ecoPol;

    return 0;
}