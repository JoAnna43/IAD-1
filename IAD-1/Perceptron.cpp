#include "Perceptron.h"
#include <cmath>


Perceptron::Perceptron()
{
	//losowanie wag
	for (int i = 0; i<wagi.length; i++)
	{
		wagi.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));		//Init with random number from 0.0 to 1.0
	}
}


Perceptron::~Perceptron()
{

}



