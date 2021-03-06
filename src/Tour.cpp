#include "Tour.h"

CTour::CTour	(CConfiguration& aConfig, const TCoordonnee& aCoordCentre, int aTypeTour):
   mConfig              (aConfig),
   mCoordCentre         (aCoordCentre),
   mAngleTire           (0.0),
   mTypeTour            (aTypeTour)
{
   std::string CheminRessource;
   std::string NomImageBase;
   std::string NomImageTourelle;
   std::string NomImagePortee;

   bool bLectureConf  = mConfig.Get ("ressourcesImages", CheminRessource);
   bLectureConf      &= mConfig.GetCaracsTourParId (mTypeTour, NomImageBase, NomImageTourelle, NomImagePortee, mPorteeTire, mPuissanceProjectile, mVitesseProjectile, mCadenceTire);

   //On charge toutes les images dans les surfaces associ�es
   mImageBasePtr.reset (new CImage (CheminRessource));
   mImageBasePtr->Load (NomImageBase);
   mImageTourellePtr.reset (new CImage (CheminRessource));
   mImageTourellePtr->Load (NomImageTourelle);
   mImageTourellePtr->SetTransparence (255,0,0);
   mImagePorteePtr.reset (new CImage (CheminRessource));
   mImagePorteePtr->Load (NomImagePortee);
   mImagePorteePtr->SetAlpha    (128);
}

CTour::~CTour (void)
{
   ;
}

void CTour::Afficher (CSurface::Ptr& aEcranPtr, bool abEstSelectionnee)
{
   if (abEstSelectionnee)
   {
      AfficherPortee (aEcranPtr);
   }

   mImageBasePtr     ->AfficherParCentre (aEcranPtr, mCoordCentre);   
   mImageTourellePtr ->AfficherParCentre (aEcranPtr, mCoordCentre);
}

void CTour::AfficherPortee  (CSurface::Ptr& aEcranPtr)
{
   mImagePorteePtr->AfficherParCentre (aEcranPtr, mCoordCentre);
}

void CTour::GetCentre (TCoordonnee& aCoordonnee)
{
   aCoordonnee = mCoordCentre;
}

void CTour::OnAfficheProjectiles(CSurface::Ptr& aSurfaceDestPtr)
{
   // Affichage des projectiles li� � la tour
   CProjectile::Liste::iterator IterProjectile;
   for (IterProjectile = mListeProjectilesTires.begin (); IterProjectile != mListeProjectilesTires.end (); ++IterProjectile)
   {
      (*IterProjectile)->OnAffiche (aSurfaceDestPtr);
   }
}

// Cette m�thode permet de faire avancer les projectiles tir�s par la tour
// Retourne True si il rester des projectiles, False sinon.
bool CTour::OnAvanceProjectiles (void)
{
   bool bProjectileDetruit = false;
      
   CProjectile::Liste::iterator IterProjectile = mListeProjectilesTires.begin ();
   while (IterProjectile != mListeProjectilesTires.end ())
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

void CTour::Vise (const TCoordonnee& aCoordoonneCible)
{
   if ((aCoordoonneCible.mX == 0) && (aCoordoonneCible.mY == 0))
   {
      ; // Rien � faire
   }
   else if ((aCoordoonneCible.mX < mCoordCentre.mX) && (aCoordoonneCible.mY <= mCoordCentre.mY))
   {
      mAngleTire = (atan ((double)(mCoordCentre.mY - aCoordoonneCible.mY)/(double)(mCoordCentre.mX - aCoordoonneCible.mX))) * 180 / PI;
   }
   else if ((aCoordoonneCible.mX >= mCoordCentre.mX) && (aCoordoonneCible.mY < mCoordCentre.mY))
   {
      mAngleTire = 90 + (atan ((double)(aCoordoonneCible.mX - mCoordCentre.mX)/(double)(mCoordCentre.mY - aCoordoonneCible.mY))) * 180 / PI;
   }
   else if ((aCoordoonneCible.mX > mCoordCentre.mX) && (aCoordoonneCible.mY >= mCoordCentre.mY))
   {
      mAngleTire = 180 + (atan ((double)(aCoordoonneCible.mY - mCoordCentre.mY)/(double)(aCoordoonneCible.mX - mCoordCentre.mX))) * 180 / PI;
   }
   else if ((aCoordoonneCible.mX <= mCoordCentre.mX) && (aCoordoonneCible.mY > mCoordCentre.mY))
   {
      mAngleTire = 270 + (atan ((double)(mCoordCentre.mX - aCoordoonneCible.mX)/(double)(aCoordoonneCible.mY - mCoordCentre.mY))) * 180 / PI;
   }

   mImageTourellePtr->Rotation (mAngleTire);
}
   
bool CTour::AutoriseATirer (void)
{
   bool bAutorisation = true;

   int TickCourant = mTimer.GetNbTicks ();

   // V�rifie que le timer est lanc� (que la tour a tir�e)
   if (TickCourant != 0)
   {
      // V�rifie la possibilit� de tirer
      if ((TickCourant) < (mCadenceTire * 1000))
      {
         bAutorisation = false;
      }
   }

   return bAutorisation;
}

void CTour::Tire (CEnnemi::Ptr& aEnnemiCiblePtr)
{
   // Cr�ation et ajout du projectile dans la liste des projectiles tir�s
   CProjectile::Ptr ProjectileTirePtr (new CProjectile(  aEnnemiCiblePtr,
                                                         mCoordCentre,
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
