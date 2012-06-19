#include "../include/Image.h"

CImage::CImage (void) :
   mpSurface (NULL)
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
   
   std::string CheminRessource ("../ressources/");
   CheminRessource += aNomFichier;
   
   if(mpSurface != NULL)
   {
      SDL_FreeSurface(mpSurface), mpSurface = NULL;
   }
   
   mpSurface = SDL_LoadBMP(CheminRessource.c_str ());

   //On teste le retour du chargement
   if (mpSurface == NULL)
   {
	   std::cout << "Probleme de chargement de l'image : " << CheminRessource.c_str () << std::endl;
	   bResultat = false;
   }
   
   return bResultat;
}

void CImage::SetAlpha (int aValeurAlpha)
{
   SDL_SetAlpha (mpSurface, SDL_SRCALPHA, aValeurAlpha);
}

