//HW1 by Brijesh Verma
//SU Net ID: brverma  SUID: 826257344

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>


using namespace std;
ofstream Out("solution.txt");

class Cell {
public:
	int id;
	int wall;
	bool visited;
	int from;

		Cell();

		Cell(int id, int wall) {
			this->id = id;
			this->wall = wall;
			this->visited = false;
			this->from = -1;
		}
};

void DFS_iterative(vector<Cell>& maze, int numC, int start, int end);
void DFS_recursive(vector<Cell>& maze, int numC, int start, int end, bool& done);
void BFS(vector<Cell>& maze, int numC, int start, int end);

int main() {

	ifstream In("maze.txt");//the file maze.txt in in same folder as the C++ source file.

	int numR, numC;//number of rows, number of columns
	In >> numR >> numC;
	int Start, End;//beginning cell and target cell
	In >> Start >> End;

	vector<int> CellWalls(numR * numC);//CellWalls is a vector of size numR * numC .
	for (int i = 0; i < numR * numC; ++i) {
		In >> CellWalls[i];
	}
	In.close();
	cout << numR << " " << numC << endl;

	cout << Start << endl;
	cout << End << endl;
	for (auto i : CellWalls) cout << i << " ";
	cout << endl;

	vector <Cell> maze;
	vector < vector <int> > graph(numR * numC);

	//Graph Formation
	for (int i = 0; i < numR * numC; i++) {
		int cellWall = CellWalls[i];
		maze.push_back(Cell(i, cellWall));
	}
	
	DFS_iterative(maze, numC, Start, End);				// DFS Iterative function call

	for (int i = 0; i < numR * numC; i++) {
		maze[i].from = -1;
		maze[i].visited = false;
	}

	BFS(maze, numC, Start, End);

	for (int i = 0; i < numR * numC; i++) {
		maze[i].from = -1;
		maze[i].visited = false;
	}

	bool done = false;
	cout << endl << "All Moves Using DFS_recursive:" << endl;
	Out << endl << "All Moves Using DFS_recursive:" << endl;
	DFS_recursive(maze, numC, Start, End, done);			// DFS Recursive function call

	cout << endl << endl << "DFS_recursive Solution:" << endl << endl;
	Out << endl << endl << "DFS_recursive Solution:" << endl;
	if (done) {
		int currentNode = End;
		
		cout << currentNode;
		Out << currentNode;
		currentNode = maze[currentNode].from;

		while (currentNode != Start) { 
			cout << " <- " << currentNode;
			Out << " <- " << currentNode;
			currentNode = maze[currentNode].from;
		}
		cout << " <- " << currentNode << endl << endl;
		Out << " <- " << currentNode << endl << endl;
	}
	else {
		cout << "No Solution." << endl << endl;
		Out << "No Solution." << endl << endl;
	}
	Out.close();
	return 0;
}

void DFS_iterative(vector<Cell>& maze, int numC, int start, int end) {
	stack <int> dfsStack;
	bool pathFound = false;
	dfsStack.push(start);
	maze[start].from = start;
	while (!dfsStack.empty()) {
		int currentNode = dfsStack.top();

		if (currentNode == end) {
			pathFound = true;
			break;
		}

		if (!maze[currentNode].visited) {
			maze[currentNode].visited = true;

			bool northWall = false, southWall = false, eastWall = false, westWall = false;
			int cellWall = maze[currentNode].wall;
			//Finding out existence of wall around a maze cell
			if (cellWall - 8 >= 0) {	// North wall exists
				northWall = true;
				cellWall -= 8;
			}
			if (cellWall - 4 >= 0) {	// east wall exists
				eastWall = true;
				cellWall -= 4;
			}
			if (cellWall - 2 >= 0) {	// south wall exists
				southWall = true;
				cellWall -= 2;
			}
			if (cellWall - 1 == 0) {	// west wall exists
				westWall = true;
			}

			if (!southWall && !maze[currentNode + numC].visited) {
				dfsStack.push(currentNode + numC);
				maze[currentNode + numC].from = currentNode;
			}
			if (!westWall && !maze[currentNode - 1].visited) {
				dfsStack.push(currentNode - 1);
				maze[currentNode - 1].from = currentNode;
			}
			if (!northWall && !maze[currentNode - numC].visited) {
				dfsStack.push(currentNode - numC);
				maze[currentNode - numC].from = currentNode;
			}
			if (!eastWall && !maze[currentNode + 1].visited) {
				dfsStack.push(currentNode + 1);
				maze[currentNode + 1].from = currentNode;
			}
		}
		else {
			dfsStack.pop();
		}
	}

	cout << endl << "DFS_iterative Solution:" << endl;
	Out << "DFS_iterative Solution:" << endl;
	if (pathFound) {
		int currentNode = end;
		cout << currentNode;
		Out << currentNode;
		currentNode = maze[currentNode].from;
		while (currentNode != start) {
			cout << " <- " << currentNode;
			Out << " <- " << currentNode;
			currentNode = maze[currentNode].from;
		}
		cout << " <- " << currentNode << endl;
		Out << " <- " << currentNode << endl;
	}
	else {
		cout << "No Solution."<<endl;
		Out << "No Solution." << endl;
	}
}

