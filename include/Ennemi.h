#ifndef _ENNEMI_H_
#define _ENNEMI_H_

#include "Defined.h"

class CIA;

typedef std::pair<TCoordonnee, TCoordonnee > TVecteurChemin ;

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

   EType GetType (void);
   void  SetType (EType aType);

   bool OnInit    (void);
   void OnAffiche (SDL_Surface* apScreen);

   void  SetPCCheminCase (std::vector<int>& aPPCheminCase);

   int   DetermineCaseCourante   (void);
   void  CalculPCCheminReel      (std::vector<int>& aPCChemin);

   void  Avance (void);

private:
   void  CalculPCChemin  (void);
   
private:
   CIA*  mIA;

   EType mType;

   int                           mVitesse;
   TCoordonnee                   mCoordonnee;
   int                           mNumCaseArrivee;
   std::vector<int>              mPCCheminCase;
   std::list<TVecteurChemin>     mPCCheminReel;

   SDL_Surface*  mpImage;
   SDL_Rect      mPosition;
};

#endif
