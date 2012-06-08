#include "../include/Moteur.h"

CMoteur::CMoteur (void):
   mIA      (mJeu.GetPlateau ()),
   mJeu     (&mIA),
   mpScreen (NULL)
{
	;
}

CMoteur::~CMoteur (void)
{
	;
}

bool CMoteur::OnInit (void)
{
	bool bReturn = false;
   
	bReturn  = mJeu.OnInit ();
   mIA.OnInit ();

   //Initialisation de la SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Probleme pour initialiser SDL: " << SDL_GetError() << std::endl;
		bReturn = false;
	}

   // Mettre un titre à la fenêtre
   SDL_WM_SetCaption("TowerDefense by Guit00n 0.2", NULL);

   //Ouvrir une fenetre
   mpScreen = SDL_SetVideoMode ( mJeu.GetLargeur (),
                                 mJeu.GetHauteur (),
                                 32,
                                 SDL_DOUBLEBUF | SDL_HWSURFACE);
   if (mpScreen == NULL)
   {
      bReturn = false;
   }

   mIA.ConstruireMatriceGraphe ();
   mJeu.PlacementEstAutorise ();

	return bReturn;
}

void CMoteur::OnQuit (void)
{
	SDL_Quit();
}

void CMoteur::OnClic (int aX, int aY)
{
   bool bAutorisePlacementTour = false;

#ifdef DEBUG
	std::cout << "Moteur.OnClic (" << aX << ", " << aY << ")" << std::endl;
#endif
	
   /*int NumCase = */mJeu.OnClic (aX, aY);

/*
   if (NumCase != -1)
   {
      mIA.MiseAJourMatriceGraphe (NumCase, true);

      // Vérification de la possibilité de poser la tour en parcourant les listes des ennemis
      bAutorisePlacementTour = mJeu.PlacementEstAutorise ();

      if (bAutorisePlacementTour)
      {
         mJeu.AjoutTour (NumCase);
      }
      else
      {
         std::cout << "Placement non autorisé" << std::endl;
         mJeu.AnnuleDerniereModif ();
         mIA.MiseAJourMatriceGraphe (NumCase, false);
      }
   }
*/
}

void CMoteur::OnProgression   (void)
{
   if (mJeu.PartieEnCours ())
   {
      mJeu.OnProgression ();
   }
}

void CMoteur::OnTire (void)
{
   if (mJeu.PartieEnCours ())
   {
      mJeu.OnTire ();
   }
}

void CMoteur::OnAffiche (void)
{
	mJeu.OnAffiche (mpScreen);
   SDL_Flip(mpScreen);
}

void CMoteur::handle_input(SDL_Event* apEvent)
{
	// Capture d'un appuis clavier
}
