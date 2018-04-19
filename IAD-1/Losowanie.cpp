#include "Losowanie.h"
#include <cstdlib>
#include <ctime>


Losowanie::Losowanie()
{
<<<<<<< HEAD

}

Losowanie::~Losowanie()
{

=======
}


Losowanie::~Losowanie()
{
>>>>>>> 323f41fb6909ffdb052eaad832e2f0df7db6284c
}

bool Losowanie::czyBylaWylosowana(int iLiczba, int tab[], int ile)
{
	if (ile <= 0)
		return false;

	int i = 0;
	do
	{
		if (tab[i] == iLiczba)
			return true;

		i++;
	} while (i < ile);

	return false;
}

int Losowanie::wylosuj()
{
	return(rand() % 4);
}