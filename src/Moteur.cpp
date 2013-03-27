#include "Moteur.h"

CMoteur::CMoteur (void):
   mLogger     ("Moteur")
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

void CMoteur::OnClic (const TCoordonnee& aCoordonneeClic)
{
   mJeu.OnClic (aCoordonneeClic);
}

void CMoteur::OnMotion (const TCoordonnee& aCoordonneeSouri)
{
   mJeu.OnSurvole (aCoordonneeSouri);
}

void CMoteur::OnProgression   (void)
{
   mJeu.OnProgression ();
}

void CMoteur::OnTire (void)
{
   mJeu.OnTire ();
}

void CMoteur::OnAffiche (void)
{
	mJeu.OnAffiche ();
}

void CMoteur::OnInputEvent (SDL_Event* apEvent)
{
	// Capture d'un appuis clavier
}

void CMoteur::OnDemande (void)
{
   mJeu.TraiteDemande ();
   //TODO
}
