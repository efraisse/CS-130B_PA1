#include <iostream>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

using namespace std;

class data {
    public:
        void addPoint(pair<double, double> point);
        int getPointsSize();
        vector<pair<double,double>> getPoints();
        void quickHull();
        set<pair<double, double>> getConvexHull();
        vector<pair<double, double>> getSortedHull();
        void quickHullHelper(vector<pair<double, double>> hull, pair<double, double> p1, pair<double, double> p2, int totalPoints, int side);
        int findSide(pair<double, double> p1, pair<double, double> p2, pair<double, double> point);
        double distance(pair<double, double> p1, pair<double, double> p2, pair<double, double> point);
        void sortHull();
        void mergeSort(vector<double>& angles);
        void mergeSortHelper(vector<double>& angles, int min, int max);
        void merge(vector<double>& angles, int min, int mid, int max);
    
    private:
        vector<pair<double, double>> points;
        set<pair<double, double>> convexHull;
        vector<pair<double, double>> sortedHull;
};