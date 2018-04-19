#include "NeuralNetwork.h"
#include <cmath>
#include <iostream>

double f_aktywacyjna(double a)
{
	return 1 / (1 + exp(-a));
}

double pochodna(double x)
{
	return x * (1 - x);
}

double liniowa(double x)
{
	return 1;
}

NeuralNetwork::NeuralNetwork(int input, int hidden, int output) : input(input), hidden(hidden), output(output)
{
	weightsOH = Matrix(output, hidden);
	weightsHI = Matrix(hidden, output);

	deltaWeightsHI = ( Matrix(hidden,input) );
	deltaWeightsOH = ( Matrix(output, hidden) );

	biasH = ( Matrix(hidden, 1) );
	biasO = ( Matrix(output, 1) );

	deltaBiasH = (Matrix(hidden, 1) );
	deltaBiasO = (Matrix(output, 1) );

}


NeuralNetwork::~NeuralNetwork()
{
}

Matrix NeuralNetwork::Feedforward(Matrix input)
{
	Matrix temp = (weightsHI * input);
	Matrix hidden = temp;
	if (usingBias)
	{
		hidden = hidden + biasH;
	}
	if (!lineral)
	{
		hidden.map(f_aktywacyjna);
	}

	Matrix temp2 = (weightsOH * hidden);
	Matrix output = temp2;
	if (usingBias)
	{
		output = output + biasO;
	}
	if (!lineral)
	{
		output.map(f_aktywacyjna);
	}

	return output;
}


void NeuralNetwork::Backpropagation(Matrix input, Matrix answer)
{
	//Feedforward Start
	Matrix temp = (weightsHI * input);
	Matrix hidden = temp;
	if (usingBias)
	{
		hidden = hidden + biasH;
	}
	if (!lineral)
	{
		hidden.map(f_aktywacyjna);
	}

	Matrix temp2 = (weightsOH * hidden);
	Matrix output = temp2;
	if (usingBias)
	{
		output = output + biasO;
	}
	if (!lineral)
	{
		output.map(f_aktywacyjna);
	}
	//Feedforward End

	//Calculate the output error 
	Matrix outputError = answer - output;

	//Calculate hidden layer errors
	Matrix hiddenErrors = weightsOH.transpose() * outputError;

	//calculate gradient
	Matrix gradient = output;
	if (!lineral)
	{
		gradient.map(pochodna);
		gradient = (gradient * outputError) * learningRate;
	}
	else
	{
		gradient = outputError * learningRate;
	}

	// Delta weightsOutputHidden
	deltaWeightsOH = (gradient * hidden.transpose()) + (deltaWeightsOH * momentum);

	//Adjust weightsOH by delta
	weightsOH = weightsOH + deltaWeightsOH;

	//Adjust the output layer bias
	if (usingBias)
	{
		deltaBiasO = gradient + (deltaBiasO * momentum);
		biasO = biasO + deltaBiasO;
	}

	// calculate hidden gradient
	Matrix gradientHidden = hidden;
	if (!lineral)
	{
		gradientHidden.map(pochodna);
		gradientHidden = (gradientHidden * hiddenErrors) * learningRate;
	}
	else
	{
		gradient = hiddenErrors * learningRate;
	}

	//calculate inputs->hidden deltas
	deltaWeightsHI = (gradientHidden * input.transpose()) + (deltaWeightsHI * momentum);

	//Adjust weightsHI by delta
	weightsHI = weightsHI + deltaWeightsHI;

	//Adjust hidden layer bias
	if (usingBias)
	{
		deltaBiasH = gradientHidden + (deltaBiasH * momentum);
		biasH = biasH + deltaBiasH;
	}
}

