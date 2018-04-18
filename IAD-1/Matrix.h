#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Matrix
{
public:
	vector<vector<double>> values;
	Matrix();
	Matrix(int rows, int cols);
	Matrix(const Matrix &_m);
	Matrix(vector<vector<double>> yes);
	Matrix(int rows, int cols, string filename, int skipInputs);
	~Matrix();
	void wyswietl();
	void map(double(*f)(double));
	Matrix operator*(double s);
	Matrix operator*(Matrix _m);
	Matrix operator+(double s);
	Matrix operator+(Matrix _m);
	Matrix operator-(double s);
	Matrix operator-(Matrix _m);
	Matrix transpose();
};

