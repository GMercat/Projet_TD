#include "../include/Case.h"

CCase::CCase (void):
	mIdPlateauX          (-1),
	mIdPlateauY          (-1),
	mEtat		            (eVide),
	mCourImage	         (0),
   mNumCase             (-1),
   mbEstPlusCourtChemin (false)
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
}

CTourPtr& CCase::ConstruireTour (int aTypeTour, int aPortee, int aPuissance, int aVitesse, int aCadence)
{
   TCoordonnee CoordCentre;
   
   CoordCentre.first = mPosition.x + (mPosition.w / 2);
   CoordCentre.second = mPosition.y + (mPosition.h / 2);

   mTourPtr = CTourPtr (new CTour (CoordCentre, aTypeTour, aPortee, aPuissance, aVitesse, aCadence));
   return mTourPtr;
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
	mEtat = aeNouvelEtat;
	mCourImage = aeNouvelEtat;
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

void CCase::GetCentre (int& aXCentre, int &aYCentre)
{
   aXCentre = mPosition.x + (mPosition.w / 2);
   aYCentre = mPosition.y + (mPosition.h / 2);
}

int CCase::GetTypeTour (void)
{
   int TypeRetour = -1;
   if (mTourPtr)
   {
      TypeRetour = mTourPtr->GetTypeTour ();
   }
   return TypeRetour;
}

SDL_Rect& CCase::GetPosition (void)
{
   return mPosition;
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
