//HW3 by Brijesh Verma
//SU Net ID: brverma  SUID: 826257344

//HW3 Due: 11:59pm, Sunday, October 9.

//HW2A: Dijkstra's algorithm with HEAP (20 points)
//HW2B: Use the same design for Prim's algorithm (5 points)
//In HW2B, for each x->y edges, also create a y->x edge with the same weight
// Note that printing results is also performed in the functions.

//You need to use the same function parameters as described.
//You are not allowed to use any extra functions
//You are not allowed to define any class.


//Note that even though we can pick any node as starting node for Prim's algorithm,
//for grading purpose, we will use the same source node as in Dijkstra's algorithm for Prim's algorithm.


#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <fstream>
using namespace std;


void ShortestPath(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool, int>>& table, vector<tuple<int, int>>& heap, int source);//20 points
void MST(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool,int>>& table, vector<tuple<int, int>>& heap, int source); //5 points


int main() {
	int source, numNodes, numEdges;//number of rows, number of columns

	//your code to read in graph from "graph.txt"
	ifstream In("graph.txt");//the file maze.txt in in same folder as the C++ source file.
	In >> source >> numNodes >> numEdges;

	vector<list<pair<int, int>>> graph(numNodes);   // connected-node, cost
	vector<list<pair<int, int>>> graphUnDir(numNodes);  // Undirected graph
	
	vector<tuple<int, int, bool, int>> table(numNodes);//define your tuple - cost, from, visited, heap index(array index in heap for a node)
	vector<tuple<int, int>> heap(numNodes); //define your tuple - node index, cost

	for (int i = 0; i < numEdges; ++i) {
		int node1, node2, cost;
		In >> node1 >> node2 >> cost;
		graph[node1].push_back(make_pair(node2, cost));
		graphUnDir[node1].push_back(make_pair(node2, cost));
		graphUnDir[node2].push_back(make_pair(node1, cost));
	}

	for (int i = 0; i < numNodes; i++) {
		table[i] = make_tuple(INT_MAX, -1, false, i);
		heap[i] = make_tuple(i, INT_MAX);
	}
	In.close();

	ShortestPath(graph, table, heap, source);		//HW2A
	
	//You might need to reset some data.
	table.clear();
	table.resize(numNodes);
	heap.resize(numNodes);
	for (int i = 0; i < numNodes; i++) {
		table[i] = make_tuple(INT_MAX, -1, false, i);
		heap[i] = make_tuple(i, INT_MAX);
	}
	
	MST(graphUnDir, table, heap, source);		//HW2B
	
}
																
void ShortestPath(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool, int>>& table, vector<tuple<int, int>>& heap, int source) {

	get<0>(table[source]) = 0;
	get<1>(table[source]) = source;
	get<1>(heap[get<3>(table[source])]) = 0;

	int k = get<3>(table[source]);
	while (k > 0 ) {  
		if ( get<1>(heap[k]) < get<1>(heap[(k - 1) / 2]) ) {
			get<3>(table[get<0>(heap[k])]) = (k - 1) / 2;	// changes values in table to new heap index
			get<3>(table[get<0>(heap[(k - 1) / 2])]) = k;

			swap(heap[k], heap[(k - 1) / 2]);
			k = (k - 1) / 2;
		}
	}
	while (!heap.empty()) {
		if ( get<2>(table[get<0>(heap[0])]) ) {	// heap top is visited then remove it from top and correct heap
			get<3>(table[get<0>(heap[0])]) = heap.size() - 1;	// changes values in table to new heap index
			get<3>(table[get<0>(heap[heap.size() - 1])]) = 0;
			swap(heap[0], heap[heap.size() - 1]);
			heap.pop_back();
			int k = 0;
			while (2 * k + 1 < heap.size()) {   
				int min;
				if (2 * k + 2 < heap.size()) {
					min = get<1>(heap[2 * k + 1]) < get<1>(heap[2 * k + 2]) ? 2 * k + 1 : 2 * k + 2;
				}
				else {
					min = 2 * k + 1;
				}
				if (get<1>(heap[k]) > get<1>(heap[min])) {
					get<3>(table[get<0>(heap[k])]) = min;	// changes values in table to new heap index
					get<3>(table[get<0>(heap[min])]) = k;
					swap(heap[k], heap[min]);
					k = min;
				}
				else {
					break;
				}
			}
		}
		else {		//heap top is not visited -- now check cost of all its neighbour nodes
			int top = get<0>(heap[0]);	//get node index of heap top 
			get<2>(table[top]) = true;  // set visited true
			if (get<0>(table[top]) != INT_MAX && get<1>(table[top]) != -1) {
				for (auto node : graph[top]) {
					if (!get<2>(table[node.first])) {	//check unvisited nodes
						if (get<0>(table[top]) + node.second < get<0>(table[node.first])) // this path has lower cost -- update cost
						{
							get<0>(table[node.first]) = get<0>(table[top]) + node.second;
							get<1>(table[node.first]) = top;
							int k = get<3>(table[node.first]);
							get<1>(heap[k]) = get<0>(table[top]) + node.second;	//update cost in heap 
							while (k > 0) {  
								if (get<1>(heap[k]) < get<1>(heap[(k - 1) / 2])) {
									get<3>(table[get<0>(heap[k])]) = (k - 1) / 2;	// changes values in table to new heap index
									get<3>(table[get<0>(heap[(k - 1) / 2])]) = k;

									swap(heap[k], heap[(k - 1) / 2]);
									k = (k - 1) / 2;
								}
								else {
									break;
								}
							}
						}
					}
				}
			}			
		}
	}
	cout <<endl<< "For the shortest paths using Dijkstra's algorithm:" << endl;
	for (int i = 0; i < table.size(); i++) {
		if (get<0>(table[i]) == INT_MAX) {
			cout << "The cost from " << source << " to " << i << " is infinity and no paths exist!"<<endl;
		}
		else {
			cout << "The cost from " << source << " to " << i << " is " << get<0>(table[i]) << " and the path is   "<<i;
			int k = i;
			while (k != source) {
				k = get<1>(table[k]);
				cout << " <- " << k;
			}
			cout << endl;
		}
	}
}

