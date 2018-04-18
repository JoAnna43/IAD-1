#include "Matrix.h"
#include <vector>
#include <iostream>


#include "Matrix.h"

Matrix::Matrix()
{

}

Matrix::Matrix(int rows, int cols, string filename, int skipInputs)
{
	fstream file(filename, std::ios_base::in);
	if (skipInputs > 0)
	{
		int i = skipInputs;
		double temp2;
		for (i; i <= 0; i--)
			file >> temp2;
	}
	for (int i = 0; i < rows; i++)
	{
		vector<double> temp;
		for (int j = 0; j < cols; j++)
		{
			double temp2;
			file >> temp2;
			temp.push_back(temp2);
		}
		values.push_back(temp);
	}
	file.close();
}

Matrix::Matrix(int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		vector<double> temp;
		for (int j = 0; j < cols; j++)
		{
			temp.push_back((static_cast <float> (rand()) / static_cast <float> (RAND_MAX * 2)) - 1);		//Init with random number from -1.0 to 1.0
		}
		values.push_back(temp);
	}
}

Matrix::Matrix(const Matrix &_m)
{
	for (int i = 0; i < _m.values.size(); i++)
	{
		vector<double> temp;
		for (int j = 0; j < _m.values[0].size(); j++)
		{
			temp.push_back(_m.values[i][j]);
		}
		values.push_back(temp);
	}
}

Matrix::~Matrix()
{
}

void Matrix::wyswietl()
{
	cout << "Matrix:\n";
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			cout << values[i][j] << " ";
		}
		cout << "\n";
	}
}

Matrix::Matrix(vector<vector<double>> vector) : values(vector)
{

}

void Matrix::map(double(*f)(double))
{
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			values[i][j] = f(values[i][j]);
		}
	}
}

Matrix Matrix::operator*(double s)
{
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			values[i][j] *= s;
		}
	}
	return *this;
}

Matrix Matrix::operator*(Matrix _m)
{
	//Matrix product
	if (values[0].size() == _m.values.size())
	{
		Matrix result(values.size(), _m.values[0].size());
		for (int i = 0; i < result.values.size(); i++)
		{
			for (int j = 0; j < result.values[i].size(); j++)
			{
				double sum = 0;
				for (int k = 0; k < values[0].size(); k++)
				{
					sum += values[i][k] * _m.values[k][j];
				}
				result.values[i][j] = sum;
			}
		}
		return result;
	}
	//Hadamard product
	else if (values.size() == _m.values.size() && values[0].size() == _m.values[0].size())
	{
		Matrix result(values.size(), values[0].size());
		for (int i = 0; i < result.values.size(); i++)
		{
			for (int j = 0; j < result.values[i].size(); j++)
			{
				double sum = 0;
				{
					sum += values[i][j] * _m.values[i][j];
				}
				result.values[i][j] = sum;
			}
		}
		return result;
	}
}

Matrix Matrix::operator+(double s)
{
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			values[i][j] += s;
		}
	}
	return *this;
}

Matrix Matrix::operator+(Matrix _m)
{
	Matrix result(values.size(), values[0].size());
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			result.values[i][j] = values[i][j] + _m.values[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator-(double s)
{
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			values[i][j] -= s;
		}
	}
	return *this;
}

Matrix Matrix::operator-(Matrix _m)
{
	Matrix result(values.size(), values[0].size());
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			//cout << values[i][j] << " - " << _m.values[i][j] << " = " << values[i][j] - _m.values[i][j] << "\n";
			result.values[i][j] = values[i][j] - _m.values[i][j];
		}
	}
	return result;
}

Matrix Matrix::transpose()
{
	Matrix result(values[0].size(), values.size());
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			result.values[j][i] = values[i][j];
		}
	}
	return result;
}
