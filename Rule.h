#ifndef LAB2_RULE_H
#define LAB2_RULE_H

#include <vector>
#include <iostream>
#include <string>
#include "Predicate.h"

using namespace std;

class Rule {
private:
    Predicate headPred;
    vector<Predicate> body;
public:
    // non-default constructor
    Rule(Predicate head) {
        headPred = head;
    }

    Predicate getHeadPred() const {
        return headPred;
    }

    Predicate& getHeadPred() {
        return headPred;
    }

    vector<Predicate> getBody() const {
        return body;
    }

    vector<Predicate>& getBody() {
        return body;
    }

    void setHeadPred(Predicate input) {
        headPred = input;
    }

    void setBody(vector<Predicate> input) {
        body = input;
    }

    int sizeBody() const {
        int size = 0;
        size = (int)body.size();
        return size;
    }

    void clear() {
        headPred.clear();
        body.clear();
    }

    void toString() const {
        cout << headPred.getID();

        cout << "(";

        // print the parameters
        for (int j = 0; j < (int)headPred.getParameters().size(); j++) {
            headPred.getParameters()[j].toString();
            if (j < (int)(headPred.getParameters().size() - 1)) {
                cout << ",";
            }
        }

        cout << ")";

        cout << " :- ";

        // print the body
        for (int k = 0; k < (int)body.size(); k++) {
            cout << body[k].getID();

            cout << "(";

            // print the parameters of the body
            for (int l = 0; l < (int)body[k].getParameters().size(); l++) {
                body[k].getParameters()[l].toString();
                if (l < (int)(body[k].getParameters().size() - 1)) {
                    cout << ",";
                }
            }

            cout << ")";

            // separate each body with comma
            if (k < (int)body.size() - 1) {
                cout << ",";
            }
        }

        cout << "." << endl;
    }
};

#endif //LAB2_RULE_H
