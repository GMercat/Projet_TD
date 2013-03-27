#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Defined.h"
#include "Surface.h"
#include "Rect.h"

class CImage : public CSurface
{
public:
   typedef std::shared_ptr<CImage> Ptr;
   typedef std::vector<CImage::Ptr>  Vecteur;

public:
   CImage (void);
   CImage (std::string& aCheminRessources);
   virtual ~CImage (void);

   void  Afficher (CSurface::Ptr& aEcranPtr);
   void  Afficher (CSurface::Ptr& aEcranPtr, CRect::Ptr& aPositionPtr);
   void  Afficher (CSurface::Ptr& aEcranPtr, TCoordonnee& aCoordonnees);
   void  AfficherParCentre (CSurface::Ptr& aEcranPtr, TCoordonnee& aCoordonneesCentre);
   bool  Load     (std::string& aNomFichier);
   
private:
   std::string    mCheminRessources;

   TCoordonnee mCoordonneesCentre;
};

#endif
