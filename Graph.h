#ifndef LABWORK3_GRAPH_H
#define LABWORK3_GRAPH_H
#include <map>
#include <list>
#include <fstream>
#include "Edge.h"


typedef unsigned int uint;

template<class node_type, class weight_type, class key_type = uint>
class Graph {
protected:
    using iterator = typename std::map<key_type, node_type>::iterator;
    using const_iterator = typename std::map<key_type, node_type>::const_iterator;
    using e_iterator = typename std::list<Edge<weight_type, key_type>>::iterator;
    using e_const_iterator = typename std::list<Edge<weight_type, key_type>>::const_iterator;
    std::map<key_type, node_type> nodes;
    std::list<Edge<weight_type, key_type>> graph;
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
    //Methods for work with graph data
    size_t degree_in(key_type key) const;
    size_t degree_out(key_type key) const;
    bool loop(key_type key) const;
    //Inserting nodes and edges
    std::pair<iterator, bool> insert_node(key_type key, node_type value = node_type());
    std::pair<iterator, bool> insert_node(std::pair<key_type, node_type> node);
    std::pair<iterator, bool> insert_or_assign_node(key_type key, node_type value = node_type());
    std::pair<iterator, bool> insert_or_assign_node(std::pair<key_type, node_type> node);

    std::pair<e_iterator, bool> insert_edge(key_type begin, key_type end, weight_type weight);
    std::pair<e_iterator, bool> insert_edge(std::pair<key_type, key_type> pair, weight_type weight);
    std::pair<e_iterator, bool> insert_or_assign_edge(key_type begin, key_type end, weight_type weight);
    std::pair<e_iterator, bool> insert_or_assign_edge(std::pair<key_type, key_type> pair, weight_type weight);
    //Erasing nodes and edges
    void clear_edges();
    bool erase_edges_go_from(key_type key);
    bool erase_edges_go_to(key_type key);
    bool erase_node(key_type key);
    //Working with file
    bool load_from_file(const std::string& path);
};

//CONSTRUCTORS
template<class n_type, class w_type, class k_type>
Graph<n_type, w_type, k_type>:: Graph(): nodes(), graph(){};

template<class n_type, class w_type, class k_type>
Graph<n_type, w_type, k_type>::Graph(const Graph<n_type, w_type, k_type> &other){
    nodes = other.nodes;
    graph = other.graph;
}

template<class n_type, class w_type, class k_type>
Graph<n_type, w_type, k_type>::Graph(Graph<n_type, w_type, k_type> &&other) noexcept:
    nodes(std::move(other.nodes)),
    graph(std::move(other.graph)){
}

//OPERATORS
template<class n_type, class w_type, class k_type>
Graph<n_type, w_type, k_type>& Graph<n_type, w_type, k_type>::operator=(const Graph<n_type, w_type, k_type> &other) {
    nodes = other.nodes;
    graph = other.graph;
    return *this;
}

template<class n_type, class w_type, class k_type>
Graph<n_type, w_type, k_type>& Graph<n_type, w_type, k_type>::operator=(
        Graph<n_type, w_type, k_type> &&other) noexcept {
    nodes = std::move(other.nodes);
    graph = std::move(other.graph);
    return *this;
}

//BASIC METHODS
template<class n_type, class w_type, class k_type>
bool Graph<n_type, w_type, k_type>::empty() const {
    return nodes.empty();
}

template<class n_type, class w_type, class k_type>
size_t Graph<n_type, w_type, k_type>::size() const {
    return nodes.size();
}

template<class n_type, class w_type, class k_type>
void Graph<n_type, w_type, k_type>::clear() {
    nodes.clear();
    graph.clear();
}

