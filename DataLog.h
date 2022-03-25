#ifndef LAB2_DATALOG_H
#define LAB2_DATALOG_H

#include <vector>
#include <set>
#include "Predicate.h"
#include "Rule.h"

using namespace std;

class dataLog{
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
    set<string> domains;
public:
    // getters

    vector<Predicate>& getSchemes() {
        return schemes;
    }

    vector<Predicate>& getFacts() {
        return facts;
    }

    vector<Predicate>& getQueries() {
        return queries;
    }

    vector<Rule>& getRules() {
        return rules;
    }

    set<string>& getDomains() {
        return domains;
    }

    // toString methods

    void schemesToString() const {
        cout << "Schemes(" << schemes.size() << "):\n";

        // print the ID
        for (int i = 0; i < (int)schemes.size(); i++) {
            cout << "  " << schemes[i].getID();

            // print the parenthesis
            cout << "(";

            // print the parameters
            for (int j = 0; j < (int)schemes[i].getParameters().size(); j++) {
                schemes[i].getParameters()[j].toString();
                if (j < (int)(schemes[i].getParameters().size() - 1)) {
                    cout << ",";
                }
            }

            // close the parenthesis
            cout << ")\n";
        }
    }

    void factsToString() const {
        cout << "Facts(" << facts.size() << "):\n";

        // print the ID
        for (int i = 0; i < (int)facts.size(); i++) {
            cout << "  " << facts[i].getID();

            cout << "(";

            // print the parameters
            for (int j = 0; j < (int)facts[i].getParameters().size(); j++) {
                facts[i].getParameters()[j].toString();
                if (j < (int)(facts[i].getParameters().size() - 1)) {
                    cout << ",";
                }
            }

            cout << ")." << endl;
        }
    }

    void queriesToString() const {
        cout << "Queries(" << queries.size() << "):\n";

        // print the ID
        for (int i = 0; i < (int)queries.size(); i++) {
            cout << "  " << queries[i].getID();

            cout << "(";

            // print the parameters
            for (int j = 0; j < (int)queries[i].getParameters().size(); j++) {
                queries[i].getParameters()[j].toString();
                if (j < (int)(queries[i].getParameters().size() - 1)) {
                    cout << ",";
                }
            }

            cout << ")?" << endl;
        }
    }

    void rulesToString() const {
        cout << "Rules(" << rules.size() << "):\n";

        // print headPredicate
        for (int i = 0; i < (int)rules.size(); i++) {
            cout << "  " << rules[i].getHeadPred().getID();

            cout << "(";

            // print the parameters
            for (int j = 0; j < (int)rules[i].getHeadPred().getParameters().size(); j++) {
                rules[i].getHeadPred().getParameters()[j].toString();
                if (j < (int)(rules[i].getHeadPred().getParameters().size() - 1)) {
                    cout << ",";
                }
            }

            cout << ")";

            cout << " :- ";

            // print the body
            for (int k = 0; k < (int)rules[i].getBody().size(); k++) {
                cout << rules[i].getBody()[k].getID();

                cout << "(";

                // print the parameters of the body
                for (int l = 0; l < (int)rules[i].getBody()[k].getParameters().size(); l++) {
                    rules[i].getBody()[k].getParameters()[l].toString();
                    if (l < (int)(rules[i].getBody()[k].getParameters().size() - 1)) {
                        cout << ",";
                    }
                }

                cout << ")";

                // separate each body with comma
                if (k < (int)rules[i].getBody().size() - 1) {
                    cout << ",";
                }
            }

            // period if it's the last rule
            if (i < (int)rules.size()) {
                cout << "." << endl;
            }
        }
    }

    void domainsToString() const {
        // counter
        int c = 0;

        cout << "Domain(" << domains.size() << "):\n";

        // print the strings
        for (set<string>::const_iterator it = domains.cbegin(); it != domains.cend(); ++it) {
            cout << "  " << *it << endl;

            c++;
        }
    }
};

#endif //LAB2_DATALOG_H
