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

//Matrix NeuralNetwork::Error(Matrix input[], Matrix answer[], int size)
//{
//
//	return error;
//}

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

	//cout << "Input" << endl;
	//input.wyswietl();

	//calculate the output error 
	Matrix outputError = answer - output;
	/*cout << "outputError"<<endl;
	outputError.wyswietl();*/
	
	//calculate hidden layer errors
	Matrix weightsOHt = weightsOH.transpose();
	Matrix hiddenErrors = weightsOHt * outputError;
	//cout << "hiddenErrors"<<endl;
	//hiddenErrors.wyswietl();

	//calculate gradient
	Matrix gradient = output;
	if (!lineral)
	{
		gradient.map(pochodna);
		gradient = (gradient * outputError) * learningRate;
		//cout << "gradient"<<endl;
		//gradient.wyswietl();
	}
	else
	{
		gradient = outputError * learningRate;
		//cout << "gradient" << endl;
		//gradient.wyswietl();
	}

	// Delta weightsOutputHidden
	Matrix hiddenT = hidden.transpose();
	deltaWeightsOH = (gradient * hiddenT) + (deltaWeightsOH * momentum);
	//cout << "deltaWeightsOH" << endl;
	//deltaWeightsOH.wyswietl();

	//Adjust weightsOH by delta
	weightsOH = weightsOH + deltaWeightsOH;
	//cout << "weightsOH" << endl;
	//weightsOH.wyswietl();

	//Adjust the output layer bias
	if (usingBias)
	{
		deltaBiasO = gradient + (deltaBiasO * momentum);
		biasO = biasO + deltaBiasO;
		//cout << "biasO" << endl;
		//biasO.wyswietl();
	}

	// calculate hidden gradient
	Matrix gradientHidden = hidden;
	if (!lineral)
	{
		gradientHidden.map(pochodna);
		gradientHidden = (gradientHidden * hiddenErrors) * learningRate;
		//cout << "gradientHidden" << endl;
		//gradientHidden.wyswietl();
	}
	else
	{
		gradient = hiddenErrors * learningRate;
		//cout << "gradientHidden" << endl;
		//gradientHidden.wyswietl();
	}

	//calculate inputs->hidden deltas
	Matrix inputT = input.transpose();
	//cout << "inputT" << endl;
	//inputT.wyswietl();
	deltaWeightsHI = (gradientHidden * inputT) + (deltaWeightsHI * momentum);
	//cout << "deltaWeightsHI" << endl;
	//deltaWeightsHI.wyswietl();

	//Adjust weightsHI by delta
	weightsHI = weightsHI + deltaWeightsHI;
	//cout << "weightsHI" << endl;
	//weightsHI.wyswietl();

	//Adjust hidden layer bias
	if (usingBias)
	{
		deltaBiasH = gradientHidden + (deltaBiasH * momentum);
		biasH = biasH + deltaBiasH;
		//cout << "biasH" << endl;
		//biasH.wyswietl();
	}


}

