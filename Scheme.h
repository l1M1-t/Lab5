#ifndef LAB3_SCHEME_H
#define LAB3_SCHEME_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Scheme : public vector<string> {
private:
    int numVar = 0;
public:
    // default constructor
    Scheme() {};
    // non-default constructor
    Scheme(vector<string> names) : vector<string>(names) {}

    // getter
    int getNumVar() const {
        return numVar;
    }

    // setter
    void setNumVar(int newNum) {
        numVar = newNum;
    }
};

#endif //LAB3_SCHEME_H
