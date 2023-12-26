//
// Created by alexandre on 22-12-2023.
//

#ifndef AED_PROJ_2_GRAPH_H
#define AED_PROJ_2_GRAPH_H

#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <unordered_set>
#include "Airline.h"
#include "Airport.h"


using namespace std;

class Edge;
class Graph;
class Vertex;

class Vertex {
    Airport info;                // contents
    std::vector<Edge> adj;        // list of outgoing edges
    bool visited;                 // auxiliary field
    bool processing;              // auxiliary field
    int indegree;                 // auxiliary field
    int num;                      // auxiliary field
    int low;                      // auxiliary field

    void addEdge(Vertex *dest, double w, const Airline &airline);
    bool removeEdgeTo(Vertex *d);

public:
    Vertex(Airport in);
    Airport &getInfo();
    Airport getInfo() const;
    void setInfo(Airport in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const std::vector<Edge> &getAdj() const;
    void setAdj(const std::vector<Edge> &adj);

    int getIndegree() const;

    void setIndegree(int indegree);

    int getNum() const;

    void setNum(int num);

    int getLow() const;

    void setLow(int low);

    size_t getNumDifferentAirlines();

    friend class Graph;
};


class Edge {
    Vertex * dest;      // destination vertex
    double weight;         // edge weight
    Airline airline_;
public:
    Edge(Vertex *d, double w, const Airline &airline);
    Vertex *getDest() const;
    void setDest(Vertex *dest);
    double getWeight() const;
    void setWeight(double weight);
    const Airline &getAirline() const;
    friend class Graph;
    friend class Vertex;
};

class Graph {
    unordered_map<string, Vertex *> vertexSet;      // vertex set
    int _index_;                        // auxiliary field
    stack<Vertex> _stack_;           // auxiliary field
    list<list<Airport>> _list_sccs_;        // auxiliary field
    size_t edgeCount_ = 0;

    void dfsVisit(Vertex *v,  vector<Airport> & res) const;
    bool dfsIsDAG(Vertex *v) const;
public:
    Vertex *findVertex(const Airport &in) const;
    int getNumVertex() const;
    bool addVertex(const Airport &in);
    bool removeVertex(const Airport &in);
    bool addEdge(const Airport &sourc, const Airport &dest, double w, const Airline &airline);
    bool removeEdge(const Airport &sourc, const Airport &dest);
    unordered_map<string, Vertex *> getVertexSet() const;
    vector<Airport> dfs() const;
    vector<Airport> dfs(const Airport & source) const;
    vector<Airport> bfs(const Airport &source) const;
    vector<Airport> topsort() const;
    bool isDAG() const;
    size_t getNumEdge() const;

    vector<Airport> bfsWithSteps(const Airport &source, int step) const;

    vector<Airport> bfsFurthestVertices(const Airport &source) const;
};

#endif //AED_PROJ_2_GRAPH_H
