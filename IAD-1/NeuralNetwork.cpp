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
<<<<<<< HEAD
	}
	if (!lineral)
	{
		output.map(f_aktywacyjna);
	}

	return output;
}
=======
	output.map(f_aktywacyjna);

	return output;
}

//Matrix NeuralNetwork::Error(Matrix input[], Matrix answer[], int size)
//{
//
//	return error;
//}
>>>>>>> 323f41fb6909ffdb052eaad832e2f0df7db6284c


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

<<<<<<< HEAD
	//Calculate the output error 
	Matrix outputError = answer - output;

	//Calculate hidden layer errors
	Matrix hiddenErrors = weightsOH.transpose() * outputError;
=======
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
>>>>>>> 323f41fb6909ffdb052eaad832e2f0df7db6284c

	//calculate gradient
	Matrix gradient = output;
	if (!lineral)
	{
		gradient.map(pochodna);
		gradient = (gradient * outputError) * learningRate;
<<<<<<< HEAD
	}
	else
	{
		gradient = outputError * learningRate;
	}

	// Delta weightsOutputHidden
	deltaWeightsOH = (gradient * hidden.transpose()) + (deltaWeightsOH * momentum);

	//Adjust weightsOH by delta
	weightsOH = weightsOH + deltaWeightsOH;
=======
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
>>>>>>> 323f41fb6909ffdb052eaad832e2f0df7db6284c

	//Adjust the output layer bias
	if (usingBias)
	{
		deltaBiasO = gradient + (deltaBiasO * momentum);
		biasO = biasO + deltaBiasO;
<<<<<<< HEAD
=======
		//cout << "biasO" << endl;
		//biasO.wyswietl();
>>>>>>> 323f41fb6909ffdb052eaad832e2f0df7db6284c
	}

	// calculate hidden gradient
	Matrix gradientHidden = hidden;
	if (!lineral)
	{
		gradientHidden.map(pochodna);
		gradientHidden = (gradientHidden * hiddenErrors) * learningRate;
<<<<<<< HEAD
	}
	else
	{
		gradient = hiddenErrors * learningRate;
	}

	//calculate inputs->hidden deltas
	deltaWeightsHI = (gradientHidden * input.transpose()) + (deltaWeightsHI * momentum);

	//Adjust weightsHI by delta
	weightsHI = weightsHI + deltaWeightsHI;
=======
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
>>>>>>> 323f41fb6909ffdb052eaad832e2f0df7db6284c

	//Adjust hidden layer bias
	if (usingBias)
	{
		deltaBiasH = gradientHidden + (deltaBiasH * momentum);
		biasH = biasH + deltaBiasH;
<<<<<<< HEAD
=======
		//cout << "biasH" << endl;
		//biasH.wyswietl();
>>>>>>> 323f41fb6909ffdb052eaad832e2f0df7db6284c
	}
}

