#include "../include/Plateau.h"
#include "../include/Jeu.h"

CPlateau::CPlateau (CJeu& aJeu):
   mJeu           (aJeu),
   mNumCaseDepart (-1),
   mNumCaseArrivee(-1),
   mpImagePause (NULL),
   mpImagePCC (NULL)
{
   mImages.resize (CCase::eNbEtat);

   std::vector<SDL_Surface*>::iterator IterImage;
   for (IterImage = mImages.begin (); IterImage != mImages.end (); ++IterImage)
   {
      (*IterImage) = NULL;
   }
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
   std::vector<SDL_Surface*>::iterator IterImage;

   //Vérification de l'allocation des surfaces
   for (IterImage = mImages.begin (); IterImage != mImages.end (); ++IterImage)
   {
      if((*IterImage) != NULL)
	   {
		   SDL_FreeSurface(*IterImage), (*IterImage) = NULL;
      }

      //On charge toutes les images dans les surfaces associées
	   if ((LARGEUR_CASE == 50) && (HAUTEUR_CASE == 50))
	   {
         switch (iImage)
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
         }
	   }
	   else if ((LARGEUR_CASE == 25) && (HAUTEUR_CASE == 25))
	   {
         switch (iImage)
         {
            case CCase::eVide :
               (*IterImage) = SDL_LoadBMP("../Ressources/Vide_25.bmp");
               break;

            case CCase::eMur :
               (*IterImage) = SDL_LoadBMP("../Ressources/Mur_25.bmp");
               break;

            case CCase::eTour1 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour1_25.bmp");
               break;

            case CCase::eTour2 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour2_25.bmp");
               break;

            case CCase::eTour3 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour3_25.bmp");
               break;

            case CCase::eTour4 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour4_25.bmp");
               break;

            case CCase::eTour5 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour5_25.bmp");
               break;

            case CCase::eTour6 :
               (*IterImage) = SDL_LoadBMP("../Ressources/Tour6_25.bmp");
               break;

            default:
               break;
         }
	   }

      //On teste le retour du chargement
	   if ((*IterImage) == NULL)
	   {
		   std::cout << "Probleme de chargement de l'image : " << iImage << std::endl;
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
   else if ((LARGEUR_CASE == 25) && (HAUTEUR_CASE == 25)) 
   {
      mpImagePCC  = SDL_LoadBMP("../Ressources/PCC_25.bmp");
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
   std::cout << "Largeur = " << NB_CASE_LARGEUR << ", Hauteur = " << NB_CASE_HAUTEUR << std::endl;
#endif  

	// Initialisation du plateau
	for (int iLargeur = 0; iLargeur < NB_CASE_LARGEUR; iLargeur++)
	{
		for (int iHauteur = 0; iHauteur < NB_CASE_HAUTEUR; iHauteur++)
		{
			CCase Case;

			Case.OnInit ();
			Rect.x = iLargeur * LARGEUR_CASE;
			Rect.y = iHauteur * HAUTEUR_CASE;
			Case.SetPosition  (&Rect, iLargeur, iHauteur);
         Case.SetNumCase   (iLargeur + (NB_CASE_LARGEUR * iHauteur));

			if ((iLargeur == 0) || (iLargeur == (NB_CASE_LARGEUR - 1)) || (iHauteur == 0) || (iHauteur == (NB_CASE_HAUTEUR -1)))
			{
			   if (((iLargeur != 0) && (iHauteur != ((int)NB_CASE_HAUTEUR/2))) || ((iLargeur != (NB_CASE_LARGEUR - 1)) && (iHauteur != ((int)NB_CASE_HAUTEUR/2))))
			   {
				   Case.SetEtat (CCase::eMur);
				}
            else if ((iLargeur == 0) && (iHauteur == ((int)NB_CASE_HAUTEUR/2)))
            {
               mNumCaseDepart = iLargeur + (NB_CASE_LARGEUR * iHauteur);
            }
            else if ((iLargeur == (NB_CASE_LARGEUR - 1)) && (iHauteur == ((int)NB_CASE_HAUTEUR/2)))
            {
               mNumCaseArrivee = iLargeur + (NB_CASE_LARGEUR * iHauteur);
            }
			}

			mPlateau[iLargeur][iHauteur] = Case;
		}
	}

   return bReturn;
}

void CPlateau::OnReset (void)
{
	// Initialisation du plateau
	for (int iLargeur = 0; iLargeur < NB_CASE_LARGEUR; iLargeur++)
	{
		for (int iHauteur = 0; iHauteur < NB_CASE_HAUTEUR; iHauteur++)
		{
			mPlateau[iLargeur][iHauteur].OnInit ();

			if ((iLargeur == 0) || (iLargeur == (NB_CASE_LARGEUR - 1)) || (iHauteur == 0) || (iHauteur == (NB_CASE_HAUTEUR -1)))
			{
			   if (((iLargeur != 0) && (iHauteur != ((int)NB_CASE_HAUTEUR/2))) || ((iLargeur != (NB_CASE_LARGEUR - 1)) && (iHauteur != ((int)NB_CASE_HAUTEUR/2))))
			   {
				   mPlateau[iLargeur][iHauteur].SetEtat (CCase::eMur);
				}
            else if ((iLargeur == 0) && (iHauteur == ((int)NB_CASE_HAUTEUR/2)))
            {
               mNumCaseDepart = iLargeur + (NB_CASE_LARGEUR * iHauteur);
            }
            else if ((iLargeur == (NB_CASE_LARGEUR - 1)) && (iHauteur == ((int)NB_CASE_HAUTEUR/2)))
            {
               mNumCaseArrivee = iLargeur + (NB_CASE_LARGEUR * iHauteur);
            }
			}
		}
	}
}

void CPlateau::OnAffiche (SDL_Surface* apEcran)
{
   int IterLargeur = 0;
   int IterHauteur = 0;

   //Dessiner chaque case
   for(IterLargeur; IterLargeur < NB_CASE_LARGEUR; IterLargeur++)
   {
      for(IterHauteur = 0; IterHauteur < NB_CASE_HAUTEUR; IterHauteur++)
      {
         if (false == mPlateau[IterLargeur][IterHauteur].EstPlusCourtChemin ())
         {
            mPlateau[IterLargeur][IterHauteur].OnAffiche (apEcran, mImages[mPlateau[IterLargeur][IterHauteur].GetEtat()] );
         }
         else
         {
            mPlateau[IterLargeur][IterHauteur].OnAffiche (apEcran, mpImagePCC);
         }
      }
   }

   if (false == mJeu.PartieEnCours ())
   {
      SDL_Rect Position;
      Position.x = 0;
      Position.y = 0;
      Position.w = NB_CASE_LARGEUR * LARGEUR_CASE;
      Position.h = NB_CASE_HAUTEUR * HAUTEUR_CASE;
      SDL_BlitSurface(mpImagePause, NULL, apEcran, &Position);
   }
}

CCase* CPlateau::GetCase (int aX, int aY)
{
   return &(mPlateau[aX][aY]);
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
   int IterLargeur = 0;
   int IterHauteur = 0;
   for(IterLargeur; IterLargeur < NB_CASE_LARGEUR; IterLargeur++)
   {
      for(IterHauteur = 0; IterHauteur < NB_CASE_HAUTEUR; IterHauteur++)
      {
         mPlateau[IterLargeur][IterHauteur].SetPlusCourtChemin (false);
      }
   }
   
   std::vector<int>::iterator IterPlusCourtChemin = aPlusCourtChemin.begin ();
   for (IterPlusCourtChemin; IterPlusCourtChemin != aPlusCourtChemin.end (); IterPlusCourtChemin++)
   {
      IterHauteur = (*IterPlusCourtChemin) / (NB_CASE_LARGEUR);
      IterLargeur = (*IterPlusCourtChemin) % (NB_CASE_LARGEUR);
      mPlateau[IterLargeur][IterHauteur].SetPlusCourtChemin (true);
   }
}
