#include "Terrain.h"

CTerrain::CTerrain (CConfiguration& aConfig):
   mLog              ("Terrain"),
   mConfig           (aConfig),
   mNbCasesHauteur   (1),
   mNbCasesLargeur   (1)
{
   ;
}

CTerrain::~CTerrain (void)
{
   ;
}

void CTerrain::OnInit (int aNumCaseDepart, int aNumCaseArrivee)
{
   bool        bConfig = false;
   int         NumCase = 0;
   std::string NomRessourceImageStr;
   std::string CheminRessourcesImageStr;

   bConfig  = mConfig.Get ("nbCaseLargeur",     mNbCasesLargeur);
   bConfig &= mConfig.Get ("nbCaseHauteur",     mNbCasesHauteur);
   bConfig &= mConfig.Get ("largeurCase",       mLargeurCase);
   bConfig &= mConfig.Get ("hauteurCase",       mHauteurCase);
   bConfig &= mConfig.Get ("ressourcesImages",  CheminRessourcesImageStr);
   bConfig &= mConfig.GetRessourcesCases (mNomImagesCase);

   if (bConfig)
   {
      std::string NomFichier ("JeuPause.bmp");
      mImagePausePtr = CImage::Ptr (new CImage (CheminRessourcesImageStr));
      mImagePausePtr->Load        (NomFichier);
      mImagePausePtr->SetAlpha    (128);

      // Allocation des surfaces des cases
      for (unsigned int IterImage = 0; IterImage < mNomImagesCase.size (); ++IterImage)
      {
         CImage::Ptr ImageCourantePtr (new CImage (CheminRessourcesImageStr));

         ImageCourantePtr->Load (mNomImagesCase[IterImage]);

         mImagesCases.push_back (ImageCourantePtr);
      }
   }

   for (int iHauteur = 0; iHauteur < mNbCasesHauteur; iHauteur++)
   {
      for (int iLargeur = 0; iLargeur < mNbCasesLargeur; iLargeur++)
      {
         NumCase = iLargeur + (mNbCasesLargeur * iHauteur);

         CCase::Ptr CasePtr (new CCase());
         CRect::Ptr  RectPtr (new CRect ());

         CasePtr->OnInit ();

         RectPtr->SetW (mLargeurCase);
         RectPtr->SetH (mHauteurCase);
         RectPtr->SetX (iLargeur * mLargeurCase);
         RectPtr->SetY (iHauteur * mHauteurCase);
         CasePtr->SetPosition  (RectPtr, iLargeur, iHauteur);
         CasePtr->SetNumCase   (NumCase);

         if ((iLargeur == 0) || (iLargeur == (mNbCasesLargeur - 1)) || (iHauteur == 0) || (iHauteur == (mNbCasesHauteur -1)))
         {
            if ((NumCase != aNumCaseDepart) && (NumCase != aNumCaseArrivee))
            {
               CasePtr->SetType (CCase::eMur);
            }
         }
         mCases.push_back (CasePtr);
      }
   }
}

void CTerrain::OnReset (int aNumCaseDepart, int aNumCaseArrivee)
{
   int NumCase = 0;

   // Initialisation du plateau
   for (int iHauteur = 0; iHauteur < mNbCasesHauteur; iHauteur++)
   {
      for (int iLargeur = 0; iLargeur < mNbCasesLargeur; iLargeur++)
      {
         NumCase = iHauteur * mNbCasesLargeur + iLargeur;

         // Initialisation de la case
         mCases[NumCase]->OnInit ();

         if ((iLargeur == 0) || (iLargeur == (mNbCasesLargeur - 1)) || (iHauteur == 0) || (iHauteur == (mNbCasesHauteur -1)))
         {
            if ((NumCase != aNumCaseDepart) && (NumCase != aNumCaseArrivee))
            {
               mCases[NumCase]->SetType (CCase::eMur);
            }
         }
         else
         {
            mCases[NumCase]->SetType (CCase::eVide);
         }
      }
   }
}

void CTerrain::OnAffiche (CSurface::Ptr& aEcranPtr)
{
   // Dessiner chaque case
   for (int IterHauteur = 0; IterHauteur < mNbCasesHauteur; IterHauteur++)
   {
      for (int IterLargeur = 0; IterLargeur < mNbCasesLargeur; IterLargeur++)
      {
         // Les surfaces ne sont pas les mêmes !
         CCase::ETypeCase EtatCase = mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetType ();
         if (EtatCase == CCase::eTour)
         {
            int TypeCase = mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetTypeTour ();
            mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->OnAffiche (aEcranPtr);
         }
         else
         {
            if (mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->EstSurvolee ())
            {
               // TODO Image survolee
            }
            else
            {
               mImagesCases[EtatCase]->Afficher (aEcranPtr, mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetPosition ());
            }
         }
      }
   }
}

