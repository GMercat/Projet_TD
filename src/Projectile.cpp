#include "Projectile.h"
#include <cmath>

CProjectile::CProjectile (CEnnemi::Ptr aEnnemiCiblePtr, TCoordonnee& aCoordonnee, int aPuissance, int aVitesse) :
   mLog              ("Projectile"),
   mPuissance        (aPuissance),
   mVitesse          (aVitesse),
   mCoordonnee       (aCoordonnee),
   mEnnemiCiblePtr   (aEnnemiCiblePtr)
{
   ;
}

CProjectile::~CProjectile (void)
{
   ;
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
   bool bADetruire = false;
   
   // Si l'ennemi est pas encore détruit
   if (mEnnemiCiblePtr)
   {
      TCoordonnee CoordonneeEnnemi;

      // Récupération de la position de l'ennemi
      mEnnemiCiblePtr->GetCentre (CoordonneeEnnemi);
      
      // Calcul de l'avancé du projectile
      double Avance = mVitesse;
   
      // Calcul de la distance restante à parcourir
      double DistanceRestante = sqrt ((double)((CoordonneeEnnemi.mX - mCoordonnee.mX) * (CoordonneeEnnemi.mX - mCoordonnee.mX))
                                   +  (double)((CoordonneeEnnemi.mY - mCoordonnee.mY) * (CoordonneeEnnemi.mY - mCoordonnee.mY)));
   
      double PourcentageParcouru = Avance / DistanceRestante;
      
      if (Avance > DistanceRestante)
      {
         // L'ennemi est touché !
         mEnnemiCiblePtr->Touche (mPuissance);
         
         bADetruire = true;
      }
      else
      {
         // Le projectile avance
         mCoordonnee.mX += (int)((CoordonneeEnnemi.mX - mCoordonnee.mX) * PourcentageParcouru);
         mCoordonnee.mY += (int)((CoordonneeEnnemi.mY - mCoordonnee.mY) * PourcentageParcouru);
      }
   }
   else
   {
      bADetruire = true;
   }
   
   return bADetruire;
}
