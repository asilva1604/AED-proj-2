//
// Created by alexandre on 06-12-2023.
//

#include "Graph.h"

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}

template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}

template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

template<class T>
double Edge<T>::getWeight() const {
    return weight;
}

template<class T>
void Edge<T>::setWeight(double weight) {
    Edge::weight = weight;
}

template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}

// TODO
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (const auto &a : vertexSet) {
        if (!a->isVisited()) {
            dfsVisit(a, res);
        }
    }
    for (const auto &a : vertexSet) {
        a->setVisited(false);
    }
    return res;
}

// TODO
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->setVisited(true);
    res.push_back(v->getInfo());
    for (const Edge<T> &a : v->getAdj()) {
        if (!a.getDest()->isVisited()) {
            dfsVisit(a.getDest(), res);
        }
    }
}

// TODO
template <class T>
vector<T> Graph<T>::dfs(const T & source) const {
    vector<T> res;
    bool flag = false;
    for (const auto &v : vertexSet) {
        if (v->getInfo() == source) {
            flag = true;
        }
        if (!flag) {
            continue;
        }
        if (!v->isVisited()) {
            dfsVisit(v, res);
        }
    }
    for (const auto &v : vertexSet) {
        v->setVisited(false);
    }
    return res;
}
template<class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    //TODO
    return false;
}

template<class T>
vector<T> Graph<T>::bfs(const T &source) const {
    //TODO
    return vector<T>();
}

