#include "../include/Case.h"

CCase::CCase (void):
	mIdPlateauX          (-1),
	mIdPlateauY          (-1),
	mEtat		            (eVide),
	mCourImage	         (0),
   mNumCase             (-1),
   mbEstPlusCourtChemin (false),
   mPorteeTire          (1),
   mCadenceTire         (0)
{
	mPosition.x = 0;
	mPosition.y = 0;
	mPosition.w = 0;
}

CCase::~CCase (void)
{
	;
}

void CCase::OnInit (void)
{
	mCourImage = 0;
	mEtat = eVide;
}

void CCase::OnAffiche (SDL_Surface* apSurfaceDest, SDL_Surface* apSurfaceCase)
{   
	SDL_BlitSurface(apSurfaceCase,NULL,apSurfaceDest,&mPosition);

   // Affichage des projectiles li� � la tour
   std::list<CProjectilePtr>::iterator IterProjectile;
   for (IterProjectile = mListeProjectilesTires.begin (); IterProjectile != mListeProjectilesTires.end (); ++IterProjectile)
   {
      (*IterProjectile)->OnAffiche (apSurfaceDest);
   }
}

bool CCase::OnAvanceProjectiles (void)
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

bool CCase::EstDedans (int aX, int aY)
{
	bool bReturn = true;

	bReturn  = (aX > mPosition.x);
	bReturn &= (aX < (mPosition.x + mPosition.w));
	bReturn &= (aY > mPosition.y);
	bReturn &= (aY < (mPosition.y + mPosition.h));
	
	return bReturn;
}

bool CCase::EstVide (void)
{
   return (mEtat == eVide);
}

const CCase::ETypeCase	CCase::GetEtat (void) const
{
	return mEtat;
}

void CCase::SetEtat (CCase::ETypeCase aeNouvelEtat)
{
	switch (aeNouvelEtat)
	{
		case eVide:
		case eMur:
      case eTour1:
         mPorteeTire  = 100;
         mCadenceTire = 1;
      case eTour2:
         mPorteeTire  = 150;
         mCadenceTire = 2;
      case eTour3:
      case eTour4:
      case eTour5:
      case eTour6:
			mEtat = aeNouvelEtat;
			mCourImage = aeNouvelEtat;
			break;

		default:
			break;
	}
}

void CCase::SetPosition (SDL_Rect* apRect, int aIdPlateauX, int aIdPlateauY)
{ 
	mIdPlateauX = aIdPlateauX;
	mIdPlateauY = aIdPlateauY;
	mPosition = *apRect;
}

void  CCase::SetNumCase (int aNumCase)
{
   mNumCase = aNumCase;
}

int CCase::GetNumCase (void)
{
   return mNumCase;
}

int CCase::GetPorteeTire  (void)
{
   return mPorteeTire;
}

void CCase::GetCentre (int& aXCentre, int &aYCentre)
{
   aXCentre = mPosition.x + (mPosition.w / 2);
   aYCentre = mPosition.y + (mPosition.h / 2);
}

void CCase::SetPlusCourtChemin (bool abEstPlusCourtChemin)
{
   mbEstPlusCourtChemin = abEstPlusCourtChemin;
   if (mbEstPlusCourtChemin)
   {
      mCourImage = 2;
   }
   else
   {
      mCourImage = mEtat;
   }
}

bool CCase::EstPlusCourtChemin (void)
{
   return mbEstPlusCourtChemin;
}

void CCase::GetIdPlateau (int& aIdPlateauX, int& aIdPlateauY)
{
	aIdPlateauX = mIdPlateauX;
	aIdPlateauY = mIdPlateauY;
}

bool CCase::AutoriseATirer (void)
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

void CCase::Tire (CEnnemiPtr& aEnnemiCiblePtr)
{
   int PuissanceProjectile = 1;
   int VitesseProjectile   = 1;

   // La puissance et la vitesse du projectile d�pend du type de la tour
   switch (mEtat)
   {
      case eTour1:
         PuissanceProjectile = 2;
         VitesseProjectile   = 10;
         break;
      
      case eTour2:
         PuissanceProjectile = 4;
         VitesseProjectile   = 7;
         break;

      case eTour3:
      case eTour4:
      case eTour5:
      case eTour6:
      default:
         break;
   }

   // Cr�ation et ajout du projectile dans la liste des projectiles tir�s
   CProjectilePtr ProjectileTirePtr (new CProjectile( aEnnemiCiblePtr,
                                                      mPosition.x + (mPosition.w / 2),
                                                      mPosition.y + (mPosition.h / 2),
                                                      PuissanceProjectile,
                                                      VitesseProjectile));
   ProjectileTirePtr->OnInit ();
   mListeProjectilesTires.push_back (ProjectileTirePtr);

   // Gestion de la cadence de tire de la tour
   mTimer.Start ();
}
