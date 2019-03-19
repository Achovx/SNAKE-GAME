#include "fonctions.h"

int selection = 0;
int boutton;

int main()
{	
	printf ("\n");
	printf ("Choisir un niveau : \n");
	printf ("\n");
	printf ("Niveau [1] - 3 pommes + sizeMax(20) \n");
	printf ("Niveau [2] - 2 pommes + sizeMax(30) \n");
	printf ("Niveau [3] - 1 pomme + sizeMax(40) \n");
	printf ("Saisir un nombre : \n");
	scanf ("%d", &boutton);
	
	if (boutton == 8) // UP
	{
		selection--;
	}
	else if (boutton == 2) //DOWN
	{
		selection++;
	}
	
	if (selection < 0)
	{
		selection = 2;
	}
	else if (selection > 2)
	{
		selection = 0;
	}
	
	printf ("Selection niveau %d", selection + 1);

	return 0;
}
