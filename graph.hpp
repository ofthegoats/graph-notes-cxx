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
    Graph();                     // constructor
    virtual ~Graph() = default;  // destructor
    void addNode(int, std::string);
    void removeNode(int);
    void addEdge(int, int);
    void removeEdge(int, int);

    bool containsNode(int);
    bool containsEdge(int, int);

    std::vector<int> outboundLinks(int);
    std::vector<int> inboundLinks(int);

    std::vector<struct node> getNodes();

private:
    std::list<std::pair<struct node, std::list<int>>> graph;  // adjacency list
};

#endif  // GRAPH_H_
