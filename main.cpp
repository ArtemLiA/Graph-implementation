#include <iostream>
#include "Graph.h"


int main() {
    Graph<int, int> g1;
    std::cout << "size: " << g1.size() << std::endl;
    std::cout << "Is empty? " << g1.empty() << std::endl;
    g1.clear();
    auto beg = g1.begin();
    auto end = g1.end();
    auto cbeg = g1.cbegin();
    auto cend = g1.cend();
    std::cout << "program completed successfully" << std::endl;
    std::cout << cbeg->first << cbeg ->second << std::endl;
    //loop check
    try {
        std::cout << g1.loop(0) << std::endl;
    }
    catch(std::out_of_range out){
        std::cout << out.what() << std::endl;
    }
    //degree_in check
    try {
        std::cout << g1.degree_in(0) << std::endl;
    }
    catch(std::out_of_range out){
        std::cout << out.what() << std::endl;
    }
    //degree_out check
    try {
        std::cout << g1.degree_out(0) << std::endl;
    }
    catch(std::out_of_range out){
        std::cout << out.what() << std::endl;
    }
    return 0;
}