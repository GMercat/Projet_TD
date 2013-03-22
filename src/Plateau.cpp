#include "Plateau.h"
#include "ContexteJeu.h"



CPlateau::CPlateau (CConfiguration& aConfig, CContexteJeu& aContexte):
   mLog                    ("Plateau"),
   mConfig                 (aConfig),
   mContexte               (aContexte),
   mTerrain                (aConfig),
   mDerniereCaseSurvolee   (-1),
   mNumCaseDepart          (-1),
   mNumCaseArrivee         (-1)
{
}

CPlateau::~CPlateau (void)
{
   ;
}

bool CPlateau::OnInit (void)
{
   bool bConfig = true;

   std::string CheminRessourcesImageStr;

   bConfig &= mConfig.Get ("numeroCaseDepart",  mNumCaseDepart);
   bConfig &= mConfig.Get ("numeroCaseArrivee", mNumCaseArrivee);

   if (bConfig)
   {
      mLog << Debug << "NumCaseDepart = " << mNumCaseDepart << EndLine;
      mLog << Debug << "NumCaseArrivee = " << mNumCaseArrivee << EndLine;
      
	   // Initialisation du terrain
      mTerrain.OnInit (mNumCaseDepart, mNumCaseArrivee);
   }
   else
   {
      mLog << Erreur << "Erreur de lecture de la configuration du plateau" << EndLine;
   }

   return bConfig;
}

void CPlateau::OnReset (void)
{
   mTerrain.OnReset (mNumCaseDepart, mNumCaseArrivee);
}

int CPlateau::OnClic (const TCoordonnee& aCoordonneeClic)
{
   int NumCaseCliquee = -1;
      
   // Test si on est sur le plateau
   if(EstDansPlateau (aCoordonneeClic))
   {
      NumCaseCliquee = mTerrain.OnClic (aCoordonneeClic, mContexte.mTypeTourSelectMenu);
   }

   return NumCaseCliquee;
}

void CPlateau::OnAffiche (CSurface::Ptr& aEcranPtr)
{
   mTerrain.OnAffiche (aEcranPtr);
}

void CPlateau::OnAfficheEnPause (CSurface::Ptr& aEcranPtr)
{
   mTerrain.OnAfficheEnPause (aEcranPtr);
}

void CPlateau::OnSurvoleCase (const TCoordonnee& aCoordonnee)
{
   //On renseigne le numéro de la case que l'on a trouvé
   int NumeroCaseSurvolee = mTerrain.CoordonneeToNum (aCoordonnee);

   mLog << Erreur << "Case n: " << NumeroCaseSurvolee << " survolée" << EndLine;

   if (NumeroCaseSurvolee != mDerniereCaseSurvolee)
   {
      if (mDerniereCaseSurvolee != -1)
      {
         mTerrain.GetCase (aCoordonnee)->MarqueSurvolee (false);
      }

      // Si la case est vide
      if (mTerrain.GetCase(aCoordonnee)->EstVide())
      {
         //On met le type à jour
         mTerrain.GetCase(aCoordonnee)->MarqueSurvolee (true);
      }

      mDerniereCaseSurvolee = NumeroCaseSurvolee;
   }
}

// Test si on est sur le plateau
bool CPlateau::EstDansPlateau (const TCoordonnee& aCoordonneeClic)
{
   return (aCoordonneeClic.mX < (mTerrain.GetLargeur ())) && (aCoordonneeClic.mY < (mTerrain.GetHauteur ()));
}

bool CPlateau::EstCaseVide (int aIndexLargeur, int aIndexHauteur)
{
   TIndexTableau IndexCase (aIndexLargeur, aIndexHauteur);

   return mTerrain.EstCaseVide (IndexCase);
}

CTour::Ptr& CPlateau::ConstruireTour (int aNumCaseCliquee)
{
   return mTerrain.ConstruireTour (mContexte.mTypeTourSelectMenu, aNumCaseCliquee);
}

void CPlateau::AnnuleDerniereModif (void)
{
   mTerrain.AnnuleDerniereModif ();
}

int CPlateau::GetNbCaseLargeur (void)
{
   return mTerrain.GetNbCaseLargeur ();
}

int CPlateau::GetNbCaseHauteur (void)
{
   return mTerrain.GetNbCaseHauteur ();
}

int CPlateau::GetLargeurCase   (void)
{
   return mTerrain.GetLargeurCase ();
}

int CPlateau::GetHauteurCase   (void)
{
   return mTerrain.GetHauteurCase ();
}

void CPlateau::GetCoordonneesCentreCaseCaseParNumero (int aNumCase, TCoordonnee& aCoordonnees)
{
   mTerrain.GetCoordonneesCentreCaseCaseParNumero (aNumCase, aCoordonnees);
}

int CPlateau::GetNumCaseParCoordonnees (TCoordonnee& aCoordonnees)
{
   return mTerrain.CoordonneeToNum (aCoordonnees);
}

int CPlateau::GetNumCaseDepart  (void)
{
   return mNumCaseDepart;
}

int CPlateau::GetNumCaseArrivee (void)
{
   return mNumCaseArrivee;
}
/*
void CPlateau::RenseignePlusCourtChemin (std::vector<int>& aPlusCourtChemin)
{
   int IterHauteur = 0;
   int IterLargeur = 0;
   for(IterHauteur = 0; IterHauteur < mNbCasesHauteur; IterHauteur++)
   {
      for(IterLargeur = 0; IterLargeur < mNbCasesLargeur; IterLargeur++)
      {
         mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->SetPlusCourtChemin (false);
      }
   }
   
   std::vector<int>::iterator IterPlusCourtChemin = aPlusCourtChemin.begin ();
   for (IterPlusCourtChemin; IterPlusCourtChemin != aPlusCourtChemin.end (); IterPlusCourtChemin++)
   {
      IterHauteur = (*IterPlusCourtChemin) / mNbCasesLargeur;
      IterLargeur = (*IterPlusCourtChemin) % mNbCasesLargeur;
      mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->SetPlusCourtChemin (true);
   }
}
*/
