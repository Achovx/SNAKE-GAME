#include "fonctions.h"
#include "constantes.h"
#include "level3.h"


void level2()
{		
	//Création de la fenêtre
	SDL_Window* fenetre = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);
	
	//Création de l'écran du contenu
	SDL_Surface* ecran = SDL_GetWindowSurface(fenetre);
	
	//SDL_mixer
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); //Fréquence, Format, Nombre channel, Taille d'échantillon
	
	//Theme musique
	Mix_Music* music = NULL;
	// music = Mix_LoadMUS("musics/theme.mp3");
	Mix_PlayMusic(music, -1);
	
	//Sound effects
	Mix_Music* dead;
	dead = Mix_LoadMUS("effects/dead.mp3");
	Mix_Music* victory;
	victory = Mix_LoadMUS("effects/victory.mp3");
	
	//Chargement d'image
	SDL_Surface* background = IMG_Load("images/Background.jpg");
	SDL_Surface* pomme = IMG_Load("sprites/apple.png");
	SDL_Surface* pomme2 = IMG_Load("sprites/apple.png");
	
	//Moteur de rendu
	SDL_Renderer* renderer = SDL_CreateRenderer(fenetre, -1, 0);
	
	//Déclaration
	int continuer = 1;
	SDL_Event event;
	
	//Couleur d'écriture
	SDL_Color noir = {0, 0, 0};
	SDL_Color blanc = {255, 255, 255};
	SDL_Color rouge = {178, 38, 38};
	SDL_Color vert = {76, 181, 59};
	SDL_Color bleu = {25, 143, 191};
	
	//Position du serpent
	SDL_Rect position; //Crée un box rectangle
	position.x = 500;
	position.y = 500;
	
	//Dimension du serpent
	const int BOX_WIDTH = 50;
	const int BOX_HEIGHT = 50;
	position.w = BOX_WIDTH;
	position.h = BOX_HEIGHT;
	
	//SDL_TTF
	TTF_Init();
	
	//Police d'écriture
	TTF_Font* font = TTF_OpenFont("font/Aero.ttf", 50);;
	
	//Création du temps de jeu
	int compteur = 0;
	int tempsActuel = 0;
	int tempsPrecedent = 0;
	char temps[20]= "";
	
	tempsActuel = SDL_GetTicks(); //Fonction pour obtenir le nombre de milliseconde
	sprintf(temps, "Temps : %d", compteur);
	
	SDL_Surface* temps_texte = TTF_RenderText_Shaded(font, temps, noir, blanc); //Choix : Solid(rapide + transparence) - Shaded(antialiasée + lisse + fond couleur) - Blended (lent + beau);
	SDL_Texture* temps_texture = SDL_CreateTextureFromSurface(renderer, temps_texte); //Créer un texture depuis une surface
	
	//Position du temps
	SDL_Rect tempsPOS;
	tempsPOS.x = 5;
	tempsPOS.y = 10;
	
	//Création du score
	int nombrepoint = 0;
	int scoreActuel = 0;
	int scorePrecedent = 0;
	char score[20] = "";
	
	scoreActuel = SDL_GetTicks(); //Fonction pour obtenir le nombre de milliseconde
	sprintf(score, "Score : %d", nombrepoint);
	
 	SDL_Surface* score_texte = TTF_RenderText_Solid(font, score, noir);
 	SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer, score_texte);
	
	//Position du score
 	SDL_Rect scorePOS;
 	scorePOS.x = 900;
 	scorePOS.y = 10;
	
	//Random
	int random;
	srand(time(NULL));
	random = rand() % 650;
	
	int random2;
	srand(time(NULL));
	random = rand() % 650;
	
	//Position de la pomme
	SDL_Rect pommePOS;
	pommePOS.x = random;
	pommePOS.y = random;
	
	SDL_Rect pomme2POS;
	pomme2POS.x = random2;
	pomme2POS.y = random2;
	
	//Gameover
	SDL_Surface* gameover_texte = TTF_RenderText_Blended(font, "GAMEOVER", rouge);
	SDL_Texture* gameover_texture = SDL_CreateTextureFromSurface(renderer, gameover_texte);
	
	SDL_Surface* continuer_texte = TTF_RenderText_Blended(font, "Appuyer sur ENTREE pour continuer", noir);
	SDL_Texture* continuer_texture = SDL_CreateTextureFromSurface(renderer, continuer_texte);
	
	//Position gameover
	SDL_Rect gameoverPOS;
	gameoverPOS.x = 520;
	gameoverPOS.y = 360;
	
	SDL_Rect continuerPOS;
	continuerPOS.x = 220;
	continuerPOS.y = 420;
	
	//Victory
	SDL_Surface* victory_texte = TTF_RenderText_Blended(font, "GOOD GAME", bleu);
	SDL_Texture* victory_texture = SDL_CreateTextureFromSurface(renderer, gameover_texte);
	
	//Position victory
	SDL_Rect victoryPOS;
	victoryPOS.x = 520;
	victoryPOS.y = 360;
	
	//Vitesse du serpent
	int speed = 50;
	
	//Taille du serpent
	int size = 0;
	SDL_Surface* body[50] = {};
	SDL_Rect bodybox[50] = {};
	int sizeMax = 30;
	
	//Position initiale du serpent
	bodybox[0].x = 500;
	bodybox[0].y = 500;
	
	//Création d'un carré
	SDL_Rect box;
	SDL_Surface* head = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0); //Flag - Width - Height - Depth - R - G - B - Alpha
	SDL_FillRect(head, NULL, SDL_MapRGB(head->format, 255, 241, 117)); //Rempli le carré avec un code couleur
	
	//Création d'une fond blanc
	SDL_Surface* background2 = SDL_CreateRGBSurface(0, LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, 0, 0, 0, 0); //Flag - Width - Height - Depth - R - G - B - Alpha
	SDL_FillRect(background2, NULL, SDL_MapRGB(background2->format, 255, 255, 255)); //Rempli le carré avec un code couleur
	
	//Controle de direction
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	
	//Pause /////////////////////////////////// non fonctionnelle
	bool pause = false;
    
    //Utiliser pour mettre un delay entre les corps du serpent
	float time = SDL_GetTicks() / 100;
		
	//Boucle du jeu
	while(continuer)
	{
		//Mettre un delay pour les movements des corps du serpent
		float newTime = SDL_GetTicks() / 75; //La valeur pour la update le corps du serpent
		float delta = newTime - time;
		time = newTime;
			
		//Initialise le background
		SDL_BlitSurface(background, NULL, ecran, NULL);
		
		if (SDL_PollEvent(&event)) 
		{
			//Fermeture
			if (event.type == SDL_QUIT) 
			{
				exit(0);
			}
			//Quand la touche est appuyé
			if (event.type == SDL_KEYDOWN) 
			{
				if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					continuer = 0;
				}
				
				//Alors change de direction
				if (down == false && event.key.keysym.scancode == SDL_SCANCODE_UP) 
				{
					up = true;
					left = false;
					right = false;
					down = false;
				}
				else if (right == false && event.key.keysym.scancode == SDL_SCANCODE_LEFT) 
				{
					up = false;
					left = true;
					right = false;
					down = false;
				}
				else if (up == false && event.key.keysym.scancode == SDL_SCANCODE_DOWN) 
				{
					up = false;
					left = false;
					right = false;
					down = true;
				}
				else if (left == false && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) 
				{
					up = false;
					left = false;
					right = true;
					down = false;
				}
				
				if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) 
				{
					printf ("PAUSE\n");
					while (pause = true)
					{
						SDL_Delay;
						if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
						{
							pause = false;
						}
					}
				}
				else
				{
					pause = false;
				}
			}
		}
			
		if (up)
		{
			bodybox[0].y -= speed * delta;
			//Si il y a collision
			if (bodybox[0].y < 0 || (bodybox[0].y + BOX_HEIGHT > HAUTEUR_FENETRE))
			{
				//Vitesse annuler
				bodybox[0].y += speed;
				Mix_PlayMusic(dead, 0);
				while (true) 
				{
					if (SDL_PollEvent(&event)) 
					{
						if (event.type == SDL_QUIT) 
						{
							exit(0);
						}
						if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) 
						{
							return;
						}
					}
					tempsPOS.x = 210;
					tempsPOS.y = 480;
					scorePOS.x = 880;
 					scorePOS.y = 480;
 					SDL_BlitSurface(background2, NULL, ecran, NULL);
					SDL_BlitSurface(temps_texte, NULL, ecran, &tempsPOS);
					SDL_BlitSurface(score_texte, NULL, ecran, &scorePOS);
					SDL_BlitSurface(gameover_texte, NULL, ecran, &gameoverPOS);
					SDL_BlitSurface(continuer_texte, NULL, ecran, &continuerPOS);
					SDL_UpdateWindowSurface(fenetre);
				}
			}
			SDL_BlitSurface(head, NULL, ecran, &bodybox[0]);
		}
		else if (left) 
		{
			bodybox[0].x -= speed * delta;
			//Si il y a collision
			if (bodybox[0].x < 0 || (bodybox[0].x + BOX_WIDTH > LARGEUR_FENETRE))
			{
				//Vitesse annuler
				bodybox[0].x += speed;
				Mix_PlayMusic(dead, 0);
				while (true) 
				{
					if (SDL_PollEvent(&event)) 
					{
						if (event.type == SDL_QUIT) 
						{
							exit(0);
						}
						if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) 
						{
							return;
						}
					}
					tempsPOS.x = 210;
					tempsPOS.y = 480;
					scorePOS.x = 880;
 					scorePOS.y = 480;
 					SDL_BlitSurface(background2, NULL, ecran, NULL);
					SDL_BlitSurface(temps_texte, NULL, ecran, &tempsPOS);
					SDL_BlitSurface(score_texte, NULL, ecran, &scorePOS);
					SDL_BlitSurface(gameover_texte, NULL, ecran, &gameoverPOS);
					SDL_BlitSurface(continuer_texte, NULL, ecran, &continuerPOS);
					SDL_UpdateWindowSurface(fenetre);
				}		
			}
			SDL_BlitSurface(head, NULL, ecran, &bodybox[0]);
		}
		else if (right) 
		{
			bodybox[0].x += speed * delta;
			//Si il y a collision
			if (bodybox[0].x < 0 || (bodybox[0].x + BOX_WIDTH > LARGEUR_FENETRE))
			{
				//Vitesse annuler
				bodybox[0].x -= speed;
				Mix_PlayMusic(dead, 0);
				while (true) 
				{
					if (SDL_PollEvent(&event)) 
					{
						if (event.type == SDL_QUIT) 
						{
							exit(0);
						}
						if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) 
						{
							return;
						}
					}
					tempsPOS.x = 210;
					tempsPOS.y = 480;
					scorePOS.x = 880;
 					scorePOS.y = 480;
 					SDL_BlitSurface(background2, NULL, ecran, NULL);
					SDL_BlitSurface(temps_texte, NULL, ecran, &tempsPOS);
					SDL_BlitSurface(score_texte, NULL, ecran, &scorePOS);
					SDL_BlitSurface(gameover_texte, NULL, ecran, &gameoverPOS);
					SDL_BlitSurface(continuer_texte, NULL, ecran, &continuerPOS);
					SDL_UpdateWindowSurface(fenetre);
				}
			}
			SDL_BlitSurface(head, NULL, ecran, &bodybox[0]);
		}
		else if (down) 
		{
			bodybox[0].y += speed * delta;
			//Si il y a collision
			if (bodybox[0].y < 0 || (bodybox[0].y + BOX_HEIGHT > HAUTEUR_FENETRE))
			{
				//Vitesse annuler
				bodybox[0].y -= speed;
				Mix_PlayMusic(dead, 0);
				while (true) 
				{
					if (SDL_PollEvent(&event)) 
					{
						if (event.type == SDL_QUIT) 
						{
							exit(0);
						}
						if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) 
						{
							return;
						}
					}
					tempsPOS.x = 210;
					tempsPOS.y = 480;
					scorePOS.x = 880;
 					scorePOS.y = 480;
 					SDL_BlitSurface(background2, NULL, ecran, NULL);
					SDL_BlitSurface(temps_texte, NULL, ecran, &tempsPOS);
					SDL_BlitSurface(score_texte, NULL, ecran, &scorePOS);
					SDL_BlitSurface(gameover_texte, NULL, ecran, &gameoverPOS);
					SDL_BlitSurface(continuer_texte, NULL, ecran, &continuerPOS);
					SDL_UpdateWindowSurface(fenetre);
				}
			}
			SDL_BlitSurface(head, NULL, ecran, &bodybox[0]);
		}
		
		//Temps de jeu
		tempsActuel = SDL_GetTicks();		
        if (tempsActuel - tempsPrecedent >= 50) //Si 50 ms au moins se sont écoulées
        	{
	            compteur += 50; //On rajoute 50 ms au compteur
	            sprintf(temps, "Temps : %d", compteur); //On écrit dans la chaîne "temps" le nouveau temps
	            SDL_FreeSurface(temps_texte); //On supprime la surface précédente
	            temps_texte = TTF_RenderText_Shaded(font, temps, noir, blanc); //On écrit la chaîne temps dans la SDL_Surface
	            tempsPrecedent = tempsActuel; //On met à jour le tempsPrecedent
				
				//Définir les nouvelles positions des corps du serpent
		        int nextX = bodybox[0].x;
		        int nextY = bodybox[0].y;
		        int tmpX, tmpY;
		            	
		        for (int i = 1; i <= sizeMax; i++)
			    {
			        tmpX = bodybox[i - 1].x;
			        tmpY = bodybox[i - 1].y;
			        bodybox[i - 1].x = nextX;
			        bodybox[i - 1].y = nextY;
			                             
			        nextX = tmpX;
			        nextY = tmpY;
			    }
			}
				
		//Collision pomme
		if (collision(bodybox[0], pommePOS))
			{
				//Générer un nombre aléatoire pour repositionner la pomme	
				random = rand() % 650;
				pommePOS.x = random;
				pommePOS.y = random;
				
				nombrepoint += 1;
				
				//Créer une nouvelle SDL_Surface pour agrandir le serpent
				if (size <= sizeMax)
				{	
					body[size] = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0); //Flag - Width - Height - Depth - R - G - B - Alpha
					SDL_FillRect(body[size], NULL, SDL_MapRGB(body[size]->format, 134, 241, 117)); //Rempli le carré avec un code couleur
					size++;
				}
			}
			
		if (collision(bodybox[0], pomme2POS))
			{
				random2 = rand() % 650;
				pomme2POS.x = random2;
				pomme2POS.y = random2;
				
				nombrepoint += 1;
				
				//Créer une nouvelle SDL_Surface pour agrandir le serpent
				if (size <= sizeMax)
				{	
					body[size] = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0); //Flag - Width - Height - Depth - R - G - B - Alpha
					SDL_FillRect(body[size], NULL, SDL_MapRGB(body[size]->format, 134, 241, 117)); //Rempli le carré avec un code couleur
					size++;
				}
			}
			
		//Score
		scoreActuel = SDL_GetTicks();
		sprintf(score, "Score : %d", nombrepoint);
		SDL_FreeSurface(score_texte);
		score_texte = TTF_RenderText_Solid(font, score, noir);
		scorePrecedent = scoreActuel;
		
		//Gagner le niveau
		if (nombrepoint == 30)
		{
			Mix_PlayMusic(victory, 0);
			while (true) 
			{
				if (SDL_PollEvent(&event)) 
				{
					if (event.type == SDL_QUIT) 
					{
						exit(0);
					}
					if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) 
					{
						level3();
					}
				}
					tempsPOS.x = 210;
					tempsPOS.y = 480;
					scorePOS.x = 880;
		 			scorePOS.y = 480;
		 			SDL_BlitSurface(background2, NULL, ecran, NULL);
					SDL_BlitSurface(temps_texte, NULL, ecran, &tempsPOS);
					SDL_BlitSurface(score_texte, NULL, ecran, &scorePOS);
					SDL_BlitSurface(continuer_texte, NULL, ecran, &continuerPOS);
					SDL_BlitSurface(victory_texte, NULL, ecran, &victoryPOS);
					SDL_BlitSurface(continuer_texte, NULL, ecran, &continuerPOS);
					SDL_UpdateWindowSurface(fenetre);
			}
		}	
		
		//Manger la queue
		for (int i = 4; i <= sizeMax; i++) //Pourquoi mettre 4 ? Pour éviter de les frames des précédents
		{
			if (collision(bodybox[0], bodybox[i]))
			{
				Mix_PlayMusic(dead, 0);
				while (true) 
				{
					if (SDL_PollEvent(&event)) 
					{
						if (event.type == SDL_QUIT) 
						{
							exit(0);
						}
						if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) 
						{
							return;
						}
					}
					tempsPOS.x = 210;
					tempsPOS.y = 480;
					scorePOS.x = 880;
	 				scorePOS.y = 480;
	 				SDL_BlitSurface(background2, NULL, ecran, NULL);
					SDL_BlitSurface(temps_texte, NULL, ecran, &tempsPOS);
					SDL_BlitSurface(score_texte, NULL, ecran, &scorePOS);
					SDL_BlitSurface(gameover_texte, NULL, ecran, &gameoverPOS);
					SDL_BlitSurface(continuer_texte, NULL, ecran, &continuerPOS);
					SDL_UpdateWindowSurface(fenetre);
				}
			}
		}
		
		//Blitter = BLIT (bit block transfer) fonction pour défiler les mouvements des surfaces
		for (int i = 1; i <= sizeMax; i++)
		{	
			SDL_BlitSurface(body[i], NULL, ecran, &bodybox[i]);
		}
		
		SDL_BlitSurface(temps_texte, NULL, ecran, &tempsPOS);
		SDL_BlitSurface(score_texte, NULL, ecran, &scorePOS);
		SDL_BlitSurface(pomme, NULL, ecran, &pommePOS);
		SDL_BlitSurface(pomme2, NULL, ecran, &pomme2POS);
		SDL_UpdateWindowSurface(fenetre);
	}
	SDL_FreeSurface(background);
	SDL_FreeSurface(temps_texte);
	SDL_FreeSurface(pomme);
	SDL_FreeSurface(pomme2);
	SDL_FreeSurface(score_texte);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return;
}
