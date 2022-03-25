#ifndef LAB3_RELATION_H
#define LAB3_RELATION_H

#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include "Scheme.h"
#include "Tuple.h"
#include <map>

using namespace std;

class Relation {
private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;
    map<int, int> matchingCols;
public:
    Relation() {};
    Relation(const string& name, const Scheme& scheme) : name(name), scheme(scheme) {}

    // getters
    string getName() const {
        return name;
    }

    Scheme getScheme() const {
        return scheme;
    }

    set<Tuple> getTuples() const {
        return tuples;
    }

    // setters
    void setName(string value) {
        name = value;
    }

    void setScheme(Scheme s) {
        scheme = s;
    }

    void setTuples(set<Tuple> t) {
        tuples = t;
    }

    int size() const {
        return tuples.size();
    }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

    // type 1
    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        //
        for (auto& tuple : tuples)
            if (tuple.at(index) == value)
                result.addTuple(tuple);
        return result;
    }

    // type 2
    Relation select(int index1, int index2) const {
        Relation result(name, scheme);

        for (auto& tuple : tuples) {
            if (tuple.at(index1) == tuple.at(index2)) {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    Relation project(vector<int> colsToKeep) {
        Scheme newScheme;

        for (auto& index : colsToKeep) {
            newScheme.push_back(scheme[index]);
        }

        Relation newResult(name, newScheme);

        for (auto& tuple : tuples) {
            vector<string> temp;
            for (int i = 0; i < (int)colsToKeep.size(); i++) {
                int index = colsToKeep[i];
                temp.push_back(tuple[index]);
            }
            Tuple newTuple(temp);
            newResult.addTuple(newTuple);
        }

        return newResult;
    }

    Relation rename(vector<string> var) {
        // Rename the scheme of the relation to the variable names
        for (int i = 0; i < (int)var.size(); i++) {
            scheme[i] = var[i];
        }

        Relation result(name, scheme);

        for (auto& tuple : tuples) {
            result.addTuple(tuple);
        }

        return result;
    }

    string toString() const {
        stringstream out;
        for (auto& tuple : tuples) {
            out << "  " << tuple.toString(scheme) << endl;
        }
        return out.str();
    }

    static bool joinable(const Tuple& leftTuple, const Tuple& rightTuple, const map<int, int> cols) {
        for (auto& c : cols) {
            if (leftTuple[c.first] != rightTuple[c.second]) {
                return false;
            }
        }

        return true;
    }

    Relation join(const Relation &rhs) {
        // create r1 to increase the easiness to follow the code
        Scheme newScheme = scheme;
        // keep track of columns that need to be removed
        vector<int>colsToRemove;
        vector<int>match;

        // combine the two schemes
        Scheme leftScheme = scheme;
        Scheme rightScheme = rhs.getScheme();
        // concatenate both schemes into the same vector
        for (auto& s : rightScheme) {
            newScheme.push_back(s);
        }

        //add the newScheme to the new Relation
        Relation newRelation(name, newScheme);

        // find the columns of the schemes that are the same and store it in matchingCols
        for (int i = 0; i < (int)scheme.size(); i++) {
            for (int j = 0; j < (int)rhs.getScheme().size(); j++) {
                if (scheme[i] == rhs.getScheme()[j]) {
                    matchingCols.insert({i, j});
                }
            }
        }

        // add the tuples to the new relation
        for (auto& leftTuple : tuples) {
            for (auto& rightTuple: rhs.getTuples()) {
                Tuple newTuple = leftTuple;
                if (joinable(leftTuple, rightTuple, matchingCols)) {
                    for (auto& s : rightTuple) {
                        newTuple.push_back(s);
                    }
                    newRelation.addTuple(newTuple);
                }
            }
        }

        map<string, int>map;
        // find the columns that do are not repetitive
        for (int i = 0; i < (int)newRelation.getScheme().size(); i++) {
            string v = newRelation.getScheme()[i];
            if (map.find(v) == map.end()) {
                map.insert({v, i});
                colsToRemove.push_back(i);
            }
        }

        newRelation = newRelation.project(colsToRemove);

        return newRelation;
    }

    void unionize(Relation r) {
        if (this->scheme != r.getScheme()) {
            throw "Cannot combine b/c the schemes are different!";
        }

        for (auto& t : r.getTuples()) {
            if (add(t)) {
                if (t.size() > 0) {
                    cout << "  " << t.toString(scheme) << endl;
                }
            }
        }
    }

    bool add(Tuple t) {
        return tuples.insert(t).second;
    }
};

#endif //LAB3_RELATION_H
