/*
sources cited:

https://www.geeksforgeeks.org/quickhull-algorithm-convex-hull/
helped me with the overarching quick hull algorithm
*/


#include "graph.h"
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

//change everything to be a double for the points
//also, save their index in the beginning so you can output it
//use another dictionary to save the points relative to their indices in the original points vector

int main() {
    map<pair<double, double>, int> indexes;
    int numPoints;
    //cout << "enter the amount of points you would like" << endl;
    cin >> numPoints;
    //cout << "The number of points is " << numPoints << endl;

    data graph;
    for (int i = 0; i < numPoints; i++) {
        pair<double, double> point;
        string stringX, stringY;
        //cout << "enter a point: ";
        cin >> stringX >> stringY;
        stringX = stringX.substr(0, stringX.length() - 1);
        double x, y;
        x = stod(stringX);
        y = stod(stringY);
        point.first = x;
        point.second = y;
        indexes[point] = i;
        graph.addPoint(point);
    }

    //at this point all the different points should be added to the graph
    //call the quickhull algorithm here
    
    graph.quickHull();
    if (graph.getSortedHull().size() == 0) graph.sortHull();

    cout << graph.getSortedHull().size() << endl;

    int i = 0;
    for (auto el : graph.getSortedHull()) {
        cout << indexes[el] << ", " << el.first << ", " << el.second << endl;
        i++;
    }

    return 0;
}