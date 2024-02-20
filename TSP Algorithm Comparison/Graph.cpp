#include "Graph.h"
#include "DataGenerator.h"
#include "Ant.h"
#include <queue>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

vector<int> Graph::christofides() {
	vector<int> tree = this->mst();
	vector<vector<double>> minTree;

	for (int i = 0; i < tree.size(); i++) {
		if (tree[i] != -1) {
			minTree.push_back({ (double)i, (double)tree[i], adj[i][tree[i]] });
		}
	}

	unordered_set<int> oddDegrees = findOddDegreeVertices(tree);

	perfectMatching( minTree, oddDegrees);

	vector<int> et = eulerianTour(minTree);

	int cur = et[0];
	vector<bool> visited(et.size(), false);
	visited[cur] = true;
	vector<int> path = { cur };
	for (int node : et) {
		if (!visited[node]) {
			path.push_back(node);
			visited[node] = true;

			cLength += adj[cur][node];
			cur = node;
		}
	}

	cLength += adj[cur][et[0]];
	path.push_back(et[0]);

	return path;
}

double Graph::getCLength() {
	return cLength;
}

vector<int> Graph::eulerianTour(vector<vector<double>>& minTree) {
	unordered_map<int, vector<int>> neighbors;
	for (vector<double> edge : minTree) {
		if (neighbors.find((int)edge[0]) == neighbors.end()) {
			neighbors[(int)edge[0]] = vector<int>();
		}
		if (neighbors.find((int)edge[1]) == neighbors.end()) {
			neighbors[(int)edge[1]] = vector<int>();
		}
		neighbors[(int)edge[0]].push_back((int)edge[1]);
		neighbors[(int)edge[1]].push_back((int)edge[0]);
 	}

	int startVertex = (int)minTree[0][0];

	vector<int> et = {neighbors[startVertex][0]};

	while (minTree.size() > 0) {
		int v, index = 0;
		for (index; index < et.size(); index++) {
			if (neighbors[et[index]].size() > 0) {
				v = et[index];
				break;
			}
		}
		while (neighbors[v].size() > 0) {
			int w = neighbors[v][0];

			removeEdge(minTree, v, w);

			neighbors[v].erase(find(neighbors[v].begin(), neighbors[v].end(), w));
			neighbors[w].erase(find(neighbors[w].begin(), neighbors[w].end(), v));

			index += 1;
			et.insert(et.begin() + index, w);

			v = w;
		}
	}

	return et;

	
}

void Graph::removeEdge(vector<vector<double>>& minTree, int v, int w) {
	for (int i = 0; i < minTree.size(); i++) {
		if ((int)minTree[i][0] == v && (int)minTree[i][1] == w || (int)minTree[i][0] == w && (int)minTree[i][1] == v) {
			minTree.erase(minTree.begin() + i);
		}
	}
}

void Graph::perfectMatching(vector<vector<double>>& minTree, unordered_set<int>& oddDegrees) {
	while (oddDegrees.size() > 0) {
		int v = *oddDegrees.begin();
		oddDegrees.erase(oddDegrees.begin());
		double length = INFINITY;
		int closest = 0;
		unordered_set<int>::iterator it = oddDegrees.begin();
		for (it; it != oddDegrees.end(); it++) {
			if (v != *it && adj[v][*it] < length) {
				length = adj[v][*it];
				closest = *it;
			}
			
		}
		minTree.push_back({ (double)v, (double)closest, length });
		oddDegrees.erase(closest);
	}

}

Graph::Graph(vector<pair<int, int>>& points, vector<vector<double>>& adj) {
	this->vertices = adj.size();
	this->points = points;
	this->adj = adj;
	cLength = 0;
}

Graph::Graph() {
	adj = vector<vector<double>>(0);
	vertices = 0;
	cLength = 0;
}

Graph::Graph(vector<vector<double>>& adj) {

	this->adj = adj;
	vertices = adj.size();
	cLength = 0;
}

vector<pair<int, int>> Graph::getPoints() {
	return points;
}

double Graph::lowerBound() {
	double l = 0;
	vector<int> tree;
	for (int i = 0; i < vertices; i++) {
		if (vertices >= 10 && i % (vertices / 10) == 0) {
			cout << 10 * (i / (vertices / 10)) << "%" << "\n";
		}
		tree = mst(i);
		double totalWeight = 0;

		for (int j = 0; j < tree.size(); j++) {
			if (tree[j] != -1) {
				totalWeight += adj[j][tree[j]];
			}
		}
		double smallest = INFINITY, second = INFINITY;
		for (int j = 0; j < vertices; j++) {
			if (j == i) {
				continue;
			}
			if (adj[i][j] < smallest) {
				second = smallest;
				smallest = adj[i][j];
			}
			else if (adj[i][j] < second) {
				second = adj[i][j];
			}
		}
		l = max(l, totalWeight + smallest + second);
	}

	return l;
}

unordered_set<int> Graph::findOddDegreeVertices(vector<int>& tree) {
	vector<int> degrees(vertices);
	for (int i = 0; i < vertices; i++) {
		if (tree[i] != -1) {
			degrees[tree[i]]++;
			degrees[i]++;
		}
	}
	unordered_set<int> oddDegrees;
	for (int i = 0; i < vertices; i++) {
		if (degrees[i] % 2 != 0) {
			oddDegrees.insert(i);
		}
	}
	return oddDegrees;
}

vector<int> Graph::mst(int ignore) {
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
	vector<bool> visited(vertices);
	vector<int> parent(vertices, -1);
	vector<double> smallest(vertices, -1);

	q.push( { 0, ignore == 0 ? 1 : 0 });

	while (!q.empty()) {
		int v = q.top().second;
		q.pop();
		visited[v] = true;
		for (int i = 0; i < vertices; i++) {
			if (!visited[i] && i != ignore && adj[v][i] != 0) {
				
				if (adj[v][i] < smallest[i] || smallest[i] == -1) {
					q.push({ adj[v][i], i });
					smallest[i] = adj[v][i];
					parent[i] = v;
				}
			}
		}
	}
	
	return parent;
}
