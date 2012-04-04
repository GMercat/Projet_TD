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
	int  OnClic		      (int aX, int aY);
	void OnAffiche	      (SDL_Surface* apScreen);
   void OnReset         (void);
   void OnQuit          (void);
   void OnProgression   (void);
   void OnTire          (void);

   CPlateau& GetPlateau (void);

   void AjoutEnnemi (void);

   bool PartieEnCours         (void);
   void ChangerEtatPartie     (bool abEtatPartie);
   bool PlacementEstAutorise  (void);
   void AnnuleDerniereModif   (void);

   CCase::ETypeCase  GetTourSelectionnee  (void);
   void              SelectTour           (CCase::ETypeCase aTypeTourSelect);

private:
	int mHauteur;
	int mLargeur;

   std::pair<int, int>  mCoordonneesDerniereCaseModifiee;

   bool              mbPartieEnCours;
   CCase::ETypeCase  mTypeTourSelect;
   
   std::list<CEnnemiPtr>   mListEnnemi;

   CPlateau mPlateau;
   CMenu    mMenu;

   CIA*     mpIA;
};

#endif