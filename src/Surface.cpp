#include "Surface.h"
#include <SDL/SDL_rotozoom.h>

CSurface::CSurface (bool abEstFenetre):
   mLog                    ("Surface"),
   mbEstFenetre            (abEstFenetre),
   mpSurfaceSDLOrigine     (NULL),
   mpSurfaceSDLAffichable  (NULL)
{

}

CSurface::~CSurface (void)
{
   if (false == mbEstFenetre)
   {
      Free ();
   }
}

void CSurface::Blit (CSurface::Ptr& apEcran, CRect::Ptr& aPositionDestPtr)
{
   SDL_BlitSurface (mpSurfaceSDLAffichable, NULL, apEcran->mpSurfaceSDLAffichable, aPositionDestPtr->GetSDLRect ());
}

void CSurface::SetAlpha (int aValeurAlpha)
{
   SDL_SetAlpha (mpSurfaceSDLAffichable, SDL_SRCALPHA, aValeurAlpha);
}

bool CSurface::LoadBMP (std::string aNom)
{
   bool bResultat = true;

   mpSurfaceSDLOrigine = SDL_LoadBMP(aNom.c_str ());
   
   mpSurfaceSDLAffichable = SDL_CreateRGBSurface(  SDL_HWSURFACE,
                                                   mpSurfaceSDLOrigine->w,
                                                   mpSurfaceSDLOrigine->h,
                                                   mpSurfaceSDLOrigine->format->BitsPerPixel,
                                                   mpSurfaceSDLOrigine->format->Rmask,
                                                   mpSurfaceSDLOrigine->format->Gmask,
                                                   mpSurfaceSDLOrigine->format->Bmask,
                                                   mpSurfaceSDLOrigine->format->Amask);

   SDL_BlitSurface (mpSurfaceSDLOrigine, NULL, mpSurfaceSDLAffichable, NULL);

   if(mpSurfaceSDLOrigine == NULL || mpSurfaceSDLAffichable == NULL)
   {
	   mLog << Erreur << "Probleme de chargement de l'image : " << aNom.c_str () << EndLine;
	   bResultat = false;
   }

   return bResultat;
}

void CSurface::SetTransparence (int aValeurRouge, int aValeurVert, int aValeurBleu)
{
   if(   (SDL_SetColorKey (mpSurfaceSDLOrigine, SDL_SRCCOLORKEY, SDL_MapRGB(mpSurfaceSDLOrigine->format, aValeurRouge, aValeurVert, aValeurBleu)) == -1)
      || (SDL_SetColorKey (mpSurfaceSDLAffichable, SDL_SRCCOLORKEY, SDL_MapRGB(mpSurfaceSDLAffichable->format, aValeurRouge, aValeurVert, aValeurBleu)) == -1))
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

void CSurface::Fill (int aValeurRouge, int aValeurVert, int aValeurBleu)
{
   SDL_FillRect(mpSurfaceSDLAffichable, NULL, SDL_MapRGB(mpSurfaceSDLAffichable->format, aValeurRouge, aValeurVert, aValeurBleu));
}
