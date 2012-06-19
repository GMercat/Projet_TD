#ifndef _TOUR_H_
#define _TOUR_H_

#include "Defined.h"
#include "Projectile.h"
#include "Timer.h"

class CTour
{
public:
   CTour	   (TCoordonnee& aCoordCentre, int aTypeTour, int aPortee, int aPuissance, int aVitesse, int aCadence);
	~CTour	(void);

   void Construire ();

   void GetCentre (int& aXCentre, int &aYCentre);

   void OnAfficheProjectiles  (SDL_Surface* apSurfaceDest);
   bool OnAvanceProjectiles   (void);

   int GetTypeTour   (void);
   int GetPorteeTire (void);

   bool AutoriseATirer  (void);
   void Tire            (CEnnemiPtr& aEnnemiCiblePtr);

private:
   TCoordonnee mCoordCentre;
   
   int      mTypeTour;
   int      mPorteeTire;  // Portée de tire de la tour
   int      mCadenceTire; // Cadence de tire en seconde
   int      mVitesseProjectile;
   int      mPuissanceProjectile;
   CTimer   mTimer;       // Gestion de la cadence de tire de la tour

   std::list<CProjectilePtr>  mListeProjectilesTires; // Liste de projectiles tirés par la tour
};

typedef boost::shared_ptr<CTour> CTourPtr;

#endif
