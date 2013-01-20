#ifndef _MENU_H_
#define _MENU_H_

#include "Defined.h"
#include "Config.h"
#include "Image.h"

class CContexteJeu;

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
   CMenu    (CConfiguration& aConfig, CContexteJeu& aContexte);
   ~CMenu   (void);

   bool OnInit    (void);
   void OnClic		(const TCoordonnee& aCoordonneeClic);
   void OnAffiche (CSurface::Ptr& aScreenPtr);

   int GetLargeur (void);

private:
   CLog              mLog;
   CConfiguration&   mConfig;
   CContexteJeu&     mContexte;

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
