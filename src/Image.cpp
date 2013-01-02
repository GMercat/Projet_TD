#include "Image.h"

CImage::CImage (void) :
   mCheminRessources ("")
{
   ;
}

CImage::CImage (std::string& aCheminRessources) :
   mCheminRessources (aCheminRessources)
{
   ;
}

CImage::~CImage (void)
{
}

void CImage::Afficher (CSurface::Ptr& aEcranPtr)
{
   CRect::Ptr RectPtr (new CRect ());
   RectPtr->SetX (mCoordonneesCentre.mX - mpSurfaceSDLAffichable->w / 2);
   RectPtr->SetY (mCoordonneesCentre.mY - mpSurfaceSDLAffichable->h / 2);
   RectPtr->SetH (mpSurfaceSDLAffichable->h);
   RectPtr->SetW (mpSurfaceSDLAffichable->w);

   Blit (aEcranPtr, RectPtr);
}

void CImage::Afficher (CSurface::Ptr& aEcranPtr, CRect::Ptr& aPositionPtr)
{
   // Mise à jour de la position du centre de l'image
   mCoordonneesCentre.mX = aPositionPtr->GetX () + mpSurfaceSDLAffichable->w / 2;
   mCoordonneesCentre.mY = aPositionPtr->GetY () + mpSurfaceSDLAffichable->h / 2;

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

void CImage::AfficherParCentre (CSurface::Ptr& aEcranPtr, TCoordonnee& aCoordonneesCentre)
{
   CRect::Ptr RectPtr (new CRect ());
   RectPtr->SetX (aCoordonneesCentre.mX - mpSurfaceSDLAffichable->w / 2);
   RectPtr->SetY (aCoordonneesCentre.mY - mpSurfaceSDLAffichable->h / 2);
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
