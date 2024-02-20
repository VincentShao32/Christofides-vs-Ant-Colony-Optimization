#pragma once
#include <vector>
#include <unordered_set>
using namespace std;

class Graph
{
private: 
	vector<int> mst(int ignore = -1);
	unordered_set<int> findOddDegreeVertices(vector<int>& tree);
	void perfectMatching(vector<vector<double>>& minTree, unordered_set<int>& oddDegrees);
	vector<int> eulerianTour(vector<vector<double>>& minTree);
	void removeEdge(vector<vector<double>>& minTree, int v, int w);
	vector<pair<int, int>> points;
	double cLength;

public:
	vector<vector<double>>	 adj;
	vector<pair<int, int>> getPoints();
	int vertices;

	Graph(vector<pair<int, int>>&, vector<vector<double>>&);
	Graph(vector<vector<double>>&);
	Graph();
	
	double lowerBound();
	
	vector<int> christofides();
	double getCLength();
};

