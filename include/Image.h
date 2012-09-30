#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Defined.h"
#include "Surface.h"

class CImage : public CSurface
{
public:
   typedef boost::shared_ptr<CImage> Ptr;

public:
   CImage (void);
   CImage (std::string& aCheminRessources);
   virtual ~CImage (void);
      
   void  Afficher (CSurface::Ptr& aEcranPtr, SDL_Rect& aPosition);
   void  Afficher (CSurface::Ptr& aEcranPtr, TCoordonnee& aCoordonnees);
   bool  Load     (std::string& aNomFichier);
   
private:
   std::string    mCheminRessources;
};

#endif
