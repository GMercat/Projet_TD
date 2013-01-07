#include "Jeu.h"

CJeu::CJeu (void):
   mLog                    ("Jeu"),
   mPlateau                (mConfig, mContexte),
   mIA                     (mPlateau),
   mMenu                   (mConfig, mContexte),
	mHauteur                (1),
	mLargeur                (1),
	mbPremiereTour          (true),
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

   mScreenPtr.reset (new CFenetre ());
   
   bool bContinue = mConfig.Get ("tempsInterVague", mTempsInterVague);
   if (bContinue)
   {
      bContinue = mPlateau.OnInit ();
   }
   if (bContinue)
   {
      bContinue = mMenu.OnInit ();
   }
   if (bContinue)
   {
      mHauteur = mPlateau.GetNbCaseHauteur () * mPlateau.GetHauteurCase ();
      mLargeur = mPlateau.GetNbCaseLargeur () * mPlateau.GetLargeurCase () + mMenu.GetLargeur ();
   }   
   if (bContinue)
   {
      bContinue = mScreenPtr->Init (mLargeur, mHauteur);
   }
   if (bContinue)
   {
      mIA.OnInit ();

      mIA.ConstruireMatriceGraphe ();
      PlacementEstAutorise (); // TODO Renommer ?
   }

  	return bContinue;
}

void CJeu::OnClic (int aX, int aY)
{
   int   NumCaseCliquee = -1;
   int   IterLargeur    = 0;
   int   IterHauteur    = 0;

   if (mContexte.mbPartieEnCours)
   {
      NumCaseCliquee = mPlateau.OnClic (aX, aY);
   }

   if (NumCaseCliquee == -1)
   {
      mMenu.OnClic (aX, aY);
   }
   else
   {
      mIA.MiseAJourMatriceGraphe (NumCaseCliquee, true);
      
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
         mIA.MiseAJourMatriceGraphe (NumCaseCliquee, false);
      }
   }
}

void CJeu::OnAffiche (void)
{
   // Affichage du menu
   mMenu.   OnAffiche (mScreenPtr->GetSurface ());

   // Affichage du plateau
   mPlateau.OnAffiche (mScreenPtr->GetSurface ());
   
   // Affichage des ennemis
   CVagueEnnemis::Liste::iterator IterVague;
   for (IterVague = mListVagues.begin (); IterVague != mListVagues.end (); IterVague++)
   {
      (*IterVague)->OnAffiche (mScreenPtr->GetSurface ());
   }

   // Affichage des projectiles
   CTour::Liste::iterator IterTourTiree = mListTourTiree.begin ();
   for (IterTourTiree; IterTourTiree != mListTourTiree.end (); ++IterTourTiree)
   {
      (*IterTourTiree)->OnAfficheProjectiles (mScreenPtr->GetSurface ());
   }

   if (false == mContexte.mbPartieEnCours)
   {
      mPlateau.OnAfficheEnPause (mScreenPtr->GetSurface ());
   }

   mScreenPtr->Flip ();
}

void CJeu::OnReset   (void)
{
   mTypeTourSelect = -1;
   mListVagues    .clear ();
   mListTour      .clear ();
   mListTourTiree .clear ();
   mPlateau.OnReset ();
   mIA.OnInit ();
}

void CJeu::OnQuit (void)
{
   SDL_Event Event;

   Event.type = SDL_QUIT;
   SDL_PushEvent (&Event);
}

void CJeu::OnProgression   (void)
{
   if (mContexte.mbPartieEnCours)
   {
      // Progression des projectiles
      ProgressionProjectiles ();

      // Progression des ennemis
      ProgressionEnnemis ();
   }
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
   CVagueEnnemis::Ptr NouvelleVague (new CVagueEnnemis (mConfig, &mIA, mPlateau.GetNumCaseDepart (), mPlateau.GetNumCaseArrivee ()/*TypeEnnemi, nbEnnemis*/));

   // On l'ajoute
   mListVagues.push_back (NouvelleVague);
}

void CJeu::OnTire (void)
{
   if (mContexte.mbPartieEnCours)
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
            (*IterTour)->GetCentre (CoordonneeCentreTour);

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
}

void CJeu::TraiteDemande (void)
{
   if (mContexte.mbDemandeQuit)
   {
      OnQuit ();
   }
   else if (mContexte.mbDemandeReset)
   {
      OnReset ();
   }
}

CPlateau& CJeu::GetPlateau (void)
{
   return mPlateau;
}

bool CJeu::PlacementEstAutorise  (void)
{
   bool bEstAutorise = true;
   
   std::list<int> PlusCourtChemin;
   bEstAutorise = mIA.CalculPlusCourtChemin (mPlateau.GetNumCaseDepart (), mPlateau.GetNumCaseArrivee (), PlusCourtChemin);
   
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
