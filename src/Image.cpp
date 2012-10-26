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

void CImage::Afficher (CSurface::Ptr& aEcranPtr, CRect::Ptr& aPositionPtr)
{
   Blit (aEcranPtr, aPositionPtr);
}

void CImage::Afficher (CSurface::Ptr& aEcranPtr, TCoordonnee& aCoordonnees)
{
   CRect::Ptr RectPtr (new CRect ());
   RectPtr->SetX (aCoordonnees.mX);
   RectPtr->SetY (aCoordonnees.mY);
   RectPtr->SetH (mpSurfaceSDLAffichable->h);
   RectPtr->SetW (mpSurfaceSDLAffichable->w);

   Afficher (aEcranPtr, RectPtr);
}

bool CImage::Load (std::string& aNomFichier)
{
   std::string Ressource;
   Ressource = mCheminRessources + aNomFichier;
   
   Free ();
   
   return LoadBMP (Ressource);
}
