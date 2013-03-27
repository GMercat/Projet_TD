#ifndef _CASE_H_
#define _CASE_H_

#include "Defined.h"
#include "Tour.h"
#include "ConfigJeu.h"
#include "Ennemi.h"
#include "Rect.h"

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
typedef std::shared_ptr<CCase> Ptr;
typedef std::vector<CCase::Ptr> Vector;

public:
            CCase (void);
	virtual ~CCase	(void);

	virtual  void OnInit     (void);
	virtual  void OnAffiche  (CSurface::Ptr& aSurfaceDestPtr);
   
   CTour::Ptr& ConstruireTour (CConfiguration& aConfig, int aTypeTour);
   
	bool EstDedans	(int aX, int aY);
	bool EstVide	(void);

	TIndexTableau& GetIdPlateau (void);
	
         ETypeCase	GetType        (void) const;
         void	      SetType        (ETypeCase aeNouvelType);
         void	      SetPosition    (CRect::Ptr& aRectPtr, int aIdPlateauX, int aIdPlateauY);
         void        SetNumCase     (int aNumCase);
         int         GetNumCase     (void);
         void        GetCentre      (TCoordonnee& aCoordonneeCentre);
         int         GetTypeTour    (void);
         CRect::Ptr& GetPosition    (void);

   void SetPlusCourtChemin (bool abEstPlusCourtChemin);
   bool EstPlusCourtChemin (void);

   void MarqueSurvolee     (bool abEstSurvolee);
   void MarqueSelectionnee (bool abEstSelectionnee);
   bool EstSurvolee (void);

private:
   Log::Logger           mLogger;
	ETypeCase      mType;
   
   int   mNumCase;
   bool  mbEstPlusCourtChemin;
   bool  mbEstSurvolee;
   bool  mbEstSelectionnee;

   TIndexTableau  mIdPlateau;

   CTour::Ptr  mTourPtr;

	int		   mCourImage; // L'image à afficher
	CRect::Ptr  mPositionPtr;	// Position de la case
};

#endif
