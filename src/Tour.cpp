#include "../include/Tour.h"

CTour::CTour	(CConfiguration& aConfig, TCoordonnee& aCoordCentre, int aTypeTour, int aPortee, int aPuissance, int aVitesse, int aCadence):
   mConfig              (aConfig),
   mTypeTour            (aTypeTour),
   mPorteeTire          (aPortee),
   mPuissanceProjectile (aPuissance),
   mVitesseProjectile   (aVitesse),
   mCadenceTire         (aCadence)
{
   mCoordCentre.first   = aCoordCentre.first;
   mCoordCentre.second  = aCoordCentre.second;
}

CTour::~CTour (void)
{
   ;
}

void CTour::GetCentre (int& aXCentre, int &aYCentre)
{
   aXCentre = mCoordCentre.first;
   aYCentre = mCoordCentre.second;
}

void CTour::OnAfficheProjectiles(SDL_Surface* apSurfaceDest)
{
   // Affichage des projectiles lié à la tour
   std::list<CProjectilePtr>::iterator IterProjectile;
   for (IterProjectile = mListeProjectilesTires.begin (); IterProjectile != mListeProjectilesTires.end (); ++IterProjectile)
   {
      (*IterProjectile)->OnAffiche (apSurfaceDest);
   }
}

bool CTour::OnAvanceProjectiles (void)
{
   bool bProjectileDetruit = false;
      
   std::list<CProjectilePtr>::iterator IterProjectile    = mListeProjectilesTires.begin ();
   std::list<CProjectilePtr>::iterator IterProjectileEnd = mListeProjectilesTires.end ();
   while (IterProjectile != IterProjectileEnd)
   {
      bProjectileDetruit = (*IterProjectile)->Avance ();

      if (bProjectileDetruit)
      {
         IterProjectile = mListeProjectilesTires.erase (IterProjectile);
      }
      else
      {
         ++IterProjectile;
      }
   }
   
   return (false == mListeProjectilesTires.empty ());
}

int CTour::GetTypeTour (void)
{
   return mTypeTour;
}

int CTour::GetPorteeTire (void)
{
   return mPorteeTire;
}

bool CTour::AutoriseATirer (void)
{
   bool bAutorisation = true;

   int TickCourant = mTimer.GetNbTicks ();

   // Vérifie que le timer est lancé (que la tour a tirée)
   if (TickCourant != 0)
   {
      // Vérifie la possibilité de tirer
      if ((TickCourant) < (mCadenceTire * 1000))
      {
         bAutorisation = false;
      }
   }

   return bAutorisation;
}

void CTour::Tire (CEnnemiPtr& aEnnemiCiblePtr)
{
   // Création et ajout du projectile dans la liste des projectiles tirés
   CProjectilePtr ProjectileTirePtr (new CProjectile( aEnnemiCiblePtr,
                                                      mCoordCentre.first,
                                                      mCoordCentre.second,
                                                      mPuissanceProjectile,
                                                      mVitesseProjectile));
   std::string RessourceImage;
   std::string RessourceProjectile;

   bool LectureConfigOk  = mConfig.Get ("ressourcesImages",    RessourceImage);
   LectureConfigOk      &= mConfig.Get ("ressourceProjectile", RessourceProjectile);

   ProjectileTirePtr->OnInit (RessourceImage, RessourceProjectile);
   mListeProjectilesTires.push_back (ProjectileTirePtr);

   // Gestion de la cadence de tire de la tour
   mTimer.Start ();
}
