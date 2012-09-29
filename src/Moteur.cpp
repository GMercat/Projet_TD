#include "../include/Moteur.h"

CMoteur::CMoteur (void):
   mLog     ("Moteur"),
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

   if (bReturn)
   {
      mIA.OnInit ();

      //Initialisation de la SDL
	   if (SDL_Init(SDL_INIT_VIDEO) != 0)
	   {
		   mLog << Erreur << "Probleme pour initialiser SDL: " << SDL_GetError() << EndLine;
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
   }

	return bReturn;
}

void CMoteur::OnQuit (void)
{
	SDL_Quit();
}

void CMoteur::OnClic (int aX, int aY)
{
   mJeu.OnClic (aX, aY);
}

void CMoteur::OnMotion (int aX, int aY)
{
   // Si on survole le plateau et si une tour est sélectionnée
   if (mJeu.GetPlateau ().EstDansPlateau (aX, aY) && (mJeu.GetTourSelectionnee () != -1))
   {
      mJeu.GetPlateau ().OnSurvoleCase (aX, aY);
   }
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
