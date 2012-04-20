#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include "Defined.h"
#include "Config.h"
#include "Case.h"

class CJeu;

class CPlateau
{
public:
   CPlateau (CJeu& aJeu);
   ~CPlateau (void);

   bool OnInit (void);
   void OnReset (void);
   void OnAffiche (SDL_Surface* apEcran);

   int GetNbCaseLargeur (void);
   int GetNbCaseHauteur (void);

   CCasePtr&   GetCase                       (int aNumCase);
   CCasePtr&   GetCase                       (int aX, int aY); // Index dans le tableau
   void        GetCoordonneesCaseParNumero   (int aNumero, TCoordonnee& aCoordonnees);
   int         GetNumCaseParCoordonnees      (TCoordonnee& aCoordonnees); // Coordonnées
   int         GetNumCaseDepart              (void);
   int         GetNumCaseArrivee             (void);

   void RenseignePlusCourtChemin (std::vector<int>& aPlusCourtChemin);

private:
   CConfiguration mConfig;
   CJeu&          mJeu;

   int mNbCasesLargeur; // Nombre de cases du plateau en largeur lu dans le fichier de config
   int mNbCasesHauteur; // Nombre de cases du plateau en hauteur lu dans le fichier de config

	//CCasePtr mPlateau[NB_CASE_LARGEUR][NB_CASE_HAUTEUR];
   std::vector<CCasePtr> mCases;

   int mNumCaseDepart;
   int mNumCaseArrivee;

   std::vector <SDL_Surface*> mImages;
   
   SDL_Surface*   mpImagePause;
   SDL_Surface*	mpImagePCC;
};

#endif
