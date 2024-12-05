#include "Settlement.h"
#include <iostream>

Settlement::Settlement(const string &name, enum SettlementType type) : name(name), type(type) {}
const string &Settlement::getName() const
{
    return name;
}
Settlement::Settlement(const Settlement &s): name(s.getName()), type(s.getType()){}

SettlementType Settlement::getType() const
{
    return type;
}
const string Settlement::toString() const
{
    if (type == SettlementType::VILLAGE)
        return "Settlement Name is: " + name + ", Settlement type is: village";
    else if (type == SettlementType::CITY)
        return "Settlement Name is: " + name + ", Settlement type is: city";
    else
        return "Settlement Name is: " + name + ", Settlement type is: metropolis";
}

SettlementType Settlement::StringToSettlementType(const string &st)
{
    if (st.compare("0") == 0)
    {
        return SettlementType::VILLAGE;
    }
    else if (st.compare("1") == 0)
    {
        return SettlementType::CITY;
    }
    else if (st.compare("2") == 0)
    {
        return SettlementType::METROPOLIS;
    }
    throw std::runtime_error("The string: " + st + " dont represent a valid SettlementType.");
}

string Settlement::settlementTypeToString(SettlementType st)
{
    if (st == SettlementType::VILLAGE)
    {
        return "village";
    }
    else if (st == SettlementType::CITY)
    {
        return "city";
    }
    else
    {
        return "metropolis";
    }
}
