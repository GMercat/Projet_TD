#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include "Defined.h"
#include "Config.h"
#include "Case.h"
#include "Image.h"
#include "Terrain.h"

class CJeu;

class CPlateau
{
public:
   CPlateau (CConfiguration& aConfig, CJeu& aJeu);
   ~CPlateau (void);

   bool OnInit (void);
   void OnReset (void);
   int  OnClic (int aX, int aY);
   void OnAffiche (CSurface::Ptr& aEcranPtr);
   void OnAfficheEnPause (CSurface::Ptr& aEcranPtr);
   void OnSurvoleCase (int aX, int aY);

   bool EstDansPlateau (int aX, int aY);

   CTour::Ptr& ConstruireTour (int aNumCaseCliquee);
   void AnnuleDerniereModif   (void);

   int GetNbCaseLargeur (void);
   int GetNbCaseHauteur (void);
   int GetLargeurCase   (void);
   int GetHauteurCase   (void);

   void        GetCoordonneesCaseParNumero   (int aNumero, TCoordonnee& aCoordonnees);
   int         GetNumCaseParCoordonnees      (TCoordonnee& aCoordonnees); // Coordonnées
   int         GetNumCaseDepart              (void);
   int         GetNumCaseArrivee             (void);

   // void RenseignePlusCourtChemin (std::vector<int>& aPlusCourtChemin);

private:
   CLog              mLog;
   CConfiguration&   mConfig;
   CJeu&             mJeu;
   CTerrain          mTerrain;

   int mLargeurCase;
   int mHauteurCase;

   int mDerniereCaseSurvolee;

   int mNumCaseDepart;
   int mNumCaseArrivee;

   std::pair<int, int>  mCoordonneesDerniereCaseModifiee;
      
   CImage::Ptr   mImagePausePtr;
};

#endif
