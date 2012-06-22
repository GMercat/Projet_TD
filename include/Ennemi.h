#ifndef _ENNEMI_H_
#define _ENNEMI_H_

#include "Defined.h"

class CIA;

class CEnnemi
{
public:
   enum EType {
      eType1,
      eType2
   };

public:
   CEnnemi  (CIA* apIA, int aNumCaseDepart, int aNumCaseArrivee);
   ~CEnnemi (void);

   bool  OnInit    (void);
   void  OnAffiche (SDL_Surface* apScreen);

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
   CIA*  mpIA;

   EType mType;

   int         mVitesse;
   TCoordonnee mCoordonnee; // Coordonnée du centre de l'ennmi
   int         mVie;

   int                           mNumCaseArrivee;
   std::list<int>                mPCCheminCase;
   std::list<TVecteurChemin>     mPCCheminReel;

   SDL_Surface*  mpImage;
   SDL_Rect      mPosition;
};

typedef boost::shared_ptr<CEnnemi> CEnnemiPtr;

#endif
