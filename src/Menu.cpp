#include "../include/Menu.h"
#include "../include/Jeu.h"
#include "../include/Case.h"

CMenu::CMenu (CConfiguration& aConfig, CJeu& aJeu):
   mConfig     (aConfig),
   mJeu        (aJeu),
   mImageFond  (NULL)
{
   ; // Rien à faire
}

CMenu::~CMenu (void)
{
   std::vector<SDL_Surface*>::iterator IterImages;

   // Libération de l'image du fond du menu
   SDL_FreeSurface (mImageFond);

   // Libération des images boutons du menu
   for (IterImages = mImagesBoutons.begin (); IterImages != mImagesBoutons.end (); IterImages++)
   {
      SDL_FreeSurface (*IterImages);
   }

   // Libération des images tours du menu
   for (IterImages = mImagesTours.begin (); IterImages != mImagesTours.end (); IterImages++)
   {
      SDL_FreeSurface (*IterImages);
   }
}

bool CMenu::OnInit (void)
{
   bool bReturn = true;

   int NbCaseLargeur;
   int NbCaseHauteur;
   int LargeurCase;
   int HauteurCase;
   int HauteurMenu;
      
   bReturn &= mConfig.Get ("nbCaseLargeur",  NbCaseLargeur);
   bReturn &= mConfig.Get ("nbCaseHauteur",  NbCaseHauteur);
   bReturn &= mConfig.Get ("largeurCase",    LargeurCase);
   bReturn &= mConfig.Get ("hauteurCase",    HauteurCase);
   bReturn &= mConfig.Get ("hauteurMenu",    HauteurMenu);
   bReturn &= mConfig.Get ("largeurMenu",    mLargeur);
   bReturn &= mConfig.Get ("nombreTypeTour", mNbTours);
   
   if (bReturn)
   {
      mPositionsBoutons.resize (eNbBouton);
      mImagesBoutons.resize (eNbBouton);

      // Position du menu
      mPositionFond.x = NbCaseLargeur * LargeurCase;
      mPositionFond.y = 0;
      mPositionFond.w = mLargeur;
      mPositionFond.h = HauteurMenu;

      // Positions des boutons du menu
      mPositionsBoutons[eNew].x = mPositionFond.x + 25;
      mPositionsBoutons[eNew].y = 25;
      mPositionsBoutons[eNew].w = mLargeur - 25;
      mPositionsBoutons[eNew].h = 40;

      mPositionsBoutons[ePause].x = mPositionFond.x + 25;
      mPositionsBoutons[ePause].y = 75;
      mPositionsBoutons[ePause].w = mLargeur - 25;
      mPositionsBoutons[ePause].h = 40;

      mPositionsBoutons[eReprendre].x = mPositionFond.x +25;
      mPositionsBoutons[eReprendre].y = 125;
      mPositionsBoutons[eReprendre].w = mLargeur - 25;
      mPositionsBoutons[eReprendre].h = 40;

      mPositionsBoutons[eQuit].x = mPositionFond.x + 25;
      mPositionsBoutons[eQuit].y = 175;
      mPositionsBoutons[eQuit].w = mLargeur - 25;
      mPositionsBoutons[eQuit].h = 40;

      mPositionsBoutons[eNewEnnemi].x = mPositionFond.x + 25;
      mPositionsBoutons[eNewEnnemi].y = 225;
      mPositionsBoutons[eNewEnnemi].w = LargeurCase;
      mPositionsBoutons[eNewEnnemi].h = HauteurCase;

      int EspacementBtTour = (int)((HauteurMenu / 2) / mNbTours);
      if (HauteurCase < EspacementBtTour)
      {
         mPositionsTours.resize (mNbTours);
         int InterBtTour = EspacementBtTour - HauteurCase;
         for (int IterTypeTour = 0; IterTypeTour < mNbTours; ++IterTypeTour)
         {            
            mPositionsTours[IterTypeTour].x = mPositionFond.x + 25;
            mPositionsTours[IterTypeTour].y = HauteurMenu / 2 + (IterTypeTour * EspacementBtTour) + (InterBtTour / 2);
            mPositionsTours[IterTypeTour].w = LargeurCase;
            mPositionsTours[IterTypeTour].h = HauteurCase;
         }
      }

      // Vérification de l'allocation des surfaces
      // Fond du menu
      if (mImageFond != NULL)
      {
         SDL_FreeSurface (mImageFond), mImageFond = NULL;
      }
      mImageFond = SDL_LoadBMP("../ressources/Menu.bmp");
      //On teste le retour du chargement
      if (mImageFond == NULL)
      {
		   std::cout << "Probleme de chargement de l'image du fond du menu." << std::endl;
		   return false;
      }

      // Pour les boutons du menu
      for (int IterImage = 0; IterImage < eNbBouton; IterImage++)
      {
	      if(mImagesBoutons[IterImage] != NULL)
	      {
		      SDL_FreeSurface (mImagesBoutons[IterImage]), mImagesBoutons[IterImage] = NULL;
   	   }
      }

      // Construction du chemin des ressources
      std::string CheminRessource;
      std::string NomResource;
      
      // Bouton Nouvelle partie
      bReturn = mConfig.Get ("ressourceBtNew", NomResource);
      CheminRessource = "../ressources/";
      CheminRessource += NomResource;
      mImagesBoutons[eNew] = SDL_LoadBMP(CheminRessource.c_str ());

      // Bouton Pause
      CheminRessource.clear ();
      bReturn = mConfig.Get ("ressourceBtPause", NomResource);
      CheminRessource = "../ressources/";
      CheminRessource += NomResource;
      mImagesBoutons[ePause] = SDL_LoadBMP(CheminRessource.c_str ());

      // Bouton reprendre la partie
      bReturn = mConfig.Get ("ressourceBtReprendre", NomResource);
      CheminRessource = "../ressources/";
      CheminRessource += NomResource;
      mImagesBoutons[eReprendre] = SDL_LoadBMP(CheminRessource.c_str ());

      // Bouton Quitter la partie
      bReturn = mConfig.Get ("ressourceBtQuit", NomResource);
      CheminRessource = "../ressources/";
      CheminRessource += NomResource;
      mImagesBoutons[eQuit] = SDL_LoadBMP(CheminRessource.c_str ());

      // Bouton Nouvel Ennemi (DEBUG)
      bReturn = mConfig.Get ("ressourceBtNewEnnemi", NomResource);
      CheminRessource = "../ressources/";
      CheminRessource += NomResource;
      mImagesBoutons[eNewEnnemi] = SDL_LoadBMP(CheminRessource.c_str ());
            
      //On teste le retour du chargement
      for (int IterImage = 0; IterImage < eNbBouton; IterImage++)
      {
	      if (mImagesBoutons[IterImage] == NULL)
         {
		      std::cout << "Probleme de chargement de l'image du menu : " << IterImage << std::endl;
		      return false;
         }
      }

      int iImage = 0;
      
      bReturn &= mConfig.GetRessourcesTours (mNomImagesTour);
      mImagesTours.resize (mNomImagesTour.size ());
      // Pour les boutons tours
      std::vector<SDL_Surface*>::iterator IterImage;
      for (IterImage = mImagesTours.begin (); (IterImage != mImagesTours.end ()) && (bReturn); ++IterImage)
      {
         if((*IterImage) != NULL)
	      {
		      SDL_FreeSurface (*IterImage), (*IterImage) = NULL;
   	   }

         //On charge toutes les images dans les surfaces associées
         std::string CheminRessource ("../ressources/");
         CheminRessource += mNomImagesTour[iImage];
         
         std::cout << "Chargement de : " << CheminRessource.c_str () << std::endl;
         
         (*IterImage) = SDL_LoadBMP(CheminRessource.c_str ());
                  
         //On teste le retour du chargement
	      if ((*IterImage) == NULL)
	      {
            std::cout << "Probleme de chargement de l'image : " << (mNomImagesTour[iImage]).c_str () << std::endl;
		      bReturn = false;
	      }
         iImage++;
      }
   }
   else
   {
      std::cout << "Problème de configuration du menu" << std::endl;
   }

   return bReturn;
}

