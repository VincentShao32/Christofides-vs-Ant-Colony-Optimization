#pragma once
#include <vector>
#include "Graph.h"
#include "Ant.h"

using namespace std;

class ACO
{
	private:
		int numAnts;
		double dstPower;
		double pheromonePower;
		int iterations;
		double bestLength;
		double decayRate;
		double Q;
		vector<vector<double>> pheromones;
		vector<int> bestPath;
		Graph graph;
public:
	ACO(int, double, double, int, double, Graph&);
	vector<int> runAlgorithm();
	void updatePheromones(vector<Ant>&);
	double getBestLength();

};

