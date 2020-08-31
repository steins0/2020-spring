#pragma once
#include <iostream>
#include <vector>
#define k 3
using namespace std;
struct Sample
{
	int x;
	int y;
};
int getDistance(Sample pt1, Sample pt2);
int getCluster(Sample means[], Sample point);
Sample getMeans(vector<Sample> cluster);
float getVar(vector<Sample> clusters[], Sample means[]);
void Kmeas(int **data);