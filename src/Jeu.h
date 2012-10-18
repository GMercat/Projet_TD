#ifndef _JEU_H_
#define _JEU_H_

#include "Defined.h"

#include "Plateau.h"
#include "Menu.h"
#include "Ennemi.h"
#include "Timer.h"

class CIA;

class CJeu
{
public:
	CJeu (CIA* apIA);
	~CJeu (void);

	bool OnInit		      (void);
	void OnClic		      (int aX, int aY);
	void OnAffiche	      (CSurface::Ptr& aScreenPtr);
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
   void AjoutEnnemi  (void);
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
   CTimer         mTimerEnnemi;

   bool  mbPremiereTour;
   bool  mbPartieEnCours;

  	int   mHauteur;
	int   mLargeur;
   int   mDerniereVagueLancee;
   int   mNumVagueEnCours;
   int   mNbEnnemisVague;
   int   mTypeTourSelect;
   int   mTempsInterVague;
   int   mTempsProchainEnnemi;
   
   CTour::Liste     mListTour;
   CTour::Liste     mListTourTiree;
   CEnnemi::Liste   mListEnnemi;
};

#endif
