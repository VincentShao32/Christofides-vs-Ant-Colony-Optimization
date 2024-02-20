#include "DataGenerator.h"
#include <vector>
#include <cstdlib>
#include "Graph.h"
#include <time.h>
#include <iostream>
#include <unordered_set>
#include <math.h>
#include <fstream>

using namespace std;

// Main data generation function
Graph DataGenerator::generate(int vertices) {
	vector<vector<double>> adj(vertices, vector<double>(vertices));

	// Vector to store generated coordinate points
	vector<pair<int, int>> points;

	// Store points that have already been seen to prevent repeats
	unordered_set<int> seen;

	//srand(time(NULL));
	for (int i = 0; i < vertices; i++) {
		// Generate random x and y
		int x = rand() % (int)(vertices * 1.5) + 1;
		int y = rand() % (int)(vertices * 1.5) + 1;
		
		// By encoding the x and y values into a unique integer using a pairing function, 
		// we can efficiently use an unordered_set to check if an x y pair has already
		// been added, preventing repeats
		while (seen.find(pair_function(x, y)) != seen.end()) {
			x = rand() % (int)(vertices * 1.5) + 1;
		    y = rand() % (int)(vertices * 1.5) + 1;
		}
		seen.insert(pair_function(x, y));
		points.push_back({ x, y });
		
	}


	// Store edge weights/distances in the adj of the graph g
	for (int i = 0; i < vertices; i++) {
		for (int j = i + 1; j < vertices; j++) {
			if (j != i && adj[i][j] == 0) {
				// Calculate distance between points using Euclidian distance formula
				double dist = distance(points[i], points[j]);
				// Assigning weights
				adj[i][j] = dist;
				adj[j][i] = dist;
			}

		}
	}
	return Graph(points, adj);

}

// Function for calculating the distance between two coordinate points
double DataGenerator::distance(pair<int, int>& a, pair<int, int>& b) {
	
	return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

// Pairing function used for encoding two integers
int DataGenerator::pair_function(int a, int b) {
	return (int)(0.5 * (a + b - 2) * (a + b - 1));
}


void DataGenerator::printPoints(vector<pair<int, int>>& points) {
	cout << "[" << "\n";
	for (pair<int, int> point : points) {
		cout << "[" << point.first << ", " << point.second << "]," << "\n";
	}
	cout << "]" << "\n";
}