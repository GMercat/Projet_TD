#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "Defined.h"
#include "Ennemi.h"

class CProjectile
{
public:
   CProjectile   (CEnnemiPtr& aEnnemiCiblePtr, int aPuissance, int aVitesse);
   ~CProjectile  (void);

   void  OnAffiche   (SDL_Surface* apScreen);
   
   void  Avance    (void);

private:
   int   mPuissance;
   int   mVitesse;

   TCoordonnee mCoordonnee;

   CEnnemiPtr& mEnnemiCiblePtr; // Ennemi visé par le projectile
};

typedef boost::shared_ptr<CProjectile> CProjectilePtr;

#endif