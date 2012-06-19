#include "../include/Plateau.h"
#include "../include/Jeu.h"



CPlateau::CPlateau (CConfiguration& aConfig, CJeu& aJeu):
   mConfig        (aConfig),
   mJeu           (aJeu),
   mNumCaseDepart (-1),
   mNumCaseArrivee(-1)
//   mpImagePause   (NULL)
// TODO Non utilisé    mpImagePCC     (NULL)
{
	mCoordonneesDerniereCaseModifiee.first = -1;
   mCoordonneesDerniereCaseModifiee.second = -1;
}

CPlateau::~CPlateau (void)
{
   ;
/*   std::vector<SDL_Surface*>::iterator IterImage;
   for (IterImage = mImagesCases.begin (); IterImage != mImagesCases.end (); ++IterImage)
   {
      SDL_FreeSurface (*IterImage);
   }
   for (IterImage = mImagesTours.begin (); IterImage != mImagesTours.end (); ++IterImage)
   {
      SDL_FreeSurface (*IterImage);
   }*/

//   SDL_FreeSurface (mpImagePause);
   // TODO Non utilisé SDL_FreeSurface (mpImagePCC);
}

bool CPlateau::OnInit (void)
{
   bool bReturn = true;

   std::string NomRessourceImageStr;
   int         IterImage = 0;

   bool bConfig = true;
   bConfig &= mConfig.Get ("nbCaseLargeur",     mNbCasesLargeur);
   bConfig &= mConfig.Get ("nbCaseHauteur",     mNbCasesHauteur);
   bConfig &= mConfig.Get ("numeroCaseDepart",  mNumCaseDepart);
   bConfig &= mConfig.Get ("numeroCaseArrivee", mNumCaseArrivee);
   bConfig &= mConfig.Get ("largeurCase",       mLargeurCase);
   bConfig &= mConfig.Get ("hauteurCase",       mHauteurCase);

   bConfig &= mConfig.GetRessourcesCases (mNomImagesCase);
   bConfig &= mConfig.GetRessourcesTours (mNomImagesTour);
  
   if (bConfig)
   {

      // Allocation des surfaces des cases
      for (IterImage = 0; IterImage < mNomImagesCase.size (); ++IterImage)
      {
         CImagePtr ImageCourantePtr (new CImage ());
         
         ImageCourantePtr->Load (mNomImagesCase[IterImage]);
         
         mImagesCases.push_back (ImageCourantePtr);
         
/*         (*IterImage) = NULL;
         
         //On charge toutes les images dans les surfaces associées
         std::string CheminRessource ("../ressources/");
         CheminRessource += mNomImagesCase[iImage];
         
         (*IterImage) = SDL_LoadBMP(CheminRessource.c_str ());
                  
         //On teste le retour du chargement
	      if ((*IterImage) == NULL)
	      {
            std::cout << "Probleme de chargement de l'image : " << (mNomImagesCase[iImage]).c_str () << "(" << CheminRessource.c_str () << ")" << std::endl;
		      bReturn = false;
	      }
         iImage++;*/
      }

      // Allocation des surfaces des tours
      for (IterImage = 0; IterImage < mNomImagesTour.size (); ++IterImage)
      {
         CImagePtr ImageCourantePtr (new CImage ());
         
         ImageCourantePtr->Load (mNomImagesTour[IterImage]);
         
         mImagesTours.push_back (ImageCourantePtr);
      
/*         (*IterImage) = NULL;
         
         //On charge toutes les images dans les surfaces associées
         std::string CheminRessource ("../ressources/");
         CheminRessource += mNomImagesTour[iImage];
         
         (*IterImage) = SDL_LoadBMP(CheminRessource.c_str ());
                  
         //On teste le retour du chargement
	      if ((*IterImage) == NULL)
	      {
            std::cout << "Probleme de chargement de l'image : " << (mNomImagesTour[iImage]).c_str () << "(" << CheminRessource.c_str () << ")" << std::endl;
		      bReturn = false;
	      }
         iImage++;*/
      }

      // TODO Non utilisé 
      /*if(mpImagePCC != NULL)
      {
         SDL_FreeSurface(mpImagePCC), mpImagePCC = NULL;
      }
      if ((mLargeurCase == 50) && (mHauteurCase == 50))
      {
         mpImagePCC  = SDL_LoadBMP("../Ressources/PCC_50.bmp");
      }*/
            
      std::string NomFichier ("JeuPause.bmp");
      mImagePausePtr = CImagePtr (new CImage ());
      mImagePausePtr->Load        (NomFichier);
      mImagePausePtr->SetAlpha    (128);
      
//      if(mpImagePause != NULL)
//      {
//         SDL_FreeSurface(mpImagePause), mpImagePause = NULL;
//      }   
//      mpImagePause = SDL_LoadBMP("../ressources/JeuPause.bmp");
   
//	   //On teste le retour du chargement
//	   if (mpImagePause == NULL)
//	   {
//		   std::cout << "Probleme de chargement des images" << std::endl;
//		   bReturn = false;
//	   }

	   //Mis en place de la transparence
	   //if(SDL_SetColorKey(o,SDL_SRCCOLORKEY,0)==-1)
	   //	std::cout << "Erreur avec la transparence du rond" << std::endl;
	   //if(SDL_SetColorKey(x,SDL_SRCCOLORKEY,0)==-1)
	   //	std::cout << "Erreur avec la transparence de la croix" << std::endl;

//      SDL_SetAlpha (mpImagePause, SDL_SRCALPHA, 128);

      SDL_Rect	Rect;

	   Rect.w = mLargeurCase;
	   Rect.h = mHauteurCase;

#ifdef DEBUG
      std::cout << "Largeur = " << mNbCasesLargeur << ", Hauteur = " << mNbCasesHauteur << std::endl;
      std::cout << "NbCaseLargeur = " << mNbCasesLargeur << std::endl;
      std::cout << "NbCaseHauteur = " << mNbCasesHauteur << std::endl;
      std::cout << "NumCaseDepart = " << mNumCaseDepart << std::endl;
      std::cout << "NumCaseArrivee = " << mNumCaseArrivee << std::endl;
#endif
      
      int NumCase = 0;

	   // Initialisation du plateau
      for (int iHauteur = 0; iHauteur < mNbCasesHauteur; iHauteur++)
		{
	      for (int iLargeur = 0; iLargeur < mNbCasesLargeur; iLargeur++)
	      {
            NumCase = iLargeur + (mNbCasesLargeur * iHauteur);

		      CCasePtr CasePtr (new CCase());

			   CasePtr->OnInit ();
			   Rect.x = iLargeur * mLargeurCase;
			   Rect.y = iHauteur * mHauteurCase;
			   CasePtr->SetPosition  (&Rect, iLargeur, iHauteur);
            CasePtr->SetNumCase   (NumCase);

			   if ((iLargeur == 0) || (iLargeur == (mNbCasesLargeur - 1)) || (iHauteur == 0) || (iHauteur == (mNbCasesHauteur -1)))
			   {
			      if ((NumCase != mNumCaseDepart) && (NumCase != mNumCaseArrivee))
			      {
				      CasePtr->SetEtat (CCase::eMur);
				   }
			   }
            mCases.push_back (CasePtr);
		   }
	   }
   }
   else
   {
      bReturn = false;

      std::cout << "Erreur de lecture de la configuration du plateau" << std::endl;
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
               mCases[NumCase]->SetEtat (CCase::eMur);
				}
			}
         else
         {
            mCases[NumCase]->SetEtat (CCase::eVide);
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
   if((aX < (mNbCasesLargeur * mLargeurCase)) && aY < (mNbCasesHauteur * mHauteurCase))
   {
      IterLargeur = (int)(aX / mLargeurCase);
      IterHauteur = (int)(aY / mHauteurCase);
      
      //On renseigne le numéro de la case que l'on a trouvé
      NumeroCaseCliquee = IterHauteur * mNbCasesLargeur + IterLargeur;

#ifdef DEBUG
   std::cout << "Case (" << IterLargeur << ", " << IterHauteur << ")" << std::endl;
#endif

      // Si la case est vide ET on a sélectionnée un type de tour dans le menu
      if (GetCase(NumeroCaseCliquee)->EstVide() && (mJeu.GetTourSelectionnee () != -1))
      {
         //On met le type à jour
         //TODO Prévision Construction tour
         GetCase(NumeroCaseCliquee)->SetEtat (CCase::eTour);
         //GetCase(NumeroCaseCliquee)->SetEtat (mJeu.GetTourSelectionnee ());
         mCoordonneesDerniereCaseModifiee.first    = IterLargeur;
         mCoordonneesDerniereCaseModifiee.second   = IterHauteur;
      }
   }

   return NumeroCaseCliquee;
}

