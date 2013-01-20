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

void CMoteur::OnClic (const TCoordonnee& aCoordonneeClic)
{
   mJeu.OnClic (aCoordonneeClic);
}

void CMoteur::OnMotion (const TCoordonnee& aCoordonneeSouri)
{
   // Si on survole le plateau et si une tour est sélectionnée
   // TODO a revoir/refaire autrement... Directement dans la classe CJeu
   if (mJeu.GetPlateau ().EstDansPlateau (aCoordonneeSouri) && (mJeu.GetTourSelectionnee () != -1))
   {
      mJeu.GetPlateau ().OnSurvoleCase (aCoordonneeSouri);
   }
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
