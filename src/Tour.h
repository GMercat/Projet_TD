#ifndef _TOUR_H_
#define _TOUR_H_

#include "Defined.h"
#include "Projectile.h"
#include "Timer.h"
#include "Image.h"
#include "Config.h"

class CTour
{
public:
   typedef boost::shared_ptr<CTour> Ptr;
   typedef std::list<CTour::Ptr>    Liste;

public:
   CTour	   (CConfiguration& aConfig, const TCoordonnee& aCoordCentre, int aTypeTour);
	~CTour	(void);

   void Afficher (CSurface::Ptr& aEcranPtr, bool abEstSelectionnee);

   void GetCentre (TCoordonnee& aCoordonnee);

   void OnAfficheProjectiles  (CSurface::Ptr& aSurfaceDestPtr);
   bool OnAvanceProjectiles   (void);

   int GetTypeTour   (void);
   int GetPorteeTire (void);

   void Vise            (const TCoordonnee& aCoordoonneCible);
   bool AutoriseATirer  (void);
   void Tire            (CEnnemi::Ptr& aEnnemiCiblePtr);

private:
   CConfiguration& mConfig;

   TCoordonnee mCoordCentre;
   double      mAngleTire;
   
   int      mTypeTour;
   int      mPorteeTire;  // Portée de tire de la tour
   int      mCadenceTire; // Cadence de tire en seconde
   int      mVitesseProjectile;
   int      mPuissanceProjectile;
   CTimer   mTimer;       // Gestion de la cadence de tire de la tour

   CImage::Ptr mImageBasePtr;
   CImage::Ptr mImageTourellePtr;

   CProjectile::Liste  mListeProjectilesTires; // Liste de projectiles tirés par la tour
};

#endif
