#include "../include/Case.h"

CCase::CCase (void)
{
	mIdPlateauX = -1;
	mIdPlateauX = -1;
	mEtat		= eVide;
	mCourImage	= 0;
	mPosition.x = 0;
	mPosition.y = 0;
	mPosition.w = 0;
   mNumCase = -1;
   mbEstPlusCourtChemin = false;
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
      case eTour2:
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

int   CCase::GetNumCase (void)
{
   return mNumCase;
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
