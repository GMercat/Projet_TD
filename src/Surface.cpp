#include "Surface.h"

CSurface::CSurface (void):
   mLog                    ("Surface"),
   mpSurfaceSDLOrigine     (NULL),
   mpSurfaceSDLAffichable  (NULL)
{

}

CSurface::~CSurface (void)
{
   Free ();
}

void CSurface::Blit (CSurface::Ptr& apEcran, SDL_Rect* aPositionDest)
{
   SDL_BlitSurface(mpSurfaceSDLAffichable, NULL, apEcran->mpSurfaceSDLAffichable, aPositionDest);
}

void CSurface::SetAlpha (int aValeurAlpha)
{
   SDL_SetAlpha (mpSurfaceSDLAffichable, SDL_SRCALPHA, aValeurAlpha);
}

bool CSurface::LoadBMP (std::string aNom)
{
   bool bResultat = true;

   mpSurfaceSDLOrigine = SDL_LoadBMP(aNom.c_str ());
   mpSurfaceSDLAffichable = mpSurfaceSDLOrigine;

   //On teste le retour du chargement
   if (mpSurfaceSDLAffichable == NULL)
   {
	   mLog << Erreur << "Probleme de chargement de l'image : " << aNom.c_str () << EndLine;
	   bResultat = false;
   }

   return bResultat;
}

void CSurface::SetTransparence (int aValeurRouge, int aValeurVert, int aValeurBleu)
{
	if(SDL_SetColorKey (mpSurfaceSDLAffichable, SDL_SRCCOLORKEY, SDL_MapRGB(mpSurfaceSDLAffichable->format, aValeurRouge, aValeurVert, aValeurBleu)) == -1)
   {
		mLog << Erreur << "Erreur avec la transparence" << EndLine;
   }
}

void CSurface::Flip (void)
{
   SDL_Flip(mpSurfaceSDLAffichable);
}

void CSurface::Free (void)
{
   if (mpSurfaceSDLAffichable != NULL)
   {
      SDL_FreeSurface (mpSurfaceSDLAffichable);
   }

   if (mpSurfaceSDLOrigine != NULL)
   {
      SDL_FreeSurface (mpSurfaceSDLOrigine);
   }
}

bool CSurface::SetVideoMode (const int aLargeur, const int aHauteur)
{
   bool bReturn = true;

   mpSurfaceSDLAffichable = SDL_SetVideoMode ( aLargeur , aHauteur , 32, SDL_DOUBLEBUF | SDL_HWSURFACE);

   if (mpSurfaceSDLAffichable == NULL)
   {
      bReturn = false;
   }

   return bReturn;
}

void CSurface::Rotation (double aAngleDegre)
{
	mpSurfaceSDLAffichable = rotozoomSurface(mpSurfaceSDLOrigine, -aAngleDegre, 1.0, 1);
}