void CPlateau::OnAffiche (SDL_Surface* apEcran)
{
   int IterLargeur = 0;
   int IterHauteur = 0;

   //Dessiner chaque case
   for(IterHauteur = 0; IterHauteur < mNbCasesHauteur; IterHauteur++)
   {
      for(IterLargeur = 0; IterLargeur < mNbCasesLargeur; IterLargeur++)
      {
         /*if (false ==  mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->EstPlusCourtChemin ())
         {*/
         // TODO  Gérer le fait que ça peut être une case ou une tour !
         //       Les surfaces ne sont pas les mêmes !
         CCase::ETypeCase EtatCase = mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetEtat ();
         if (EtatCase == CCase::eTour)
         {
            int TypeCase = mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetTypeTour ();
            mImagesTours[TypeCase]->Afficher (apEcran, mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetPosition ());
            //mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->OnAffiche (apEcran, mImagesTours[TypeCase]);
         }
         else
         {
            mImagesCases[EtatCase]->Afficher (apEcran, mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetPosition ());
            //mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->OnAffiche (apEcran, mImagesCases[EtatCase]);
         }
         //mPlateau[IterLargeur][IterHauteur]->OnAffiche (apEcran, mImages[mPlateau[IterLargeur][IterHauteur]->GetEtat()] );
         /*}
         else

         {
             mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->OnAffiche (apEcran, mpImagePCC);
         }*/
      }
   }
}