void CTerrain::OnAfficheEnPause (CSurface::Ptr& aEcranPtr)
{
   CRect::Ptr PositionPtr (new CRect ());
   PositionPtr->SetX (0);
   PositionPtr->SetY (0);
   PositionPtr->SetW (mNbCasesLargeur * mLargeurCase);
   PositionPtr->SetH (mNbCasesHauteur * mHauteurCase);
      
   mImagePausePtr->Afficher (aEcranPtr, PositionPtr);
}

int CTerrain::OnClic (const TCoordonnee& aCoordonneeClic, int aTypeTourSelectMenu)
{
   bool bCaseTrouvee = false;

   // Cas 1 : la case est vide et un type de tour est sélectionné dans le menu
   if (GetCase(aCoordonneeClic)->EstVide() && (aTypeTourSelectMenu != -1))
   {
      //On met le type à jour
      GetCase(aCoordonneeClic)->SetType (CCase::eTour);

      mIndexDerniereCaseModifiee = GetCase(aCoordonneeClic)->GetIdPlateau ();
   }

   // Cas 2 : la case contient une tour, on l'upgrade (TODO gestion des fonds dispo !)
   else if (false == GetCase (aCoordonneeClic)->EstVide ())
   {
      // TODO upgrade
      mIndexDerniereCaseModifiee = GetCase(aCoordonneeClic)->GetIdPlateau ();
   }

   mLog << Info << "Case (" << mIndexDerniereCaseModifiee.mIndLargeur << ", " << mIndexDerniereCaseModifiee.mIndHauteur << ")" << EndLine;

   return IndexToNum (mIndexDerniereCaseModifiee);
}

CTour::Ptr& CTerrain::ConstruireTour (int aTypeTourSelectMenu, int aNumCaseCliquee)
{
   return mCases [aNumCaseCliquee]->ConstruireTour (mConfig, aTypeTourSelectMenu);
}

void CTerrain::AnnuleDerniereModif (void)
{
   if (mIndexDerniereCaseModifiee.mIndLargeur != -1 && mIndexDerniereCaseModifiee.mIndHauteur != -1)
   {
      GetCase (mIndexDerniereCaseModifiee)->SetType (CCase::eVide);
      GetCase (mIndexDerniereCaseModifiee)->SetPlusCourtChemin (GetCase (mIndexDerniereCaseModifiee)->EstPlusCourtChemin ());
   }
}

bool CTerrain::EstCaseVide (const TIndexTableau& aIndexCase)
{
   return mCases[IndexToNum (aIndexCase)]->EstVide ();
}

CCase::Ptr& CTerrain::GetCase (const TCoordonnee& aCoordonneeClic)
{
   return mCases[CoordonneeToNum (aCoordonneeClic)];
}

CCase::Ptr& CTerrain::GetCase (const TIndexTableau& aIndexCase)
{
   return mCases[aIndexCase.mIndHauteur * mNbCasesLargeur + aIndexCase.mIndLargeur];
}

int CTerrain::GetLargeur (void)
{
   return mNbCasesLargeur * mLargeurCase;
}

int CTerrain::GetHauteur (void)
{
   return mNbCasesHauteur * mHauteurCase;
}

int CTerrain::GetNbCaseLargeur (void)
{
   return mNbCasesLargeur;
}

int CTerrain::GetNbCaseHauteur (void)
{
   return mNbCasesHauteur;
}

int CTerrain::GetLargeurCase (void)
{
   return mLargeurCase;
}

int CTerrain::GetHauteurCase (void)
{
   return mHauteurCase;
}

void CTerrain::GetCoordonneesCentreCaseCaseParNumero (int aNumCase, TCoordonnee& aCoordonnees)
{
   int IterHauteur = aNumCase / mNbCasesLargeur;
   int IterLargeur = aNumCase % mNbCasesLargeur;
   
   mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetCentre (aCoordonnees);
}

int CTerrain::CoordonneeToNum (const TCoordonnee& aCoordonnee)
{
   TIndexTableau IndexTableau;
   IndexTableau.mIndLargeur = aCoordonnee.mX / mLargeurCase;
   IndexTableau.mIndHauteur = aCoordonnee.mY / mHauteurCase;

   return (IndexToNum (IndexTableau));
}

int CTerrain::IndexToNum (const TIndexTableau& aIndexPlateau)
{
   return aIndexPlateau.mIndLargeur + aIndexPlateau.mIndHauteur * mNbCasesLargeur;
}