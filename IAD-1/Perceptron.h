#pragma once
#include <vector>
#include <stdlib.h>

using namespace std;

class Perceptron
{
	vector<double> wagi;
	double lr = 0.1; //learning rate, random number
	double bias;
public:
	Perceptron();
	~Perceptron();

};

