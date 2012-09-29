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
   CProjectile   (CEnnemi::Ptr aEnnemiCiblePtr, int aX, int aY, int aPuissance, int aVitesse);
   ~CProjectile  (void);

   bool  OnInit      (std::string& aCheminRessource, std::string& aNomImage); 
   void  OnAffiche   (SDL_Surface* apScreen);
   
   bool  Avance    (void);

private:
   CLog  mLog;
   int   mPuissance;
   int   mVitesse;

   TCoordonnee mCoordonnee;

   CEnnemi::Ptr mEnnemiCiblePtr; // Ennemi visé par le projectile
   
   CImage::Ptr      mImagePtr;
   SDL_Rect       mPosition;
};

#endif
