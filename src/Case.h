#ifndef _CASE_H_
#define _CASE_H_

#include "Defined.h"
#include "Tour.h"
#include "Config.h"
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
typedef boost::shared_ptr<CCase> Ptr;

public:
   CCase    (void);
	~CCase	(void);

	void OnInit                (void);
	void OnAffiche             (CSurface::Ptr& aSurfaceDestPtr, CSurface::Ptr& aSurfaceCasePtr);
   
   CTour::Ptr& ConstruireTour (CConfiguration& aConfig, int aTypeTour, int aPortee, int aPuissance, int aVitesse, int aCadence);
   
	bool EstDedans	(int aX, int aY);
	bool EstVide	(void);

	void GetIdPlateau (int& aIdPlateauX, int& aIdPlateauY);
	
   const ETypeCase	GetType        (void) const;
         void	      SetType        (ETypeCase aeNouvelType);
         void	      SetPosition    (CRect::Ptr& aRectPtr, int aIdPlateauX, int aIdPlateauY);
         void        SetNumCase     (int aNumCase);
         int         GetNumCase     (void);
         void        GetCentre      (TCoordonnee& aCoordonneeCentre);
         int         GetTypeTour    (void);
         CRect::Ptr& GetPosition    (void);

   void SetPlusCourtChemin (bool abEstPlusCourtChemin);
   bool EstPlusCourtChemin (void);

   void MarqueSurvolee (bool abEstSurvolee);
   bool EstSurvolee (void);

private:
   CLog           mLog;
	ETypeCase      mType;
   
   int         mNumCase;
   bool        mbEstPlusCourtChemin;
   bool        mbEstSurvolee;

   int	      mIdPlateauX;
	int	      mIdPlateauY;

   CTour::Ptr  mTourPtr;

	int		   mCourImage; // L'image à afficher
	CRect::Ptr  mPositionPtr;	// Position de la case
};

#endif
