#include "../include/Projectile.h"
#include <cmath>

CProjectile::CProjectile (CEnnemiPtr& aEnnemiCiblePtr, int aX, int aY, int aPuissance, int aVitesse) :
   mpImage           (NULL),
   mEnnemiCiblePtr   (aEnnemiCiblePtr),
   mPuissance        (aPuissance),
   mVitesse          (aVitesse)
{
   mCoordonnee.first  = aX;
   mCoordonnee.second = aY;

   mPosition.x = mCoordonnee.first;
   mPosition.y = mCoordonnee.second;
}

CProjectile::~CProjectile (void)
{
   SDL_FreeSurface (mpImage);
}

bool CProjectile::OnInit (void)
{
   bool bReturn = true;
   
   if(mpImage != NULL)
	{
		SDL_FreeSurface(mpImage), mpImage = NULL;
	}
	
	//On charge toutes les images dans les surfaces associées
	mpImage = SDL_LoadBMP ("../Ressources/Projectile.bmp");
	
   //On teste le retour du chargement
	if ((mpImage == NULL))
	{
		std::cout << "Probleme de chargement de l'image d'un projectile" << std::endl;
		bReturn = false;
	}
	
	//Mis en place de la transparence
	if(SDL_SetColorKey (mpImage, SDL_SRCCOLORKEY, SDL_MapRGB(mpImage->format, 255, 255, 255)) == -1)
		std::cout << "Erreur avec la transparence" << std::endl;
		
   mPosition.w = mpImage->w;
   mPosition.h = mpImage->h;

	return bReturn;
}

void CProjectile::OnAffiche (SDL_Surface* apScreen)
{
   SDL_BlitSurface (mpImage, NULL, apScreen, &mPosition);
}

bool CProjectile::Avance (void)
{
   std::cout << "CProjectile::Avance" << std::endl;
   /*
   std::cout << "X = " << mCoordonnee.first << std::endl;
   std::cout << "Y = " << mCoordonnee.second << std::endl;
   */
   bool bEstDetruit = false;
   
   // Si l'ennemi est pas encore détruit
   if (mEnnemiCiblePtr)
   {
      int      XEnnemi  = 0;
      int      YEnnemi  = 0;
   
      // Récupération de la position de l'ennemi
      mEnnemiCiblePtr->GetCentre (XEnnemi, YEnnemi);

      // Calcul de l'avancé du projectile
      double Avance = mVitesse * LARGEUR_CASE * ((double)BASE_VITESSE / 100.0);
   
      // Calcul de la distance restante à parcourir
      double DistanceRestante = sqrt ((double)((XEnnemi - mCoordonnee.first)  * (XEnnemi - mCoordonnee.first))
                                   +  (double)((YEnnemi - mCoordonnee.second) * (YEnnemi - mCoordonnee.second)));
   
      //std::cout << "DistanceRestante = " << DistanceRestante << std::endl;

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
      
         mPosition.x = mCoordonnee.first;
         mPosition.y = mCoordonnee.second;
      }
   }
   
   return bEstDetruit;
}