void CMenu::OnClic (int aX, int aY)
{
   bool  bBoutonTrouve  = false;
   int   IdBouton;
   int   IdTour;
   
   if (mJeu.PartieEnCours ())
   {
      for (IdBouton = eNew; (IdBouton < eNbBouton) && (false == bBoutonTrouve); ++IdBouton)
      {
         if (  (mPositionsBoutons[IdBouton].x < aX) && (aX < (mPositionsBoutons[IdBouton].x + mPositionsBoutons[IdBouton].w))
            && (mPositionsBoutons[IdBouton].y < aY) && (aY < (mPositionsBoutons[IdBouton].y + mPositionsBoutons[IdBouton].h)))
         {
            bBoutonTrouve = true;
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

            case eNewEnnemi:
//               mJeu.AjoutEnnemi ();
               break;
               
            default:
               std::cout << "Ce bouton n'est pas actif dans ce mode" << std::endl;
               break;
         }
      }
      else
      {
         for (IdTour = 0; (IdTour < mNbTours) && (false == bBoutonTrouve); ++IdTour)
         {
            if (  (mPositionsTours[IdTour].x < aX) && (aX < (mPositionsTours[IdTour].x + mPositionsTours[IdTour].w))
               && (mPositionsTours[IdTour].y < aY) && (aY < (mPositionsTours[IdTour].y + mPositionsTours[IdTour].h)))
            {
               bBoutonTrouve = true;
            }
         }

         if (bBoutonTrouve)
         {
            mJeu.SelectTour (IdTour - 1);
         }
         else
         {
            std::cout << "[GAME ON] Aucun bouton correspond à la position : " << aX << ", " << aY << std::endl;
         }
      }
   }
   else
   {
      for (IdBouton = eNew; (IdBouton < eNbBouton) && (false == bBoutonTrouve); ++IdBouton)
      {
         if (  (mPositionsBoutons[IdBouton].x < aX) && (aX < (mPositionsBoutons[IdBouton].x + mPositionsBoutons[IdBouton].w))
            && (mPositionsBoutons[IdBouton].y < aY) && (aY < (mPositionsBoutons[IdBouton].y + mPositionsBoutons[IdBouton].h)))
         {
            bBoutonTrouve = true;
#ifdef DEGUB
            std::cout << "Bouton trouve OFF : " << IdBouton << std::endl;
#endif
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
               std::cout << "Ce bouton n'est pas actif dans ce mode" << std::endl;
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
   SDL_BlitSurface(mImageFond,NULL,apScreen,&(mPositionFond));

  if (mJeu.PartieEnCours ())
   {
      SDL_BlitSurface(mImagesBoutons[ePause], NULL, apScreen, &(mPositionsBoutons[ePause]));
      SDL_BlitSurface(mImagesBoutons[eNewEnnemi], NULL, apScreen, &(mPositionsBoutons[eNewEnnemi]));

      for (unsigned int IdTour = 0; IdTour < mImagesTours.size (); IdTour++)
      {
         SDL_BlitSurface(mImagesTours[IdTour], NULL, apScreen, &(mPositionsTours[IdTour]));
      }
   }
   else
   {
      SDL_BlitSurface(mImagesBoutons[eNew],      NULL,apScreen,&(mPositionsBoutons[eNew]));
      SDL_BlitSurface(mImagesBoutons[eReprendre],NULL,apScreen,&(mPositionsBoutons[eReprendre]));
      SDL_BlitSurface(mImagesBoutons[eQuit],     NULL,apScreen,&(mPositionsBoutons[eQuit]));
   }
}

int CMenu::GetLargeur (void)
{
   return mLargeur;
}
