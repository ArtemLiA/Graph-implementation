#ifndef LABWORK3_GRAPH_H
#define LABWORK3_GRAPH_H
#include <iostream>
#include "Node.h"
#include "Edge.h"
#include <map>
#include <set>
#include <list>

typedef unsigned int uint;

template<class node_type, class weight_type, class key_type = uint>
class Graph {
protected:
    std::map<key_type, node_type> num_nodes;
    std::map<node_type, uint> nodes; //Вершины
    std::map<std::pair<key_type, key_type>, weight_type> edges; //Рёбра
    uint size_;
public:
    Graph(): size_(0){};
    Graph(std::initializer_list<std::pair<std::pair<node_type, node_type>, weight_type>> list);
    Graph(const Graph<node_type, weight_type, key_type>& other);
    Graph(Graph<node_type, weight_type, key_type>&& other) noexcept;
    Graph<node_type, weight_type, key_type>& operator=(const Graph<node_type, weight_type, key_type>& other);
    Graph<node_type, weight_type, key_type>& operator=(Graph<node_type, weight_type, key_type>&& other) noexcept;

    bool empty();
    size_t size();
    void clear() noexcept;
    void swap(Graph<node_type, weight_type, key_type>& other) noexcept;
    void print_nodes();
    void print_edges();
};

template<class node_type, class weight_type, class key_type>
Graph<node_type, weight_type, key_type>::
Graph(const Graph<node_type, weight_type, key_type>& other){
    num_nodes = other.num_nodes;
    nodes = other.nodes;
    edges = other.edges;
    size_ = other.size_;
}

template<class node_type, class weight_type, class key_type>
Graph<node_type, weight_type, key_type>::
Graph(Graph<node_type, weight_type, key_type>&& other) noexcept{
    num_nodes = std::move(other.num_nodes);
    nodes = std::move(other.nodes);
    edges = std::move(other.edges);
    size_ = other.size_;
    other.size_ = 0;
}

template<class node_type, class weight_type, class key_type>
Graph<node_type, weight_type, key_type>& Graph<node_type, weight_type, key_type>::
operator=(const Graph<node_type, weight_type, key_type>& other){
    num_nodes = other.num_nodes;
    nodes = other.nodes;
    edges = other.edges;
    size_ = other.size_;
    return *this;
}

template<class node_type, class weight_type, class key_type>
Graph<node_type, weight_type, key_type>& Graph<node_type, weight_type, key_type>::
operator=(Graph<node_type, weight_type, key_type>&& other) noexcept{

    num_nodes = std::move(other.num_nodes);
    nodes = std::move(other.nodes);
    edges = std::move(other.edges);
    size_ = other.size_;
    other.size_ = 0;

    return *this;
}

template<class node_type, class weight_type, class key_type>
bool Graph<node_type, weight_type, key_type>::empty() {
    return size_ == 0;
}

template<class Node_type, class Weight_type, class key_type>
size_t Graph<Node_type, Weight_type, key_type>:: size(){
    return size_;
}

template<class node_type, class weight_type, class key_type>
void Graph<node_type, weight_type, key_type>:: clear() noexcept{
    num_nodes.clear();
    nodes.clear();
    edges.clear();
    size_ = 0;
}

template<class node_type, class weight_type, class key_type>
void Graph<node_type, weight_type, key_type>::
swap(Graph<node_type, weight_type, key_type>& other) noexcept{
    std::swap(num_nodes, other.num_nodes);
    std::swap(nodes, other.nodes);
    std::swap(edges, other.edges);
    std::swap(size_, other.size_);
}

template<class node_type, class weight_type, class key_type>
void Graph<node_type, weight_type, key_type>::print_nodes() {
    for (auto node: num_nodes){
        std::cout << "(" << node.first << " " << node.second << ")" << std::endl;
    }
}

template<class node_type, class weight_type, class key_type>
void Graph<node_type, weight_type, key_type>::print_edges() {
    for (auto edge: edges){
        std::cout << num_nodes[edge.first.first] << "  ---["
                  << edge.second << "]-->  " << num_nodes[edge.first.second] <<
                  std::endl;
    }
}

template<class node_type, class weight_type, class key_type>
Graph<node_type, weight_type, key_type>::Graph(
        std::initializer_list<std::pair<std::pair<node_type, node_type>, weight_type>> list){
    size_ = 0;
    for (auto iter = list.begin(); iter != list.end(); iter++){
        if (iter->first.first == iter->first.second){
            throw std::out_of_range("There are loops");
        }
        if (!nodes.contains(iter->first.first) && !nodes.contains(iter->first.second)){
            nodes[iter->first.first] = size_;
            num_nodes[size_] = iter->first.first;
            size_++;
            nodes[iter->first.second] = size_;
            num_nodes[size_] = iter->first.second;
            size_++;
            edges[std::make_pair(nodes[iter->first.first], nodes[iter->first.second])] = iter->second;
            continue;
        }
        if (!nodes.contains(iter->first.first)){
            nodes[iter->first.first] = size_;
            num_nodes[size_] = iter->first.first;
            ++size_;
            edges[std::make_pair(nodes[iter->first.first], nodes[iter->first.second])] = iter->second;
            continue;
        }
        if (!nodes.contains(iter->first.second)){
            nodes[iter->first.second] = size_;
            num_nodes[size_] = iter->first.second;
            ++size_;
            edges[std::make_pair(nodes[iter->first.first], nodes[iter->first.second])] = iter->second;
            continue;
        }
        edges[std::make_pair(nodes[iter->first.first], nodes[iter->first.second])] = iter->second;
    }
}


#endif //LABWORK3_GRAPH_H
