#include "../include/Plateau.h"
#include "../include/Jeu.h"



CPlateau::CPlateau (CJeu& aJeu):
   mJeu           (aJeu),
   mNumCaseDepart (-1),
   mNumCaseArrivee(-1),
   mpImagePause   (NULL),
   mpImagePCC     (NULL)
{
   ;
}

CPlateau::~CPlateau (void)
{
   std::vector<SDL_Surface*>::iterator IterImage;
   for (IterImage = mImages.begin (); IterImage != mImages.end (); ++IterImage)
   {
      SDL_FreeSurface (*IterImage);
   }

   SDL_FreeSurface (mpImagePause);
   SDL_FreeSurface (mpImagePCC);
}

bool CPlateau::OnInit (void)
{
   bool bReturn = true;

   int iImage = 0;
   int NbTypeCase;
   std::vector<SDL_Surface*>::iterator IterImage;

   // Lecture du fichier de configuration
   mConfig.Chargement ("../conf/ConfJeu.txt");

   bool bConfig = true;
   bConfig &= mConfig.Get ("nbCaseLargeur", mNbCasesLargeur);
   bConfig &= mConfig.Get ("nbCaseHauteur", mNbCasesHauteur);
   bConfig &= mConfig.Get ("numeroCaseDepart", mNumCaseDepart);
   bConfig &= mConfig.Get ("numeroCaseArrivee", mNumCaseArrivee);

   bConfig &= mConfig.Get ("nombreTypeCase", NbTypeCase);

   for (iImage = 0; (iImage < NbTypeCase) && bConfig; ++iImage)
   {
      std::string NomRessourceImageStr;
      //bConfig &= mConfig.Get ("nom", );
      bConfig &= mConfig.Get ("ressource", NomRessourceImageStr);
      //bConfig &= mConfig.Get ("portee", );
      //bConfig &= mConfig.Get ("puissance", );
      //bConfig &= mConfig.Get ("vitesse", );
      //bConfig &= mConfig.Get ("cadence", );
      mNomImages.push_back (NomRessourceImageStr);
   }

   if (bConfig)
   {
      iImage = 0;

      mImages.resize (NbTypeCase);

      //Vérification de l'allocation des surfaces
      for (IterImage = mImages.begin (); IterImage != mImages.end (); ++IterImage)
      {
         (*IterImage) = NULL;

/*         if((*IterImage) != NULL)
	      {
		      SDL_FreeSurface(*IterImage), (*IterImage) = NULL;
         }*/

         //On charge toutes les images dans les surfaces associées
         std::string CheminRessource ("../Ressources/");
         CheminRessource+=mNomImages[iImage];

         (*IterImage) = SDL_LoadBMP(CheminRessource.c_str ());
         
         /*switch (iImage)
         {
            case CCase::eVide :
               (*IterImage) = SDL_LoadBMP("../Ressources/Vide_50.bmp");
               break;

            case CCase::eMur :
               (*IterImage) = SDL_LoadBMP("../Ressources/Mur_50.bmp");
               break;

            case CCase::eTour1 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour1_50.bmp");
               break;

            case CCase::eTour2 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour2_50.bmp");
               break;

            case CCase::eTour3 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour3_50.bmp");
               break;

            case CCase::eTour4 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour4_50.bmp");
               break;

            case CCase::eTour5 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour5_50.bmp");
               break;

            case CCase::eTour6 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour6_50.bmp");
               break;

            default:
               break;
         }*/

         //On teste le retour du chargement
	      if ((*IterImage) == NULL)
	      {
            std::cout << "Probleme de chargement de l'image : " << mNomImages[iImage].c_str () << std::endl;
		      bReturn = false;
	      }

         iImage++;
      }
   
      if(mpImagePCC != NULL)
      {
         SDL_FreeSurface(mpImagePCC), mpImagePCC = NULL;
      }
      if(mpImagePause != NULL)
      {
         SDL_FreeSurface(mpImagePause), mpImagePause = NULL;
      }

      if ((LARGEUR_CASE == 50) && (HAUTEUR_CASE == 50))
      {
         mpImagePCC  = SDL_LoadBMP("../Ressources/PCC_50.bmp");
      }
   
      mpImagePause = SDL_LoadBMP("../Ressources/JeuPause.bmp");
   
	   //On teste le retour du chargement
	   if ((mpImagePCC == NULL) || (mpImagePause == NULL))
	   {
		   std::cout << "Probleme de chargement des images" << std::endl;
		   bReturn = false;
	   }

	   //Mis en place de la transparence
	   //if(SDL_SetColorKey(o,SDL_SRCCOLORKEY,0)==-1)
	   //	std::cout << "Erreur avec la transparence du rond" << std::endl;
	   //if(SDL_SetColorKey(x,SDL_SRCCOLORKEY,0)==-1)
	   //	std::cout << "Erreur avec la transparence de la croix" << std::endl;

      SDL_SetAlpha (mpImagePause, SDL_SRCALPHA, 128);

      SDL_Rect	Rect;

	   Rect.w = LARGEUR_CASE;
	   Rect.h = HAUTEUR_CASE;

#ifdef DEBUG
   std::cout << "Largeur = " << mNbCasesLargeur << ", Hauteur = " << mNbCasesHauteur << std::endl;
#endif  


#ifdef DEBUG
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
			   Rect.x = iLargeur * LARGEUR_CASE;
			   Rect.y = iHauteur * HAUTEUR_CASE;
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
         CCase::ETypeCase EtatCase = mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->GetEtat ();
         mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->OnAffiche (apEcran, mImages[EtatCase]);
         //mPlateau[IterLargeur][IterHauteur]->OnAffiche (apEcran, mImages[mPlateau[IterLargeur][IterHauteur]->GetEtat()] );
         /*}
         else
         {
             mCases[IterHauteur * mNbCasesLargeur + IterLargeur]->OnAffiche (apEcran, mpImagePCC);
         }*/
      }
   }

   if (false == mJeu.PartieEnCours ())
   {
      SDL_Rect Position;
      Position.x = 0;
      Position.y = 0;
      Position.w = mNbCasesLargeur * LARGEUR_CASE;
      Position.h = mNbCasesHauteur * HAUTEUR_CASE;
      SDL_BlitSurface(mpImagePause, NULL, apEcran, &Position);
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
   int IndexCaseX = aCoordonnees.first  / LARGEUR_CASE;
   int IndexCaseY = aCoordonnees.second / HAUTEUR_CASE;

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
