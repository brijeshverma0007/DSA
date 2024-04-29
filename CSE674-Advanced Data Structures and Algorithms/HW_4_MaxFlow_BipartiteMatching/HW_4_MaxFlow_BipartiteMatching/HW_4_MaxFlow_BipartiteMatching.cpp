//HW4 by Brijesh Verma
//SU Net ID: brverma  SUID: 826257344

//HW4 maxflow and bipartite matching
//Due: 11:59pm, Saturday Oct. 29.
/*
When performing BFS for max flow or max matching, you need to explore neighbors in the order of increasing node IDs.
For example, if a node has unvisited neighbors 7, 3, 5, and 2.  Then the order for exploring neighbors will be 2, 3, 5, and 7.
This implies that you have to sort neighbors when forming the graph.

For simplicity, in the case of max flow problem, assume there will be at most one directed edge from a node to another node.


It is also assume that if there is a directed edge from n1 to n2, then there will be no edge from n2 to n1.

For max matching problem, since you are dealing with undirected graph, for simplicity, you can assume that there will at most one edge between
any two nodes.

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

//You will implement the following three functions.  No additional functions are allowed.
void BipartiteMatching(vector<list<pair<int, int>>>& G, vector<tuple<int, bool, int>>& T, int s, int t);//Graph, Table, source, sink
void MaxFlow(vector<list<pair<int, int>>>& G, vector<tuple<int, bool, int>>& T, int s, int t);//Graph, Table, source, sink
int BFS(vector<list<pair<int, int>>>& G, vector<tuple<int, bool, int>>& T, int s, int t);

//Both BipartiteMatching and MaxFlow will call BFS.
//Return the flow on the path found by BFS or 0 if no path found

int main() {
	int source, sink, numNodes, numEdges;//number of rows, number of columns

	//your code to read in graph from "graph.txt"
	ifstream In("graph1.txt");//the file maze.txt in in same folder as the C++ source file.
	In >> source>> sink >> numNodes >> numEdges;

	vector<list<pair<int, int>>> graph1(numNodes);   // connected-node, cost
	vector<list<pair<int, int>>> graph1copy(numNodes);  // Undirected graph

	vector<tuple<int,bool, int>> table1(numNodes);//define your tuple - cost, from, visited, heap index(array index in heap for a node)
	
	for (int i = 0; i < numEdges; ++i) {
		int node1, node2, cost;
		In >> node1 >> node2 >> cost;
		graph1[node1].push_back(make_pair(node2, cost));
		graph1[node2].push_back(make_pair(node1, 0));
		
		graph1copy[node1].push_back(make_pair(node2, cost));
	}
	
	for (int i = 0; i < numNodes; i++) {
		table1[i] = make_tuple( -1, false, INT_MAX);
		graph1[i].sort();
		graph1copy[i].sort();
	}
	In.close();

	//Read in graph from graph1.txt
	//Data initialization

	MaxFlow(graph1, table1, source, sink);

	cout << "The following edges have scheduled flow as indicated:"<<endl;
	for (int i = 0; i < graph1copy.size(); i++) {
		for (auto n : graph1copy[i]) {
			for (auto m : graph1[i]) {
				if (n.first == m.first && n.second - m.second != 0) {
				//The scheduled flow on edge (0, 1) = 10 out of capacity = 10
					cout << "The scheduled flow on edge (" << i << ", " << m.first << ") = " << n.second - m.second << " out of capacity = " << n.second;
					cout << endl;
					break;
				}
			}
		}
	}

	/*********   BIPARTITE MATCHING START  ************/
	//Read in graph from graph2.txt
	//Data initialization
	int leftNodes, rightNodes, numNodes2, numEdges2;//number of rows, number of columns

	//your code to read in graph from "graph.txt"
	ifstream In2("graph2.txt");//the file maze.txt in in same folder as the C++ source file.
	In2  >> numNodes2 >> numEdges2 >> leftNodes >> rightNodes;

	vector<list<pair<int, int>>> graph2(numNodes2 + 2);
	vector<list<pair<int, int>>> graph2copy(numNodes2 + 2);
	vector<tuple<int, bool, int>> table2(numNodes2 + 2);
	//Read in graph from graph2.txt
	//Data initialization
	for (int i = 0; i < numEdges2; ++i) {
		int node1, node2;
		In2 >> node1 >> node2;
		graph2[node1].push_back(make_pair(node2, 1));
		graph2[node2].push_back(make_pair(node1, 0));

		graph2copy[node1].push_back(make_pair(node2, 1));
	}

	for (int i = 0; i < leftNodes; i++) {			//connecting source to all left side nodes
		graph2[numNodes2].push_back(make_pair(i, 1));
		graph2[i].push_back(make_pair(numNodes2, 0));

		graph2copy[numNodes2].push_back(make_pair(i, 1));
	}

	for (int i = leftNodes; i < graph2.size()-2; i++) {			// connecting sink to all right side nodes
		graph2[i].push_back(make_pair(numNodes2 + 1, 1));
		graph2[numNodes2 + 1].push_back(make_pair(i, 0));

		graph2copy[i].push_back(make_pair(numNodes2 + 1, 1));
	}

	for (int i = 0; i < numNodes2+2; i++) {
		table2[i] = make_tuple(-1, false, INT_MAX);
		graph2[i].sort();
		graph2copy[i].sort();
	}
	In2.close();

	cout << endl << endl;
	BipartiteMatching(graph2, table2, numNodes2, numNodes2 + 1);

	cout << "The following matchings are selected:" << endl;
	for (int i = 0; i < graph2copy.size()-2; i++) {
		for (auto n : graph2copy[i]) {
			for (auto m : graph2[i]) {
				if (n.first == m.first && n.second - m.second != 0 && m.first != numNodes2 && m.first != numNodes2 + 1) {
					cout << "(" << i << ", " << m.first << ") " << endl;
					break;
				}
			}
		}
	}

	return 0;
}


