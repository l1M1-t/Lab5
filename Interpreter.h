#ifndef LAB3_INTERPRETER_H
#define LAB3_INTERPRETER_H

#include "Database.h"
#include "DataLog.h"
#include "Relation.h"
#include "Parameter.h"
#include "Graph.h"

class Interpreter {
private:
    dataLog datalog;
    Database database;
public:
    Interpreter(dataLog datalog) : datalog(datalog) {}

    // getter
    Database getDatabase() const {
        return database;
    }

    void run() {
        evalSchemes();
        evalFacts();
        evalRules();
        evalQueries();
    }

    void evalSchemes() {
        for (Predicate p : datalog.getSchemes()) {
            Relation newR;
            vector<string> contents;
            for (Parameter param : p.getParameters()) {
                contents.push_back(param.getValue());
            }
            newR.setScheme(Scheme(contents));
            newR.setName(p.getID());
            database.insert(newR);
        }
    }

    void evalFacts() {
        for (Predicate p : datalog.getFacts()) {
            Relation newR = database.getRelationReference(p.getID());
            vector<string> contents;
            for (Parameter param : p.getParameters()) {
                contents.push_back(param.getValue());
            }
            database.getRelationReference(p.getID()).addTuple(Tuple(contents));
        }
    }

    void evalRules() {
        cout << "Rule Evaluation" << endl;
        evalRuleListAlg(datalog.getRules());
    }

    void evalRuleListAlg(vector<Rule> rules) {
        unsigned int numTupBefore = 0;
        unsigned int numTupAfter = 0;
        int numPasses = 0;
        do {
            numPasses++;
            numTupBefore = (unsigned int)database.size();
            //segmentation fault
            evalRuleList(rules);
            numTupAfter = (unsigned int)database.size();
        } while(numTupBefore != numTupAfter);

        cout << endl << "Schemes populated after " << numPasses << " passes through the Rules." << endl << endl;
    }

    void evalRuleList(vector<Rule> rules) {
        //cn(c, n) :- snap(S, N, A, P), csg(C, S, G)
        for (Rule r : rules) {
            vector<Relation> bodyRelations;
            vector<int> colsToKeep;
            //cout << r.toString() << endl;
            for (auto& p : r.getBody()) {
                Relation currR = evaluatePredicate(p);
                bodyRelations.push_back(currR);
            }

            Relation result = bodyRelations[0];
            for (unsigned int i = 1; i < (unsigned int)bodyRelations.size(); i++) {
                result = result.join(bodyRelations[i]);
            }

            //extracting the locations of the schemes of the rule from joined relation
            vector<Parameter> temp = r.getHeadPred().getParameters();

            for (auto& param : temp) {
                for (int i = 0; i < (int)result.getScheme().size(); i++) {
                    vector<string> var = result.getScheme();
                    if (param.getValue() == var[i]) {
                        colsToKeep.push_back(i);
                    }
                }
            }

            result = result.project(colsToKeep);

            string name = r.getHeadPred().getID();
            result = result.rename(database.getRelationReference(name).getScheme());

            //print the rule that is being evaluated
            r.toString();

            database.getRelationReference(name).unionize(result);
        }
    }

    void evalQueries() {
        cout << "Query Evaluation" << endl;
        for (Predicate p : datalog.getQueries()) {
            Relation newR = evaluatePredicate(p);

            p.toString();
            if ((int)newR.getTuples().size() > 0) {
                cout << "Yes(" << (int)newR.getTuples().size() << ")" << endl;
                if (!(p.isAllConst())) {
                    cout << newR.toString();
                }
            } else {
                cout << "No" << endl;
            }
        }
    }

    Relation evaluatePredicate(Predicate p) {
        Relation currR = database.getRelationCopy(p.getID());

        // create vectors that will store the location of the matching parameters
        // and variables that are matched
        vector<string> var;
        vector<int> index;
        map<string, int> seen;

        for (int i = 0; i < (int)p.getParameters().size(); i++) {
            // currP is the parameter we are checking for in the set of tuples
            Parameter currP = p.getParameters()[i];

            // is the parameter a constant?
            if (currP.getConst()) {
                currR = currR.select(i, currP.getValue());
            }
            // parameter is a variable
            else {
                // iterate through the set of tuples (columns) and check the parameters
                if (seen.find(currP.getValue()) != seen.end()) {
                    // type 2 select
                    currR = currR.select(i, seen.at(currP.getValue()));
                } else {
                    var.push_back(currP.getValue());
                    index.push_back(i);
                    seen[currP.getValue()] = i;
                }
            }
        }

        //project
        currR = currR.project(index);
        //rename
        currR = currR.rename(var);

        return currR;
    }

    static Graph makeGraph(const vector<Rule>& rules) {
        Graph graph(rules.size());

        for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
            const Rule& fromRule = rules.at(fromID);
            cout << "from rule R" << fromID << ": ";
            fromRule.toString();

            for (unsigned pred = 0; pred < (unsigned)fromRule.sizeBody(); pred++) {
                Predicate bodyPred(fromRule.getBody()[pred]);
                bodyPred.setID(fromRule.getBody()[pred].getID());
                cout << "from body predicate: ";
                bodyPred.toStringRule();

                for (unsigned toID = 0; toID < rules.size(); toID++) {
                    const Rule& toRule = rules.at(toID);
                    cout << "to rule R" << toID << ": ";
                    toRule.toString();

                    if (fromRule.getHeadPred().getID() == fromRule.getBody()[pred].getID()) {
                        cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl;
                    }
                }
            }
        }

        return graph;
    }
};

#endif //LAB3_INTERPRETER_H
