#include "Jeu.h"
#include "IA.h"
#include <cmath>
#include <ctime>

CJeu::CJeu (CIA* apIA):
   mLog                    ("Jeu"),
   mpIA                    (apIA),
   mPlateau                (mConfig, *this),
   mMenu                   (mConfig, *this),
	mHauteur                (1),
	mLargeur                (1),
	mbPremiereTour          (true),
   mbPartieEnCours         (true),
   mTempsInterVague        (1),
   mTypeTourSelect         (-1)
{
   ;
}

CJeu::~CJeu (void)
{
   ;
}

bool CJeu::OnInit (void)
{
   // initialisation de rand
   srand((unsigned int)time(NULL));

   // Lecture du fichier de configuration
   mConfig.Chargement ("../../conf/ConfJeu.txt");

	bool bReturn = mPlateau.OnInit ();
   bReturn &= mMenu.OnInit ();

   bReturn &= mConfig.Get ("tempsInterVague", mTempsInterVague);

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
      NumCaseCliquee = mPlateau.OnClic (aX, aY);
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
         // Construction de la tour dans la case
         CTour::Ptr NouvelleTour = mPlateau.ConstruireTour (NumCaseCliquee);
         mListTour.push_back (NouvelleTour);

         // Première tour posée ?
         if (mbPremiereTour)
         {
            mTimerVague.Start ();
            
            mbPremiereTour = false;
         }
      }
      else
      {
         mLog << Erreur << "Placement non autorisé" << EndLine;
         mPlateau.AnnuleDerniereModif ();
         mpIA->MiseAJourMatriceGraphe (NumCaseCliquee, false);
      }
   }
}

void CJeu::OnAffiche (CSurface::Ptr& aScreenPtr)
{
   // Affichage du menu
   mMenu.   OnAffiche (aScreenPtr);

   // Affichage du plateau
   mPlateau.OnAffiche (aScreenPtr);
   
   // Affichage des ennemis
   CVagueEnnemis::Liste::iterator IterVague;
   for (IterVague = mListVagues.begin (); IterVague != mListVagues.end (); IterVague++)
   {
      (*IterVague)->OnAffiche (aScreenPtr);
   }

   // Affichage des projectiles
   CTour::Liste::iterator IterTourTiree = mListTourTiree.begin ();
   for (IterTourTiree; IterTourTiree != mListTourTiree.end (); ++IterTourTiree)
   {
      (*IterTourTiree)->OnAfficheProjectiles (aScreenPtr);
   }

   if (false == mbPartieEnCours)
   {
      mPlateau.OnAfficheEnPause (aScreenPtr);
   }
}

void CJeu::OnReset   (void)
{
   mTypeTourSelect = -1;
   mListVagues    .clear ();
   mListTour      .clear ();
   mListTourTiree .clear ();
   mPlateau.OnReset ();
   mpIA->OnInit ();
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
   ProgressionProjectiles ();

   // Progression des ennemis
   ProgressionEnnemis ();
}

void CJeu::ProgressionProjectiles (void)
{
   CTour::Liste::iterator IterTourTiree    = mListTourTiree.begin ();
   CTour::Liste::iterator IterTourTireeEnd = mListTourTiree.end ();
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
}

void CJeu::ProgressionEnnemis (void)
{
   // Lancement d'une vague d'ennemis
   if (LancementNouvelleVagueEnnemisPossible ())
   {
      LancementVagueEnnemis ();
      
      // On relance le timer de lancement de vague
      mTimerVague.Start ();   
   }

   CVagueEnnemis::Liste::iterator   IterVagues     = mListVagues.begin ();
   CVagueEnnemis::Liste::iterator   IterVaguesEnd  = mListVagues.end ();

   while (IterVagues != IterVaguesEnd)
   {
      (*IterVagues)->ProgressionEnnemis ();

      if ((*IterVagues)->EstVide ())
      {
         IterVagues = mListVagues.erase (IterVagues);
      }
      else
      {
         IterVagues++;
      }
   }
}

bool CJeu::LancementNouvelleVagueEnnemisPossible (void)
{
   bool bLancement = false;

   int TickCourant = mTimerVague.GetNbTicks ();
   
   // Vérifie que le timer est lancé (que la tour a tirée)
   if (TickCourant != 0)
   {
      // Vérifie la possibilité de tirer
      if ((TickCourant) >= (mTempsInterVague * 1000))
      {
         bLancement = true;
      }
   }

   return bLancement;
}

void CJeu::LancementVagueEnnemis (void)
{
   // Création de la nouvelle vague d'ennemis
   // TODO : Type d'ennemi en paramètre
   CVagueEnnemis::Ptr NouvelleVague (new CVagueEnnemis (mPlateau.GetNumCaseDepart (), mPlateau.GetNumCaseArrivee ()/*TypeEnnemi, nbEnnemis*/));

   // On l'ajoute
   mListVagues.push_back (NouvelleVague);
}

void CJeu::OnTire (void)
{
   int XTour = 0;
   int Ytour = 0;
   bool bEnnemiTrouve   = false;
   TCoordonnee CoordonneeCentreTour;

   CEnnemi::Ptr   EnnemiSelectionnePtr;

   // Gestion des tires des tours
   CTour::Liste::iterator           IterTour;
   CVagueEnnemis::Liste::iterator   IterVague;

   // Parcours des tours pour rechercher les ennemis à la porté
   for (IterTour = mListTour.begin (); IterTour != mListTour.end (); ++IterTour)
   {
      // Si la tour peut tirer
      if ((*IterTour)->AutoriseATirer ())
      {
         // Récupération des positions de la tour
         (*IterTour)->GetCentre (XTour, Ytour);
         CoordonneeCentreTour.first  = XTour;
         CoordonneeCentreTour.second = Ytour;

         for (IterVague = mListVagues.begin (); (IterVague != mListVagues.end ()) && (false == bEnnemiTrouve); ++IterVague)
         {
            bEnnemiTrouve = (*IterVague)->SelectionneEnnemi (CoordonneeCentreTour, (*IterTour)->GetPorteeTire (), EnnemiSelectionnePtr);
         }

         if (bEnnemiTrouve && EnnemiSelectionnePtr)
         {
            (*IterTour)->Tire (EnnemiSelectionnePtr);
            mListTourTiree.push_back ((*IterTour));
         }

         
      }
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
   
   std::list<int> PlusCourtChemin;
   bEstAutorise = mpIA->CalculPlusCourtChemin (mPlateau.GetNumCaseDepart (), mPlateau.GetNumCaseArrivee (), PlusCourtChemin);
   
   // Parcours la liste des vagues d'ennemis afin de vérifier le placement de la tour
   CVagueEnnemis::Liste::iterator IterVague;
   for (IterVague = mListVagues.begin (); (IterVague != mListVagues.end ()) && (bEstAutorise); IterVague++)
   {
      bEstAutorise &= (*IterVague)->PlacementEstAutorise (mPlateau.GetNumCaseArrivee ());
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
