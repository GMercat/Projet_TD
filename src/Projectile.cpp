#include "Projectile.h"
#include <cmath>

CProjectile::CProjectile (CEnnemi::Ptr aEnnemiCiblePtr, int aX, int aY, int aPuissance, int aVitesse) :
   mLog              ("Projectile"),
   mEnnemiCiblePtr   (aEnnemiCiblePtr),
   mPuissance        (aPuissance),
   mVitesse          (aVitesse)
{
   mCoordonnee.first  = aX;
   mCoordonnee.second = aY;
}

CProjectile::~CProjectile (void)
{

}

bool CProjectile::OnInit (std::string& aCheminRessource, std::string& aNomImage)
{
   bool bReturn = true;
   
   //On charge toutes les images dans les surfaces associées
   mImagePtr.reset (new CImage (aCheminRessource));
   bReturn = mImagePtr->Load (aNomImage);
	
   if (bReturn)
   {
	   //Mis en place de la transparence
      mImagePtr->SetTransparence (255, 255, 255);
   }
   else
   {
      mLog << Erreur << "Erreur lors du chargement de l'image d'un projectile " << aCheminRessource + aNomImage << EndLine;
   }
	return bReturn;
}

void CProjectile::OnAffiche (CSurface::Ptr& aScreenPtr)
{
   mImagePtr->Afficher (aScreenPtr, mCoordonnee);
}

bool CProjectile::Avance (void)
{
   bool bEstDetruit = false;
   
   // Si l'ennemi est pas encore détruit
   if (mEnnemiCiblePtr)
   {
      int      XEnnemi  = 0;
      int      YEnnemi  = 0;

      // Récupération de la position de l'ennemi
      mEnnemiCiblePtr->GetCentre (XEnnemi, YEnnemi);

      // Calcul de l'avancé du projectile
      double Avance = mVitesse;
   
      // Calcul de la distance restante à parcourir
      double DistanceRestante = sqrt ((double)((XEnnemi - mCoordonnee.first)  * (XEnnemi - mCoordonnee.first))
                                   +  (double)((YEnnemi - mCoordonnee.second) * (YEnnemi - mCoordonnee.second)));
   
      double PourcentageParcouru = Avance / DistanceRestante;
   
      if (Avance > DistanceRestante)
      {
         // L'ennemi est touché !
         mEnnemiCiblePtr->Touche (mPuissance);
         
         bEstDetruit = true;
      }
      else
      {
         // Le projectile avance
         mCoordonnee.first  += (int)((XEnnemi - mCoordonnee.first)  * PourcentageParcouru);
         mCoordonnee.second += (int)((YEnnemi - mCoordonnee.second) * PourcentageParcouru);
      }
   }
   else
   {
      bEstDetruit = true;
   }
   
   return bEstDetruit;
}
