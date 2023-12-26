//
// Created by alexandre on 26-12-2023.
//

#include "Graph.h"

namespace std {
    template <>
    struct hash<Vertex*> {
        std::size_t operator()(const Vertex* v) const {
            return hash<string>()(v->getInfo().getCode());
        }
    };
}


size_t Vertex::getNumDifferentAirlines() {
    std::unordered_set<std::string> airlines;

    for (const auto e : adj) {
        airlines.insert(e.getAirline().getCode());
    }

    return airlines.size();
}

const Airline &Edge::getAirline() const{
    return airline_;
}

size_t Graph::getNumEdge() const{
    return edgeCount_;
}

/****************** Provided constructors and functions ********************/


Vertex::Vertex(Airport in): info(in) {}


Edge::Edge(Vertex *d, double w, const Airline &airline): dest(d), weight(w), airline_(airline) {}



int Graph::getNumVertex() const {
    return vertexSet.size();
}


unordered_map<string, Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}


Airport &Vertex::getInfo() {
    return info;
}


void Vertex::setInfo(Airport in) {
    Vertex::info = in;
}


bool Vertex::isProcessing() const {
    return processing;
}


void Vertex::setProcessing(bool p) {
    Vertex::processing = p;
}


Vertex *Edge::getDest() const {
    return dest;
}


void Edge::setDest(Vertex *d) {
    Edge::dest = d;
}


double Edge::getWeight() const {
    return weight;
}


void Edge::setWeight(double weight) {
    Edge::weight = weight;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */

Vertex * Graph::findVertex(const Airport &in) const {
    auto it = vertexSet.find(in.getCode());
    if (it == vertexSet.end()) return NULL;
    return it->second;
}


bool Vertex::isVisited() const {
    return visited;
}


int Vertex::getIndegree() const {
    return indegree;
}


void Vertex::setIndegree(int indegree) {
    Vertex::indegree = indegree;
}


int Vertex::getNum() const {
    return num;
}


void Vertex::setNum(int num) {
    Vertex::num = num;
}


int Vertex::getLow() const {
    return low;
}


void Vertex::setLow(int low) {
    Vertex::low = low;
}


void Vertex::setVisited(bool v) {
    Vertex::visited = v;
}


const vector<Edge> &Vertex::getAdj() const {
    return adj;
}


void Vertex::setAdj(const vector<Edge> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

bool Graph::addVertex(const Airport &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.insert({in.getCode(), new Vertex(in)});
    return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const Airport &sourc, const Airport &dest, double w, const Airline &airline) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w, airline);
    ++edgeCount_;
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */

void Vertex::addEdge(Vertex *d, double w, const Airline &airline) {
    adj.push_back(Edge(d, w, airline));
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */

bool Graph::removeEdge(const Airport &sourc, const Airport &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */

bool Vertex::removeEdgeTo(Vertex *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

Airport Vertex::getInfo() const {
    return info;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */

bool Graph::removeVertex(const Airport &in) {
    auto it = vertexSet.find(in.getCode());
    if (it == vertexSet.end()) return false;
    auto v = it->second;
    vertexSet.erase(it);
    for (auto u : vertexSet)
        u.second->removeEdgeTo(v);
    delete v;
    return true;
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */

vector<Airport> Graph::dfs() const {
    vector<Airport> res;
    for (auto v : vertexSet)
        v.second->visited = false;
    for (auto v : vertexSet)
        if (! v.second->visited)
            dfsVisit(v.second, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */

void Graph::dfsVisit(Vertex *v, vector<Airport> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */

vector<Airport> Graph::dfs(const Airport & source) const {
    vector<Airport> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v.second->visited = false;

    dfsVisit(s, res);
    return res;
}


/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */

vector<Airport> Graph::bfs(const Airport & source) const {
    vector<Airport> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex *> q;
    for (auto v : vertexSet)
        v.second->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto &e: v->adj) {
            auto w = e.dest;
            if (!w->visited) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}

/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */

vector<Airport> Graph::bfsWithSteps(const Airport & source, int step) const {
    int count = 0;
    int count_level_elements = 0;
    vector<Airport> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex *> q;
    for (auto v : vertexSet)
        v.second->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        if (count < step) {
            for (auto &e: v->adj) {
                auto w = e.dest;
                if (!w->visited) {
                    q.push(w);
                    w->visited = true;
                    count_level_elements ++;
                }
            }
            if (q.size() == count_level_elements) {
                count_level_elements = 0;
                count++;
            }
        }
    }
    return res;
}

/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */

vector<Airport> Graph::bfsFurthestVertices(const Airport & source) const {
    int count_level_elements = 0;
    vector<Airport> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex *> q;
    for (auto v : vertexSet)
        v.second->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto &e: v->adj) {
            auto w = e.dest;
            if (!w->visited) {
                q.push(w);
                w->visited = true;
                count_level_elements ++;
            }
        }
        if (q.size() == count_level_elements) {
            if (count_level_elements != 0){
                res.clear();
            }
            count_level_elements = 0;
        }
    }
    return res;
}


/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */


bool Graph::isDAG() const {
    for (auto v : vertexSet) {
        v.second->visited = false;
        v.second->processing = false;
    }
    for (auto v : vertexSet)
        if (! v.second->visited)
            if ( ! dfsIsDAG(v.second) )
                return false;
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */

bool Graph::dfsIsDAG(Vertex *v) const {
    v->visited = true;
    v->processing = true;
    for (auto & e : v->adj) {
        auto w = e.dest;
        if (w->processing)
            return false;
        if (! w->visited)
            if (! dfsIsDAG(w))
                return false;
    }
    v->processing = false;
    return true;
}


/****************** toposort ********************/
//=============================================================================
// Exercise 1: Topological Sorting
//=============================================================================
// TODO
/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */


void topSortHelper(Vertex *v, vector<Airport> &res) {
    v->setVisited(true);
    for (const Edge &e : v->getAdj()) {
        auto dest = e.getDest();
        topSortHelper(dest, res);
    }
    if (find(res.begin(), res.end(), v->getInfo()) == res.end()) {
        res.push_back(v->getInfo());
    }

}


vector<Airport> Graph::topsort() const {
    vector<Airport> res;
    if (!isDAG()) return res;

    for (auto &v : vertexSet) {
        v.second->setVisited(false);
    }

    for (auto &v : vertexSet) {
        topSortHelper(v.second, res);
    }

    reverse(res.begin(), res.end());

    return res;
}