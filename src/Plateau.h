#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include "Defined.h"
#include "ConfigJeu.h"
#include "Case.h"
#include "Image.h"
#include "Terrain.h"

class CContexteJeu;

class CPlateau
{
public:
   CPlateau (CConfiguration& aConfig, CContexteJeu& aContexte);
   ~CPlateau (void);

   bool  OnInit            (void);
   void  OnReset           (void);
   bool  OnClic            (const TCoordonnee& aCoordonneeClic, int& aNumCaseCliquee);
   void  OnAffiche         (CSurface::Ptr& aEcranPtr);
   void  OnAfficheEnPause  (CSurface::Ptr& aEcranPtr);
   void  OnSurvoleCase     (const TCoordonnee& aCoordonnee);
   void  OnSurvoleCase     (const TCoordonnee& aCoordonnee, const int aTypeTourSelect);

   bool EstDansPlateau     (const TCoordonnee& aCoordonneeClic);
   bool EstCaseVide        (int aIndexLargeur, int aIndexHauteur);

   CTour::Ptr& ConstruireTour (int aNumCaseCliquee);
   void AnnuleDerniereModif   (void);

   int GetNbCaseLargeur (void);
   int GetNbCaseHauteur (void);
   int GetLargeurCase   (void);
   int GetHauteurCase   (void);

   void        GetCoordonneesCentreCaseCaseParNumero  (int aNumCase, TCoordonnee& aCoordonnees);
   int         GetNumCaseParCoordonnees               (TCoordonnee& aCoordonnees); // Coordonnées
   int         GetNumCaseDepart                       (void);
   int         GetNumCaseArrivee                      (void);

   // void RenseignePlusCourtChemin (std::vector<int>& aPlusCourtChemin);

private:
   Log::Logger              mLogger;
   CConfiguration&   mConfig;
   CContexteJeu&     mContexte;
   CTerrain          mTerrain;
   
   int mDerniereCaseSurvolee;

   int mNumCaseDepart;
   int mNumCaseArrivee;
};

#endif
