#include "Plateau.h"
#include "Jeu.h"



CPlateau::CPlateau (CConfiguration& aConfig, CJeu& aJeu):
   mLog                    ("Plateau"),
   mConfig                 (aConfig),
   mJeu                    (aJeu),
   mNumCaseDepart          (-1),
   mNumCaseArrivee         (-1),
   mDerniereCaseSurvolee   (-1)
{
	mCoordonneesDerniereCaseModifiee.first = -1;
   mCoordonneesDerniereCaseModifiee.second = -1;
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
   bConfig &= mConfig.Get ("largeurCase",       mLargeurCase);
   bConfig &= mConfig.Get ("hauteurCase",       mHauteurCase);
   bConfig &= mConfig.Get ("ressourcesImages",  CheminRessourcesImageStr);

   if (bConfig)
   {
      std::string NomFichier ("JeuPause.bmp");
      mImagePausePtr = CImage::Ptr (new CImage (CheminRessourcesImageStr));
      mImagePausePtr->Load        (NomFichier);
      mImagePausePtr->SetAlpha    (128);

      mLog << Debug << "NumCaseDepart = " << mNumCaseDepart << EndLine;
      mLog << Debug << "NumCaseArrivee = " << mNumCaseArrivee << EndLine;
      
      int NumCase = 0;

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

int CPlateau::OnClic (int aX, int aY)
{
   int NumeroCaseCliquee = -1;
   int IterLargeur = 0;
   int IterHauteur = 0;

   mCoordonneesDerniereCaseModifiee.first    = -1;
   mCoordonneesDerniereCaseModifiee.second   = -1;

   // Test si on est sur le plateau
   if(EstDansPlateau (aX, aY))
   {
      IterLargeur = (int)(aX / mLargeurCase);
      IterHauteur = (int)(aY / mHauteurCase);
      
      //On renseigne le numéro de la case que l'on a trouvé
      NumeroCaseCliquee = IterHauteur * mNbCasesLargeur + IterLargeur;

      mLog << Info << "Case (" << IterLargeur << ", " << IterHauteur << ")" << EndLine;

      // Si la case est vide ET on a sélectionnée un type de tour dans le menu
      if (GetCase(NumeroCaseCliquee)->EstVide() && (mJeu.GetTourSelectionnee () != -1))
      {
         //On met le type à jour
         GetCase(NumeroCaseCliquee)->SetType (CCase::eTour);

         mCoordonneesDerniereCaseModifiee.first    = IterLargeur;
         mCoordonneesDerniereCaseModifiee.second   = IterHauteur;
      }
   }

   return NumeroCaseCliquee;
}

void CPlateau::OnAffiche (CSurface::Ptr& aEcranPtr)
{
   mTerrain.OnAffiche (aEcranPtr);
}

void CPlateau::OnAfficheEnPause (CSurface::Ptr& aEcranPtr)
{
   CRect::Ptr PositionPtr (new CRect ());
   PositionPtr->SetX (0);
   PositionPtr->SetY (0);
   PositionPtr->SetW (mNbCasesLargeur * mLargeurCase);
   PositionPtr->SetH (mNbCasesHauteur * mHauteurCase);
      
   mImagePausePtr->Afficher (aEcranPtr, PositionPtr);
}

void CPlateau::OnSurvoleCase (int aX, int aY)
{
   int IterLargeur = (int)(aX / mLargeurCase);
   int IterHauteur = (int)(aY / mHauteurCase);
      
   //On renseigne le numéro de la case que l'on a trouvé
   int NumeroCaseSurvolee = IterHauteur * mNbCasesLargeur + IterLargeur;

   mLog << Erreur << "CaseSurvolée (" << IterLargeur << ", " << IterHauteur << ") = " << NumeroCaseSurvolee << EndLine;

   if (NumeroCaseSurvolee != mDerniereCaseSurvolee)
   {
      if (mDerniereCaseSurvolee != -1)
      {
         GetCase(mDerniereCaseSurvolee)->MarqueSurvolee (false);
      }

      // Si la case est vide
      if (GetCase(NumeroCaseSurvolee)->EstVide())
      {
         //On met le type à jour
         GetCase(NumeroCaseSurvolee)->MarqueSurvolee (true);
      }

      mDerniereCaseSurvolee = NumeroCaseSurvolee;
   }
}

// Test si on est sur le plateau
bool CPlateau::EstDansPlateau (int aX, int aY)
{
   return (aX < (mNbCasesLargeur * mLargeurCase)) && (aY < (mNbCasesHauteur * mHauteurCase));
}

CTour::Ptr& CPlateau::ConstruireTour (int aNumCaseCliquee)
{
   std::string Ressource; // Non utilisé ici !
   int Portee;
   int Puissance;
   int Vitesse;
   int Cadence;

   mConfig.GetCaracsTourParId (mJeu.GetTourSelectionnee (), Ressource, Portee, Puissance, Vitesse, Cadence);
   return GetCase (aNumCaseCliquee)->ConstruireTour (mConfig, mJeu.GetTourSelectionnee (), Portee, Puissance, Vitesse, Cadence);
}

void CPlateau::AnnuleDerniereModif (void)
{
   if (mCoordonneesDerniereCaseModifiee.first != -1 && mCoordonneesDerniereCaseModifiee.second != -1)
   {
      GetCase (mCoordonneesDerniereCaseModifiee.first, mCoordonneesDerniereCaseModifiee.second)->SetType (CCase::eVide);
      GetCase (mCoordonneesDerniereCaseModifiee.first, mCoordonneesDerniereCaseModifiee.second)
         ->SetPlusCourtChemin (GetCase (mCoordonneesDerniereCaseModifiee.first, mCoordonneesDerniereCaseModifiee.second)->EstPlusCourtChemin ());
   }
}

int CPlateau::GetNbCaseLargeur (void)
{
   return mNbCasesLargeur;
}

int CPlateau::GetNbCaseHauteur (void)
{
   return mNbCasesHauteur;
}

int CPlateau::GetLargeurCase   (void)
{
   return mLargeurCase;
}

int CPlateau::GetHauteurCase   (void)
{
   return mHauteurCase;
}

void CPlateau::GetCoordonneesCaseParNumero (int aNumero, TCoordonnee& aCoordonnees)
{
   int IterHauteur = aNumero / mNbCasesLargeur;
   int IterLargeur = aNumero % mNbCasesLargeur;
   
   mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetCentre (aCoordonnees);

}

int CPlateau::GetNumCaseParCoordonnees (TCoordonnee& aCoordonnees)
{
   int IndexCaseX = aCoordonnees.mX / mLargeurCase;
   int IndexCaseY = aCoordonnees.mY / mHauteurCase;

   return IndexCaseY * mNbCasesLargeur + IndexCaseX;
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
