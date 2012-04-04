#include "../include/Jeu.h"

#include "../include/IA.h"

CJeu::CJeu (CIA* apIA):
   mpIA              (apIA),
   mMenu             (*this),
   mPlateau          (*this),
	mHauteur          (NB_CASE_HAUTEUR),
	mLargeur          (NB_CASE_LARGEUR),
   mbPartieEnCours   (true),
   mTypeTourSelect   (CCase::eVide)
{
	mCoordonneesDerniereCaseModifiee.first = -1;
   mCoordonneesDerniereCaseModifiee.second = -1;
}

CJeu::~CJeu (void)
{
 ;
}

bool CJeu::OnInit (void)
{
	bool bReturn = mPlateau.OnInit ();
   bReturn |= mMenu.OnInit ();

  	return bReturn;
}

int CJeu::OnClic (int aX, int aY)
{
   int TickEnd = 0;
   int TickStart = SDL_GetTicks();

   int NumCase = -1;
   bool bCaseTrouve = false;
   int IterLargeur  = 0;
   int IterHauteur  = 0;

   if (mbPartieEnCours)
   {
      // Test si on est sur le plateau
      if((aX < (NB_CASE_LARGEUR * LARGEUR_CASE)) && aY < (NB_CASE_HAUTEUR * HAUTEUR_CASE))
      {
         IterLargeur = (int)(aX / LARGEUR_CASE);
         IterHauteur = (int)(aY / HAUTEUR_CASE);

#ifdef DEBUG
         std::cout << "Case (" << IterLargeur << ", " << IterHauteur << ")" << std::endl;
#endif

         //Si la case est vide
         if (mPlateau.GetCase(IterLargeur, IterHauteur)->EstVide())
         {
            //On met le type à jour
            mPlateau.GetCase(IterLargeur, IterHauteur)->SetEtat (mTypeTourSelect);
            mCoordonneesDerniereCaseModifiee.first    = IterLargeur;
            mCoordonneesDerniereCaseModifiee.second   = IterHauteur;
         }

         //On dit qu'on a trouvé la case associé
         bCaseTrouve = true;
      }
   }

   if (false == bCaseTrouve)
   {
      mMenu.OnClic (aX, aY);
   }
   else
   {
      NumCase = mPlateau.GetCase(IterLargeur, IterHauteur)->GetNumCase ();
   }

   return NumCase;
}

void CJeu::OnAffiche (SDL_Surface* apScreen)
{
   // Affichage du menu
   mMenu.   OnAffiche (apScreen);

   // Affichage du plateau
   mPlateau.OnAffiche (apScreen);
   
   // Affichage des ennemis
   std::list<CEnnemiPtr>::iterator IterEnnemi;
   for (IterEnnemi = mListEnnemi.begin (); IterEnnemi != mListEnnemi.end (); IterEnnemi++)
   {
      (*IterEnnemi)->OnAffiche (apScreen);
   }
}

void CJeu::OnReset   (void)
{
   mTypeTourSelect = CCase::eVide;
   mPlateau.OnReset ();
}

void CJeu::OnQuit (void)
{
   SDL_Event Event;

   Event.type = SDL_QUIT;
   SDL_PushEvent (&Event);
}

void CJeu::OnProgression   (void)
{
   std::list<CEnnemiPtr>::iterator IterEnnemi = mListEnnemi.begin ();
   std::list<CEnnemiPtr>::iterator IterEnnemiEnd = mListEnnemi.end ();
   while (IterEnnemi != IterEnnemiEnd)
   {
      (*IterEnnemi)->Avance ();

      if ((*IterEnnemi)->EstArrive ())
      {
         IterEnnemi = mListEnnemi.erase (IterEnnemi);
      }
      else
      {
         ++IterEnnemi;
      }
   }
}

void CJeu::OnTire (void)
{
   // Gestion des tires des tours
}

void CJeu::AjoutEnnemi (void)
{
   std::list<int> PlusCourtChemin;

   CEnnemiPtr EnnemiPtr (new CEnnemi(mpIA, mPlateau.GetNumCaseDepart (), mPlateau.GetNumCaseArrivee ()));
   
   EnnemiPtr->OnInit ();
   
   mpIA->CalculPlusCourtChemin (EnnemiPtr->DetermineCaseCourante (), mPlateau.GetNumCaseArrivee (), PlusCourtChemin);
   EnnemiPtr->SetPCCheminCase (PlusCourtChemin);

   mListEnnemi.push_back (EnnemiPtr);
}

CPlateau& CJeu::GetPlateau (void)
{
   return mPlateau;
}

bool CJeu::PartieEnCours (void)
{
   return mbPartieEnCours;
}

void CJeu::ChangerEtatPartie (bool abEtatPartie)
{
   mbPartieEnCours = abEtatPartie;
}

bool CJeu::PlacementEstAutorise  (void)
{
   bool bEstAutorise = true;
   
   std::list<int> PlusCourtChemin;
   bEstAutorise = mpIA->CalculPlusCourtChemin (mPlateau.GetNumCaseDepart (), mPlateau.GetNumCaseArrivee (), PlusCourtChemin);
   
   PlusCourtChemin.clear ();
   // Parcours la liste des ennemis afin de vérifier le placement de la tour
   std::list <CEnnemiPtr>::iterator IterEnnemi;
   for (IterEnnemi = mListEnnemi.begin (); (IterEnnemi != mListEnnemi.end ()) && (bEstAutorise); IterEnnemi++)
   {
      PlusCourtChemin.clear ();
      bEstAutorise &= mpIA->CalculPlusCourtChemin ((*IterEnnemi)->DetermineCaseCourante (), mPlateau.GetNumCaseArrivee (), PlusCourtChemin);
      (*IterEnnemi)->SetPCCheminCase (PlusCourtChemin);
   }

   return bEstAutorise;
}

void CJeu::AnnuleDerniereModif (void)
{
   mPlateau.GetCase (mCoordonneesDerniereCaseModifiee.first, mCoordonneesDerniereCaseModifiee.second)->SetEtat (CCase::eVide);
   mPlateau.GetCase (mCoordonneesDerniereCaseModifiee.first, mCoordonneesDerniereCaseModifiee.second)->SetPlusCourtChemin (
   mPlateau.GetCase (mCoordonneesDerniereCaseModifiee.first, mCoordonneesDerniereCaseModifiee.second)->EstPlusCourtChemin ());
}

CCase::ETypeCase CJeu::GetTourSelectionnee  (void)
{
   return mTypeTourSelect;
}

void CJeu::SelectTour (CCase::ETypeCase aTypeTourSelect)
{
   mTypeTourSelect = aTypeTourSelect;
}