void MaxFlow(vector<list<pair<int, int>>>& G, vector<tuple<int, bool, int>>& T, int s, int t){	//Graph, Table, source, sink 
	int maxFlow = 0;
	while (BFS(G, T, s, t)) {
		
			int min = INT_MAX;
			int curr = t;
			while (curr != s) {
				int from = get<0>(T[curr]);
			if ( get<2>(T[curr]) < min ){
				min = get<2>(T[curr]);
			}
			curr = from;
			}
			
			maxFlow += min;

			curr = t;
			while (curr != s) {
				int from = get<0>(T[curr]);
				for (auto & n : G[curr]) {
					if (n.first == from) {
						n.second += min;
						break;
					}
				}
				for (auto & n : G[from]) {
					if (n.first == curr) {
						n.second -= min;
						break;
					}
				}
				curr = from;
			}

			for (int i = 0; i < T.size(); i++) {
				T[i] = make_tuple(-1, false, INT_MAX);
			}
	}
	cout << "The maximum flow = " << maxFlow<<endl;
}


int BFS(vector<list<pair<int, int>>>& G, vector<tuple<int, bool, int>>& T, int s, int t) {

	queue<int> bfsQueue;
	bfsQueue.push(s);
	get<0>(T[s]) = s;																																																						

	while (!bfsQueue.empty()) {
		int node = bfsQueue.front();
		bfsQueue.pop();
		get<1>(T[node]) = true;
		
		for (auto n : G[node]) {
			if (n.second > 0 && get<0>(T[n.first]) == -1) {
				bfsQueue.push(n.first);
				get<0>(T[n.first]) = node;
				get<2>(T[n.first]) = n.second;
				if (n.first == t) {
					return 1;
				}
			}
		}
	}
	return 0;
}

void BipartiteMatching(vector<list<pair<int, int>>>& G, vector<tuple<int, bool, int>>& T, int s, int t) {	//Graph, Table, source, sink

	//MaxFlow(G, T, s, t);
	int maxFlow = 0;
	while (BFS(G, T, s, t)) {

		int min = INT_MAX;
		int curr = t;
		while (curr != s) {
			int from = get<0>(T[curr]);
			if (get<2>(T[curr]) < min) {
				min = get<2>(T[curr]);
			}
			curr = from;
		}

		maxFlow += min;

		curr = t;
		while (curr != s) {
			int from = get<0>(T[curr]);
			for (auto& n : G[curr]) {
				if (n.first == from) {
					n.second += min;
					break;
				}
			}
			for (auto& n : G[from]) {
				if (n.first == curr) {
					n.second -= min;
					break;
				}
			}
			curr = from;
		}

		for (int i = 0; i < T.size(); i++) {
			T[i] = make_tuple(-1, false, INT_MAX);
		}
	}
	cout << "The maximum matching = " << maxFlow << endl;
}
