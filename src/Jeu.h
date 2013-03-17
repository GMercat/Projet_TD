#ifndef _JEU_H_
#define _JEU_H_

#include "Defined.h"

#include "Fenetre.h"
#include "IA.h"
#include "Plateau.h"
#include "Menu.h"
#include "ContexteJeu.h"
#include "Timer.h"
#include "VagueEnnemis.h"

class CJeu
{
public:
	 CJeu (void);
	~CJeu (void);

	bool OnInit		      (void);
	void OnClic		      (const TCoordonnee& aCoordonneeClic);
	void OnAffiche	      (void);
   void OnReset         (void);
   void OnQuit          (void);
   void OnProgression   (void);
   void OnTire          (void);

   void TraiteDemande (void);

   CPlateau& GetPlateau (void);

   bool PlacementEstAutorise  (void);

   int   GetTourSelectionnee  (void);
   void  SelectTour           (int aTypeTourSelect);

   int GetHauteur (void);
   int GetLargeur (void);

private:
   void ProgressionProjectiles   (void);
   void ProgressionEnnemis       (void);
   
   bool LancementNouvelleVagueEnnemisPossible   (void);
   void LancementVagueEnnemis                   (void);

private:
   CLog           mLog;
   CConfiguration mConfig;
   CIA            mIA;
   CPlateau       mPlateau;
   CMenu          mMenu;
   CContexteJeu   mContexte;
   CTimer         mTimerVague;

   CFenetre::Ptr	mScreenPtr;

   bool  mbPremiereTour;
   
  	int   mHauteur;
	int   mLargeur;
   int   mTypeTourSelect;
   int   mTempsInterVague;
   
   CTour::Liste         mListTour;
   CVagueEnnemis::Liste mListVagues;
};

#endif