void CPlateau::OnAfficheEnPause (SDL_Surface* apEcran)
{
   SDL_Rect Position;
   Position.x = 0;
   Position.y = 0;
   Position.w = mNbCasesLargeur * mLargeurCase;
   Position.h = mNbCasesHauteur * mHauteurCase;
      
   mImagePausePtr->Afficher (apEcran, Position);
}

CTourPtr& CPlateau::ConstruireTour (int aNumCaseCliquee)
{
   std::string Ressource; // Non utilisé ici !
   int Portee;
   int Puissance;
   int Vitesse;
   int Cadence;

   mConfig.GetCaracsTourParId (mJeu.GetTourSelectionnee (), Ressource, Portee, Puissance, Vitesse, Cadence);
   return GetCase (aNumCaseCliquee)->ConstruireTour (mJeu.GetTourSelectionnee (), Portee, Puissance, Vitesse, Cadence);
}

void CPlateau::AnnuleDerniereModif (void)
{
   if (mCoordonneesDerniereCaseModifiee.first != -1 && mCoordonneesDerniereCaseModifiee.second != -1)
   {
      GetCase (mCoordonneesDerniereCaseModifiee.first, mCoordonneesDerniereCaseModifiee.second)->SetEtat (CCase::eVide);
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

CCasePtr& CPlateau::GetCase (int aNumCase)
{
   int IterHauteur = aNumCase / mNbCasesLargeur;
   int IterLargeur = aNumCase % mNbCasesLargeur;
   return mCases[IterHauteur * mNbCasesLargeur + IterLargeur];
}

CCasePtr& CPlateau::GetCase (int aX, int aY)
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
         //mPlateau[IterLargeur][IterHauteur]->SetPlusCourtChemin (false);
      }
   }
   
   std::vector<int>::iterator IterPlusCourtChemin = aPlusCourtChemin.begin ();
   for (IterPlusCourtChemin; IterPlusCourtChemin != aPlusCourtChemin.end (); IterPlusCourtChemin++)
   {
      IterHauteur = (*IterPlusCourtChemin) / mNbCasesLargeur;
      IterLargeur = (*IterPlusCourtChemin) % mNbCasesLargeur;
      mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->SetPlusCourtChemin (true);
      //mPlateau[IterLargeur][IterHauteur]->SetPlusCourtChemin (true);
   }
}
