#include "../include/Projectile.h"
#include <cmath>

CProjectile::CProjectile (CEnnemiPtr aEnnemiCiblePtr, int aX, int aY, int aPuissance, int aVitesse) :
   mLog              ("Projectile"),
   mpImage           (NULL),
   mEnnemiCiblePtr   (aEnnemiCiblePtr),
   mPuissance        (aPuissance),
   mVitesse          (aVitesse)
{
   mCoordonnee.first  = aX;
   mCoordonnee.second = aY;
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
	
	//On charge toutes les images dans les surfaces associ�es
	mpImage = SDL_LoadBMP ("../../ressources/Projectile.bmp");
	
   //On teste le retour du chargement
	if ((mpImage == NULL))
	{
		mLog << Erreur << "Probleme de chargement de l'image d'un projectile" << EndLine;
		bReturn = false;
	}
	
	//Mis en place de la transparence
	if(SDL_SetColorKey (mpImage, SDL_SRCCOLORKEY, SDL_MapRGB(mpImage->format, 255, 255, 255)) == -1)
		mLog << Erreur << "Erreur avec la transparence" << EndLine;

   mPosition.x = mCoordonnee.first;
   mPosition.y = mCoordonnee.second;
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
   bool bEstDetruit = false;
   
   // Si l'ennemi est pas encore d�truit
   if (mEnnemiCiblePtr)
   {
      int      XEnnemi  = 0;
      int      YEnnemi  = 0;

      // R�cup�ration de la position de l'ennemi
      mEnnemiCiblePtr->GetCentre (XEnnemi, YEnnemi);

      // Calcul de l'avanc� du projectile
      double Avance = mVitesse;
   
      // Calcul de la distance restante � parcourir
      double DistanceRestante = sqrt ((double)((XEnnemi - mCoordonnee.first)  * (XEnnemi - mCoordonnee.first))
                                   +  (double)((YEnnemi - mCoordonnee.second) * (YEnnemi - mCoordonnee.second)));
   
      double PourcentageParcouru = Avance / DistanceRestante;
   
      if (Avance > DistanceRestante)
      {
         // L'ennemi est touch� !
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
   else
   {
      bEstDetruit = true;
   }
   
   return bEstDetruit;
}
