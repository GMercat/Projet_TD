#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include "Defined.h"
#include "Config.h"
#include "Case.h"
#include "Image.h"

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

   CCase::Ptr& GetCase                       (int aNumCase);
   CCase::Ptr& GetCase                       (int aX, int aY); // Index dans le tableau
   void        GetCoordonneesCaseParNumero   (int aNumero, TCoordonnee& aCoordonnees);
   int         GetNumCaseParCoordonnees      (TCoordonnee& aCoordonnees); // Coordonnées
   int         GetNumCaseDepart              (void);
   int         GetNumCaseArrivee             (void);

   void RenseignePlusCourtChemin (std::vector<int>& aPlusCourtChemin);

private:
   CLog              mLog;
   CConfiguration&   mConfig;
   CJeu&             mJeu;

   int mNbCasesLargeur; // Nombre de cases du plateau en largeur lu dans le fichier de config
   int mNbCasesHauteur; // Nombre de cases du plateau en hauteur lu dans le fichier de config
   int mLargeurCase;
   int mHauteurCase;

   int mDerniereCaseSurvolee;

   std::vector<CCase::Ptr> mCases;

   int mNumCaseDepart;
   int mNumCaseArrivee;

   std::pair<int, int>  mCoordonneesDerniereCaseModifiee;

   std::vector <std::string>  mNomImagesCase;
   std::vector <CImage::Ptr>    mImagesCases;
   std::vector <std::string>  mNomImagesTour;
   std::vector <CImage::Ptr>    mImagesTours;
      
   CImage::Ptr   mImagePausePtr;
};

#endif
