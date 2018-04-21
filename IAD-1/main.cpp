#include <iostream>
#include "Matrix.h"
#include "NeuralNetwork.h"
#include "Losowanie.h"
#include <time.h>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;


double printError(vector<Matrix> answer, vector<Matrix> learning, NeuralNetwork brain)
{
	vector<vector<double>> errors;
	Matrix error = answer[0];
	error = error * 0;			//init of empty matrix with right size
	for (int i = 0; i < 4; i++)
	{
		Matrix target = answer[i];
		Matrix result = brain.Feedforward(learning[i]);
		error = error + (target - result) * (target - result);
	}
	double errorek = 0.0;
	for (int i = 0; i < 4; i++)
	{
		errorek += error.values[i][0];
	}
	errorek = errorek * (1.0 / 4);
	cout << "Blad MSE : ";
	cout << errorek << endl;
	return errorek;
}

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


	NeuralNetwork brain(4, 2, 4);

	int wylosowane[4];
	int wylosowanych = 0;
	int qqq = 0;
	for (int i = 0; i < 10; i++)
	{
		wylosowanych = 0;
		do
		{
			Losowanie losuj;
			int liczba = losuj.wylosuj();
			if (losuj.czyBylaWylosowana(liczba, wylosowane, wylosowanych) == false)
			{
				wylosowane[wylosowanych] = liczba;
				wylosowanych++;
			} 
		} while (wylosowanych < 4);

		for (int j = 0; j < 4; j++)
		{
			brain.Backpropagation(learning[wylosowane[j]], answer[wylosowane[j]]);
			
		}
		//Matrix showTrain = brain.Feedforward(learning[wylosowane[j]]);
			//showTrain.print();
			//showTrain.toFile(outFile);
			outFile << " ";
			outFile << i;
			outFile << " ";
			outFile << printError(answer, learning, brain);
			outFile << "\n";

	}

	for (int i = 0; i < 4; i++)
	{
		Matrix output = brain.Feedforward(answer[i]);
		answer[i].print();
	}
	outFile.close();
	system("pause");
	return 0;
}
