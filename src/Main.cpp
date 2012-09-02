#include "../include/Defined.h"

#include "../include/Moteur.h"
#include "../include/Timer.h"

int main( int argc, char *argv[ ] )
{
   CLog  Log ("Main");

	SDL_Event		Event;
		
	//Le regulateur
   CTimer Fps;

	int Done = 0;

	CMoteur Moteur;
	
   //Initialiser le jeu
   if(false == Moteur.OnInit ())
   {
      Log << Erreur << "Problème rencontré à l'initialisation du moteur" << EndLine;
      Done = 1;
   }

	//Boucle generale
	while(!Done)
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
					Done=1;
					break;
				case SDL_KEYUP:
					if (Event.key.keysym.sym==SDLK_q)
						Done=1;
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
		Moteur.OnAffiche ();

      //Tant que le timer fps n'est pas assez haut
      while( Fps.GetNbTicks () < 1000 / IMAGES_PAR_SECONDE )
      {
         //On attend...
      }
	}

   Moteur.OnQuit ();

	system("pause");

	return 0;
}
