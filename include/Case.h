#ifndef _CASE_H_
#define _CASE_H_

#include "Defined.h"

class CCase
{
public:
	enum EEtat {
		eVide = 0,
		eMur,

      eTour1,
      eTour2,
      eTour3,
      eTour4,
      eTour5,
      eTour6,
      eNbEtat
	};


public:
	CCase	(void);
	~CCase	(void);

	void OnInit (void);
	void OnAffiche (SDL_Surface* apSurfaceDest, SDL_Surface* apSurfaceCase);

	bool EstDedans	(int aX, int aY);
	bool EstVide	(void);

	void GetIdPlateau (int& aIdPlateauX, int& aIdPlateauY);
	
   const EEtat	GetEtat (void) const;
   void	SetEtat (EEtat aeNouvelEtat);
   void	SetPosition (SDL_Rect* apRect, int aIdPlateauX, int aIdPlateauY);
   void  SetNumCase (int aNumCase);
   int   GetNumCase (void);

   void SetPlusCourtChemin (bool abEstPlusCourtChemin);
   bool EstPlusCourtChemin (void);

private:
	int							   mIdPlateauX;
	int							   mIdPlateauY;
	EEtat						      mEtat;
	int							   mCourImage; // L'image à afficher
	SDL_Rect					      mPosition;	// Position de la case
   int                        mNumCase;
   bool                       mbEstPlusCourtChemin;
};

#endif