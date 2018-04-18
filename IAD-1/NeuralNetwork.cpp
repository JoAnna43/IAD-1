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

	deltaWeightsHI = Matrix(hidden,input);
	deltaWeightsHI = deltaWeightsHI * 0;
	deltaWeightsOH = Matrix(output, hidden);
	deltaWeightsOH = deltaWeightsOH * 0;

	biasH = Matrix(hidden, 1);
	biasO = Matrix(output, 1);

	deltaBiasH = Matrix(hidden, 1);
	deltaBiasH = deltaBiasH * 0;
	deltaBiasO = Matrix(output, 1);
	deltaBiasO = deltaBiasO * 0;

}


NeuralNetwork::~NeuralNetwork()
{
}

Matrix NeuralNetwork::Feedforward(Matrix input)
{
	
	Matrix hidden = (weightsHI * input);
	if (usingBias)
		hidden = hidden + biasH;
	hidden.map(f_aktywacyjna);

	Matrix output = (weightsOH * hidden);
	if (usingBias)
		output = output + biasO;
	output.map(f_aktywacyjna);

	return output;
}
//
Matrix NeuralNetwork::Error(Matrix input[], Matrix answer[], int size)
{
	vector<vector<double>> errors;
	Matrix error = answer[0];
	error = error * 0;			//init of empty matrix with right size
	for (int i = 0; i < size; i++)
	{
		Matrix target = answer[i];
		Matrix result = Feedforward(input[i]);
		error = error + (target - result) * (target - result);
	}
	error = error * (1.0 / size);
	return error;
}

void NeuralNetwork::Backpropagation(Matrix input, Matrix answer)
{
	//Feedforward Start
	Matrix hidden = (weightsHI * input);
	if (usingBias)
		hidden = hidden + biasH;
	if(!lineral)
	hidden.map(f_aktywacyjna);

	Matrix output = (weightsOH * hidden);
	if (usingBias)
		output = output + biasO;
	if (!lineral)
	output.map(f_aktywacyjna);
	//Feedforward End

	//calculate the output error 
	Matrix outputError = answer - output;

	//calculate hidden layer errors
	Matrix weightsOHt = weightsOH.transpose();
	Matrix hiddenErrors = weightsOHt * outputError;

	//calculate gradient
	Matrix gradient = output;
	if (!lineral)
	{
		gradient.map(pochodna);
		gradient = (gradient * outputError) * learningRate;
	}
	else gradient = outputError * learningRate;

	// Delta weightsOutputHidden
	Matrix hiddenT = hidden.transpose();
	deltaWeightsOH = (gradient * hiddenT) + (deltaWeightsOH * momentum);

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
	else gradient = hiddenErrors * learningRate;

	//calculate inputs->hidden deltas
	Matrix inputT = input.transpose();
	deltaWeightsHI = (gradientHidden * inputT) + (deltaWeightsHI * momentum);
	
	//Adjust weightsHI by delta
	weightsHI = weightsHI * deltaWeightsHI;
	
	//Adjust hidden layer bias
	if (usingBias)
	{
		deltaBiasH = gradientHidden + (deltaBiasH * momentum);
		biasH = biasH + deltaBiasH;
	}


}

