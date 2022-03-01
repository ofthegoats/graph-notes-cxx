#include "database.hpp"

#include "graph.hpp"

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

// Using Sqlite3 C API, this is not good C++ code

int graph_build_nodes_cb(void*, int, char**, char**);
int graph_build_edges_cb(void*, int, char**, char**);

int db_prepare(const char* filename)
{
    sqlite3*    db;
    char*       err_msg = NULL;
    int         rc;
    const char* sql = "PRAGMA foreign_keys = ON;"         // referential integrity
                      "CREATE TABLE IF NOT EXISTS Node("  // node entity
                      "id INTEGER NOT NULL,"
                      "filepath TEXT NOT NULL,"
                      "PRIMARY KEY(id)"
                      ");"
                      "CREATE TABLE IF NOT EXISTS Edge("  // edge entity
                      "src INTEGER NOT NULL,"
                      "dest INTEGER NOT NULL,"
                      "PRIMARY KEY(src, dest),"
                      "FOREIGN KEY(src) REFERENCES Node(id),"
                      "FOREIGN KEY(dest) REFERENCES Node(id)"
                      ");";
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "preparing database failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    sqlite3_close(db);
    return DB_OP_SUCCESS;
}

int db_add_node(const char* filename, int id, const char* fp)
{
    sqlite3* db;
    char*    err_msg = NULL;
    int      rc;
    char*    sql;
    sprintf(sql,
      "PRAGMA foreign_keys = ON;INSERT INTO Node(id, filepath) VALUES(%d, %s);", id, fp);
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "opening database failed\n");
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "inserting into node failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    sqlite3_close(db);
    return DB_OP_SUCCESS;
}

int db_remove_node(const char* filename, int id)
{
    sqlite3* db;
    char*    err_msg = NULL;
    int      rc;
    char*    sql;
    sprintf(sql, "PRAGMA foreign_keys = ON;DELETE FROM Node WHERE id = %d;", id);
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "opening database failed\n");
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "deleting from node failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    sqlite3_close(db);
    return DB_OP_SUCCESS;
}

int db_add_edge(const char* filename, int src, int dest)
{
    sqlite3* db;
    char*    err_msg = NULL;
    int      rc;
    char*    sql;
    sprintf(sql, "PRAGMA foreign_keys = ON;INSERT INTO Edge(src, dest) VALUES (%d, %d);",
      src, dest);
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "opening database failed\n");
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "inserting into edge failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    sqlite3_close(db);
    return DB_OP_SUCCESS;
}

int db_remove_edge(const char* filename, int src, int dest)
{
    sqlite3* db;
    char*    err_msg = NULL;
    int      rc;
    char*    sql;
    sprintf(sql, "PRAGMA foreign_keys = ON;DELETE FROM Edge WHERE src = %d AND dest = %d",
      src, dest);
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "opening database failed\n");
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "deleting from edge failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    sqlite3_close(db);
    return DB_OP_SUCCESS;
}

Graph db_get_graph(const char* filename)
{
    Graph    g;
    Graph    g_null;  // empty graph for failed return
    sqlite3* db;
    char*    err_msg = NULL;
    int      rc;
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "opening database failed\n");
        sqlite3_close(db);
        return g_null;
    }
    rc = sqlite3_exec(db, "SELECT * FROM Node;", graph_build_nodes_cb, &g, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "failed building nodes from database: %s\n", err_msg);
        sqlite3_close(db);
        return g_null;
    }
    rc = sqlite3_exec(db, "SELECT * FROM Edge;", graph_build_edges_cb, &g, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "failed building edges from database: %s\n", err_msg);
        sqlite3_close(db);
        return g_null;
    }
    return g;
}

int graph_build_nodes_cb(void* p, int count, char** dat, char** col)
{
    Graph* g = (Graph*)p;
    int    id;
    char*  fp = NULL;
    sscanf(dat[0], "%d", &id);
    sscanf(dat[1], "%s", fp);
    g->addNode(id, fp);
    return 0;
}

int graph_build_edges_cb(void* p, int count, char** dat, char** col)
{
    Graph* g = (Graph*)p;
    int    src;
    int    dest;
    sscanf(dat[0], "%d", &src);
    sscanf(dat[1], "%d", &dest);
    g->addEdge(src, dest);
    return 0;
}
