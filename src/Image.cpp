#include "../include/Image.h"

CImage::CImage (void) :
   mLog              ("Image"),
   mpSurface         (NULL),
   mCheminRessources ("")
{

}

CImage::CImage (std::string& aCheminRessources) :
   mLog              ("Image"),
   mpSurface         (NULL),
   mCheminRessources (aCheminRessources)
{
   ;
}

CImage::~CImage (void)
{
   if (mpSurface != NULL)
   {
      SDL_FreeSurface (mpSurface);
   }
}

void CImage::Afficher (SDL_Surface* apEcran, SDL_Rect& aPosition)
{
   SDL_BlitSurface(mpSurface, NULL, apEcran, &aPosition);
}

bool CImage::Load (std::string& aNomFichier)
{
   bool bResultat = true;
   
   std::string Ressource;
   Ressource = mCheminRessources + aNomFichier;
   
   if(mpSurface != NULL)
   {
      SDL_FreeSurface(mpSurface), mpSurface = NULL;
   }
   
   mpSurface = SDL_LoadBMP(Ressource.c_str ());

   //On teste le retour du chargement
   if (mpSurface == NULL)
   {
	   mLog << Erreur << "Probleme de chargement de l'image : " << Ressource.c_str () << EndLine;
	   bResultat = false;
   }
   
   return bResultat;
}

void CImage::SetAlpha (int aValeurAlpha)
{
   SDL_SetAlpha (mpSurface, SDL_SRCALPHA, aValeurAlpha);
}

void CImage::SetTransparence (void)
{
	if(SDL_SetColorKey (mpSurface, SDL_SRCCOLORKEY, SDL_MapRGB(mpSurface->format, 255, 255, 255)) == -1)
   {
		mLog << Erreur << "Erreur avec la transparence" << EndLine;
   }
}