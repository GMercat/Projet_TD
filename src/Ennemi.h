#ifndef _ENNEMI_H_
#define _ENNEMI_H_

#include "Defined.h"
#include "Config.h"
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
   typedef boost::shared_ptr<CEnnemi>  Ptr;
   typedef std::list<CEnnemi::Ptr>     Liste;

public:
   CEnnemi  (CConfiguration& aConfig, CIA* apIA, EType aType, int aNumCaseDepart, int aNumCaseArrivee);
   ~CEnnemi (void);

   bool  OnInit    (void);
   void  OnAffiche (CSurface::Ptr& aScreenPtr);

   EType GetType           (void);
   void  SetType           (EType aType);
   void  SetPCCheminCase   (std::list<int>& aPPCheminCase);
   void  GetCentre         (int& aXCentre, int& aYCentre);

   int   DetermineCaseCourante   (void);

   void  Avance (void);
   void  Touche (int aPuissance);
   
   bool  EstVivant (void);
   bool  EstArrive (void);
   
private:
   CConfiguration&   mConfig;
   CLog              mLog;
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
