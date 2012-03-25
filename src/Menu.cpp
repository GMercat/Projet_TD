#include "../include/Menu.h"
#include "../include/Jeu.h"
#include "../include/Case.h"

CMenu::CMenu (CJeu& aJeu):
   mJeu  (aJeu)
{
   for (int IterImages = 0; IterImages < eNbBouton; IterImages++)
   {
      mImages[IterImages] = NULL;
   }

   mPositions[eFond].x = NB_CASE_LARGEUR * LARGEUR_CASE;
   mPositions[eFond].y = 0;
   mPositions[eFond].w = LARGEUR_MENU;
   mPositions[eFond].h = NB_CASE_HAUTEUR * HAUTEUR_CASE;

   mPositions[eNew].x = mPositions[eFond].x + 25;
   mPositions[eNew].y = (NB_CASE_HAUTEUR * HAUTEUR_CASE )  / 2 + 25;
   mPositions[eNew].w = LARGEUR_MENU - 25;
   mPositions[eNew].h = 40;
      
   mPositions[eReprendre].x = mPositions[eFond].x +25;
   mPositions[eReprendre].y = (NB_CASE_HAUTEUR * HAUTEUR_CASE )  / 2 + 75;
   mPositions[eReprendre].w = LARGEUR_MENU - 25;
   mPositions[eReprendre].h = 40;

   mPositions[eQuit].x = mPositions[eFond].x + 25;
   mPositions[eQuit].y = (NB_CASE_HAUTEUR * HAUTEUR_CASE )  / 2 + 125;
   mPositions[eQuit].w = LARGEUR_MENU - 25;
   mPositions[eQuit].h = 40;

   mPositions[ePause].x = mPositions[eFond].x + 25;
   mPositions[ePause].y = 25;
   mPositions[ePause].w = LARGEUR_MENU - 25;
   mPositions[ePause].h = 40;

   mPositions[eTour1].x = mPositions[eFond].x + 25;
   mPositions[eTour1].y = (NB_CASE_HAUTEUR * HAUTEUR_CASE ) / 2 + 10;
   mPositions[eTour1].w = LARGEUR_CASE;
   mPositions[eTour1].h = HAUTEUR_CASE;

   mPositions[eTour2].x = mPositions[eFond].x + 125;
   mPositions[eTour2].y = (NB_CASE_HAUTEUR * HAUTEUR_CASE ) / 2 + 10;
   mPositions[eTour2].w = LARGEUR_CASE;
   mPositions[eTour2].h = HAUTEUR_CASE;

   mPositions[eTour3].x = mPositions[eFond].x + 25;
   mPositions[eTour3].y = (NB_CASE_HAUTEUR * HAUTEUR_CASE ) / 2 + 70;
   mPositions[eTour3].w = LARGEUR_CASE;
   mPositions[eTour3].h = HAUTEUR_CASE;

   mPositions[eTour4].x = mPositions[eFond].x + 125;
   mPositions[eTour4].y = (NB_CASE_HAUTEUR * HAUTEUR_CASE ) / 2 + 70;
   mPositions[eTour4].w = LARGEUR_CASE;
   mPositions[eTour4].h = HAUTEUR_CASE;

   mPositions[eTour5].x = mPositions[eFond].x + 25;
   mPositions[eTour5].y = (NB_CASE_HAUTEUR * HAUTEUR_CASE ) / 2 + 130;
   mPositions[eTour5].w = LARGEUR_CASE;
   mPositions[eTour5].h = HAUTEUR_CASE;

   mPositions[eTour6].x = mPositions[eFond].x + 125;
   mPositions[eTour6].y = (NB_CASE_HAUTEUR * HAUTEUR_CASE ) / 2 + 130;
   mPositions[eTour6].w = LARGEUR_CASE;
   mPositions[eTour6].h = HAUTEUR_CASE;
}

CMenu::~CMenu (void)
{
   for (int IterImage = 0; IterImage < eNbBouton; IterImage++)
   {
      SDL_FreeSurface (mImages[IterImage]);
   }
}

bool CMenu::OnInit (void)
{
   bool bReturn = false;

   //Vérification de l'allocation des surfaces
   for (int IterImage = 0; IterImage < eNbBouton; IterImage++)
   {
	   if(mImages[IterImage] != NULL)
	   {
		   SDL_FreeSurface (mImages[IterImage]), mImages[IterImage] = NULL;
   	}

      switch (IterImage)
      {
         case eFond:
            mImages[IterImage] = SDL_LoadBMP("../Ressources/Menu.bmp");
            break;
         case eNew:
            mImages[IterImage] = SDL_LoadBMP("../Ressources/BoutonNew.bmp");
            break;
         case eReprendre:
            mImages[IterImage] = SDL_LoadBMP("../Ressources/BoutonReprendre.bmp");
            break;
         case eQuit:
            mImages[IterImage] = SDL_LoadBMP("../Ressources/BoutonQuit.bmp");
            break;

         case ePause:
            mImages[IterImage] = SDL_LoadBMP("../Ressources/BoutonPause.bmp");
            break;

         case eTour1:
            mImages[IterImage] = SDL_LoadBMP("../Ressources/Tour1_50.bmp");
            break;

         case eTour2:
            mImages[IterImage] = SDL_LoadBMP("../Ressources/Tour2_50.bmp");
            break;

         case eTour3:
            mImages[IterImage] = SDL_LoadBMP("../Ressources/Tour3_50.bmp");
            break;

         case eTour4:
            mImages[IterImage] = SDL_LoadBMP("../Ressources/Tour4_50.bmp");
            break;

         case eTour5:
            mImages[IterImage] = SDL_LoadBMP("../Ressources/Tour5_50.bmp");
            break;

         case eTour6:
            mImages[IterImage] = SDL_LoadBMP("../Ressources/Tour6_50.bmp");
            break;

         default:
            std::cout << "ERR : Images inconnues" << std::endl;
            break;
      }

      //On teste le retour du chargement
      if (mImages[IterImage] == NULL)
      {
		   std::cout << "Probleme de chargement de l'image du menu : " << IterImage << std::endl;
		   bReturn = false;
      }
   }

   return bReturn;
}

