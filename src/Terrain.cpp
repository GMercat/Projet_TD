#include "Terrain.h"

CTerrain::CTerrain (CConfiguration& aConfig):
   mConfig         (aConfig),
   mNbCasesHauteur (1),
   mNbCasesLargeur (1)
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

   bConfig  = mConfig.Get ("nbCaseLargeur", mNbCasesLargeur);
   bConfig &= mConfig.Get ("nbCaseHauteur", mNbCasesHauteur);
   bConfig &= mConfig.Get ("ressourcesImages",  CheminRessourcesImageStr);
   bConfig &= mConfig.GetRessourcesCases (mNomImagesCase);
   bConfig &= mConfig.GetRessourcesTours (mNomImagesTour);

   if (bConfig)
   {
      // Allocation des surfaces des cases
      for (int IterImage = 0; IterImage < mNomImagesCase.size (); ++IterImage)
      {
         CImage::Ptr ImageCourantePtr (new CImage (CheminRessourcesImageStr));

         ImageCourantePtr->Load (mNomImagesCase[IterImage]);

         mImagesCases.push_back (ImageCourantePtr);
      }

      // Allocation des surfaces des tours
      for (int IterImage = 0; IterImage < mNomImagesTour.size (); ++IterImage)
      {
         CImage::Ptr ImageCourantePtr (new CImage (CheminRessourcesImageStr));

         ImageCourantePtr->Load (mNomImagesTour[IterImage]);

         mImagesTours.push_back (ImageCourantePtr);
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
   //Dessiner chaque case
   for (int IterHauteur = 0; IterHauteur < mNbCasesHauteur; IterHauteur++)
   {
      for (int IterLargeur = 0; IterLargeur < mNbCasesLargeur; IterLargeur++)
      {
         // TODO Affichage Plus Court Chemin
         /*if (mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->EstPlusCourtChemin ())
         {
             mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->OnAffiche (apEcran, mpImagePCC);
         }
         else*/
         {
            //       Les surfaces ne sont pas les mêmes !
            CCase::ETypeCase EtatCase = mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetType ();
            if (EtatCase == CCase::eTour)
            {
               int TypeCase = mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetTypeTour ();
               mImagesTours[TypeCase]->Afficher (aEcranPtr, mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetPosition ());
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
}

CCase::Ptr& CTerrain::GetCase (int aX, int aY)
{
   return mCases[aY * mNbCasesLargeur + aX];
}

