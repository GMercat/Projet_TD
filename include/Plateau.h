#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include "Defined.h"

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

   CCase*   GetCase           (int aX, int aY);
   int      GetNumCaseDepart  (void);
   int      GetNumCaseArrivee (void);

   void     RenseignePlusCourtChemin (std::vector<int>& aPlusCourtChemin);

private:
   CJeu& mJeu;

	CCase mPlateau[NB_CASE_LARGEUR][NB_CASE_HAUTEUR];

   int mNumCaseDepart;
   int mNumCaseArrivee;

   std::vector <SDL_Surface*> mImages;
   
   SDL_Surface* mpImagePause;
   
   SDL_Surface*	mpImagePCC;
};

#endif