void CMenu::OnClic (int aX, int aY)
{
   bool  bBoutonTrouve  = false;
   int   IdBouton       = 1;
   
   if (mJeu.PartieEnCours ())
   {
      for (IdBouton = ePause; (IdBouton < eNbBouton) && (false == bBoutonTrouve); ++IdBouton)
      {
         if (  (mPositions[IdBouton].x < aX) && (aX < (mPositions[IdBouton].x + mPositions[IdBouton].w))
            && (mPositions[IdBouton].y < aY) && (aY < (mPositions[IdBouton].y + mPositions[IdBouton].h)))
         {
            bBoutonTrouve = true;
            std::cout << "Bouton trouve ON : " << IdBouton << std::endl;
         }
      }

      if (bBoutonTrouve)
      {
         // IdBouton a été incrémenté lors de la dernière itération
         IdBouton--;
         switch (IdBouton)
         {
            case ePause:
               mJeu.ChangerEtatPartie (false);
               break;

            case eTour1:
               mJeu.SelectTour (CCase::eTour1);
               break;

            case eTour2:
               mJeu.SelectTour (CCase::eTour2);
               break;

            case eTour3:
               mJeu.SelectTour (CCase::eTour3);
               break;

            case eTour4:
               mJeu.SelectTour (CCase::eTour4);
               break;

            case eTour5:
               mJeu.SelectTour (CCase::eTour5);
               break;

            case eTour6:
               mJeu.SelectTour (CCase::eTour6);
               break;

            default:
               break;
         }
      }
      else
      {
         std::cout << "[GAME ON] Aucun bouton correspond à la position : " << aX << ", " << aY << std::endl;
      }
   }
   else
   {
      for (IdBouton = eNew; (IdBouton < eNbBouton) && (false == bBoutonTrouve); ++IdBouton)
      {
         if (  (mPositions[IdBouton].x < aX) && (aX < (mPositions[IdBouton].x + mPositions[IdBouton].w))
            && (mPositions[IdBouton].y < aY) && (aY < (mPositions[IdBouton].y + mPositions[IdBouton].h)))
         {
            bBoutonTrouve = true;
            std::cout << "Bouton trouve OFF : " << IdBouton << std::endl;
         }
      }

      if (bBoutonTrouve)
      {
         // IdBouton a été incrémenté lors de la dernière itération
         IdBouton--;

         switch (IdBouton)
         {
            case eNew:
               mJeu.OnReset ();
               mJeu.ChangerEtatPartie (true);
               break;

            case eReprendre:
               mJeu.ChangerEtatPartie (true);
               break;

            case eQuit:
               mJeu.OnQuit ();
               break;

            default:
               break;
         }
      }
      else
      {
         std::cout << "[GAME OFF] Aucun bouton correspond à la position : " << aX << ", " << aY << std::endl;
      }
   }
}

void CMenu::OnAffiche (SDL_Surface* apScreen)
{
   SDL_BlitSurface(mImages[eFond],NULL,apScreen,&(mPositions[eFond]));

  if (mJeu.PartieEnCours ())
   {
      SDL_BlitSurface(mImages[ePause],NULL,apScreen,&(mPositions[ePause]));
      SDL_BlitSurface(mImages[eTour1],NULL,apScreen,&(mPositions[eTour1]));
      SDL_BlitSurface(mImages[eTour2],NULL,apScreen,&(mPositions[eTour2]));
      SDL_BlitSurface(mImages[eTour3],NULL,apScreen,&(mPositions[eTour3]));
      SDL_BlitSurface(mImages[eTour4],NULL,apScreen,&(mPositions[eTour4]));
      SDL_BlitSurface(mImages[eTour5],NULL,apScreen,&(mPositions[eTour5]));
      SDL_BlitSurface(mImages[eTour6],NULL,apScreen,&(mPositions[eTour6]));
   }
   else
   {
      SDL_BlitSurface(mImages[eNew],      NULL,apScreen,&(mPositions[eNew]));
      SDL_BlitSurface(mImages[eReprendre],NULL,apScreen,&(mPositions[eReprendre]));
      SDL_BlitSurface(mImages[eQuit],     NULL,apScreen,&(mPositions[eQuit]));
   }
}
