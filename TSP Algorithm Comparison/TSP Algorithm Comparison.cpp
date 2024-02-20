// TSP Algorithm Comparison.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "DataGenerator.h"
#include "Graph.h"
#include "ACO.h"
#include <time.h>
#include <fstream>
#include <numeric>

using namespace std;


ofstream fout("output.txt");

void printGraphInformation(Graph& g) {
    fout << "Graph Information";
    vector<pair<int, int>> points = g.getPoints();
    for (int i = 0; i < points.size(); i++) {
        if (i % 10 == 0) {
            fout << "\n";
        }
        fout << "[" << points[i].first << ", " << points[i].second << "], ";
    }
    fout << "\n";
}

void printPath(vector<int>& path, Graph& g) {
    for (int i = 0; i < path.size(); i++) {
        if (i % 10 == 0) {
            fout << "\n";
        }
        fout << "[" << g.getPoints()[path[i]].first << ", " << g.getPoints()[path[i]].second << "], ";
    }
    fout << "\n";
}

double average(vector<double>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

void runTrials(int vertices, int trials, int acoIterations) {
    fout << "TRIALS FOR GRAPH OF " << vertices << " VERTICES AND " << acoIterations << " ACO ITERATIONS\n";
    vector<double> cARatio, cTimes, acoARatio, acoTimes;
    for (int i = 1; i < trials + 1; i++) {
        Graph graph = DataGenerator::generate(vertices);
        cout << "Begin Trial " << i << "\n";
        cout << "Printing graph information...\n";
        fout << "||||||||||||||||||||TRIAL " << i << "||||||||||||||||||||\n";
        printGraphInformation(graph);
        
        cout << "Calculating lower bound...\n";
        double lowerBound = graph.lowerBound();
        fout << "Lower Bound: " << lowerBound << "\n";

        clock_t clkStart;
        clock_t clkFinish;

        cout << "Beginning Christofides execution...\n";
        clkStart = clock();
        vector<int> cPath = graph.christofides();
        double cWeight = graph.getCLength();
        clkFinish = clock();
        double cTime = (double)clkFinish - clkStart;
        cARatio.push_back(cWeight / lowerBound);
        cTimes.push_back(cTime / CLOCKS_PER_SEC);

        cout << "Beginning ACO execution...\n";
        ACO aco = ACO(vertices / 4, 5, 1, acoIterations, 100, graph);

        clkStart = clock();
        vector<int> acoPath = aco.runAlgorithm();
        double acoWeight = aco.getBestLength();
        clkFinish = clock();
        double acoTime = (double)clkFinish - clkStart;

        acoARatio.push_back(acoWeight / lowerBound);
        acoTimes.push_back(acoTime / CLOCKS_PER_SEC);

        fout << "|||||||||||||| Trial " << i << " Results ||||||||||||||" << "\n";
        fout << "Christofides best weight: " << cWeight << "\n";
        fout << "Christofides approximation ratio: " << cWeight / lowerBound << "\n";
        fout << "Christofides path: ";
        printPath(cPath, graph);
        fout << "Christofides runtime: " << cTime / CLOCKS_PER_SEC << "\n";
        fout << "ACO best weight: " << aco.getBestLength() << "\n";
        fout << "ACO approximation ratio: " << acoWeight / lowerBound << "\n";
        fout << "ACO path:";
        printPath(acoPath, graph);
        fout << "ACO time: " << acoTime / CLOCKS_PER_SEC << "\n";
        fout << "\n";
        cout << "Trial " << i << " finished\n";

    }
    fout << "SUMMARY OF TRIALS\n";
    fout << "Christofides average approximation ratio: " << average(cARatio) << "\n";
    fout << "Christofides average runtime: " << average(cTimes) << "\n";
    fout << "ACO average approximation ratio: " << average(acoARatio) << "\n";
    fout << "ACO average runtime: " << average(acoTimes) << "\n\n";
}


int main()
{
   
    srand(time(NULL));

    runTrials(250, 5, 200);

    
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
