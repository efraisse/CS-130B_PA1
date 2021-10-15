#include "graph.h"
#include <cmath>
using namespace std;

void data::addPoint(pair<double, double> point) {
    points.push_back(point);
}

int data::getPointsSize() {
    return points.size();
}

vector<pair<double,double>> data::getPoints() {
    return points;
}

void data::quickHull() {
    //this is to start off the quickhull algorithm, it should not be looped or recursed
    //think about edge case when all three points are in a line and add a condition
    if (points.size() < 1) {
        cout << "no points exist" << endl;
        exit;
    }  
    if (points.size() == 1){
        sortedHull.push_back(points[0]);
        exit;
    }
    if (points.size() == 2) {
        if (points[0].second < points[1].second) {
            sortedHull.push_back(points[0]);
            sortedHull.push_back(points[1]);
        }
        else {
            sortedHull.push_back(points[1]);
            sortedHull.push_back(points[0]);
        }
        exit;
    }
    if (points.size() == 3) {
        double area = 0.5 * (points[0].first * (points[1].second - points[2].second) +
                    points[1].first * (points[2].second - points[0].second) + 
                    points[2].first * (points[0].second - points[1].second));
        if (area == 0) {
            pair<double, double> maxPoint = make_pair(INT_MIN, INT_MIN);
            pair<double, double> minPoint = make_pair(INT_MAX, INT_MAX);
            for (int i = 0; i < points.size(); i++) {
                if (points[i].second < minPoint.second) {
                    minPoint = points[i];
                }
                if (points[i].second > maxPoint.second) {
                    maxPoint = points[i];
                }
            }
            sortedHull.push_back(minPoint);
            sortedHull.push_back(maxPoint);
            exit;
        }
    }
       

    pair<double, double> minX = make_pair(INT_MAX, INT_MAX);
    pair<double, double> maxX = make_pair(INT_MIN, INT_MIN);
    for (int i = 0; i < points.size(); i++) {
        if (points[i].first < minX.first) {
            minX.first = points[i].first;
            minX.second = points[i].second;
        }
        if (points[i].first > maxX.first) {
            maxX.first = points[i].first;
            maxX.second = points[i].second;
        }
    }
    quickHullHelper(points, minX, maxX, points.size(), 1);
    quickHullHelper(points, minX, maxX, points.size(), -1);
}

void data::quickHullHelper(vector<pair<double, double>> hull, pair<double, double> p1, pair<double, double> p2, int totalPoints, int side) {
    int index = -1;
    double maxDist = 0;

    for (int i = 0; i < totalPoints; i++) {
        if (findSide(p1, p2, hull[i]) == side && distance(p1, p2, hull[i]) > maxDist) {
            index = i;
            maxDist = distance(p1, p2, hull[i]);
        }
    }

    if (index == -1) {
        convexHull.insert(p1);
        convexHull.insert(p2);
        return;
    }

    quickHullHelper(hull, hull[index], p1, totalPoints, -findSide(hull[index], p1, p2));
    quickHullHelper(hull, hull[index], p2, totalPoints, -findSide(hull[index], p2, p1));
}

int data::findSide(pair<double, double> p1, pair<double, double> p2, pair<double, double> point) {
    double side = (point.second - p1.second) * (p2.first - p1.first) -
              (p2.second - p1.second) * (point.first - p1.first);
    if (side < 0)
        return -1;
    else
        return 1;
}

double data::distance(pair<double, double> p1, pair<double, double> p2, pair<double, double> point) {
    double value = ((point.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (point.first - p1.first));
    if (value < 0)
        return -value;
    return value;
}

set<pair<double, double>> data::getConvexHull() {
    return convexHull;
}

void data::sortHull() {
    if (points.size() < 3) return;
    for (auto el: convexHull) {
        sortedHull.push_back(el);
    }

    pair<double, double> smallestPoint = make_pair(INT_MAX, INT_MAX);
    int smallestIndex = 0;
    for (int i = 0; i < sortedHull.size(); i++) {
        if (smallestPoint.second > sortedHull[i].second) {
            smallestIndex = i, smallestPoint = sortedHull[i];
        }
        else if (smallestPoint.second == sortedHull[i].second && smallestPoint.first > sortedHull[i].first) {
            smallestIndex = i, smallestPoint = sortedHull[i];
        }
    }

    //by now sortedHull should have all the elements of the convexHull and we should have our starting point
    //make a dictionary of angles with the points as values, then sort the keys of the dictionary with angles

    vector<double> angles(sortedHull.size());
    map<double, pair<double, double>> storage;

    for (int i = 0; i < sortedHull.size(); i++) {
        if (sortedHull[i] != smallestPoint) {
            //find angle from smallest point to all other points
            if (sortedHull[i].first > smallestPoint.first) {
                double x, y;
                y = (sortedHull[i].second - smallestPoint.second);
                x = (sortedHull[i].first - smallestPoint.first); 
                angles[i] = (atan(y/x) * 180)/M_PI;
            }
            else if (sortedHull[i].first < smallestPoint.first) {
                double x, y;
                y = (sortedHull[i].second - smallestPoint.second);
                x = (sortedHull[i].first - smallestPoint.first); 
                angles[i] = (atan(y/x) * 180)/M_PI + 180;
            }
            else angles[i] = 90;

        } else {
            angles[i] = -1; //this is so we know for a fact that this point will be sorted first
        }
        storage[angles[i]] = sortedHull[i];
    }

    mergeSort(angles);

    //angles should now be sorted according to the angle sizes
    //now all thats left is to retrieve the points mapped to the angle sizes in the dictionary

    for (int i = 0; i < angles.size(); i++) {
        sortedHull[i] = storage[angles[i]];;
    }
}

vector<pair<double, double>> data::getSortedHull() {
    return sortedHull;
}

void data::mergeSort(vector<double>& angles) {
    mergeSortHelper(angles, 0, angles.size() - 1);
}

void data::mergeSortHelper(vector<double>& angles, int min, int max) {
    if (min < max) {
        int mid = (min + max)/2;
        mergeSortHelper(angles, min, mid);
        mergeSortHelper(angles, mid + 1, max);
        merge(angles, min, mid, max);
    }
}

//basic merge algorithm
void data::merge(vector<double>& angles, int min, int mid, int max) {

    //create left and right arrays instead of vectors
    vector<double> mergeVector;
    int leftIndex = min;
    int rightIndex = mid + 1;
    //merge left and right elements
    while (leftIndex <= mid && rightIndex <= max) {
        if (angles[leftIndex] <= angles[rightIndex]) {
            mergeVector.push_back(angles[leftIndex]);
            leftIndex++;
        } else {
            mergeVector.push_back(angles[rightIndex]);
            rightIndex++;
        }
    }
    //copy any remaining elements from the right and left vectors
    while(leftIndex <= mid) {
        mergeVector.push_back(angles[leftIndex]);
        leftIndex++;
    }
    while(rightIndex <= max) {
        mergeVector.push_back(angles[rightIndex]);
        rightIndex++;
    }
    //copy the sorted elements from the mergeVector to the original angles vector
    for (int i = min; i <= max; i++) {
        angles[i] = mergeVector[i - min];
    }
}