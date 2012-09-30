#include "../include/Fenetre.h"

CFenetre::CFenetre (void)
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
   mpSurfaceSDL = SDL_SetVideoMode ( aLargeur , aHauteur , 32, SDL_DOUBLEBUF | SDL_HWSURFACE);

   if (mpSurfaceSDL == NULL)
   {
      bReturn = false;
   }

   return bReturn;
}

void CFenetre::Flip (void)
{
   mSurfacePtr->Flip ();
}