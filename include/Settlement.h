#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Facility;

enum class SettlementType {
    VILLAGE,
    CITY,
    METROPOLIS,
};

class Settlement {
    public:
        Settlement(const string &name, SettlementType type);
        Settlement(const Settlement &s); //copy consrtructor 
        const string &getName() const;
        SettlementType getType() const;
        const string toString() const;

        //---------funcions we've added-----------// 
        static SettlementType StringToSettlementType (const string&);  //convert string to settlement type
        static string settlementTypeToString(SettlementType st); // convert settlement type to string

        private:
            const string name;
            SettlementType type;
};