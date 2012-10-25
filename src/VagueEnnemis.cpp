#include "VagueEnnemis.h"
#include "IA.h"

// TODO TEMPORAIRE A REFAIRE
#define NB_ENNEMI_VAGUE       5
#define TPS_BASE_INTER_ENNEMI 750

CVagueEnnemis::CVagueEnnemis (int aNumCaseDepart, int aNumCaseArrivee /*TypeEnnemi, nbEnnemis*/):
   mNbEnnemis           (NB_ENNEMI_VAGUE),
   mTempsProchainEnnemi (0),
   mNumCaseDepart       (aNumCaseDepart),
   mNumCaseArrivee      (aNumCaseArrivee)
{
   mTimerEnnemi.Start ();
   // TODO : Type d'ennemi en paramètre
   AjoutEnnemi (/*TypeEnnemi*/);
   mTempsProchainEnnemi = rand() % TPS_BASE_INTER_ENNEMI;
}

CVagueEnnemis::~CVagueEnnemis (void)
{

}

bool CVagueEnnemis::EstVide (void)
{
   return mListEnnemis.empty ();
}

void CVagueEnnemis::OnAffiche (CSurface::Ptr& aScreenPtr)
{
   CEnnemi::Liste::iterator IterEnnemi;
   for (IterEnnemi = mListEnnemis.begin (); IterEnnemi != mListEnnemis.end (); IterEnnemi++)
   {
      (*IterEnnemi)->OnAffiche (aScreenPtr);
   }
}

void CVagueEnnemis::ProgressionEnnemis (void)
{
   CEnnemi::Liste::iterator IterEnnemi    = mListEnnemis.begin ();
   CEnnemi::Liste::iterator IterEnnemiEnd = mListEnnemis.end ();
   
   while (IterEnnemi != IterEnnemiEnd)
   {
      if ((*IterEnnemi)->EstArrive () || (false == (*IterEnnemi)->EstVivant ()))
      {
         IterEnnemi = mListEnnemis.erase (IterEnnemi);
      }
      else
      {
         ++IterEnnemi;
      }
   }
}

void CVagueEnnemis::AjoutEnnemi (void)
{
   std::list<int> PlusCourtChemin;

   CEnnemi::Ptr EnnemiPtr (new CEnnemi(mConfig, mpIA, CEnnemi::eType1, mNumCaseDepart, mNumCaseArrivee));
   
   EnnemiPtr->OnInit ();
   
   mpIA->CalculPlusCourtChemin (EnnemiPtr->DetermineCaseCourante (), mNumCaseArrivee, PlusCourtChemin);
   EnnemiPtr->SetPCCheminCase (PlusCourtChemin);

   mListEnnemis.push_back (EnnemiPtr);
}

bool CVagueEnnemis::PlacementEstAutorise  (int aNumCaseArrivee)
{
   bool bEstAutorise = true;
   
   std::list<int> PlusCourtChemin;

   // Parcours la liste des ennemis afin de vérifier le placement d'une tour
   CEnnemi::Liste::iterator IterEnnemi;
   for (IterEnnemi = mListEnnemis.begin (); (IterEnnemi != mListEnnemis.end ()) && (bEstAutorise); IterEnnemi++)
   {
      PlusCourtChemin.clear ();
      bEstAutorise &= mpIA->CalculPlusCourtChemin ((*IterEnnemi)->DetermineCaseCourante (), aNumCaseArrivee, PlusCourtChemin);
      (*IterEnnemi)->SetPCCheminCase (PlusCourtChemin);
   }

   return bEstAutorise;
}


bool CVagueEnnemis::SelectionneEnnemi (TCoordonnee& aCoordonneesTour, int aPorteeTour, CEnnemi::Ptr& aEnnemiSelectionnePtr)
{
   bool bEnnemiTrouve = false;

   int DistanceEnnemi = 0;
   TCoordonnee CoordonneeEnnemi;

   aEnnemiSelectionnePtr.reset ();

   CEnnemi::Liste::iterator   IterEnnemi;
   for (IterEnnemi = mListEnnemis.begin (); (IterEnnemi != mListEnnemis.end ()) && (false == bEnnemiTrouve); ++IterEnnemi)
   {
      // TODO Selectionner l'ennemi le plus avancé ?
      // Récupération des positions de l'ennemi
      (*IterEnnemi)->GetCentre (CoordonneeEnnemi);

      DistanceEnnemi = (int)sqrt ( (double)((aCoordonneesTour.mX - CoordonneeEnnemi.mX) * (aCoordonneesTour.mX - CoordonneeEnnemi.mX))
                                 + (double)((aCoordonneesTour.mY - CoordonneeEnnemi.mY) * (aCoordonneesTour.mY - CoordonneeEnnemi.mY)));

      // Détermine si l'ennemi est à la porté de la tour
      if (aPorteeTour > DistanceEnnemi)
      {
         aEnnemiSelectionnePtr = (*IterEnnemi);

         bEnnemiTrouve = true;
      }
   }

   return bEnnemiTrouve;
}
