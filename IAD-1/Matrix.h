#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Matrix
{
private:
	vector<vector<double>> values;
public:
	Matrix();
	Matrix(vector<vector<double>>);
	Matrix(int , int );
	Matrix(const Matrix&);
	Matrix(int , int , string , int );

	void print();
	void toFile(ofstream &);

	void map(double(*)(double));
	Matrix operator*(double);
	Matrix operator*(Matrix );
	Matrix operator+(Matrix);
	Matrix operator-(Matrix);
	Matrix transpose();
};

