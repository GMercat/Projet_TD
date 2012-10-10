#include "../include/Surface.h"

CSurface::CSurface (void):
   mLog           ("Surface"),
   mpSurfaceSDL   (NULL)
{

}

CSurface::~CSurface (void)
{
   Free ();
}

void CSurface::Blit (CSurface::Ptr& apEcran, SDL_Rect* aPositionDest)
{
   SDL_BlitSurface(mpSurfaceSDL, NULL, apEcran->mpSurfaceSDL, aPositionDest);
}

void CSurface::SetAlpha (int aValeurAlpha)
{
   SDL_SetAlpha (mpSurfaceSDL, SDL_SRCALPHA, aValeurAlpha);
}

bool CSurface::LoadBMP (std::string aNom)
{
   bool bResultat = true;

   mpSurfaceSDL = SDL_LoadBMP(aNom.c_str ());

   //On teste le retour du chargement
   if (mpSurfaceSDL == NULL)
   {
	   mLog << Erreur << "Probleme de chargement de l'image : " << aNom.c_str () << EndLine;
	   bResultat = false;
   }

   return bResultat;
}

void CSurface::SetTransparence (int aValeurRouge, int aValeurVert, int aValeurBleu)
{
	if(SDL_SetColorKey (mpSurfaceSDL, SDL_SRCCOLORKEY, SDL_MapRGB(mpSurfaceSDL->format, aValeurRouge, aValeurVert, aValeurBleu)) == -1)
   {
		mLog << Erreur << "Erreur avec la transparence" << EndLine;
   }
}

void CSurface::Flip (void)
{
   SDL_Flip(mpSurfaceSDL);
}

void CSurface::Free (void)
{
   if (mpSurfaceSDL != NULL)
   {
      SDL_FreeSurface (mpSurfaceSDL);
   }
}

bool CSurface::SetVideoMode (const int aLargeur, const int aHauteur)
{
   bool bReturn = true;

   mpSurfaceSDL = SDL_SetVideoMode ( aLargeur , aHauteur , 32, SDL_DOUBLEBUF | SDL_HWSURFACE);

   if (mpSurfaceSDL == NULL)
   {
      bReturn = false;
   }

   return bReturn;
}
