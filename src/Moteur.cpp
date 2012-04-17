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
   mJeu.PlacementEstAutorise ();

	return bReturn;
}

void CMoteur::OnClic (int aX, int aY)
{
   bool bAutorisePlacementTour = false;

#ifdef DEBUG
	std::cout << "Moteur.OnClic (" << aX << ", " << aY << ")" << std::endl;
#endif
	
   int NumCase = mJeu.OnClic (aX, aY);

   if (NumCase != -1)
   {
      mIA.MiseAJourMatriceGraphe (NumCase, true);

      // Vérification de la possibilité de poser la tour en parcourant les listes des ennemis
      bAutorisePlacementTour = mJeu.PlacementEstAutorise ();

      if (bAutorisePlacementTour)
      {
         mJeu.AjoutTour (NumCase);
      }
      else
      {
         std::cout << "Placement non autorisé" << std::endl;
         mJeu.AnnuleDerniereModif ();
         mIA.MiseAJourMatriceGraphe (NumCase, false);
      }
   }
}

void CMoteur::OnProgression   (void)
{
   if (mJeu.PartieEnCours ())
   {
      mJeu.OnProgression ();
   }
}

void CMoteur::OnTire (void)
{
   if (mJeu.PartieEnCours ())
   {
      mJeu.OnTire ();
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
