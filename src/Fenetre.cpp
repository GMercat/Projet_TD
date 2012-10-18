#include "Fenetre.h"

CFenetre::CFenetre (void):
   mLog ("Fenetre")
{

}

CFenetre::~CFenetre (void)
{

}

bool CFenetre::Init (int aLargeur, int aHauteur)
{
   bool bReturn = true;

   //Initialisation de la SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		mLog << Erreur << "Probleme pour initialiser SDL: " << SDL_GetError() << EndLine;
		bReturn = false;
	}

   // Mettre un titre à la fenêtre
   SDL_WM_SetCaption("TowerDefense by Guit00n 0.2", NULL);

   //Ouvrir une fenetre
   mSurfacePtr.reset (new CSurface ());
   bReturn = mSurfacePtr->SetVideoMode (aLargeur, aHauteur);
   
   return bReturn;
}

void CFenetre::Flip (void)
{
   mSurfacePtr->Flip ();
}