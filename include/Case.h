#ifndef _CASE_H_
#define _CASE_H_

#include "Defined.h"
#include "Tour.h"
#include "Ennemi.h"


class CCase
{
public:
	enum ETypeCase {
		eMur = 0,
		eVide,
      eTour,
      eNbType
	};


public:
	CCase	   (void);
	~CCase	(void);

	void OnInit                (void);
	void OnAffiche             (SDL_Surface* apSurfaceDest, SDL_Surface* apSurfaceCase);
   
   CTourPtr& ConstruireTour (int aTypeTour, int aPortee, int aPuissance, int aVitesse, int aCadence);
   
	bool EstDedans	(int aX, int aY);
	bool EstVide	(void);

	void GetIdPlateau (int& aIdPlateauX, int& aIdPlateauY);
	
   const ETypeCase	GetEtat        (void) const;
         void	      SetEtat        (ETypeCase aeNouvelEtat);
         void	      SetPosition    (SDL_Rect* apRect, int aIdPlateauX, int aIdPlateauY);
         void        SetNumCase     (int aNumCase);
         int         GetNumCase     (void);
         void        GetCentre      (int& aXCentre, int &aYCentre);
         int         GetTypeTour    (void);
         SDL_Rect&   GetPosition    (void);

   void SetPlusCourtChemin (bool abEstPlusCourtChemin);
   bool EstPlusCourtChemin (void);

private:
	ETypeCase   mEtat;
   
   int         mNumCase;
   bool        mbEstPlusCourtChemin;

   int	      mIdPlateauX;
	int	      mIdPlateauY;

   CTourPtr    mTourPtr;

	int		   mCourImage; // L'image à afficher
	SDL_Rect		mPosition;	// Position de la case
};

typedef boost::shared_ptr<CCase> CCasePtr;

#endif
