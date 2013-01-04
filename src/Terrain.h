#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "Defined.h"

#include "Config.h"
#include "Case.h"

class CTerrain
{
public :
    CTerrain (CConfiguration& aConfig);
   ~CTerrain (void);

   void OnInit    (int aNumCaseDepart, int aNumCaseArrivee);
   void OnReset   (int aNumCaseDepart, int aNumCaseArrivee);
   void OnAffiche (CSurface::Ptr& aEcranPtr)

   CCase::Ptr& GetCase (int aX, int aY);

private:
   CConfiguration& mConfig;

   CCase::Vector mCases;

   int mNbCasesHauteur; // Nombre de cases du plateau en hauteur lu dans le fichier de config
   int mNbCasesLargeur; // Nombre de cases du plateau en largeur lu dans le fichier de config

   std::vector <std::string>  mNomImagesCase;
   std::vector <CImage::Ptr>  mImagesCases;
   std::vector <std::string>  mNomImagesTour;
   std::vector <CImage::Ptr>  mImagesTours;
};

#endif
