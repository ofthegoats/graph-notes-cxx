#include "graph.hpp"

#include <utility>

Graph::Graph() { this->graph = {}; }

void Graph::add_node(int id, std::string fp)
{
    if (!this->contains_node(id))
        this->graph.push_back(std::make_pair(node {id, fp}, std::list<int>()));
}

void Graph::remove_node(int id)
{
    // start by removing node from adj. list
    // qualifier is a lambda
    this->graph.remove_if([id](const std::pair<struct node, std::list<struct node>> n) {
        return n.first.id == id;
    });
    // then remove all edges which contain the node
    for (auto n : this->graph)
        n.second.remove_if([id](const int m) { return m == id; });
}

void Graph::add_edge(int src_id, int dest_id)
{
    // only add the edge if it does not already exist
    if (!this->contains_edge(src_id, dest_id))
        for (auto n : this->graph)
            if (n.first.id == src_id) n.second.push_back(dest_id);
}

void Graph::remove_edge(int src_id, int dest_id)
{
    for (auto n : this->graph)
        if (n.first.id == src_id)
            n.second.remove_if([dest_id](const int id) { return id == dest_id; });
}

bool Graph::contains_node(int id)
{
    for (auto n : this->graph)
        if (n.first.id == id) return true;
    return false;
}

bool Graph::contains_edge(int src_id, int dest_id)
{
    for (auto n : this->graph)
        if (n.first.id == src_id)
            for (auto m : n.second)
                if (m == dest_id) return true;
    return false;
}
