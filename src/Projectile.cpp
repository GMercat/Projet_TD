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

void CProjectile::OnAffiche (SDL_Surface* apScreen)
{
   //SDL_BlitSurface (mpImage,NULL,apScreen,&mPosition);
}

void CProjectile::Avance (void)
{
   // Si l'ennemi est pas encore détruit
   if (mEnnemiCiblePtr)
   {
      bool bEnnemiVivant = true;

      int      XEnnemi  = 0;
      int      YEnnemi  = 0;
   
      // Récupération de la position de l'ennemi
      mEnnemiCiblePtr->GetCentre (XEnnemi, YEnnemi);

      // Calcul de l'avancé du projectile
      double Avance = mVitesse * LARGEUR_CASE * ((double)BASE_VITESSE / 100.0);
   
      // Calcul de la distance restante à parcourir
      double DistanceRestante = sqrt ((double)((XEnnemi - mCoordonnee.first)  * (XEnnemi - mCoordonnee.first))
                                   +  (double)((YEnnemi - mCoordonnee.second) * (YEnnemi - mCoordonnee.second)));
   
      double PourcentageParcouru = Avance / DistanceRestante;
   
      if (Avance > DistanceRestante)
      {
         // L'ennemi est touché !
         bEnnemiVivant = mEnnemiCiblePtr->Touche (mPuissance);

         if (bEnnemiVivant)
         {
 
         }
         else
         {
         
         }
      }
      else
      {
         // Le projectile avance
         mCoordonnee.first  += (int)((XEnnemi - mCoordonnee.first)  * PourcentageParcouru);
         mCoordonnee.second += (int)((YEnnemi - mCoordonnee.second) * PourcentageParcouru);
      }
   }
}
