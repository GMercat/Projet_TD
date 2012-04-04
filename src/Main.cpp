#include "../include/Defined.h"

#include "../include/Moteur.h"
#include "../include/Timer.h"

int main( int argc, char *argv[ ] )
{
	SDL_Event		Event;
	SDL_Surface*	pScreen	= NULL;
	
	//Le regulateur
    CTimer Fps;

	int done = 0;

	CMoteur Moteur;

	//Initialisation
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Probleme pour initialiser SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

    //Mettre un titre à la fenêtre
    SDL_WM_SetCaption("TowerDefense by Guit00n 0.2", NULL);

	//Ouvrir une fenetre
    pScreen = SDL_SetVideoMode(LARGEUR_CASE * NB_CASE_LARGEUR + LARGEUR_MENU, HAUTEUR_CASE * NB_CASE_HAUTEUR, 32,	SDL_DOUBLEBUF | SDL_HWSURFACE);
    if (pScreen == NULL)
      	done = 1;

    //Initialiser le jeu
    if(false == Moteur.OnInit ())
        return 1;

	//Boucle generale
	while(!done)
	{
		//On demarre le timer fps
      Fps.Start();

		//Traiter les evenements
		while(SDL_PollEvent(&Event))
		{
   		Moteur.handle_input(&Event);
		
			switch(Event.type)
			{
				case SDL_QUIT:
					done=1;
					break;
				case SDL_KEYUP:
					if (Event.key.keysym.sym==SDLK_q)
						done=1;
					break;
				case SDL_MOUSEBUTTONUP:
					Moteur.OnClic(Event.button.x, Event.button.y);
					break;
				default:
					break;
			}
		}

      // Déplacement des ennemis
      Moteur.OnProgression ();

      // Tire des tours
      Moteur.OnTire ();

      // Affichage de toutes les parties du jeu
		Moteur.OnAffiche (pScreen);
		SDL_Flip(pScreen);

      //Tant que le timer fps n'est pas assez haut
      while( Fps.GetNbTicks () < 1000 / IMAGES_PAR_SECONDE )
      {
         //On attend...
      }
	}

	SDL_Quit();

	system("pause");

	return 0;
}
