#ifndef LAB3_DATABASE_H
#define LAB3_DATABASE_H

#include "Relation.h"
#include <iostream>
#include <map>

using namespace std;

class Database {
private:
    map<string, Relation> relations;
public:
    Database() {}
    Database(const map<string, Relation>& relations) : relations(relations) {}

    void insert(Relation r) {
        relations.insert({r.getName(), r});
    }

    Relation getRelationCopy(string name) {
        return relations.at(name);
    }

    Relation& getRelationReference(string name) {
        return relations.at(name);
    }

    unsigned int size() {
        unsigned int count = 0;
        for (auto p: relations) {
            count += p.second.size();
        }
        return count;
    }

    string toString() const {
        stringstream out;
        for (auto p : relations) {
            out << p.first << endl;
            out << p.second.toString() << endl;
        }
        return out.str();
    }
};

#endif //LAB3_DATABASE_H
