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
   void CalculCheminMinimaux     (void);
   bool CalculPlusCourtChemin    (int aNumCaseDepart, int aNumCaseArrivee, std::list<int>& aPlusCourtChemin);
   void CalculPCCheminReel       (std::list<int>& aPCChemin, TCoordonnee& aCoordonnees, std::list<TVecteurChemin>& aPCCheminReel);

   int   GetNumCaseParCoordonnees      (TCoordonnee& aCoordonnees);
   void  GetCoordonneesCaseParNumero   (int aNumero, TCoordonnee& aCoordonnees);
   
   void AfficherMatrice (void);

private:
   int **mMatriceGraph;
   int **mCheminsMinimaux;

//   int mMatriceGraph    [NB_CASE_LARGEUR * NB_CASE_HAUTEUR][NB_CASE_LARGEUR * NB_CASE_HAUTEUR];
//   int mCheminsMinimaux [NB_CASE_LARGEUR * NB_CASE_HAUTEUR][NB_CASE_LARGEUR * NB_CASE_HAUTEUR];

   CPlateau& mPlateau;
};

#endif
