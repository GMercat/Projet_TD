#include "../include/Moteur.h"

CMoteur::CMoteur (void):
   mLog     ("Moteur"),
   mIA      (mJeu.GetPlateau ()),
   mJeu     (&mIA)
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

   if (bReturn)
   {
      mIA.OnInit ();

      mScreenPtr.reset (new CFenetre ());
      bReturn = mScreenPtr->Init (mJeu.GetLargeur (), mJeu.GetHauteur ());
      
      mIA.ConstruireMatriceGraphe ();
      mJeu.PlacementEstAutorise ();
   }

	return bReturn;
}

void CMoteur::OnQuit (void)
{
	SDL_Quit();
}

void CMoteur::OnClic (int aX, int aY)
{
   mJeu.OnClic (aX, aY);
}

void CMoteur::OnMotion (int aX, int aY)
{
   // Si on survole le plateau et si une tour est sélectionnée
   if (mJeu.GetPlateau ().EstDansPlateau (aX, aY) && (mJeu.GetTourSelectionnee () != -1))
   {
      mJeu.GetPlateau ().OnSurvoleCase (aX, aY);
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

void CMoteur::OnAffiche (void)
{
	mJeu.OnAffiche (mScreenPtr->GetSurface ());
   mScreenPtr->Flip ();
}

void CMoteur::handle_input(SDL_Event* apEvent)
{
	// Capture d'un appuis clavier
}
