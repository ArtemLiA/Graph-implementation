#ifndef LABWORK3_GRAPH_H
#define LABWORK3_GRAPH_H
#include <iostream>
#include "Node.h"
#include "Edge.h"
#include <map>
#include <list>

typedef unsigned int uint;

template<class node_type, class weight_type, class key_type = uint>
class Graph {
    using iterator = typename std::map<key_type, node_type>::iterator;
    using const_iterator = typename std::map<key_type, node_type>::const_iterator;
protected:
    std::map<key_type, node_type> nodes;
    std::list<Edge<weight_type, key_type>> graph;
    uint size_;
public:
    //Constructors
    Graph();
    Graph(const Graph<node_type, weight_type, key_type>& other);
    Graph(Graph<node_type, weight_type, key_type>&& other) noexcept;
    //Operators
    Graph<node_type, weight_type, key_type>& operator=(const Graph<node_type, weight_type, key_type>& other);
    Graph<node_type, weight_type, key_type>& operator=(Graph<node_type, weight_type, key_type>&& other) noexcept;
    //Basic methods
    bool empty() const;
    size_t size() const;
    void clear();
    void swap(Graph<node_type, weight_type, key_type>& g);
    //Iterators
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
};

//CONSTRUCTORS
template<class n_type, class w_type, class k_type>
Graph<n_type, w_type, k_type>:: Graph(): nodes(), graph(), size_(0){};

template<class n_type, class w_type, class k_type>
Graph<n_type, w_type, k_type>::Graph(const Graph<n_type, w_type, k_type> &other){
    nodes = other.nodes;
    graph = other.graph;
    size_ = other.size_;
}

template<class n_type, class w_type, class k_type>
Graph<n_type, w_type, k_type>::Graph(Graph<n_type, w_type, k_type> &&other) noexcept:
    nodes(std::move(other.nodes)),
    graph(std::move(other.graph)){
    size_ = other.size_;
    other.size_ = 0;
}

//OPERATORS
template<class n_type, class w_type, class k_type>
Graph<n_type, w_type, k_type>& Graph<n_type, w_type, k_type>::operator=(const Graph<n_type, w_type, k_type> &other) {
    nodes = other.nodes;
    graph = other.graph;
    size_ = other.size_;
    return *this;
}

template<class n_type, class w_type, class k_type>
Graph<n_type, w_type, k_type>& Graph<n_type, w_type, k_type>::operator=(
        Graph<n_type, w_type, k_type> &&other) noexcept {
    nodes = std::move(other.nodes);
    graph = std::move(other.graph);
    size_ = std::move(other.size_);
    other.size_ = 0;
    return *this;
}

//BASIC METHODS
template<class n_type, class w_type, class k_type>
bool Graph<n_type, w_type, k_type>::empty() const {
    return size_ == 0;
}

template<class n_type, class w_type, class k_type>
size_t Graph<n_type, w_type, k_type>::size() const {
    return size_;
}

template<class n_type, class w_type, class k_type>
void Graph<n_type, w_type, k_type>::clear() {
    nodes.clear();
    graph.clear();
    size_ = 0;
}

template<class n_type, class w_type, class k_type>
void Graph<n_type, w_type, k_type>::swap(Graph<n_type, w_type, k_type> &g) {
    std::swap(nodes, g.nodes);
    std::swap(graph, g.graph);
    std::swap(size_, g.size_);
}

template<class n_type, class w_type, class k_type>
typename Graph<n_type, w_type, k_type>::iterator Graph<n_type, w_type, k_type>::begin(){
    return nodes.begin();
}

template<class n_type, class w_type, class k_type>
typename Graph<n_type, w_type, k_type>::iterator Graph<n_type, w_type, k_type>::end(){
    return nodes.end();
}

template<class n_type, class w_type, class k_type>
typename Graph<n_type, w_type, k_type>::const_iterator Graph<n_type, w_type, k_type>::cbegin() const {
    return nodes.cbegin();
}

template<class n_type, class w_type, class k_type>
typename Graph<n_type, w_type, k_type>::const_iterator Graph<n_type, w_type, k_type>::cend() const {
    return nodes.cend();
}

#endif //LABWORK3_GRAPH_H
