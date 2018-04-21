#pragma once

#include "Matrix.h"

class NeuralNetwork
{
private:
	int input;
	int hidden;
	int output;
	bool usingBias = false;
	bool lineral = false;

	Matrix weightsHI;
	Matrix weightsOH;
	Matrix biasH;
	Matrix biasO;

	Matrix deltaWeightsHI;
	Matrix deltaWeightsOH;
	Matrix deltaBiasO;
	Matrix deltaBiasH;

	double learningRate = 0.7;
	double momentum = 0.0;

public:
	NeuralNetwork(int input, int hidden, int output);
	~NeuralNetwork();
	Matrix Feedforward(Matrix input);

	//Matrix Error(Matrix input[], Matrix answer[], int size);
	
	void Backpropagation(Matrix input, Matrix answer);
};

