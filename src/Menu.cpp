#include "../include/Menu.h"
#include "../include/Jeu.h"
#include "../include/Case.h"

CMenu::CMenu (CConfiguration& aConfig, CJeu& aJeu):
   mLog        ("Menu"),
   mConfig     (aConfig),
   mJeu        (aJeu)
{
   ; // Rien à faire
}

CMenu::~CMenu (void)
{
   ;
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

      // Construction du chemin des ressources
      std::string NomResource;
      std::string CheminRessource;

      mConfig.Get ("ressourcesImages", CheminRessource);

      // Fond du menu
      std::string FichierFond ("Menu.bmp");
      mImageFondPtr.reset (new CImage (CheminRessource));
      bReturn &= mImageFondPtr->Load (FichierFond);
      
      // Bouton Nouvelle partie
      bReturn &= mConfig.Get ("ressourceBtNew", NomResource);
      mImagesBoutons[eNew].reset (new CImage (CheminRessource));
      bReturn &= mImagesBoutons[eNew]->Load (NomResource);
      
      // Bouton Pause
      bReturn &= mConfig.Get ("ressourceBtPause", NomResource);
      mImagesBoutons[ePause].reset (new CImage (CheminRessource));
      bReturn &= mImagesBoutons[ePause]->Load (NomResource);

      // Bouton reprendre la partie
      bReturn &= mConfig.Get ("ressourceBtReprendre", NomResource);
      mImagesBoutons[eReprendre].reset (new CImage (CheminRessource));
      bReturn &= mImagesBoutons[eReprendre]->Load (NomResource);

      // Bouton Quitter la partie
      bReturn &= mConfig.Get ("ressourceBtQuit", NomResource);
      mImagesBoutons[eQuit].reset (new CImage (CheminRessource));
      bReturn &= mImagesBoutons[eQuit]->Load (NomResource);

      // Bouton Nouvel Ennemi (DEBUG)
      bReturn &= mConfig.Get ("ressourceBtNewEnnemi", NomResource);
      mImagesBoutons[eNewEnnemi].reset (new CImage (CheminRessource));
      bReturn &= mImagesBoutons[eNewEnnemi]->Load (NomResource);
            
      int iImage = 0;
      
      bReturn &= mConfig.GetRessourcesTours (mNomImagesTour);
      mImagesTours.resize (mNbTours);

      // Pour les boutons tours
      CImage::Vecteur::iterator IterImage;
      for (IterImage = mImagesTours.begin (); (IterImage != mImagesTours.end ()) && (bReturn); ++IterImage)
      {
         //On charge toutes les images dans les surfaces associées
         mLog << Info << "Chargement de : " << mNomImagesTour[iImage].c_str () << EndLine;

         (*IterImage).reset (new CImage (CheminRessource));
         bReturn = (*IterImage)->Load (mNomImagesTour[iImage]);
         
         iImage++;
      }
   }
   else
   {
      mLog << Erreur << "Problème de configuration du menu" << EndLine;
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
         mJeu.SelectTour (-1);

         // IdBouton a été incrémenté lors de la dernière itération
         IdBouton--;
         switch (IdBouton)
         {
            case ePause:
               mJeu.ChangerEtatPartie (false);
               break;

            case eNewEnnemi:
// TODO        mJeu.AjoutEnnemi ();
               break;
               
            default:
               mLog << Info << "Ce bouton n'est pas actif dans ce mode" << EndLine;
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
            mJeu.SelectTour (-1);
            mLog << Info << "[GAME ON] Aucun bouton correspond à la position : " << aX << ", " << aY << EndLine;
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

            mLog << Info << "Bouton trouve OFF : " << IdBouton << EndLine;
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
               mLog << Info << "Ce bouton n'est pas actif dans ce mode" << EndLine;
               break;
         }
      }
      else
      {
         mLog << Erreur << "[GAME OFF] Aucun bouton correspond à la position : " << aX << ", " << aY << EndLine;
      }
   }
}

void CMenu::OnAffiche (CSurface::Ptr& aScreenPtr)
{
   mImageFondPtr->Afficher (aScreenPtr, mPositionFond);

  if (mJeu.PartieEnCours ())
   {
      mImagesBoutons[ePause]     ->Afficher (aScreenPtr, mPositionsBoutons[ePause]);
      mImagesBoutons[eNewEnnemi] ->Afficher (aScreenPtr, mPositionsBoutons[eNewEnnemi]);

      for (unsigned int IdTour = 0; IdTour < mImagesTours.size (); IdTour++)
      {
         mImagesTours[IdTour]->Afficher (aScreenPtr, mPositionsTours[IdTour]);
      }
   }
   else
   {
      mImagesBoutons[eNew]       ->Afficher (aScreenPtr, mPositionsBoutons[eNew]);
      mImagesBoutons[eReprendre] ->Afficher (aScreenPtr, mPositionsBoutons[eReprendre]);
      mImagesBoutons[eQuit]      ->Afficher (aScreenPtr, mPositionsBoutons[eQuit]);
   }
}

int CMenu::GetLargeur (void)
{
   return mLargeur;
}
