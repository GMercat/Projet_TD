#include "Menu.h"
#include "ContexteJeu.h"
#include "Case.h"

CMenu::CMenu (CConfiguration& aConfig, CContexteJeu& aContexte):
   mLog              ("Menu"),
   mConfig           (aConfig),
   mContexte         (aContexte),
   mPositionFondPtr  (new CRect)
{
   ;
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
      mPositionFondPtr->SetX (NbCaseLargeur * LargeurCase);
      mPositionFondPtr->SetY (0);
      mPositionFondPtr->SetW (mLargeur);
      mPositionFondPtr->SetH (HauteurMenu);

      // Positions des boutons du menu
      mPositionsBoutons[eNew].reset (new CRect);
      mPositionsBoutons[eNew]->SetX (mPositionFondPtr->GetX () + 25);
      mPositionsBoutons[eNew]->SetY (10);
      mPositionsBoutons[eNew]->SetW (mLargeur - 25);
      mPositionsBoutons[eNew]->SetH (40);

      mPositionsBoutons[ePause].reset (new CRect);
      mPositionsBoutons[ePause]->SetX (mPositionFondPtr->GetX () + 25);
      mPositionsBoutons[ePause]->SetY (60);
      mPositionsBoutons[ePause]->SetW (mLargeur - 25);
      mPositionsBoutons[ePause]->SetH (40);

      mPositionsBoutons[eReprendre].reset (new CRect);
      mPositionsBoutons[eReprendre]->SetX (mPositionFondPtr->GetX () +25);
      mPositionsBoutons[eReprendre]->SetY (110);
      mPositionsBoutons[eReprendre]->SetW (mLargeur - 25);
      mPositionsBoutons[eReprendre]->SetH (40);

      mPositionsBoutons[eQuit].reset (new CRect);
      mPositionsBoutons[eQuit]->SetX (mPositionFondPtr->GetX () + 25);
      mPositionsBoutons[eQuit]->SetY (160);
      mPositionsBoutons[eQuit]->SetW (mLargeur - 25);
      mPositionsBoutons[eQuit]->SetH (40);

      //mPositionsBoutons[eNewEnnemi].x = mPositionFond.x + 25;
      //mPositionsBoutons[eNewEnnemi].y = 225;
      //mPositionsBoutons[eNewEnnemi].w = LargeurCase;
      //mPositionsBoutons[eNewEnnemi].h = HauteurCase;

      int EspacementBtTour = (int)((HauteurMenu / 2) / mNbTours);
      if (HauteurCase < EspacementBtTour)
      {
         mPositionsTours.resize (mNbTours);
         int InterBtTour = EspacementBtTour - HauteurCase;
         for (int IterTypeTour = 0; IterTypeTour < mNbTours; ++IterTypeTour)
         {
            mPositionsTours[IterTypeTour].reset (new CRect);

            mPositionsTours[IterTypeTour]->SetX (mPositionFondPtr->GetX () + 25);
            mPositionsTours[IterTypeTour]->SetY (HauteurMenu / 2 + (IterTypeTour * EspacementBtTour) + (InterBtTour / 2));
            mPositionsTours[IterTypeTour]->SetW (LargeurCase);
            mPositionsTours[IterTypeTour]->SetH (HauteurCase);
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
      //bReturn &= mConfig.Get ("ressourceBtNewEnnemi", NomResource);
      //mImagesBoutons[eNewEnnemi].reset (new CImage (CheminRessource));
      //bReturn &= mImagesBoutons[eNewEnnemi]->Load (NomResource);
            
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
   
   if (mContexte.mbPartieEnCours)
   {
      for (IdBouton = eNew; (IdBouton < eNbBouton) && (false == bBoutonTrouve); ++IdBouton)
      {
         if (  (mPositionsBoutons[IdBouton]->GetX () < aX) && (aX < (mPositionsBoutons[IdBouton]->GetX () + mPositionsBoutons[IdBouton]->GetW ()))
            && (mPositionsBoutons[IdBouton]->GetY () < aY) && (aY < (mPositionsBoutons[IdBouton]->GetY () + mPositionsBoutons[IdBouton]->GetH ())))
         {
            bBoutonTrouve = true;
         }
      }

      if (bBoutonTrouve)
      {
         mContexte.mTypeTourSelectMenu = -1;

         // IdBouton a été incrémenté lors de la dernière itération
         IdBouton--;
         switch (IdBouton)
         {
            case ePause:
               mContexte.mbPartieEnCours = false;
               break;

//            case eNewEnnemi:
// TODO        mJeu.AjoutEnnemi ();
//               break;
               
            default:
               mLog << Info << "Ce bouton n'est pas actif dans ce mode" << EndLine;
               break;
         }
      }
      else
      {
         for (IdTour = 0; (IdTour < mNbTours) && (false == bBoutonTrouve); ++IdTour)
         {
            if (  (mPositionsTours[IdTour]->GetX () < aX) && (aX < (mPositionsTours[IdTour]->GetX () + mPositionsTours[IdTour]->GetW ()))
               && (mPositionsTours[IdTour]->GetY () < aY) && (aY < (mPositionsTours[IdTour]->GetY () + mPositionsTours[IdTour]->GetH ())))
            {
               bBoutonTrouve = true;
            }
         }

         if (bBoutonTrouve)
         {
            mContexte.mTypeTourSelectMenu = IdTour - 1;
         }
         else
         {
            mContexte.mTypeTourSelectMenu = -1;
            
            mLog << Info << "[GAME ON] Aucun bouton correspond à la position : " << aX << ", " << aY << EndLine;
         }
      }
   }
   else
   {
      for (IdBouton = eNew; (IdBouton < eNbBouton) && (false == bBoutonTrouve); ++IdBouton)
      {
         if (  (mPositionsBoutons[IdBouton]->GetX () < aX) && (aX < (mPositionsBoutons[IdBouton]->GetX () + mPositionsBoutons[IdBouton]->GetW ()))
            && (mPositionsBoutons[IdBouton]->GetY () < aY) && (aY < (mPositionsBoutons[IdBouton]->GetY () + mPositionsBoutons[IdBouton]->GetH ())))
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
               mContexte.mbDemandeReset = true;
               mContexte.mbPartieEnCours = true;
               break;

            case eReprendre:
               mContexte.mbPartieEnCours = true;
               break;

            case eQuit:
               mContexte.mbDemandeQuit = true;
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
   mImageFondPtr->Afficher (aScreenPtr, mPositionFondPtr);

  if (mContexte.mbPartieEnCours)
   {
      mImagesBoutons[ePause]     ->Afficher (aScreenPtr, mPositionsBoutons[ePause]);
      //mImagesBoutons[eNewEnnemi] ->Afficher (aScreenPtr, mPositionsBoutons[eNewEnnemi]);

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
