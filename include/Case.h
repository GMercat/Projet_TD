#ifndef _CASE_H_
#define _CASE_H_

#include "Defined.h"
#include "Projectile.h"
#include "Ennemi.h"
#include "../include/Timer.h"


class CCase
{
public:
	enum ETypeCase {
		eVide = 0,
		eMur,

      eTour1,
      eTour2,
      eTour3,
      eTour4,
      eTour5,
      eTour6,
      eNbType
	};


public:
	CCase	(void);
	~CCase	(void);

	void OnInit (void);
	void OnAffiche (SDL_Surface* apSurfaceDest, SDL_Surface* apSurfaceCase);

	bool EstDedans	(int aX, int aY);
	bool EstVide	(void);

	void GetIdPlateau (int& aIdPlateauX, int& aIdPlateauY);
	
   const ETypeCase	GetEtat        (void) const;
         void	      SetEtat        (ETypeCase aeNouvelEtat);
         void	      SetPosition    (SDL_Rect* apRect, int aIdPlateauX, int aIdPlateauY);
         void        SetNumCase     (int aNumCase);
         int         GetNumCase     (void);
         int         GetPorteeTire  (void);
         void        GetCentre      (int& aXCentre, int &aYCentre); 

   void SetPlusCourtChemin (bool abEstPlusCourtChemin);
   bool EstPlusCourtChemin (void);

   bool AutoriseATirer  (void);
   void Tire            (CEnnemiPtr& aEnnemiCiblePtr);
   
private:
	ETypeCase   			      mEtat;
   
   int                        mNumCase;
   bool                       mbEstPlusCourtChemin;

   int							   mIdPlateauX;
	int							   mIdPlateauY;

   CTimer                     mTimer;           

   int                        mPorteeTire;
   int                        mCadenceTire;           // Cadence de tire en seconde
   std::list<CProjectilePtr>  mListeProjectilesTires;

	int							   mCourImage; // L'image à afficher
	SDL_Rect					      mPosition;	// Position de la case
};

typedef boost::shared_ptr<CCase> CCasePtr;

#endif