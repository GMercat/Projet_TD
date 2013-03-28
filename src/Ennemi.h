#ifndef _ENNEMI_H_
#define _ENNEMI_H_

#include "Defined.h"
#include "ConfigJeu.h"
#include "Image.h"

class CIA;

class CEnnemi
{
public:
   enum EType {
      eType1,
      eType2,
      eType3,
      eType4
   };

public:
   typedef std::shared_ptr<CEnnemi>  Ptr;
   typedef std::list<CEnnemi::Ptr>     Liste;

public:
   CEnnemi  (CConfiguration& aConfig, CIA* apIA, EType aType, int aNumCaseDepart, int aNumCaseArrivee);
   ~CEnnemi (void);

   void  OnAffiche (CSurface::Ptr& aScreenPtr);

   EType GetType           (void);
   void  SetType           (EType aType);
   void  SetPCCheminCase   (std::list<int>& aPPCheminCase);
   void  GetCentre         (TCoordonnee& aCoordonneesCentre);

   int   DetermineCaseCourante   (void);

   void  Avance (void);
   void  Touche (int aPuissance);
   
   bool  EstVivant (void);
   bool  EstArrive (void);
   
private:
   CConfiguration&   mConfig;
   Log::Logger       mLogger;
   CIA*              mpIA;

   EType mType;

   int         mVitesse;
   TCoordonnee mCoordonnee; // Coordonnée du centre de l'ennmi
   int         mVie;

   int                           mNumCaseArrivee;
   std::list<int>                mPCCheminCase;
   std::list<TVecteurChemin>     mPCCheminReel;

   CImage::Ptr   mImagePtr;
   TCoordonnee   mPosition;
   int           mLargeur;
   int           mHauteur;
};

#endif
