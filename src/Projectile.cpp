#include "../include/Projectile.h"

CProjectile::CProjectile (CEnnemiPtr& aEnnemiCiblePtr, int aPuissance, int aVitesse) :
   mEnnemiCiblePtr   (aEnnemiCiblePtr),
   mPuissance        (aPuissance),
   mVitesse          (aVitesse)
{

}

CProjectile::~CProjectile (void)
{

}

void  OnAffiche (SDL_Surface* apScreen)
{
   //SDL_BlitSurface (mpImage,NULL,apScreen,&mPosition);
}