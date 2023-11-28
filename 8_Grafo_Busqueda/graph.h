#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
private:
    int edgesList;
    int edgesMat;
    int nodes;
    vector<int> *adjList;
    int *adjMatrix;

public:
    
Graph() {
    edgesList = 0;
    edgesMat = 0;
    nodes = 0;
    adjList = nullptr;
    adjMatrix = nullptr;
}


Graph(int n) {

    nodes = n;
    edgesList = 0;
    edgesMat = 0;
    adjList = new vector<int>[n];
    adjMatrix = new int[n * n]();
}


void loadGraphList(string data, int numVertices) {
    nodes = numVertices;
    adjList = new vector<int>[nodes];
    
    stringstream ss(data);
    char openParenthesis, comma, closeParenthesis;
    int u, v;

    while (ss >> openParenthesis >> u >> comma >> v >> closeParenthesis) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); 
        edgesList++;
    }
}

void addEdgeAdjList(int u, int v) {
    if (u >= 0 && u < nodes && v >= 0 && v < nodes) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);

        edgesList++;
    }
}

string printAdjList() {
    string result;

    for (int i = 0; i < nodes; i++) {
        result += "vertex " + to_string(i) + " : ";

        sort(adjList[i].begin(), adjList[i].end());

        for (int j = 0; j < adjList[i].size(); j++) {
            result += to_string(adjList[i][j]) + " ";
        }

  
    }

    return result;
}

//Matrix sTUFF

void loadGraphMat(string data, int a, int b) {
    nodes = a; 
    adjMatrix = new int[a * a](); stringstream ss(data);
    char openParenthesis, comma, closeParenthesis;
    int u, v;

    while (ss >> openParenthesis >> u >> comma >> v >> closeParenthesis) {
        adjMatrix[u * a + v] = 1;
        adjMatrix[v * a + u] = 1; 
        edgesMat++;
    }
}


void addEdgeAdjMatrix(int u, int v) {
    if (u >= 0 && u < nodes && v >= 0 && v < nodes) {
        adjMatrix[u * nodes + v] = 1;
        adjMatrix[v * nodes + u] = 1; 
        edgesMat++;
    }
}



string printAdjMat() {
    string result;
    
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            result += to_string(adjMatrix[i * nodes + j]) + " ";
        }
        
    }
    
    return result;
}


std::string DFS(int start, int end) {
    stack<int> s;
    list<int> visited;
    vector<vector<int>> path(nodes, vector<int>(1, -1));

    s.push(start);
    string ans = depthHelper(start, end, s, visited, path);
    ans = ans + print_path(path, start, end);
    return ans;
}

std::string depthHelper(int current, int end, std::stack<int>& s, std::list<int>& visited, std::vector<std::vector<int>>& path) {
   if (current == end){
        return print_visited(visited);
   } else if (s.empty()){
        return "node not found";
   } else {
        current = s.top();
        s.pop();
        visited.push_back(current);
        for (int i = 0; i < adjList[current].size(); i++)
           if (!contains(visited, adjList[current][i])){
                s.push(adjList[current][i]);
                path[adjList[current][i]][0] = current;
           }
        return depthHelper(current, end, s, visited, path);
   }
}



std::string BFS(int start, int end) {
    queue<int> qu;
    list<int> visited;
    vector<vector<int>> path(nodes, vector<int>(1, -1));

    qu.push(start);
    string ans = breadthHelper(start, end, qu, visited, path);
    ans = ans + print_path(path, start, end);
    return ans;
}

string breadthHelper(int current, int goal, queue<int> &qu, list<int> &visited, vector<vector<int>> &path){
        if(current == goal){
            return print_visited(visited);
        } else if (qu.empty()){
            return "node not found";
        }else{
            current = qu.front();
            qu.pop();
            visited.push_back(current);
            
            for (int i = 0; i < adjList[current].size(); i++){
                if (!contains(visited, adjList[current][i])){    
                    qu.push(adjList[current][i]);    
                    if (path[adjList[current][i]][0] == -1){
                        path[adjList[current][i]][0] = current;
                    }
                }
            }
            return breadthHelper(current, goal, qu, visited, path);
   }
}

bool contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

string print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
  }
	return aux.str();
}

string print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
  }
	return aux.str();
}

};


#endif /* Graph_H_ */
