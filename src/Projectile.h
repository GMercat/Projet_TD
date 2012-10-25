#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "Defined.h"
#include "Ennemi.h"
#include "Image.h"

class CProjectile
{
public:
   typedef boost::shared_ptr<CProjectile> Ptr;
   typedef std::list<CProjectile::Ptr>    Liste;

public:
   CProjectile   (CEnnemi::Ptr aEnnemiCiblePtr, TCoordonnee& aCoordonnee, int aPuissance, int aVitesse);
   ~CProjectile  (void);

   bool  OnInit      (std::string& aCheminRessource, std::string& aNomImage); 
   void  OnAffiche   (CSurface::Ptr& aScreenPtr);
   
   bool  Avance    (void);

private:
   CLog  mLog;
   int   mPuissance;
   int   mVitesse;

   TCoordonnee mCoordonnee;

   CEnnemi::Ptr mEnnemiCiblePtr; // Ennemi visé par le projectile
   
   CImage::Ptr    mImagePtr;
};

#endif
