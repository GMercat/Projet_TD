#ifndef _JEU_H_
#define _JEU_H_

#include "Defined.h"

#include "Fenetre.h"
#include "Plateau.h"
#include "Menu.h"
#include "Timer.h"
#include "VagueEnnemis.h"

class CIA;

class CJeu
{
public:
	CJeu (CIA* apIA);
	~CJeu (void);

	bool OnInit		      (void);
	void OnClic		      (int aX, int aY);
	void OnAffiche	      (void);
   void OnReset         (void);
   void OnQuit          (void);
   void OnProgression   (void);
   void OnTire          (void);

   CPlateau& GetPlateau (void);

   bool PartieEnCours         (void);
   void ChangerEtatPartie     (bool abEtatPartie);
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
   CPlateau       mPlateau;
   CMenu          mMenu;
   CIA*           mpIA;
   CTimer         mTimerVague;

   CFenetre::Ptr	mScreenPtr;

   bool  mbPremiereTour;
   bool  mbPartieEnCours;

  	int   mHauteur;
	int   mLargeur;
   int   mTypeTourSelect;
   int   mTempsInterVague;
   
   CTour::Liste         mListTour;
   CTour::Liste         mListTourTiree;
   CVagueEnnemis::Liste mListVagues;
};

#endif
