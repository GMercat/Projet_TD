#ifndef _JEU_H_
#define _JEU_H_

#include "Defined.h"

#include "Plateau.h"
#include "Menu.h"
#include "Ennemi.h"

class CIA;

class CJeu
{
public:
	CJeu (CIA* apIA);
	~CJeu (void);

	bool OnInit		      (void);
	void OnClic		      (int aX, int aY);
	void OnAffiche	      (SDL_Surface* apScreen);
   void OnReset         (void);
   void OnQuit          (void);
   void OnProgression   (void);
   void OnTire          (void);

   CPlateau& GetPlateau (void);

   void AjoutEnnemi  (void);
   /*void AjoutTour    (int aNumCase);*/

   bool PartieEnCours         (void);
   void ChangerEtatPartie     (bool abEtatPartie);
   bool PlacementEstAutorise  (void);

   int   GetTourSelectionnee  (void);
   void  SelectTour           (int aTypeTourSelect);

   int GetHauteur (void);
   int GetLargeur (void);

private:
   CConfiguration mConfig;
   CPlateau       mPlateau;
   CMenu          mMenu;
   CIA*           mpIA;

	int mHauteur;
	int mLargeur;

   bool  mbPartieEnCours;
   int   mTypeTourSelect;
   
   std::list<CTourPtr>     mListTour;
   std::list<CTourPtr>     mListTourTiree;
   std::list<CEnnemiPtr>   mListEnnemi;
};

#endif
