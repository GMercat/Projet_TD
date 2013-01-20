#include "Defined.h"

#include "Moteur.h"
#include "Timer.h"

int main( int argc, char *argv[ ] )
{
   int Done = 0;

   SDL_Event	Event;
	CLog        Log ("Main");
   CTimer      Fps; //Le regulateur
   CMoteur     Moteur;
   TCoordonnee CoordonneeClic;
   TCoordonnee CoordonneeSouri;
	
   //Initialiser le jeu
   if(false == Moteur.OnInit ())
   {
      Log << Erreur << "Problème rencontré à l'initialisation du moteur" << EndLine;
      Done = 1;
   }

	//Boucle generale
	while(!Done)
	{
      bool bMotion = false;
		//On demarre le timer fps
      Fps.Start();

      // Gestion des demandes attentes
      Moteur.OnDemande ();

		//Traiter les evenements
		while(SDL_PollEvent(&Event) && (bMotion == false))
		{
   		Moteur.OnInputEvent (&Event);
		
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
               CoordonneeClic.mX = Event.button.x;
               CoordonneeClic.mY = Event.button.y;
					Moteur.OnClic(CoordonneeClic);
					break;
            case SDL_MOUSEMOTION:
               CoordonneeSouri.mX = Event.motion.x;
               CoordonneeSouri.mY = Event.motion.y;
               Moteur.OnMotion (CoordonneeSouri);
               bMotion = true;
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
