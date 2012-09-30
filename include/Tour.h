#ifndef _TOUR_H_
#define _TOUR_H_

#include "Defined.h"
#include "Projectile.h"
#include "Timer.h"
#include "Config.h"

class CTour
{
public:
   typedef boost::shared_ptr<CTour> Ptr;
   typedef std::list<CTour::Ptr>    Liste;

public:
   CTour	   (CConfiguration& aConfig, TCoordonnee& aCoordCentre, int aTypeTour, int aPortee, int aPuissance, int aVitesse, int aCadence);
	~CTour	(void);

   void Construire ();

   void GetCentre (int& aXCentre, int &aYCentre);

   void OnAfficheProjectiles  (CSurface::Ptr& aSurfaceDestPtr);
   bool OnAvanceProjectiles   (void);

   int GetTypeTour   (void);
   int GetPorteeTire (void);

   bool AutoriseATirer  (void);
   void Tire            (CEnnemi::Ptr& aEnnemiCiblePtr);

private:
   CConfiguration& mConfig;

   TCoordonnee mCoordCentre;
   
   int      mTypeTour;
   int      mPorteeTire;  // Portée de tire de la tour
   int      mCadenceTire; // Cadence de tire en seconde
   int      mVitesseProjectile;
   int      mPuissanceProjectile;
   CTimer   mTimer;       // Gestion de la cadence de tire de la tour

   CProjectile::Liste  mListeProjectilesTires; // Liste de projectiles tirés par la tour
};

#endif
