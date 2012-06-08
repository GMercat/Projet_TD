#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include "Defined.h"
#include "Config.h"
#include "Case.h"

class CJeu;

class CPlateau
{
public:
   CPlateau (CConfiguration& aConfig, CJeu& aJeu);
   ~CPlateau (void);

   bool OnInit (void);
   void OnReset (void);
   int  OnClic (int aX, int aY);
   void OnAffiche (SDL_Surface* apEcran);
   
   CTourPtr& ConstruireTour (int aNumCaseCliquee);
   void AnnuleDerniereModif   (void);

   int GetNbCaseLargeur (void);
   int GetNbCaseHauteur (void);
   int GetLargeurCase   (void);
   int GetHauteurCase   (void);

   CCasePtr&   GetCase                       (int aNumCase);
   CCasePtr&   GetCase                       (int aX, int aY); // Index dans le tableau
   void        GetCoordonneesCaseParNumero   (int aNumero, TCoordonnee& aCoordonnees);
   int         GetNumCaseParCoordonnees      (TCoordonnee& aCoordonnees); // Coordonnées
   int         GetNumCaseDepart              (void);
   int         GetNumCaseArrivee             (void);

   void RenseignePlusCourtChemin (std::vector<int>& aPlusCourtChemin);

private:
   CConfiguration&   mConfig;
   CJeu&             mJeu;

   int mNbCasesLargeur; // Nombre de cases du plateau en largeur lu dans le fichier de config
   int mNbCasesHauteur; // Nombre de cases du plateau en hauteur lu dans le fichier de config
   int mLargeurCase;
   int mHauteurCase;

   std::vector<CCasePtr> mCases;

   int mNumCaseDepart;
   int mNumCaseArrivee;

   std::pair<int, int>  mCoordonneesDerniereCaseModifiee;

   std::vector <std::string>  mNomImagesCase;
   std::vector <SDL_Surface*> mImagesCases;
   
   std::vector <std::string>  mNomImagesTour;
   std::vector <SDL_Surface*> mImagesTours;
      
   SDL_Surface*   mpImagePause;
   // TODO Non utilisé SDL_Surface*	mpImagePCC;
};

#endif
