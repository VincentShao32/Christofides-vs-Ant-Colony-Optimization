#include "Ant.h"
#include "Graph.h"
#include <vector>
#include <unordered_set>
#include <ctime>

Ant::Ant(Graph& graph, int numAnts) {
	curPathLength = 0;
	this->numAnts = numAnts;
	this->orgVertex = rand() % numAnts;
	curVertex = orgVertex;
	visited = {curVertex};
	path = {curVertex};
	path.reserve(graph.vertices + 1);
	this->graph = graph;
}


vector<int> Ant::getPath() {
	return path;
}


inline void Ant::moveTo(int vertex, double dist) {
	curVertex = vertex;
	path.emplace_back(vertex);
	curPathLength += dist;
	visited.insert(vertex);
}
void Ant::clear() {
	curPathLength = 0;
	orgVertex = rand() % numAnts;
	curVertex = orgVertex;
	visited = { curVertex };
	path = { curVertex };
}

void Ant::runTour(vector<vector<double>>& pheromones, double dstPower, double pheromonePower) {

	vector<vector<double>> adj = graph.adj;
	for (int i = 0; i < graph.vertices - 1; i++) {
		vector<double> probabilities(adj.size());
		double sum = 0;
		for (int j = 0; j < adj[curVertex].size(); j++) {
			if (!isVisited(j)) {
				double term = pow(1 / adj[curVertex][j], dstPower) * pow(pheromones[curVertex][j], pheromonePower);
				probabilities[j] = term;
				sum += term;
			}
		}
		for (int j = 0; j < probabilities.size(); j++) {
			probabilities[j] /= sum;
			if (j != 0) {
				probabilities[j] += probabilities[j - 1];
			}
		}

		double p = (rand() % 100) / 100.0;
		int selected = -1;
		for (int j = 0; j < probabilities.size(); j++) {
			if (p <= probabilities[j] && !isVisited(j)) {
				selected = j;
				break;
			}
		}
		moveTo(selected, adj[curVertex][selected]);
	}
	moveTo(orgVertex, adj[curVertex][orgVertex]);
}

inline bool Ant::isVisited(int vertex) {
	return visited.find(vertex) != visited.end();
}

double Ant::getPathLength() {
	return curPathLength;
}

