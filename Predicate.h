#ifndef LAB2_PREDICATE_H
#define LAB2_PREDICATE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Parameter.h"

using namespace std;

class Predicate {
private:
    string id;
    vector<Parameter> params;
public:
    Predicate() {}
    // non-default constructor
    Predicate(string title) {
        id = title;
    }

    // getters
    string getID() const {
        return id;
    }

    vector<Parameter> getParameters() const {
        return params;
    }

    // setters
    void setID(string input) {
        id = input;
    }

    void addID(string input) {
        id = getID() + input;
    }

    void setParameters(Parameter input) {
        params.push_back(input);
    }

    void clearID() {
        id = "";
    }

    void clearParam() {
        params.clear();
    }

    void clear() {
        clearID();
        clearParam();
    }

    void toString() const {
        cout << id << "(";

        // print the parameters
        for (int j = 0; j < (int)params.size(); j++) {
            params[j].toString();
            if (j < (int)(params.size() - 1)) {
                cout << ",";
            }
        }

        cout << ")? ";
    }

    void toStringRule() const {
        cout << id << "(";

        for (int j = 0; j < (int)params.size(); j++) {
            params[j].toString();
            if (j < (int)(params.size() - 1)) {
                cout << ",";
            }
        }

        cout << ")" << endl;
    }

    bool isAllConst() const {
        bool temp = false;

        for (auto& param : params) {
            if (param.getConst() == false) {
                temp = false;
                return temp;
            } else {
                temp = true;
            }
        }

        return temp;
    }
};

#endif //LAB2_PREDICATE_H
