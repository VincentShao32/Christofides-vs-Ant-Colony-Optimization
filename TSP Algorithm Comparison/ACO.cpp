#include "ACO.h"
#include "Graph.h"
#include "Ant.h"
#include "time.h"
#include <iostream>
#include <cstdlib>

using namespace std;

ACO::ACO(int numAnts, double dstPower, double pheromonePower, int iterations, double Q, Graph& graph) {
	this->numAnts = numAnts;
	this->dstPower = dstPower;
	this->pheromonePower = pheromonePower;
	this->graph = graph;
	this->iterations = iterations;
	this->Q = Q;
	decayRate = 0.3;
	pheromones = vector<vector<double>>(this->graph.vertices, vector<double>(this->graph.vertices, 1));
	bestLength = INFINITY;
	bestPath = {};
}


vector<int> ACO::runAlgorithm() {
	vector<Ant> ants;
	ants.reserve(numAnts);
	for (int i = 0; i < numAnts; i++) {
		ants.emplace_back(Ant(graph, numAnts));
	}
	for (int i = 0; i < iterations; i++) {
		cout << "iteration " << i << "/" << iterations << "\r";
		for (Ant& ant : ants) {
			ant.runTour(pheromones, dstPower, pheromonePower);
		}
		updatePheromones(ants);
		for (Ant& ant : ants) {
			ant.clear();
		}
	}
	cout << "\n";

	return bestPath;
}

double ACO::getBestLength() {
	return bestLength;
}

inline void ACO::updatePheromones(vector<Ant>& ants) {
	
	for (int i = 0; i < pheromones.size(); i++) {
		for (int j = 0; j < pheromones.size(); j++) {
			pheromones[i][j] -= (pheromones[i][j] - 1) * decayRate;
		}
	}
	vector<int> path;
	path.reserve(graph.vertices + 1);
	for (Ant& ant : ants) {
		path = ant.getPath();
		double length = ant.getPathLength();
		if (length < bestLength) {
			bestLength = length;
			bestPath = path;
		}
		for (int i = 0; i < path.size() - 1; i++) {
			pheromones[path[i]][path[i + 1]] += Q / length;
		}
	}
}
