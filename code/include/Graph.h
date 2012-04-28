/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include <queue>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Vertex {
	T info;
	vector<Edge<T>  > adj;
	bool visited;
	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);

	//Fp09
	int num;
	int low;
	Vertex<T>* path;

	// Dijkstra
	Vertex<T>* previous;
	long double distance;

public:
	Vertex(T in);
	Vertex(const Vertex<T> &v);
	T getInfo() const;
	friend class Graph<T>;
};


template <class T>
T Vertex<T>::getInfo() const {
	return info;
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false), num(0), low(0), path(0){}


template <class T>
Vertex<T>::Vertex(const Vertex<T> & in): info(in.info), visited(in.visited), num(in.num), low(in.low), path(0){}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest,w);
	adj.push_back(edgeD);
}

template <class T>
class Edge {
	Vertex<T> * dest;
	double weight;
	bool visited;
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w), visited(false){}

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;


public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;
	void Dijkstra(T source);
	void clone(Graph<T> &g);
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}


template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *edgeS, *edgeD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ edgeS=*it; found++;}
		if ( (*it)->info == dest )
			{ edgeD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	edgeS->addEdge(edgeD,w);
	return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *edgeS, *edgeD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ edgeS=*it; found++;}
		if ( (*it)->info == dest )
			{ edgeD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	return edgeS->removeEdgeTo(edgeD);
}

template <class T>
void Graph<T>::clone(Graph<T> &gr) {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();

	// 1. clone vertices
	for (; it !=ite; it++) {
		gr.addVertex((*it)->getInfo());
		gr.vertexSet[gr.getNumVertex()-1]->visited = false;
	}

	// 2. clone edges
	for (it=vertexSet.begin(); it !=ite; it++) {
		typename vector<Edge<T> >::iterator edgeIt= ((*it)->adj).begin();
		typename vector<Edge<T> >::iterator edgeIte= ((*it)->adj).end();
		for (; edgeIt !=edgeIte; edgeIt++) {
			gr.addEdge((*it)->getInfo(), edgeIt->dest->getInfo(), edgeIt->weight);
		}
	}
}

template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
	    if ( it->dest->visited == false )
	    	dfs(it->dest, res);
}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}
template <class T>
void Graph<T>::Dijkstra(T source){
	long double infinity=10e100;

	// (1) Initializations
	for (int unsigned i=0; i<vertexSet.size(); i++){
		vertexSet[i]->distance=infinity;
		if(vertexSet[i]->info==source) vertexSet[i]->distance=0;
	}

	// (2) Get unoptimized vertex
	vector<Vertex<T> *> Q=getVertexSet();

	// (3) Optimizes the vertex set
	while(!Q.empty()){

		// Get the vertex with the smallest distance
		Vertex<T> *u=Q[0];
		int uIndex;
		for(int unsigned i=0; i<Q.size(); i++)
			if ((Q[i]->distance) < (u->distance)){
				u=Q[i];
				uIndex=i;
			}

		// Check if infinity
		if(u->distance==infinity) break;

		// Remove the u
		Q.erase(Q.begin()+uIndex);

		// get neighbors of u
		vector<Vertex<T>* > neighbor;
		vector<long double> weights; // distance to that neighbour
		for(int unsigned i=0; i<(u->adj.size()); i++){
			neighbor.push_back((u->adj[i]).dest);
			weights.push_back((u->adj[i]).weight);
		}

		// for each neighbor of u
		for (int unsigned i=0; i<neighbor.size(); i++){
			long double alt=u->distance + weights[i];
			if(alt< u->distance){
				neighbor[i]->distance=alt;
				neighbor[i]->previous=u;
			}
		}
	}

}


#endif /* GRAPH_H_ */
