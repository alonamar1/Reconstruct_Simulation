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
    if (st == "0") { return SettlementType::VILLAGE; }
    if (st == "1") { return SettlementType::CITY; }
    if (st == "2") { return SettlementType::METROPOLIS; }
}



