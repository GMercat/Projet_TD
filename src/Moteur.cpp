#include "Moteur.h"

CMoteur::CMoteur (void):
   mLog     ("Moteur")
{
	;
}

CMoteur::~CMoteur (void)
{
	;
}

bool CMoteur::OnInit (void)
{
   return mJeu.OnInit ();
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
	mJeu.OnAffiche ();
}

void CMoteur::OnInputEvent (SDL_Event* apEvent)
{
	// Capture d'un appuis clavier
}