void MST(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool, int>>& table, vector<tuple<int, int>>& heap, int source) {

	get<0>(table[source]) = 0;
	get<1>(table[source]) = source;

	get<1>(heap[get<3>(table[source])]) = 0;

	int k = get<3>(table[source]);
	while (k > 0) {   
		if (get<1>(heap[k]) < get<1>(heap[(k - 1) / 2])) {
			get<3>(table[get<0>(heap[k])]) = (k - 1) / 2;	// changes values in table to new heap index
			get<3>(table[get<0>(heap[(k - 1) / 2])]) = k;

			swap(heap[k], heap[(k - 1) / 2]);
			k = (k - 1) / 2;
		}
	}
	while (!heap.empty()) {
		if (get<2>(table[get<0>(heap[0])])) {	// heap top is visited then remove it from top and correct heap
			get<3>(table[get<0>(heap[0])]) = heap.size() - 1;	// changes values in table to new heap index
			get<3>(table[get<0>(heap[heap.size() - 1])]) = 0;
			swap(heap[0], heap[heap.size() - 1]);
			heap.pop_back();
			int k = 0;
			while (2 * k + 1 < heap.size()) {  
				int min;
				if (2 * k + 2 < heap.size()) {
					min = get<1>(heap[2 * k + 1]) < get<1>(heap[2 * k + 2]) ? 2 * k + 1 : 2 * k + 2;
				}
				else {
					min = 2 * k + 1;
				}
				if (get<1>(heap[k]) > get<1>(heap[min])) {
					get<3>(table[get<0>(heap[k])]) = min;	// changes values in table to new heap index
					get<3>(table[get<0>(heap[min])]) = k;
					swap(heap[k], heap[min]);
					k = min;
				}
				else {
					break;
				}
			}
		}
		else {		//heap top is not visited -- now check cost of all its neighbour nodes
			int top = get<0>(heap[0]);	//get node index of heap top 
			get<2>(table[top]) = true;  // set visited true
			for (auto node : graph[top]) {
				if (!get<2>(table[node.first])) {	//check unvisited nodes
					if ( node.second < get<0>(table[node.first])) // this path has lower cost -- update cost
					{
						get<0>(table[node.first]) =  node.second;
						get<1>(table[node.first]) = top;
						int k = get<3>(table[node.first]);
						get<1>(heap[k]) = get<0>(table[top]) + node.second;	//update cost in heap 
						while (k > 0 && get<1>(heap[k]) < get<1>(heap[(k - 1) / 2])) {
							//if ( get<1>(heap[k]) < get<1>(heap[(k - 1) / 2]) ) {
							get<3>(table[get<0>(heap[k])]) = (k - 1) / 2;	// changes values in table to new heap index
							get<3>(table[get<0>(heap[(k - 1) / 2])]) = k;

							swap(heap[k], heap[(k - 1) / 2]);
							k = (k - 1) / 2;
							//}
						}
					}
				}
			}
		}
	}

	cout << endl << endl << "For the minimum spanning tree using Prim's algorithm:\nThe selected edges are : " << endl;
	int totalCost = 0;
	for (int i = 0; i < table.size(); i++) {
		if (i != source) {
			cout << i << " " << get<1>(table[i]) << " " << get<0>(table[i]) << endl;
			totalCost += get<0>(table[i]);
		}
	}
	cout << "The overall cost is " << totalCost << " ." << endl;;
}


//sample input file graph.txt
/*
0 //source node
6 //# of nodes in graph
12 //# of edges in graph
0 5 16//an edge from node 0 to node 5 with a weight (cost) of 16
0 4 15
0 2 4
0 3 12
0 1 9
1 3 3
1 5 2
2 3 14
2 1 3
3 4 4
4 5 1
5 3 2
*/

//The following is a sample output format.  For Dijkstra's algorithm, the graph is interpreted as a directed graph.
//For Prim's algorithm, the graph is interpreted as an un-directed (i.e., bi-directional) graph.
/*
For the shortest paths using Dijkstra's algorithm:
The cost from 1 to 0 is infinity and no paths exist!
The cost from 1 to 1 is 0 and the path is   1
The cost from 1 to 2 is infinity and no paths exist!
The cost from 1 to 3 is 3 and the path is   3<-1
The cost from 1 to 4 is 7 and the path is   4<-3<-1
The cost from 1 to 5 is 2 and the path is   5<-1

For the minimum spanning tree using Prim's algorithm:
The selected edges are:
0 2 4
2 1 3
3 5 2
4 5 1
5 1 2
The overall cost is 12 .
*/
