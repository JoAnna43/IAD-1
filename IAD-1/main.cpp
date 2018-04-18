#include <iostream>
#include "Matrix.h"
#include "NeuralNetwork.h"
#include <time.h>
#include <windows.h>
#include <fstream>

using namespace std;

int main()
{
	srand(time(NULL));
	ofstream outFile;
	outFile.open("export.txt");
	const int learning_base = 4;
	fstream file("Input.txt", ios_base::in);

	vector<Matrix> learning, answer;
	for (int k = 0; k < learning_base; k++)
	{
		Matrix temp;
		vector<vector<double>> temp2;
		for (int i = 0; i < 4; i++)
		{
			vector<double> temp3;
			double temp4;
			file >> temp4;
			temp3.push_back(temp4);
			temp2.push_back(temp3);
		}
		temp = temp2;
		learning.push_back(temp);
		answer.push_back(temp);
	}
	file.close();

	learning[0].wyswietl();
	answer[0].wyswietl();

	NeuralNetwork brain(4, 1, 4);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			brain.Backpropagation(learning[2], answer[2]);
			Matrix showTrain = brain.Feedforward(learning[2]);
			showTrain.wyswietl();
			showTrain.toFile(outFile);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		Matrix output = brain.Feedforward(learning[i]);
		answer[i].wyswietl();
		output.wyswietl();
	}
	system("pause");
	return 0;
}
