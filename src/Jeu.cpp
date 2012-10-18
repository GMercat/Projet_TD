#include "Jeu.h"
#include "IA.h"
#include <cmath>
#include <ctime>

#define NB_ENNEMI_VAGUE       5
#define TPS_BASE_INTER_ENNEMI 750

CJeu::CJeu (CIA* apIA):
   mLog                 ("Jeu"),
   mpIA                 (apIA),
   mPlateau             (mConfig, *this),
   mMenu                (mConfig, *this),
	mHauteur             (1),
	mLargeur             (1),
	mbPremiereTour       (true),
   mbPartieEnCours      (true),
   mTempsInterVague     (1),
   mDerniereVagueLancee (-1),
   mNumVagueEnCours     (-1),
   mNbEnnemisVague      (NB_ENNEMI_VAGUE),
   mTypeTourSelect      (-1)
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
   srand(time(NULL));

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
   CEnnemi::Liste::iterator IterEnnemi;
   for (IterEnnemi = mListEnnemi.begin (); IterEnnemi != mListEnnemi.end (); IterEnnemi++)
   {
      (*IterEnnemi)->OnAffiche (aScreenPtr);
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
   mListEnnemi    .clear ();
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
      mNumVagueEnCours = mDerniereVagueLancee + 1;

      mLog << Info << "Lancement de la " << mNumVagueEnCours << "ieme vague d'ennemis" << EndLine;
      
      LancementVagueEnnemis ();
      
      // On relance le timer de lancement de vague
      mTimerVague.Start ();   
   }

   // Si une vague est en cours de lancement on continue
   if (mNumVagueEnCours != -1)
   {
      // Est ce que l'on doit ajouter un ennemi ?
      // Tous les ennemis n'ont pas encore été créé ET le temps depuis le dernier est suffisament grand.
      if ((mNbEnnemisVague >= 0) && (mTimerEnnemi.GetNbTicks () >= mTempsProchainEnnemi))
      {
         // TODO : Type d'ennemi en paramètre
         AjoutEnnemi ();
         mNbEnnemisVague--;
         mTempsProchainEnnemi = rand() % TPS_BASE_INTER_ENNEMI;
         mTimerEnnemi.Start ();
      }
      else if (mNbEnnemisVague < 0)
      {
         mNbEnnemisVague = NB_ENNEMI_VAGUE;
         mNumVagueEnCours = -1;
      }
   }

   CEnnemi::Liste::iterator IterEnnemi = mListEnnemi.begin ();
   CEnnemi::Liste::iterator IterEnnemiEnd = mListEnnemi.end ();
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
   mTimerEnnemi.Start ();
   // TODO : Type d'ennemi en paramètre
   AjoutEnnemi ();
   mNbEnnemisVague--;
   mTempsProchainEnnemi = rand() % TPS_BASE_INTER_ENNEMI;
   mDerniereVagueLancee++;
}

void CJeu::OnTire (void)
{
   int DistanceEnnemi   = 0;
   int XTour            = 0;
   int Ytour            = 0;
   int XEnnemi          = 0;
   int YEnnemi          = 0;
   bool bTourATiree     = false;

   // Gestion des tires des tours
   CTour::Liste::iterator    IterTour;
   CEnnemi::Liste::iterator  IterEnnemi;

   // Parcours des tours pour rechercher les ennemis à la porté
   for (IterTour = mListTour.begin (); IterTour != mListTour.end (); ++IterTour)
   {
      // Si la tour peut tirer
      if ((*IterTour)->AutoriseATirer ())
      {
         for (IterEnnemi = mListEnnemi.begin (); (IterEnnemi != mListEnnemi.end ()) && (false == bTourATiree); ++IterEnnemi)
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

               bTourATiree = true;
            }
         }
      }
   }
}

void CJeu::AjoutEnnemi (void)
{
   std::list<int> PlusCourtChemin;

   CEnnemi::Ptr EnnemiPtr (new CEnnemi(mConfig, mpIA, CEnnemi::eType1, mPlateau.GetNumCaseDepart (), mPlateau.GetNumCaseArrivee ()));
   
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
   CEnnemi::Liste::iterator IterEnnemi;
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
