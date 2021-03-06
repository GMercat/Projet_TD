#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "Defined.h"

#include "ConfigJeu.h"
#include "Case.h"

class CTerrain
{
public :
    CTerrain (CConfiguration& aConfig);
   ~CTerrain (void);

   void  OnInit            (int aNumCaseDepart, int aNumCaseArrivee);
   void  OnReset           (int aNumCaseDepart, int aNumCaseArrivee);
   void  OnAffiche         (CSurface::Ptr& aEcranPtr);
   void  OnAfficheEnPause  (CSurface::Ptr& aEcranPtr);
   bool  OnClic            (const TCoordonnee& aCoordonneeClic, int aTypeTourSelectMenu, int& aNumCaseCliquee);

   CTour::Ptr& ConstruireTour       (int aTypeTourSelectMenu, int aNumCaseCliquee);
   void        AnnuleDerniereModif  (void);
   void        DeselectionTour      (void);

   bool EstCaseVide (const TIndexTableau& aIndexCase);

   CCase::Ptr& GetCase (const TCoordonnee& aCoordonneeClic);
   CCase::Ptr& GetCase (const TIndexTableau& aIndexCase);

   int GetLargeur (void);
   int GetHauteur (void);
   int GetNbCaseLargeur (void);
   int GetNbCaseHauteur (void);
   int GetLargeurCase (void);
   int GetHauteurCase (void);

   void GetCoordonneesCentreCaseCaseParNumero (int aNumCase, TCoordonnee& aCoordonnees);

   int CoordonneeToNum (const TCoordonnee& aCoordonnee);

private:
   int IndexToNum (const TIndexTableau& aIndexPlateau);

private:
   Log::Logger       mLogger;
   CConfiguration&   mConfig;

   CCase::Vector mCases;

   int mNbCasesHauteur; // Nombre de cases du plateau en hauteur lu dans le fichier de config
   int mNbCasesLargeur; // Nombre de cases du plateau en largeur lu dans le fichier de config
   int mLargeurCase;    // Largeur d'une case lu dans le fichier de config
   int mHauteurCase;    // Hauteur d'une case lu dans le fichier de config

   TIndexTableau mIndexDerniereCaseModifiee;
   TIndexTableau mIndexCaseSelectionnee;
   
   CImage::Ptr   mImagePausePtr;

   std::vector <std::string>  mNomImagesCase;
   std::vector <CImage::Ptr>  mImagesCases;
};

#endif