void DFS_recursive(vector<Cell>& maze, int numC, int start, int end, bool& done) {
	
	if (!maze[start].visited) {
		maze[start].visited = true;
		cout << start << " -> ";
		Out << start << " -> ";
		
		if (start == end) {
			done = true;
			return;
		}

		bool northWall = false, southWall = false, eastWall = false, westWall = false;
		int cellWall = maze[start].wall;
		//Finding out existence of wall around a maze cell
		if (cellWall - 8 >= 0) {	// North wall exists
			northWall = true;
			cellWall -= 8;
		}
		if (cellWall - 4 >= 0) {	// east wall exists
			eastWall = true;
			cellWall -= 4;
		}
		if (cellWall - 2 >= 0) {	// south wall exists
			southWall = true;
			cellWall -= 2;
		}
		if (cellWall - 1 == 0) {	// west wall exists
			westWall = true;
		}

		if (!southWall && !maze[start + numC].visited) {   
			maze[start + numC].from = start;
			DFS_recursive(maze, numC, start + numC, end, done);
			cout << start << " -> ";
			Out << start << " -> ";
		}
		if (!westWall && !maze[start - 1].visited) {
			maze[start - 1].from = start;
			DFS_recursive(maze, numC, start - 1, end, done);
			cout << start << " -> ";
			Out << start << " -> ";
		}
		if (!northWall && !maze[start - numC].visited) {
			maze[start - numC].from = start;
			DFS_recursive(maze, numC, start - numC, end, done);
			cout << start << " -> ";
			Out << start << " -> ";
		}
		if (!eastWall && !maze[start + 1].visited) {    
			maze[start + 1].from = start;
			DFS_recursive(maze, numC, start + 1, end, done);
			cout << start << " -> ";
			Out << start << " -> ";
		}
	}
}

void BFS(vector<Cell>& maze, int numC, int start, int end) {
	queue<int> bfsQueue;
	bool pathFound = false;
	bfsQueue.push(start);
	maze[start].from = start;
	cout << "BFS ::::::::::::::::" << endl << endl;
	while (!bfsQueue.empty()) {
		int currentNode = bfsQueue.front();

		if (currentNode == end) {
			pathFound = true;
			break;
		}

		if (!maze[currentNode].visited) {
			maze[currentNode].visited = true;
			bool northWall = false, southWall = false, eastWall = false, westWall = false;
			int cellWall = maze[currentNode].wall;
			//Finding out existence of wall around a maze cell
			if (cellWall - 8 >= 0) {	// North wall exists
				northWall = true;
				cellWall -= 8;
			}
			if (cellWall - 4 >= 0) {	// east wall exists
				eastWall = true;
				cellWall -= 4;
			}
			if (cellWall - 2 >= 0) {	// south wall exists
				southWall = true;
				cellWall -= 2;
			}
			if (cellWall - 1 == 0) {	// west wall exists
				westWall = true;
			}

			if (!southWall && !maze[currentNode + numC].visited) {
				bfsQueue.push(currentNode + numC);
				maze[currentNode + numC].from = currentNode;
			}
			if (!westWall && !maze[currentNode - 1].visited) {
				bfsQueue.push(currentNode - 1);
				maze[currentNode - 1].from = currentNode;
			}
			if (!northWall && !maze[currentNode - numC].visited) {
				bfsQueue.push(currentNode - numC);
				maze[currentNode - numC].from = currentNode;
			}
			if (!eastWall && !maze[currentNode + 1].visited) {
				bfsQueue.push(currentNode + 1);
				maze[currentNode + 1].from = currentNode;
			}
		}
		else {
			bfsQueue.pop();
		}
	}
	cout << endl << "BFS Solution:" << endl;
	Out << endl << "BFS Solution:" << endl;
	if (pathFound) {
		int currentNode = end;
		
		cout << currentNode;
		Out << currentNode;
		currentNode = maze[currentNode].from;
		while (currentNode != start) {
			cout << " <- " << currentNode;
			Out << " <- " << currentNode;
			currentNode = maze[currentNode].from;
		}
		cout << " <- " << currentNode << endl;
		Out << " <- " << currentNode << endl;
	}
	else {
		cout << "No Solution." << endl;
		Out << "No Solution." << endl;
	}
}



