#include <iostream>
#include "Graph.h"


int main() {
    Graph<int, int> g1;
    std::cout << "size: " << g1.size() << std::endl;
    std::cout << "Is empty? " << g1.empty() << std::endl;
    g1.clear();..
    auto beg = g1.begin();
    auto end = g1.end();
    auto cbeg = g1.cbegin();
    auto cend = g1.cend();
    std::cout << "program completed successfully" << std::endl;
    return 0;
}