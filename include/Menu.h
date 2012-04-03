#ifndef _MENU_H_
#define _MENU_H_

#include "Defined.h"

class CJeu;

class CMenu
{
public:
   enum EBoutonMenu {
      eFond = 0,
      
      ePause = 1,
      eTour1,
      eTour2,
      eTour3,
      eTour4,
      eTour5,
      eTour6,
      eNewEnnemi,

      eNew,
      eReprendre,
      eQuit,

      eNbBouton
   };

public:
   CMenu    (CJeu& aJeu);
   ~CMenu   (void);

   bool OnInit    (void);
   void OnClic		(int aX, int aY);
   void OnAffiche (SDL_Surface* apScreen);

private:
   CJeu& mJeu;
   
   SDL_Surface*   mImages[eNbBouton];
   SDL_Rect       mPositions[eNbBouton];
};

#endif