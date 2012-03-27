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

void CJeu::OnClic (int aX, int aY)
{
   bool bCaseTrouve = false;
   int IterLargeur  = 0;
   int IterHauteur  = 0;

   if (mbPartieEnCours)
   {
      // TODO Calcul direct de la case avec les X et Y
      //On parcourt tout le plateau pour trouver la case associée
      for (	 IterLargeur;
            (IterLargeur < mLargeur) && (false == bCaseTrouve);
             IterLargeur++)
      {
         for (	IterHauteur = 0;
               (IterHauteur < mHauteur) && (false == bCaseTrouve);
               IterHauteur++)
         {
            //Si le clic a touché cette case
            if (mPlateau.GetCase(IterLargeur, IterHauteur)->EstDedans(aX, aY))
            {
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
      }
   }


   if (false == bCaseTrouve)
   {
      mMenu.OnClic (aX, aY);
   }
}

void CJeu::OnAffiche (SDL_Surface* apScreen)
{
   // Affichage du menu
   mMenu.   OnAffiche (apScreen);

   // Affichage du plateau
   mPlateau.OnAffiche (apScreen);
   
   // Affichage des ennemis
   std::list<CEnnemi>::iterator IterEnnemi;
   for (IterEnnemi = mListEnnemi.begin (); IterEnnemi != mListEnnemi.end (); IterEnnemi++)
   {

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
   std::list<CEnnemi>::iterator IterEnnemi;
   for (IterEnnemi = mListEnnemi.begin (); IterEnnemi != mListEnnemi.end (); IterEnnemi++)
   {

   }
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

   std::vector<int> PlusCourtChemin;
   // Parcours la liste des ennemis afin de vérifier le placement de la tour
   std::list <CEnnemi>::iterator IterEnnemi;
   for (IterEnnemi = mListEnnemi.begin (); (IterEnnemi != mListEnnemi.end ()) && (bEstAutorise); IterEnnemi++)
   {
      PlusCourtChemin.clear ();
      bEstAutorise = mpIA->CalculPlusCourtChemin ((*IterEnnemi).DetermineCaseCourante (), mPlateau.GetNumCaseArrivee (), PlusCourtChemin);
      (*IterEnnemi).SetPCCheminCase (PlusCourtChemin);
   }

   return bEstAutorise;
}

void CJeu::AnnuleDerniereModif (void)
{
   mPlateau.GetCase (mCoordonneesDerniereCaseModifiee.first, mCoordonneesDerniereCaseModifiee.second)->SetEtat (CCase::eVide);
   mPlateau.GetCase (mCoordonneesDerniereCaseModifiee.first, mCoordonneesDerniereCaseModifiee.second)->SetPlusCourtChemin (
      mPlateau.GetCase (mCoordonneesDerniereCaseModifiee.first, mCoordonneesDerniereCaseModifiee.second)->EstPlusCourtChemin ());
}

CCase::EEtat CJeu::GetTourSelectionnee  (void)
{
   return mTypeTourSelect;
}

void CJeu::SelectTour (CCase::EEtat aTypeTourSelect)
{
   mTypeTourSelect = aTypeTourSelect;
}
