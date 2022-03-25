#include "Node.h"
#include "Graph.h"
#include "Interpreter.h"
#include "Rule.h"
#include "Predicate.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    /*Node node;
    node.addEdge(4);
    node.addEdge(8);
    node.addEdge(2);
    node.toString();

    Graph graph(3);
    graph.addEdge(1, 2);
    graph.addEdge(1, 0);
    graph.addEdge(0, 1);
    graph.addEdge(1, 1);
    graph.toString();*/

    // predicate names for fake rules
    // first is name for head predicate
    // second is names for body predicates
    pair<string,vector<string>> ruleNames[] = {
            { "A", { "B" } },
            { "B", { "B", "A" } },
    };

    vector<Rule> rules;

    for (auto& rulePair : ruleNames) {
        string headName = rulePair.first;
        Rule rule = Rule(Predicate(headName));
        vector<string> bodyNames = rulePair.second;
        for (auto& bodyName : bodyNames)
            rule.getBody().push_back(Predicate(bodyName));
        rules.push_back(rule);
    }

    Graph graph = Interpreter::makeGraph(rules);
    graph.toString();

    return 0;
}
