#pragma once

#include "Graph.h"

// Class with static functions to randomly generate data
class DataGenerator
{
	private:
		static double distance(pair<int, int>& a, pair<int, int>& b);
		static int pair_function(int a, int b);
		static void printPoints(vector<pair<int, int>>& points);
	public:
		static Graph generate(int vertices);
};

