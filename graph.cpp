#include "graph.hpp"

#include <list>
#include <string>
#include <utility>
#include <vector>

Graph::Graph() { this->graph = {}; }

void Graph::addNode(int id, std::string fp)
{
    if (!this->containsNode(id))
        this->graph.push_back(std::make_pair(node {id, fp}, std::list<int>()));
}

void Graph::removeNode(int id)
{
    // start by removing node from adj. list
    // qualifier is a lambda
    this->graph.remove_if(
      [id](const std::pair<struct node, std::list<int>> n) { return n.first.id == id; });
    // then remove all edges which contain the node
    for (auto n : this->graph)
        n.second.remove_if([id](const int m) { return m == id; });
}

void Graph::addEdge(int src_id, int dest_id)
{
    // only add the edge if it does not already exist
    if (!this->containsEdge(src_id, dest_id))
        for (auto n : this->graph)
            if (n.first.id == src_id) n.second.push_back(dest_id);
}

void Graph::removeEdge(int src_id, int dest_id)
{
    for (auto n : this->graph)
        if (n.first.id == src_id)
            n.second.remove_if([dest_id](const int id) { return id == dest_id; });
}

bool Graph::containsNode(int id)
{
    for (auto n : this->graph)
        if (n.first.id == id) return true;
    return false;
}

bool Graph::containsEdge(int src_id, int dest_id)
{
    for (auto n : this->graph)
        if (n.first.id == src_id)
            for (auto m : n.second)
                if (m == dest_id) return true;
    return false;
}

std::vector<int> Graph::outboundLinks(int src_id)
{
    std::vector<int> ids;
    for (auto n : this->graph)
        if (n.first.id == src_id)
            for (auto dest_id : n.second)
                ids.push_back(dest_id);
    return ids;
}

std::vector<int> Graph::inboundLinks(int dest_id)
{
    std::vector<int> ids;
    bool             has_link;
    for (auto n : this->graph) {
        has_link = false;
        for (auto m : n.second)
            if (m == dest_id) has_link = true;
        if (has_link) ids.push_back(n.first.id);
    }
    return ids;
}

std::vector<struct node> Graph::getNodes()
{
    std::vector<struct node> nodes;
    for (auto pair : graph)
        nodes.push_back(pair.first);
    return nodes;
}