template<class n_type, class w_type, class k_type>
void Graph<n_type, w_type, k_type>::swap(Graph<n_type, w_type, k_type> &g) {
    std::swap(nodes, g.nodes);
    std::swap(graph, g.graph);
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

//WORK WITH GRAPH DATA
template<class n_type, class w_type, class k_type>
size_t Graph<n_type, w_type, k_type>::degree_in(k_type key) const {
    //Node existence check
    auto check = [&](const std::pair<k_type, n_type> pair){if(pair.first == key){return true;};return false;};
    auto iter = std::find_if(nodes.begin(), nodes.end(), check);
    if (iter == nodes.end()){
        throw std::out_of_range("No such node");
    }
    //Counting
    size_t n = 0;
    auto p = [&](const Edge<w_type, k_type> edge){if (edge.second() == key){n++;}};
    std::for_each(graph.begin(), graph.end(), p);
    return n;
}

template<class n_type, class w_type, class k_type>
size_t Graph<n_type, w_type, k_type>::degree_out(k_type key) const {
    //Node existence check
    auto check = [&](const std::pair<k_type, n_type> pair){if(pair.first == key){return true;};return false;};
    auto iter = std::find_if(nodes.begin(), nodes.end(), check);
    if (iter == nodes.end()){
        throw std::out_of_range("No such node");
    }
    //Counting
    size_t n = 0;
    auto p = [&](const Edge<w_type, k_type> edge){if (edge.first() == key){n++;}};
    std::for_each(graph.begin(), graph.end(), p);
    return n;
}

template<class n_type, class w_type, class k_type>
bool Graph<n_type, w_type, k_type>::loop(k_type key) const {
    //Node existence check
    auto check = [&](const std::pair<k_type, n_type> pair){if(pair.first == key){return true;};return false;};
    auto iter = std::find_if(nodes.begin(), nodes.end(), check);
    if (iter == nodes.end()){
        throw std::out_of_range("No such node");
    }
    //Checking for a loop
    auto p = [&](const Edge<w_type, k_type> edge){return (edge.first() == key && edge.second() == key);};
    auto it = std::find_if(graph.begin(), graph.end(), p);
    return it != graph.end();
}

//INSERTING NODES AND EDGES
template<class n_type, class w_type, class k_type>
std::pair<typename Graph<n_type, w_type, k_type>::iterator, bool> Graph<n_type, w_type, k_type>::insert_node(
        k_type key, n_type value) {
    return nodes.insert(std::make_pair(key, value));
}

template<class n_type, class w_type, class k_type>
std::pair<typename Graph<n_type, w_type, k_type>::iterator, bool> Graph<n_type, w_type, k_type>::insert_node(
        std::pair<k_type, n_type> node) {
    return nodes.insert(node);
}

template<class n_type, class w_type, class k_type>
std::pair<typename Graph<n_type, w_type, k_type>::iterator, bool> Graph<n_type, w_type, k_type>::insert_or_assign_node(
        k_type key, n_type value) {
    if (nodes.contains(key)){
        nodes[key] = value;
        return std::make_pair(nodes.find(key), true);
    }
    return nodes.insert(std::make_pair(key, value));
}

template<class n_type, class w_type, class k_type>
std::pair<typename Graph<n_type, w_type, k_type>::iterator, bool> Graph<n_type, w_type, k_type>::insert_or_assign_node(
        std::pair<k_type, n_type> node) {
    if (nodes.contains(node.first)){
        nodes[node.first] = node.second;
        return std::make_pair(nodes.find(node.first), true);
    }
    return nodes.insert(node);
}

template<class n_type, class w_type, class k_type>
std::pair<typename Graph<n_type, w_type, k_type>::e_iterator, bool> Graph<n_type, w_type, k_type>::insert_edge(
        k_type begin, k_type end, w_type weight) {
    if (!nodes.contains(begin) || !nodes.contains(end)){
        throw std::out_of_range("No such node");
    }
    Edge<w_type, k_type> new_edge(begin, end, weight);
    return std::make_pair(graph.insert(graph.end(), new_edge), true);
}

template<class n_type, class w_type, class k_type>
std::pair<typename Graph<n_type, w_type, k_type>::e_iterator, bool> Graph<n_type, w_type, k_type>::insert_edge(
        std::pair<k_type, k_type> pair, w_type weight) {
    if (!nodes.contains(pair.first) || !nodes.contains(pair.second)){
        throw std::out_of_range("No such node");
    }
    Edge<w_type, k_type> new_edge(pair, weight);
    return std::make_pair(graph.insert(graph.end(), new_edge), true);
}

template<class n_type, class w_type, class k_type>
std::pair<typename Graph<n_type, w_type, k_type>::e_iterator, bool> Graph<n_type, w_type, k_type>::insert_or_assign_edge(
        k_type begin, k_type end, w_type weight) {
    if (!nodes.contains(begin) || !nodes.contains(end)){
        throw std::out_of_range("No such node");
    }
    auto pred = [&](const Edge<w_type, k_type> edge){return edge.first() == begin && edge.second() == end;};
    auto iter = std::find_if(graph.begin(), graph.end(), pred);
    if (iter == graph.end()){
        Edge<w_type, k_type> new_edge(begin, end, weight);
        return std::make_pair(graph.insert(iter, new_edge), true);
    }
    iter->set_value(begin, end, weight);
    return std::make_pair(iter, false);
}

template<class n_type, class w_type, class k_type>
std::pair<typename Graph<n_type, w_type, k_type>::e_iterator, bool> Graph<n_type, w_type, k_type>::insert_or_assign_edge(
        std::pair<k_type, k_type> pair, w_type weight) {

    if (!nodes.contains(pair.first) || !nodes.contains(pair.second)){
        throw std::out_of_range("No such node");
    }
    auto pred = [&](const Edge<w_type, k_type> edge){return edge.first() == pair.first && edge.second() == pair.second;};
    auto iter = std::find_if(graph.begin(), graph.end(), pred);

    if (iter == graph.end()){
        Edge<w_type, k_type> new_edge(pair, weight);
        return std::make_pair(graph.insert(iter, new_edge), true);
    }
    iter->set_value(pair, weight);
    return std::make_pair(iter, false);
}

//ERASING NODES AND EDGES
template<class n_type, class w_type, class k_type>
void Graph<n_type, w_type, k_type>::clear_edges() {
    graph.clear();
}

template<class n_type, class w_type, class k_type>
bool Graph<n_type, w_type, k_type>::erase_edges_go_from(k_type key) {
    if (!nodes.contains(key)){
        return false;
    }
    std::erase_if(graph, [&](const Edge<w_type, k_type> edge){return edge.first() == key;});
    return true;
}

template<class n_type, class w_type, class k_type>
bool Graph<n_type, w_type, k_type>::erase_edges_go_to(k_type key) {
    if (!nodes.contains(key)){
        return false;
    }
    std::erase_if(graph, [&](const Edge<w_type, k_type> edge){return edge.second() == key;});
    return true;
}

template<class n_type, class w_type, class k_type>
bool Graph<n_type, w_type, k_type>::erase_node(k_type key) {
    if (!nodes.contains(key)){
        return false;
    }
    std::erase_if(graph, [&](const Edge<w_type, k_type> edge){return edge.first() == key || edge.second() == key;});
    nodes.erase(key);
    return true;
}

template<class n_type, class w_type, class k_type>
bool Graph<n_type, w_type, k_type>::load_from_file(const std::string& path){
    std::fstream file;
    file.open(path);
    if (!file.is_open()){
        return false;
    }
    size_t nodes_number;
    size_t edges_number;
    //Read dimensions
    file >> nodes_number;
    file >> edges_number;
    //Containers
    std::map<k_type, n_type> nodes_map;
    std::list<Edge<w_type, k_type>> edges_list;
    //Values for read
    k_type node_key;
    n_type node_value;
    for (size_t idx = 0; idx < nodes_number; idx++){
        file >> node_key;
        file >> node_value;
        nodes_map[node_key] = node_value;
    }
    //Values for read
    k_type begin = k_type();
    k_type end = k_type();
    w_type weight = w_type();
    Edge<w_type, k_type> new_edge(begin, end, weight);
    for (size_t idx = 0; idx < edges_number; idx++){
        file >> begin;
        file >> end;
        file >> weight;
        if (!nodes_map.contains(begin) || !nodes_map.contains(end)){
            file.close();
            throw std::out_of_range("Incorrect data in the file");
        }
        std::cout << begin << " " << end << " " << weight << std::endl;
        new_edge.set_value(begin, end, weight);
        edges_list.insert(edges_list.end(), new_edge);
    }
    nodes = std::move(nodes_map);
    graph = std::move(edges_list);
    return true;
}

#endif //LABWORK3_GRAPH_H
