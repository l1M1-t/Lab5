#ifndef LAB5_GRAPH_H
#define LAB5_GRAPH_H

#include "Node.h"
#include <iostream>
#include <map>
using namespace std;

class Graph {
private:
    map<int, Node> nodes;
public:
    Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++) {
            nodes[nodeID] = Node();
        }
    }

    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    void toString() const {
        // counter
        int i = 0;
        for (auto& pair : nodes) {
            i++;
            int nodeID = pair.first;
            cout << "R" << nodeID << ":";
            const Node& node = pair.second;
            node.toString();
            cout << endl;
        }
    }
};

#endif //LAB5_GRAPH_H
