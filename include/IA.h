#ifndef _IA_H_
#define _IA_H_

#include "Defined.h"

class CPlateau;
class CCase;

class CIA
{
public:
	CIA (CPlateau& aPlateau);
	~CIA (void);

   void OnInit (void);

   void ConstruireMatriceGraphe  (void);
   void MiseAJourMatriceGraphe   (int aNumCase, bool abEstOccuped);
   bool CalculPlusCourtChemin    (int aNumCaseDepart, int aNumCaseArrivee, std::list<int>& aPlusCourtChemin);
   void CalculPCCheminReel       (std::list<int>& aPCChemin, TCoordonnee& aCoordonnees, std::list<TVecteurChemin>& aPCCheminReel);

   int   GetNumCaseParCoordonnees      (TCoordonnee& aCoordonnees);
   void  GetCoordonneesCaseParNumero   (int aNumero, TCoordonnee& aCoordonnees);
   
   void AfficherMatrice (void);

private:
   void CalculCheminMinimaux     (void);

private:
   CLog        mLog;
   CPlateau&   mPlateau;

   int **mMatriceGraph;
   int **mMatriceGraphCalcul;
   int **mCheminsMinimaux;
};

#endif
