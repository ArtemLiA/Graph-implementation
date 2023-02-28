#ifndef LABWORK3_NODE_H
#define LABWORK3_NODE_H
#include <iostream>
#include <list>


template<class node_type, class weight_type, class key_type>
class Node{
protected:
    node_type value;
    std::list<std::pair<key_type, weight_type>> keys_to;
public:
    Node();
    explicit Node(node_type v);
    void insert_edge(key_type key_to, weight_type weight = weight_type());
    void erase_edge(key_type key_to, weight_type weight = weight_type());
    void print_value(std::ostream& os = std::cout, char end = '\n') const;
    void print_keys(std::ostream& os = std::cout, char end = '\n') const;
    void print_edges(std::ostream& os = std::cout, char end = '\n') const;
};

template<class n_type, class w_type, class k_type>
Node<n_type, w_type, k_type>::Node(): value(), keys_to(){}

template<class n_type, class w_type, class k_type>
Node<n_type, w_type, k_type>::Node(n_type v): value(v){}

template<class n_type, class w_type, class k_type>
void Node<n_type, w_type, k_type>::insert_edge(k_type key_to, w_type weight){
    keys_to.insert(std::make_pair(key_to, weight));
}

template<class n_type, class w_type, class k_type>
void Node<n_type, w_type, k_type>::erase_edge(k_type key_to, w_type weight){
    keys_to.erase(std::find(keys_to.begin(), keys_to.end(), std::make_pair(key_to, weight)));
}

template<class n_type, class w_type, class k_type>
void Node<n_type, w_type, k_type>::print_value(std::ostream &os, char end) const {
    os << value << end;
}

template<class n_type, class w_type, class k_type>
void Node<n_type, w_type, k_type>::print_keys(std::ostream &os, char end) const {
    auto p = [&](const std::pair<k_type, w_type> pair){os << pair.first << end;};
    std::for_each(keys_to.begin(), keys_to.end(), p);
}

template<class n_type, class w_type, class k_type>
void Node<n_type, w_type, k_type>::print_edges(std::ostream &os, char end) const {
    auto p = [&](const std::pair<k_type, w_type> pair){os << pair.first << " " << pair.second << end;};
    std::for_each(keys_to.begin(), keys_to.end(), p);
}

#endif //LABWORK3_NODE_H
