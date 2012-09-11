#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "Defined.h"
#include "Ennemi.h"
#include "Image.h"

class CProjectile
{
public:
   CProjectile   (CEnnemiPtr aEnnemiCiblePtr, int aX, int aY, int aPuissance, int aVitesse);
   ~CProjectile  (void);

   bool  OnInit      (std::string& aCheminRessource, std::string& aNomImage); 
   void  OnAffiche   (SDL_Surface* apScreen);
   
   bool  Avance    (void);

private:
   CLog  mLog;
   int   mPuissance;
   int   mVitesse;

   TCoordonnee mCoordonnee;

   CEnnemiPtr mEnnemiCiblePtr; // Ennemi visé par le projectile
   
   CImagePtr      mImagePtr;
   SDL_Rect       mPosition;
};

typedef boost::shared_ptr<CProjectile> CProjectilePtr;

#endif
