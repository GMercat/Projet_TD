#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "Defined.h"

class CProjectile
{
public:
 	enum ETypeProjectile {
      eProjectile1 = 0,
      eProjectile2,
      eProjectile3,
      eProjectile4,
      eProjectile5,
      eProjectile6,
      eNbType
	};

public:
   CProjectile   (ETypeProjectile aeType);
   ~CProjectile  (void);

private:
   ETypeProjectile meType;

   int   mPuissance;
   int   mVitesse;
};

typedef boost::shared_ptr<CProjectile> CProjectilePtr;

#endif