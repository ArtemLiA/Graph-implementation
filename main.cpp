#include <iostream>
#include "Graph.h"


int main() {
    Graph<std::string, size_t> sent_valent  = {{{"Mikhail", "Olya"}, 2}, {{"Senya", "Masha"}, 1},
                                               {{"Kostya", "Nastya"}, 6}, {{"Maxim", "Kristina"}, 3},
                                               {{"Denis", "Liza"}, 1}, {{"Maxim", "Vika"}, 8}};
    Graph<std::string, size_t> sent_valent2 = {{{"Kolya", "Natasha"}, 2}, {{"Karina", "Misha"}, 1},
                                               {{"Liza", "Denis"}, 1}, {{"Vika", "Kostya"}, 3}};

    Graph<std::string, size_t> g2 = sent_valent;
    Graph<std::string, size_t> g3 = std::move(g2);

    std::cout << "Is g2 empty? " << g2.empty() << std::endl;
    std::cout << g3.size() << std::endl;

    std::cout << std::endl;
    std::cout << "sent_valent:" << std::endl;
    sent_valent.print_edges();
    std::cout << std::endl;
    std::cout << "sent_valent2:" << std::endl;
    sent_valent2.print_edges();
    std::cout << std::endl;

    sent_valent.swap(sent_valent2);
    std::cout << std::endl;
    std::cout << "after swapping:" << std::endl;
    std::cout << std::endl;
    std::cout << "sent_valent:" << std::endl;
    sent_valent.print_edges();
    std::cout << std::endl;
    std::cout << "sent_valent2:" << std::endl;
    sent_valent2.print_edges();
    std::cout << std::endl;
    
    return 0;
}