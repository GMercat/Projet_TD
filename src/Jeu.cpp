#include "../include/Jeu.h"
#include "../include/IA.h"
#include <cmath>

CJeu::CJeu (CIA* apIA):
   mpIA              (apIA),
   mPlateau          (mConfig, *this),
   mMenu             (mConfig, *this),
	mHauteur          (1),
	mLargeur          (1),
   mbPartieEnCours   (true),
   mTypeTourSelect   (-1)
{
   ;
}

CJeu::~CJeu (void)
{
 ;
}

bool CJeu::OnInit (void)
{
   // Lecture du fichier de configuration
   mConfig.Chargement ("../conf/ConfJeu.txt");

	bool bReturn = mPlateau.OnInit ();
   bReturn |= mMenu.OnInit ();

   mHauteur = mPlateau.GetNbCaseHauteur () * mPlateau.GetHauteurCase ();
   mLargeur = mPlateau.GetNbCaseLargeur () * mPlateau.GetLargeurCase () + mMenu.GetLargeur ();

  	return bReturn;
}

void CJeu::OnClic (int aX, int aY)
{
   int   NumCaseCliquee = -1;
   int   IterLargeur    = 0;
   int   IterHauteur    = 0;

   if (mbPartieEnCours)
   {
      // TODO 
      NumCaseCliquee = mPlateau.OnClic (aX, aY);
/*
      // Test si on est sur le plateau
      if((aX < (mPlateau.GetNbCaseLargeur () * LARGEUR_CASE)) && aY < (mPlateau.GetNbCaseHauteur () * HAUTEUR_CASE))
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
*/
   }

   if (NumCaseCliquee == -1)
   {
      mMenu.OnClic (aX, aY);
   }
   else
   {
      mpIA->MiseAJourMatriceGraphe (NumCaseCliquee, true);

      // Vérification de la possibilité de poser la tour en parcourant les listes des ennemis
      if (PlacementEstAutorise ())
      {
         // AjoutTour (NumCase);
         // Construction de la tour dans la case
         CTourPtr NouvelleTour = mPlateau.ConstruireTour (NumCaseCliquee);
         mListTour.push_back (NouvelleTour);
      }
      else
      {
         std::cout << "Placement non autorisé" << std::endl;
         mPlateau.AnnuleDerniereModif ();
         mpIA->MiseAJourMatriceGraphe (NumCaseCliquee, false);
      }
   }
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

   // Affichage des projectiles
   std::list<CTourPtr>::iterator IterTourTiree = mListTourTiree.begin ();
   for (IterTourTiree; IterTourTiree != mListTourTiree.end (); ++IterTourTiree)
   {
      (*IterTourTiree)->OnAfficheProjectiles (apScreen);
   }

   if (false == mbPartieEnCours)
   {
      mPlateau.OnAfficheEnPause (apScreen);
   }
}

void CJeu::OnReset   (void)
{
   mTypeTourSelect = -1;
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
   // Progression des projectiles
   std::list<CTourPtr>::iterator IterTourTiree    = mListTourTiree.begin ();
   std::list<CTourPtr>::iterator IterTourTireeEnd = mListTourTiree.end ();
   while (IterTourTiree != IterTourTireeEnd)
   {
      if (false == (*IterTourTiree)->OnAvanceProjectiles ())
      {
         IterTourTiree = mListTourTiree.erase (IterTourTiree);
      }
      else
      {
         ++IterTourTiree;
      }
   }

   // Progression des ennemis
   std::list<CEnnemiPtr>::iterator IterEnnemi = mListEnnemi.begin ();
   std::list<CEnnemiPtr>::iterator IterEnnemiEnd = mListEnnemi.end ();
   while (IterEnnemi != IterEnnemiEnd)
   {
      (*IterEnnemi)->Avance ();

      if ((*IterEnnemi)->EstArrive () || (false == (*IterEnnemi)->EstVivant ()))
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
   int DistanceEnnemi   = 0;
   int XTour            = 0;
   int Ytour            = 0;
   int XEnnemi          = 0;
   int YEnnemi          = 0;

   // Gestion des tires des tours
   std::list<CTourPtr>::iterator    IterTour;
   std::list<CEnnemiPtr>::iterator  IterEnnemi;

   // Parcours des tours pour rechercher les ennemis à la porté
   for (IterTour = mListTour.begin (); IterTour != mListTour.end (); ++IterTour)
   {
      // Si la tour peut tirer
      if ((*IterTour)->AutoriseATirer ())
      {
         for (IterEnnemi = mListEnnemi.begin (); IterEnnemi != mListEnnemi.end (); ++IterEnnemi)
         {
            // TODO Selectionner l'ennemi le plus avancé ?
            // Récupération des positions de l'ennemi et de la tour
            (*IterTour)->GetCentre (XTour, Ytour);
            (*IterEnnemi)->GetCentre (XEnnemi, YEnnemi);

            DistanceEnnemi = (int)sqrt ((double)((XTour   - XEnnemi) * (XTour - XEnnemi))
                                       + (double)((Ytour - YEnnemi) * (Ytour - YEnnemi)));

            // Détermine si l'ennemi est à la porté de la tour
            if ((*IterTour)->GetPorteeTire () > DistanceEnnemi)
            {
               (*IterTour)->Tire (*IterEnnemi);
               mListTourTiree.push_back ((*IterTour));
            }
         }
      }
   }
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
/*
void CJeu::AjoutTour (int aNumCase)
{
   mListTour.push_back (mPlateau.GetCase(aNumCase));
}*/

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

int CJeu::GetTourSelectionnee  (void)
{
   return mTypeTourSelect;
}

void CJeu::SelectTour (int aTypeTourSelect)
{
   mTypeTourSelect = aTypeTourSelect;
}

int CJeu::GetHauteur (void)
{
   return mHauteur;
}

int CJeu::GetLargeur (void)
{
   return mLargeur;
}


