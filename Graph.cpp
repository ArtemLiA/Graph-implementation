//
// Created by lyaho on 26.02.2023.
//

#ifndef LABWORK3_GRAPH_CPP
#define LABWORK3_GRAPH_CPP
#include "Graph.h"

template<class Node_type, class Weight_type>
Graph<Node_type, Weight_type>::Graph(
        std::initializer_list<std::pair<std::pair<Node_type, Node_type>, Weight_type>> list){
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
        if (edges.contains(std::make_pair(nodes[iter->first.first], nodes[iter->first.second]))){
            throw std::out_of_range("There are multiple edges");
        }
        edges[std::make_pair(nodes[iter->first.first], nodes[iter->first.second])] = iter->second;
    }
}

template<class Node_type, class Weight_type>
Graph<Node_type, Weight_type>::Graph(const Graph<Node_type, Weight_type>& other){
    num_nodes = other.num_nodes;
    nodes = other.nodes;
    edges = other.edges;
    size_ = other.size_;
}

template<class Node_type, class Weight_type>
Graph<Node_type, Weight_type>::Graph(Graph<Node_type, Weight_type>&& other) noexcept{
    num_nodes = std::move(other.num_nodes);
    nodes = std::move(other.nodes);
    edges = std::move(other.edges);
    size_ = other.size_;
    other.size_ = 0;
}

template<class Node_type, class Weight_type>
Graph<Node_type, Weight_type>& Graph<Node_type, Weight_type>::operator=(const Graph<Node_type, Weight_type>& other){
    num_nodes = other.num_nodes;
    nodes = other.nodes;
    edges = other.edges;
    size_ = other.size_;
    return *this;
}

template<class Node_type, class Weight_type>
Graph<Node_type, Weight_type>& Graph<Node_type, Weight_type>::operator=(Graph<Node_type, Weight_type>&& other) noexcept{
    num_nodes = std::move(other.num_nodes);
    nodes = std::move(other.nodes);
    edges = std::move(other.edges);
    size_ = other.size_;
    other.size_ = 0;


    return *this;
}

template<class Node_type, class Weight_type>
bool Graph<Node_type, Weight_type>::empty() {
    return size_ == 0;
}

template<class Node_type, class Weight_type>
size_t Graph<Node_type, Weight_type>:: size(){
    return size_;
}

template<class Node_type, class Weight_type>
void Graph<Node_type, Weight_type>:: clear() noexcept{
    num_nodes.clear();
    nodes.clear();
    edges.clear();
    size_ = 0;
}

template<class Node_type, class Weight_type>
void Graph<Node_type, Weight_type>:: swap(Graph<Node_type, Weight_type>& other) noexcept{
    std::swap(num_nodes, other.num_nodes);
    std::swap(nodes, other.nodes);
    std::swap(edges, other.edges);
    std::swap(size_, other.size_);
}

template<class Node_type, class Weight_type>
void Graph<Node_type, Weight_type>::print_nodes() {
    for (auto node: num_nodes){
        std::cout << "(" << node.first << " " << node.second << ")" << std::endl;
    }
}

template<class Node_type, class Weight_type>
void Graph<Node_type, Weight_type>::print_edges() {
    for (auto edge: edges){
        std::cout << num_nodes[edge.first.first] << "  ---"
        << edge.second << "-->  " << num_nodes[edge.first.second] <<
        std::endl;
    }
}


#endif