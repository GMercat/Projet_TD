#include "../include/Projectile.h"

CProjectile::CProjectile (ETypeProjectile aeType) :
   meType (aeType)
{
   switch (meType)
   {
      case eProjectile1 :
         mPuissance  = 1;
         mVitesse    = 2;
         break;
         
      case eProjectile2 :
         mPuissance  = 2;
         mVitesse    = 4;
         break;
         
      case eProjectile3 :
         mPuissance  = 3;
         mVitesse    = 6;
         break;
      
      case eProjectile4 :
         mPuissance  = 4;
         mVitesse    = 8;
         break;

      case eProjectile5 :
         mPuissance  = 5;
         mVitesse    = 10;
         break;

      case eProjectile6 :
         mPuissance  = 6;
         mVitesse    = 12;
         break;

      default:
         std::cout << "Projectile : Type inconnu" << std::cout;
         break;
   }
}

CProjectile::~CProjectile (void)
{

}
