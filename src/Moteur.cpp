#include "../include/Moteur.h"

CMoteur::CMoteur (void):
   mIA (mJeu.GetPlateau ()),
   mJeu (&mIA)
{
	;
}

CMoteur::~CMoteur (void)
{
	;
}

bool CMoteur::OnInit (void)
{
	bool bReturn = false;
     
	bReturn  = mJeu.OnInit ();

   mIA.ConstruireMatriceGraphe ();
   //mIA.CalculPlusCourtChemin ();
   
	return bReturn;
}

void CMoteur::OnClic (int aX, int aY)
{
   bool bAutorisePlacementTour = false;

#ifdef DEBUG
	std::cout << "Moteur.OnClic (" << aX << ", " << aY << ")" << std::endl;
#endif
	mJeu.OnClic (aX, aY);

   mIA.ConstruireMatriceGraphe ();

   // Vérification de la possibilité de poser la tour
   bAutorisePlacementTour = mJeu.PlacementEstAutorise ();
   //bPlusCourtChemintrouvee = mIA.CalculPlusCourtChemin ();

   if (false == bAutorisePlacementTour)
   {
      mJeu.AnnuleDerniereModif ();
   }
}

void CMoteur::OnAffiche (SDL_Surface* apScreen)
{
	mJeu.OnAffiche (apScreen);
}

void CMoteur::handle_input(SDL_Event* apEvent)
{
	// Capture d'un appuis clavier
}
