#include "Settlement.h"

Settlement::Settlement(const string &name, enum SettlementType type) : 
                        name(name), type(type) {}
const string& Settlement::getName() const {
    return name;
}
SettlementType Settlement::getType() const {
    return type;
}
const string Settlement::toString() const {
    if (type == SettlementType::VILLAGE)
        return "Settlement Name is: " + name + ", Settlement type is: village";
    if (type == SettlementType::CITY)
        return "Settlement Name is: " + name + ", Settlement type is: city";
    if (type == SettlementType::METROPOLIS)
        return "Settlement Name is: " + name + ", Settlement type is: metropolis";
}

SettlementType Settlement::StringToSettlementType(const string& st) {
    if (st.compare("0") == 0) { return SettlementType::VILLAGE; }
    if (st.compare("1") == 0) { return SettlementType::CITY; }
    if (st.compare("2") == 0) { return SettlementType::METROPOLIS; }
}

string Settlement::settlementTypeToString(SettlementType st)
{
    if (st ==  SettlementType::VILLAGE) { return "village"; }
    if (st ==  SettlementType::CITY) { return "city"; }
    if (st == SettlementType::METROPOLIS) { return "metropolis"; }
}




