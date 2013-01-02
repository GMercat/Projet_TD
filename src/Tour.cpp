#include "Tour.h"

CTour::CTour	(CConfiguration& aConfig, const TCoordonnee& aCoordCentre, int aTypeTour, int aPortee, int aPuissance, int aVitesse, int aCadence):
   mConfig              (aConfig),
   mCoordCentre         (aCoordCentre),
   mAngleTire           (0.0),
   mTypeTour            (aTypeTour),
   mPorteeTire          (aPortee),
   mPuissanceProjectile (aPuissance),
   mVitesseProjectile   (aVitesse),
   mCadenceTire         (aCadence)
{
   // TODO Config nom image

   std::string NomImageBase ("Tour_Base.bmp");
   std::string NomImageTourelle ("Tour_Tourelle.bmp");

   mImageBasePtr.reset (new CImage ());
   mImageTourellePtr.reset (new CImage ());
   mImageBasePtr->Load (NomImageBase);
   mImageTourellePtr->Load (NomImageTourelle);

   mImageTourellePtr->SetTransparence (255,0,0);
}

CTour::~CTour (void)
{
   ;
}

void CTour::Afficher (CSurface::Ptr& aEcranPtr)
{
   mImageBasePtr     ->AfficherParCentre (aEcranPtr, mCoordCentre);   
   mImageTourellePtr ->AfficherParCentre (aEcranPtr, mCoordCentre);
}

void CTour::GetCentre (TCoordonnee& aCoordonnee)
{
   aCoordonnee = mCoordCentre;
}

void CTour::OnAfficheProjectiles(CSurface::Ptr& aSurfaceDestPtr)
{
   // Affichage des projectiles lié à la tour
   CProjectile::Liste::iterator IterProjectile;
   for (IterProjectile = mListeProjectilesTires.begin (); IterProjectile != mListeProjectilesTires.end (); ++IterProjectile)
   {
      (*IterProjectile)->OnAffiche (aSurfaceDestPtr);
   }
}

bool CTour::OnAvanceProjectiles (void)
{
   bool bProjectileDetruit = false;
      
   CProjectile::Liste::iterator IterProjectile    = mListeProjectilesTires.begin ();
   CProjectile::Liste::iterator IterProjectileEnd = mListeProjectilesTires.end ();
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

void CTour::Vise (const TCoordonnee& aCoordoonneCible)
{
   if ((aCoordoonneCible.mX == 0) && (aCoordoonneCible.mY == 0))
   {
      ; // Rien à faire
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

void CTour::Tire (CEnnemi::Ptr& aEnnemiCiblePtr)
{
   // Création et ajout du projectile dans la liste des projectiles tirés
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
