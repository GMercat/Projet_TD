#ifndef _VAGUE_ENNEMIS_H_
#define _VAGUE_ENNEMI_H_

#include "Defined.h"
#include "ConfigJeu.h"
#include "Ennemi.h"
#include "Timer.h"

class CIA;

class CVagueEnnemis
{
public:
   typedef std::shared_ptr<CVagueEnnemis>  Ptr;
   typedef std::list<CVagueEnnemis::Ptr>     Liste;

public:
   CVagueEnnemis  (CConfiguration& aConfig, CIA* apIA, int aNumCaseDepart, int aNumCaseArrivee);
   ~CVagueEnnemis (void);

   bool EstVide (void);

   void OnAffiche             (CSurface::Ptr& aScreenPtr);
   void ProgressionEnnemis    (void);
   bool PlacementEstAutorise  (int aNumCaseArrivee);
   bool SelectionneEnnemi     (TCoordonnee& aCoordonneesTour, int aPorteeTour, CEnnemi::Ptr& aEnnemiSelectionnePtr);

private:
   void AjoutEnnemi        (void);

private:
   CConfiguration&   mConfig;
   CIA*              mpIA;

   CEnnemi::Liste mListEnnemis;      
   CTimer         mTimerEnnemi;

   int   mNbEnnemis;
   int   mTempsProchainEnnemi;

   int   mNumCaseDepart;
   int   mNumCaseArrivee;
};

#endif