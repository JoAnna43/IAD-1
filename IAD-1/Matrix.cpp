#include "Matrix.h"
#include <vector>
#include <iostream>
#include <sstream>


#include "Matrix.h"

Matrix::Matrix()
{

}

Matrix::Matrix(vector<vector<double>> vector) : values(vector)
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
		vector<double> rows;
		for (int j = 0; j < cols; j++)
		{
			float temp = ((((float)rand() / RAND_MAX) * (1 - (-1))) + (-1));
			rows.push_back(temp);
		}
		values.push_back(rows);
	}
}

Matrix::Matrix(const Matrix& m)
{
	for (int i = 0; i < m.values.size(); i++)
	{
		vector<double> temp;
		for (int j = 0; j < m.values[0].size(); j++)
		{
			temp.push_back(m.values[i][j]);
		}
		values.push_back(temp);
	}
}

void Matrix::print()
{
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			cout << values[i][j] << " ";
		}
		cout << endl;
	}
}

void Matrix::toFile(ofstream& plik)
{
	std::string string2 = "";
	for (int i = 0; i < values.size(); i++)
	{
		std::string str = "";
		for (int j = 0; j < values[i].size(); j++)
		{
			std::ostringstream strs;
			strs << values[i][j];
			str.append(strs.str());

		}
		string2.append(" ");
		string2.append(str);
	}
	plik << string2;
	plik << "\n";
}

void Matrix::map(double(*function)(double))
{
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			values[i][j] = function(values[i][j]);
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

Matrix Matrix::operator*(Matrix m)
{
	//Matrix product
	if (values[0].size() == m.values.size())
	{
		Matrix result(values.size(), m.values[0].size());
		for (int i = 0; i < result.values.size(); i++)
		{
			for (int j = 0; j < result.values[i].size(); j++)
			{
				double sum = 0;
				for (int k = 0; k < values[0].size(); k++)
				{
					sum += values[i][k] * m.values[k][j];
				}
				result.values[i][j] = sum;
			}
		}
		return result;
	}
	else
	{
		Matrix result(values.size(), values[0].size());
		for (int i = 0; i < result.values.size(); i++)
		{
			for (int j = 0; j < result.values[i].size(); j++)
			{
				double sum = 0;
				{
					sum += values[i][j] * m.values[i][j];
				}
				result.values[i][j] = sum;
			}
		}
		return result;
	}
}


Matrix Matrix::operator+(Matrix m)
{
	Matrix result(values.size(), values[0].size());
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			result.values[i][j] = values[i][j] + m.values[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator-(Matrix m)
{
	Matrix result(values.size(), values[0].size());
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			result.values[i][j] = values[i][j] - m.values[i][j];
		}
	}
	return result;
}

Matrix Matrix::transpose()
{
	Matrix result(values[0].size(), values.size());
	for (int i = 0; i <  values.size(); i++)
	{
		for (int j = 0; j < values[0].size(); ++j)
		{
			result.values[j][i] = values[i][j];
		}
	}
	return result;
}
