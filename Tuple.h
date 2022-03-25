#ifndef LAB3_TUPLE_H
#define LAB3_TUPLE_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Scheme.h"

using namespace std;

class Tuple : public vector<string> {
private:

public:
    Tuple() {}

    Tuple(vector<string> values) : vector<string>(values) {}

    string toString(const Scheme& scheme) const {
        stringstream out;
        for (int i = 0; i < (int)size(); i++) {
            if (i > 0)
                out << ", ";
            const string& name = scheme.at(i);
            const string& value = at(i);
            if (value != "''")
                out << name << "=" << value;
        }
        return out.str();
    }
};

#endif //LAB3_TUPLE_H
