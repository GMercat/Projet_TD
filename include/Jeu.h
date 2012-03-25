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

	bool OnInit		(void);
	void OnClic		(int aX, int aY);
	void OnAffiche	(SDL_Surface* apScreen);
   void OnReset   (void);
   void OnQuit    (void);

   CPlateau& GetPlateau (void);

   bool PartieEnCours      (void);
   void ChangerEtatPartie  (bool abEtatPartie);

   bool PlacementEstAutorise  (void);
   void AnnuleDerniereModif   (void);

   CCase::EEtat   GetTourSelectionnee  (void);
   void           SelectTour           (CCase::EEtat aTypeTourSelect);

private:
	int mHauteur;
	int mLargeur;

   std::pair<int, int>  mCoordonneesDerniereCaseModifiee;

   bool           mbPartieEnCours;
   CCase::EEtat   mTypeTourSelect;
   
   std::list<CEnnemi>   mListEnnemi;

   CPlateau mPlateau;
   CMenu    mMenu;

   CIA*     mpIA;
};

#endif