#ifndef DATABASE_H_
#define DATABASE_H_

#include "graph.hpp"

#define DB_OP_SUCCESS 0
#define DB_OP_FAILURE 1

// returns whether operation succeeded
int db_prepare(const char*);
int db_add_node(const char*, void*, const char*);
int db_remove_node(const char*, void*);
int db_add_edge(const char*, void*, void*);
int db_remove_edge(const char*, void*, void*);

Graph db_get_graph(const char*);

#endif  // DATABASE_H_
