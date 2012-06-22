#ifndef _MENU_H_
#define _MENU_H_

#include "Defined.h"
#include "Config.h"

class CJeu;

class CMenu
{
public:
   enum EBoutonMenu {
      eNew = 0,
      ePause,
      eReprendre,
      eQuit,

      eNewEnnemi,
      eNbBouton
   };

public:
   CMenu    (CConfiguration& aConfig, CJeu& aJeu);
   ~CMenu   (void);

   bool OnInit    (void);
   void OnClic		(int aX, int aY);
   void OnAffiche (SDL_Surface* apScreen);

   int GetLargeur (void);

private:
   CConfiguration&   mConfig;
   CJeu&             mJeu;

   int mLargeur;
   int mNbTours;
   
   SDL_Surface*   mImageFond;
   SDL_Rect       mPositionFond;

   std::vector <SDL_Surface*> mImagesBoutons;
   std::vector <SDL_Rect>     mPositionsBoutons;
   std::vector <std::string>  mNomImagesTour;
   std::vector <SDL_Surface*> mImagesTours;
   std::vector <SDL_Rect>     mPositionsTours;
};

#endif
