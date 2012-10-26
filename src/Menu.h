#ifndef _MENU_H_
#define _MENU_H_

#include "Defined.h"
#include "Config.h"
#include "Image.h"

class CJeu;

class CMenu
{
public:
   enum EBoutonMenu {
      eNew = 0,
      ePause,
      eReprendre,
      eQuit,

//      eNewEnnemi,
      eNbBouton
   };

public:
   CMenu    (CConfiguration& aConfig, CJeu& aJeu);
   ~CMenu   (void);

   bool OnInit    (void);
   void OnClic		(int aX, int aY);
   void OnAffiche (CSurface::Ptr& aScreenPtr);

   int GetLargeur (void);

private:
   CLog              mLog;
   CConfiguration&   mConfig;
   CJeu&             mJeu;

   int mLargeur;
   int mNbTours;
   
   CImage::Ptr mImageFondPtr;
   CRect::Ptr  mPositionFondPtr;

   CImage::Vecteur            mImagesBoutons;
   std::vector <CRect::Ptr>   mPositionsBoutons;
   std::vector <std::string>  mNomImagesTour;
   CImage::Vecteur            mImagesTours;
   std::vector <CRect::Ptr>   mPositionsTours;
};

#endif
