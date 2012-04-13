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

   bool  OnInit    (void);
   void  OnAffiche (SDL_Surface* apScreen);

   void  SetPCCheminCase (std::list<int>& aPPCheminCase);
   void  GetCentre (int& aXCentre, int& aYCentre);

   int   DetermineCaseCourante   (void);
   void  CalculPCCheminReel      (std::list<int>& aPCChemin);

   void  Avance (void);
   bool  EstArrive (void);

   void  Touche (int aPuissance);
   
   bool  EstVivant (void);

private:
   void  CalculPCChemin  (void);
   
private:
   CIA*  mIA;

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
