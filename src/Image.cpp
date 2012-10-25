#include "Image.h"

CImage::CImage (void) :
   mCheminRessources ("")
{

}

CImage::CImage (std::string& aCheminRessources) :
   mCheminRessources (aCheminRessources)
{
   ;
}

CImage::~CImage (void)
{
}

void CImage::Afficher (CSurface::Ptr& aEcranPtr, SDL_Rect& aPosition)
{
   Blit (aEcranPtr, &aPosition);
}

void CImage::Afficher (CSurface::Ptr& aEcranPtr, TCoordonnee& aCoordonnees)
{
   SDL_Rect Rect;
   Rect.x = aCoordonnees.mX;
   Rect.y = aCoordonnees.mY;
   Rect.h = mpSurfaceSDLAffichable->h;
   Rect.w = mpSurfaceSDLAffichable->w;

   Afficher (aEcranPtr, Rect);
}

bool CImage::Load (std::string& aNomFichier)
{
   std::string Ressource;
   Ressource = mCheminRessources + aNomFichier;
   
   Free ();
   
   return LoadBMP (Ressource);
}
