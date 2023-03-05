#include <iostream>
#include "Graph.h"


int main() {
    Graph<int, int> g1;
    std::cout << "size: " << g1.size() << std::endl;
    std::cout << "Is empty? (before inserting nodes) " << g1.empty() << std::endl;
    g1.clear();
    auto beg = g1.begin();
    auto end = g1.end();
    auto cbeg = g1.cbegin();
    auto cend = g1.cend();
    //Inserting some nodes
    g1.insert_node(0, 25);
    g1.insert_node(1, 36);
    g1.insert_node(3, 45);
    g1.insert_node(std::make_pair(4, 5));
    g1.insert_or_assign_node(0, -36);
    auto pair1 = g1.insert_or_assign_node(3, 23);
    auto pair2 = g1.insert_or_assign_node(std::make_pair(0, 3));
    auto pair3 = g1.insert_node(4, -314);
    //Check is correct
    std::cout << "key:" << pair1.first->first << "  value:" << pair1.first->second <<
                                               "  bool:" << pair1.second << std::endl;
    std::cout << "key:" << pair2.first->first << "  value:" << pair2.first->second <<
                                               "  bool:" << pair2.second << std::endl;
    std::cout << "key:" << pair3.first->first << " value:" << pair3.first->second <<
                                               "  bool:" << pair3.second << std::endl;
    std::cout << std::endl << "size of graph:" << g1.size() << std::endl;
    std::cout << g1.loop(4) << std::endl;
    g1.insert_edge(1, 1, 2);
    g1.insert_edge(3, 1, 7);
    std::cout << g1.insert_or_assign_edge(1, 1, 3).second << std::endl;
    std::cout << g1.insert_or_assign_edge(std::make_pair(3, 3), 4).second << std::endl;
    std::cout << g1.loop(0) << std::endl;
    return 0;
}