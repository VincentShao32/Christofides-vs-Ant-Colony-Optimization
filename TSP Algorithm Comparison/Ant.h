#pragma once
#include <vector>
#include <unordered_set>
#include "Graph.h"

using namespace std;
class Ant
{
	private:
		unordered_set<int> visited;
		vector<int> path;
		double curPathLength;
		int curVertex;
		int orgVertex;
		Graph graph;
		bool isVisited(int vertex);
		void moveTo(int, double);
		int numAnts;

	public:
		Ant(Graph& graph, int);
		void clear();
		double getPathLength();
		vector<int> getPath();
		void runTour(vector<vector<double>>&, double, double);
};

