#include <iostream>
#include "Graph.h"


int main() {
    //GRAPH 1
    Graph<int, int, int> g1;
    g1.insert_node(-364, -364);
    g1.insert_node(-126, -126);
    g1.insert_node(-8, -8);
    g1.insert_node(0, 0);
    g1.insert_node(123, 123);
    g1.insert_node(136, 136);
    g1.insert_node(789, 789);
    g1.insert_node(1325, 1325);
    g1.insert_node(2042, 2042);
    g1.insert_node(7889, 7889);


    g1.insert_edge(-364, 7889, 2);
    g1.insert_edge(-364, -126, 14);
    g1.insert_edge(-364, -126, 13);
    g1.insert_edge(-364, 123, 7);

    g1.insert_edge(-126, 123, -12);

    g1.insert_edge(-8, -364, -14);
    g1.insert_edge(-8, -8, 17);

    g1.insert_edge(0, -364, 35);

    g1.insert_edge(123, 1325, 17);
    g1.insert_edge(123, 789, 1);
    g1.insert_edge(123, 2042, 14);
    g1.insert_edge(123, -8, 78);
    g1.insert_edge(123, -8, -8);

    g1.insert_edge(136, 0, 4);
    g1.insert_edge(136, 0, 16);
    g1.insert_edge(136, -364, 19);
    g1.insert_edge(136, -8, 102);

    g1.insert_edge(789, 2042, 16);

    g1.insert_edge(1325, 123, 23);

    g1.insert_edge(7889, -126, 12);
    //Tests 1
    std::cout << "GRAPH 1" << std::endl;
    std::cout << "Is empty? " << g1.empty() << std::endl;
    std::cout << "Loop in (-8) " << g1.loop(-8) << std::endl;
    std::cout << "Loop in (123) " << g1.loop(123) << std::endl;
    std::cout << "Degree in (-364) " << g1.degree_in(-364) << std::endl;
    std::cout << "Degree out (123) " << g1.degree_out(123) << std::endl;
    std::cout << "Degree in (7889) " << g1.degree_in(7889) << std::endl;

    std::cout << "Erasing edges to (7889) " << g1.erase_edges_go_to(7889) << std::endl;
    std::cout << "Erasing edges to (2) " << g1.erase_edges_go_to(2) << std::endl;
    std::cout << "Degree to (7889) after erasing " << g1.degree_in(7889) << std::endl;

    std::cout << "Erasing node (-364) " << g1.erase_node(-364) << std::endl;
    try{
        std::cout << g1.degree_in(-364) << std::endl;
    }
    catch (std::out_of_range e){
        std::cout << "Here was exception: " << e.what() << std::endl;
    }
    g1.save_to_file("write_graph1.txt");

    std::cout << std::endl;

    //GRAPH 2
    Graph<std::string, int> g2;
    g2.load_from_file("read_graph1.txt");
    std::cout << "GRAPH 2" << std::endl;
    //Tests 2
    std::cout << "Is g2 empty? " <<  g2.empty() << std::endl;
    std::cout << "g2 size: " <<g2.size() << std::endl;
    g2.insert_node(g2.size(), "Artem");
    g2.insert_edge(1, g2.size() - 1, 123);
    std::cout << "Degree in (Artem) " << g2.degree_in(g2.size() - 1) << std::endl;
    g2.save_to_file("write_graph2.txt");

    std::cout << std::endl;

    //GRAPH 3
    std::cout << "GRAPH3 " << std::endl;
    Graph<float, float>g3;
    g3.load_from_file("read_graph2.txt");
    g3.insert_or_assign_node(7, 2.718 + 3.1415);
    g3.insert_or_assign_edge(5, 8, 2.7);
    g3.insert_or_assign_edge(std::make_pair(1, 2), 3.1415/2);
    g3.insert_node(std::make_pair(10, -2.718));
    g3.insert_or_assign_edge(std::make_pair(10, 10), 7 * 3.1415);
    g3.save_to_file("write_graph3.txt");
    std::cout << "Program completed successfully" << std::endl;

    std::cout << std::endl;

    //ADDITIONAL TESTS 1
    std::cout << "ADDITIONAL TESTS 1" << std::endl;
    std::cout << "Constructors tests" << std::endl;
    Graph<int, int, int> g4(g1);
    std::cout << "g1 size before moving: " << g1.size() << std::endl;
    Graph<int, int, int> g5 = g1;
    Graph<int, int, int> g6;
    std::cout << "g6 size before moving: " << g6.size() << std::endl;
    g6 = std::move(g1);
    std::cout << "After using move operator: " << std::endl;
    std::cout << "g1 size: " << g1.size() << std::endl;
    std::cout << "g4 size: " << g4.size() << std::endl;
    std::cout << "g5 size: " << g5.size() << std::endl;
    std::cout << "g6 size: " << g6.size() << std::endl;

    std::cout << std::endl;

    //ADDITIONAL TESTS 2
    std::cout << "ADDITIONAL TESTS 2" << std::endl;
    Graph<int, int> n1;
    n1.insert_node(0, -5);
    n1.insert_node(1, 7);
    n1.insert_node(2, 5);
    n1.insert_edge(0, 1, 1);

    Graph<int, int> n2;
    n2.insert_node(0, 8);
    n2.insert_node(1, 9);
    n2.insert_node(2, 6);
    n2.insert_node(3, -9);
    n2.insert_node(4, -6);
    n2.insert_edge(0, 2, -36);

    std::cout << "n1 size: " << n1.size() << std::endl;
    std::cout << "n1: degree in 1 " << n1.degree_in(1) << std::endl;
    std::cout << "n2 size: " << n2.size() << std::endl;
    std::cout << "n2: degree in 1 " << n2.degree_in(1) << std::endl;
    std::cout << "after swap" << std::endl;
    n1.swap(n2);
    std::cout << "n1 size: " << n1.size() << std::endl;
    std::cout << "n1: degree in 1 " << n1.degree_in(1) << std::endl;
    std::cout << "n2 size: " << n2.size() << std::endl;
    std::cout << "n2: degree in 1 " << n2.degree_in(1) << std::endl;
    return 0;
}