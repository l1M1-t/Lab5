#ifndef LAB2_PARAMETER_H
#define LAB2_PARAMETER_H

#include <string>
#include <iostream>

using namespace std;

class Parameter {
private:
    string value;
    bool isConst;
public:
    //default constructor
    Parameter() {
        value = "";
        isConst = false;
    }
    // getters
    string getValue() const {
        return value;
    }

    bool getConst() const {
        return isConst;
    }

    // setters
    void setValue(string input) {
        if (input.at(0) != '\'') {
            value = input;
            setConst(false);
        } else {
            value = input;
            setConst(true);
        }
    }

    void setConst(bool isConst) {
        this->isConst = isConst;
    }

    void toString() const {
        cout << value;
    }

    void clear() {
        value = "";
    }
};

#endif //LAB2_PARAMETER_H
