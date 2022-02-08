#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>     // std::list
#include <string>   // std::string
#include <utility>  // std::pair
#include <vector>   // std::vector

struct node {
    int         id;
    std::string data;
};

class Graph
{
public:
    Graph();           // constructor
    virtual ~Graph();  // destructor
    void add_node(int, std::string);
    void remove_node(int);
    void add_edge(int, int);
    void remove_edge(int, int);

    bool contains_node(int);
    bool contains_edge(int, int);

    std::vector<int> outbound_links(int);
    std::vector<int> inbound_links(int);

private:
    std::list<std::pair<struct node, std::list<int>>> graph;  // adjacency list
};

#endif  // GRAPH_H_
