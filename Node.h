#ifndef LAB5_NODE_H
#define LAB5_NODE_H

#include <set>
#include <iostream>

using namespace std;

class Node {
private:
    set<int> adjacentNodeIDs;
public:
    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    void toString() const {
        // counter
        int i = 0;
        for (auto& num : adjacentNodeIDs) {
            i++;
            cout << "R" << num;
            if (i < (int)adjacentNodeIDs.size()) {
                cout << ",";
            } else
                cout << endl;
        }
    }
};

#endif //LAB5_NODE_H
