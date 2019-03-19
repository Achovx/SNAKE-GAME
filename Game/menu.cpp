/* TP en binome ou trinome : réalisation d'un prog serpent

Utilisation 1 : la librairie conio.c
Utilisation 2 : la librairie SDL

Fonctionnalités : 
- Le serpent s'agrandit d'un élément en mangeant 3 pommes
- Le serpent ne devra pas touche les murs
- Le serpent ne peut pas se morde la queue
- On génére trois pommes à la fois

Paramètrage :

- Niveau 1 : trois pommes, taille serpent 20 éléments vitesse 5, on saisie le nom prenom et score = nombre element / temps passe

- Niveau 2 : deux pommes, taille serpent 30 éléments vitesse 3, on saisie le nom prenom et score = nombre elements / temps passe

- Niveau 3 : 1 pomme, taille serpent 40 éléments vitesse 1, sans murs (le serpent est cyclique), on saisie le nombre elements / temps passe
Les données sont sauvegardées dans un fichier.

Indication :
	Réaliser le serpent en utilisant une matrice.
	
	gotoxy
*/

#include "fonctions.h"
#include "constantes.h"
#include "level1.h"


int main(int argc, char* argv[])
{	
		//Création de la fenêtre
	SDL_Window* fenetre = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);
	
	//Création de l'écran du contenu
	SDL_Surface* ecran = SDL_GetWindowSurface(fenetre);
	
	//Moteur de rendu
	SDL_Renderer* renderer = SDL_CreateRenderer(fenetre, -1, 0);
	
	SDL_Event event;
	
	TTF_Init();
	
	TTF_Font* font = TTF_OpenFont("font/Aero.ttf", 50);
	
	//Couleur d'écriture
	SDL_Color noir = {0, 0, 0};
	SDL_Color blanc = {255, 255, 255};
	SDL_Color rouge = {178, 38, 38};
	SDL_Color vert = {76, 181, 59};
	SDL_Color bleu = {25, 143, 191};
	
	SDL_Surface* background = IMG_Load("images/Background.jpg");
	
	SDL_Surface* commencer_texte = TTF_RenderText_Blended(font, "COMMENCER", noir);
	SDL_Texture* commencer_texture = SDL_CreateTextureFromSurface(renderer, commencer_texte);
	SDL_Rect commencerPOS;
	commencerPOS.x = 490;
	commencerPOS.y = 600;
	
	SDL_Surface* quitter_texte = TTF_RenderText_Blended(font, "QUITTER", noir);
	SDL_Texture* quitter_texture = SDL_CreateTextureFromSurface(renderer, quitter_texte);
	SDL_Rect quitterPOS;
	quitterPOS.x = 490;
	quitterPOS.y = 650;
	
	int continuer = 1;
	
	bool choix1 = false;
	bool choix2 = false;
	
	char nom[25];
	int niveau;
	
	printf ("Saisir votre nom : \n");
	scanf ("%s", &nom);
	printf("Bonne chance  %s !", nom);
	
	while(continuer)
	{
		SDL_BlitSurface(background, NULL, ecran, NULL);
		
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) 
			{
				exit(0);
			}
			if (event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)				
				{
					continuer = 0;
				}
				
				//Commencer
				if(event.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					commencer_texte = TTF_RenderText_Blended(font, "COMMENCER", rouge);
					quitter_texte = TTF_RenderText_Blended(font, "QUITTER", noir);
					choix2 = false;	
					choix1 = true;
				}
				
				//Quitter
				if(event.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					commencer_texte = TTF_RenderText_Blended(font, "COMMENCER", noir);
					quitter_texte = TTF_RenderText_Blended(font, "QUITTER", rouge);
					choix1 = false;
					choix2 = true;
				}
				
				//Valider
				if (choix1 == true && event.key.keysym.scancode == SDL_SCANCODE_RETURN)
					{
						printf ("\n");
						printf ("Choisir un niveau : \n");
						printf ("\n");
						printf ("Niveau [1] - 3 pommes + sizeMax(20) \n");
						printf ("Niveau [2] - 2 pommes + sizeMax(30) \n");
						printf ("Niveau [3] - 1 pomme + sizeMax(40) \n");
						printf ("Saisir un nombre : \n");
						scanf ("%d", &niveau);
						
						if (niveau == 1)
						{
							level1();
						}
						
						else if (niveau == 2)
						{
							level2();
						}
						
						else if (niveau == 3)
						{
							level3();
						}
					}
				
				//Valider
				if (choix2 == true && event.key.keysym.scancode == SDL_SCANCODE_RETURN)
					{
						continuer = 0;
					}
				
			}
		}
		
		SDL_BlitSurface(commencer_texte, NULL, ecran, &commencerPOS);
		SDL_BlitSurface(quitter_texte, NULL, ecran, &quitterPOS);
		SDL_UpdateWindowSurface(fenetre);
	}
	SDL_FreeSurface(commencer_texte);
	SDL_FreeSurface(quitter_texte);
	SDL_FreeSurface(background);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}
