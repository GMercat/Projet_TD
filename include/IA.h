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

   void ConstruireMatriceGraphe (void);
   bool CalculPlusCourtChemin (int aNumCaseDepart, int aNumCaseArrivee, std::list<int>& aPlusCourtChemin);
   
   void AfficherMatrice (void);

private:
   int mMatriceGraph [NB_CASE_LARGEUR * NB_CASE_HAUTEUR][NB_CASE_LARGEUR * NB_CASE_HAUTEUR];

   CPlateau& mPlateau;
};

#endif