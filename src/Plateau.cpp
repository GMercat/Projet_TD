#include "Plateau.h"
#include "Jeu.h"



CPlateau::CPlateau (CConfiguration& aConfig, CJeu& aJeu):
   mLog                    ("Plateau"),
   mConfig                 (aConfig),
   mJeu                    (aJeu),
   mNumCaseDepart          (-1),
   mNumCaseArrivee         (-1),
   mDerniereCaseSurvolee   (-1)
// TODO Non utilisé    mpImagePCC     (NULL)
{
	mCoordonneesDerniereCaseModifiee.first = -1;
   mCoordonneesDerniereCaseModifiee.second = -1;
}

CPlateau::~CPlateau (void)
{
   ;
   // TODO Non utilisé SDL_FreeSurface (mpImagePCC);
}

bool CPlateau::OnInit (void)
{
   bool bReturn = true;

   std::string NomRessourceImageStr;
   std::string CheminRessourcesImageStr;
   int         IterImage = 0;

   bool bConfig = true;
   bConfig &= mConfig.Get ("nbCaseLargeur",     mNbCasesLargeur);
   bConfig &= mConfig.Get ("nbCaseHauteur",     mNbCasesHauteur);
   bConfig &= mConfig.Get ("numeroCaseDepart",  mNumCaseDepart);
   bConfig &= mConfig.Get ("numeroCaseArrivee", mNumCaseArrivee);
   bConfig &= mConfig.Get ("largeurCase",       mLargeurCase);
   bConfig &= mConfig.Get ("hauteurCase",       mHauteurCase);
   bConfig &= mConfig.Get ("ressourcesImages",  CheminRessourcesImageStr);

   bConfig &= mConfig.GetRessourcesCases (mNomImagesCase);
   bConfig &= mConfig.GetRessourcesTours (mNomImagesTour);
  
   if (bConfig)
   {

      // Allocation des surfaces des cases
      for (IterImage = 0; IterImage < mNomImagesCase.size (); ++IterImage)
      {
         CImage::Ptr ImageCourantePtr (new CImage (CheminRessourcesImageStr));
         
         ImageCourantePtr->Load (mNomImagesCase[IterImage]);
         
         mImagesCases.push_back (ImageCourantePtr);
      }

      // Allocation des surfaces des tours
      for (IterImage = 0; IterImage < mNomImagesTour.size (); ++IterImage)
      {
         CImage::Ptr ImageCourantePtr (new CImage (CheminRessourcesImageStr));
         
         ImageCourantePtr->Load (mNomImagesTour[IterImage]);
         
         mImagesTours.push_back (ImageCourantePtr);
      }

      // TODO Non utilisé 
      /*if(mpImagePCC != NULL)
      {
         SDL_FreeSurface(mpImagePCC), mpImagePCC = NULL;
      }
      if ((mLargeurCase == 50) && (mHauteurCase == 50))
      {
         mpImagePCC  = SDL_LoadBMP("../../Ressources/PCC_50.bmp");
      }*/
            
      std::string NomFichier ("JeuPause.bmp");
      mImagePausePtr = CImage::Ptr (new CImage (CheminRessourcesImageStr));
      mImagePausePtr->Load        (NomFichier);
      mImagePausePtr->SetAlpha    (128);
      
	   //Mis en place de la transparence
	   //if(SDL_SetColorKey(o,SDL_SRCCOLORKEY,0)==-1)
	   //	mLog << Erreur << "Erreur avec la transparence du rond" << EndLine;
	   //if(SDL_SetColorKey(x,SDL_SRCCOLORKEY,0)==-1)
	   //	mLog << Erreur << "Erreur avec la transparence de la croix" << EndLine;

      SDL_Rect	Rect;

	   Rect.w = mLargeurCase;
	   Rect.h = mHauteurCase;

      mLog << Debug << "Largeur = " << mNbCasesLargeur << ", Hauteur = " << mNbCasesHauteur << EndLine;
      mLog << Debug << "NbCaseLargeur = " << mNbCasesLargeur << EndLine;
      mLog << Debug << "NbCaseHauteur = " << mNbCasesHauteur << EndLine;
      mLog << Debug << "NumCaseDepart = " << mNumCaseDepart << EndLine;
      mLog << Debug << "NumCaseArrivee = " << mNumCaseArrivee << EndLine;
      
      int NumCase = 0;

	   // Initialisation du plateau
      for (int iHauteur = 0; iHauteur < mNbCasesHauteur; iHauteur++)
		{
	      for (int iLargeur = 0; iLargeur < mNbCasesLargeur; iLargeur++)
	      {
            NumCase = iLargeur + (mNbCasesLargeur * iHauteur);

		      CCase::Ptr CasePtr (new CCase());

			   CasePtr->OnInit ();
			   Rect.x = iLargeur * mLargeurCase;
			   Rect.y = iHauteur * mHauteurCase;
			   CasePtr->SetPosition  (&Rect, iLargeur, iHauteur);
            CasePtr->SetNumCase   (NumCase);

			   if ((iLargeur == 0) || (iLargeur == (mNbCasesLargeur - 1)) || (iHauteur == 0) || (iHauteur == (mNbCasesHauteur -1)))
			   {
			      if ((NumCase != mNumCaseDepart) && (NumCase != mNumCaseArrivee))
			      {
				      CasePtr->SetType (CCase::eMur);
				   }
			   }
            mCases.push_back (CasePtr);
		   }
	   }
   }
   else
   {
      bReturn = false;

      mLog << Erreur << "Erreur de lecture de la configuration du plateau" << EndLine;
   }

   return bReturn;
}

void CPlateau::OnReset (void)
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
            if ((NumCase != mNumCaseDepart) && (NumCase != mNumCaseArrivee))
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
   int IterLargeur = 0;
   int IterHauteur = 0;

   //Dessiner chaque case
   for(IterHauteur = 0; IterHauteur < mNbCasesHauteur; IterHauteur++)
   {
      for(IterLargeur = 0; IterLargeur < mNbCasesLargeur; IterLargeur++)
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

void CPlateau::OnAfficheEnPause (CSurface::Ptr& aEcranPtr)
{
   SDL_Rect Position;
   Position.x = 0;
   Position.y = 0;
   Position.w = mNbCasesLargeur * mLargeurCase;
   Position.h = mNbCasesHauteur * mHauteurCase;
      
   mImagePausePtr->Afficher (aEcranPtr, Position);
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

CCase::Ptr& CPlateau::GetCase (int aNumCase)
{
   int IterHauteur = aNumCase / mNbCasesLargeur;
   int IterLargeur = aNumCase % mNbCasesLargeur;
   return mCases[IterHauteur * mNbCasesLargeur + IterLargeur];
}

CCase::Ptr& CPlateau::GetCase (int aX, int aY)
{
   return mCases[aY * mNbCasesLargeur + aX];
}

void CPlateau::GetCoordonneesCaseParNumero (int aNumero, TCoordonnee& aCoordonnees)
{
   int IterHauteur = aNumero / mNbCasesLargeur;
   int IterLargeur = aNumero % mNbCasesLargeur;
   
   mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetCentre (aCoordonnees.first, aCoordonnees.second);

}

int CPlateau::GetNumCaseParCoordonnees (TCoordonnee& aCoordonnees)
{
   int IndexCaseX = aCoordonnees.first  / mLargeurCase;
   int IndexCaseY = aCoordonnees.second / mHauteurCase;

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
