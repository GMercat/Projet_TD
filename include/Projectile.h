#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "Defined.h"
#include "Ennemi.h"

class CProjectile
{
public:
   CProjectile   (CEnnemiPtr aEnnemiCiblePtr, int aX, int aY, int aPuissance, int aVitesse);
   ~CProjectile  (void);

   bool  OnInit      (void); 
   void  OnAffiche   (SDL_Surface* apScreen);
   
   bool  Avance    (void);

private:
   CLog  mLog;
   int   mPuissance;
   int   mVitesse;

   TCoordonnee mCoordonnee;

   CEnnemiPtr mEnnemiCiblePtr; // Ennemi visé par le projectile
   
   SDL_Surface*  mpImage;
   SDL_Rect      mPosition;
};

typedef boost::shared_ptr<CProjectile> CProjectilePtr;

#endif
