#ifndef LABWORK3_GRAPH_H
#define LABWORK3_GRAPH_H
#include <iostream>
#include <map>
#include <set>

typedef unsigned int uint;

template<class Node_type, class Weight_type>
class Graph {
protected:
    std::map<uint, Node_type> num_nodes;
    std::map<Node_type, uint> nodes; //Вершины
    std::map<std::pair<uint, uint>, Weight_type> edges; //Рёбра
    uint size_;
public:
    Graph(): size_(0){};
    Graph(std::initializer_list<std::pair<std::pair<Node_type, Node_type>, Weight_type>> list);
    Graph(const Graph<Node_type, Weight_type>& other);
    Graph(Graph<Node_type, Weight_type>&& other) noexcept;
    Graph<Node_type, Weight_type>& operator=(const Graph<Node_type, Weight_type>& other);
    Graph<Node_type, Weight_type>& operator=(Graph<Node_type, Weight_type>&& other) noexcept;

    bool empty();
    size_t size();
    void clear() noexcept;
    void swap(Graph<Node_type, Weight_type>& other) noexcept;

    void print_nodes();
    void print_edges();
};

#include "Graph.cpp"
#endif //LABWORK3_GRAPH_H
