#include "Ennemi.h"
#include "IA.h"
#include <cmath>

CEnnemi::CEnnemi (CConfiguration& aConfig, CIA* apIA, EType aType, int aNumCaseDepart, int aNumCaseArrivee):
   mConfig           (aConfig),
   mLogger           ("Ennemi"),
   mpIA              (apIA),
   mType             (aType),
   mNumCaseArrivee   (aNumCaseArrivee)
{
   std::string CheminRessource;
   std::string NomFichier;

   bool bLectureConf = mConfig.Get ("ressourcesImages", CheminRessource);
   bLectureConf     &= mConfig.GetCaracsEnnemiParId ((int)mType, NomFichier, mLargeur, mHauteur, mVitesse, mVie);
   
   if (bLectureConf)
   {
      //On charge toutes les images dans les surfaces associées
      mImagePtr.reset (new CImage (CheminRessource));
      mImagePtr->Load (NomFichier);
	   mImagePtr->SetTransparence (255, 255, 255);
   }
   else
   {
      // TODO LOG
   }
   
   mpIA->GetCoordonneesCentreCaseCaseParNumero (aNumCaseDepart, mCoordonnee);
}

CEnnemi::~CEnnemi (void)
{
}

CEnnemi::EType CEnnemi::GetType (void)
{
   return mType;
}

void CEnnemi::SetType (EType aType)
{
   mType = aType;
}

void CEnnemi::OnAffiche (CSurface::Ptr& aScreenPtr)
{
   //mImagePtr->AfficherParCentre (aScreenPtr, mPosition);
   mImagePtr->Afficher (aScreenPtr, mPosition);
}

void CEnnemi::SetPCCheminCase (std::list<int>& aPPCheminCase)
{
   mPCCheminCase = aPPCheminCase;
}

void CEnnemi::GetCentre (TCoordonnee& aCoordonneesCentre)
{
   //TODO BUG quand ennemi mort
   aCoordonneesCentre = mCoordonnee;
}

int CEnnemi::DetermineCaseCourante (void)
{
   return mpIA->GetNumCaseParCoordonnees (mCoordonnee);
}

void CEnnemi::Avance (void)
{
   double PourcentageVecteurParcouru   = 0.0;
   double DistanceRestante             = 0.0;
   
   // Calcul du chemin réel
   mpIA->CalculPCCheminReel (mPCCheminCase, mCoordonnee, mPCCheminReel);

   // Récupération du vecteur courant
   TVecteurChemin VecteurCourant = mPCCheminReel.front ();

   // Calcul de la nouvelle position en fonction de la vitesse
   // 1 - Calcul de l'avancement de l'ennemi sur les vecteurs
   double AvancementSurVecteur = mVitesse;

   // 2 - Test si on reste sur le meme vecteur ou pas (changement de case courante)
   //     Calcul de la distance restante à parcourir sur le vecteur
   DistanceRestante = sqrt ( (double)((VecteurCourant.second.mX - mCoordonnee.mX) * (VecteurCourant.second.mX - mCoordonnee.mX))
                           + (double)((VecteurCourant.second.mY - mCoordonnee.mY) * (VecteurCourant.second.mY - mCoordonnee.mY)));
   
   PourcentageVecteurParcouru = AvancementSurVecteur / DistanceRestante;
   
   if (AvancementSurVecteur > DistanceRestante)
   {
      // On passe à la case suivante
      mPCCheminCase.pop_front ();
      // On passe au vecteur suivant
      mPCCheminReel.pop_front ();
      VecteurCourant = mPCCheminReel.front ();
      AvancementSurVecteur -= DistanceRestante;

      mCoordonnee.mX = VecteurCourant.first.mX;
      mCoordonnee.mY = VecteurCourant.first.mY;

      //     Calcul de la distance restante à parcourir sur le vecteur
      DistanceRestante = sqrt ( (double)((VecteurCourant.second.mX - mCoordonnee.mX) * (VecteurCourant.second.mX - mCoordonnee.mX))
                              + (double)((VecteurCourant.second.mY - mCoordonnee.mY) * (VecteurCourant.second.mY - mCoordonnee.mY)));
   

      PourcentageVecteurParcouru = AvancementSurVecteur / DistanceRestante;
   }

   // TODO Arrondi à l'entier supérieur sinon à faible vitesse on avance pas
   mCoordonnee.mX += /*ceil*/ ((VecteurCourant.second.mX - mCoordonnee.mX) * (PourcentageVecteurParcouru));
   mCoordonnee.mY += /*ceil*/ ((VecteurCourant.second.mY - mCoordonnee.mY) * (PourcentageVecteurParcouru));
   (*mPCCheminReel.begin ()).first.mX = mCoordonnee.mX;
   (*mPCCheminReel.begin ()).first.mY = mCoordonnee.mY;

   mPosition.mX = mCoordonnee.mX - (mLargeur / 2);
   mPosition.mY = mCoordonnee.mY - (mHauteur / 2);

   mLogger.debug () << "X = " << mCoordonnee.mX << ", Y = " << mCoordonnee.mY;
}

bool CEnnemi::EstArrive (void)
{
   bool bEstArrive = false;

   if (mPCCheminReel.size () == 1)
   {
      // Récupération du vecteur courant
      TVecteurChemin VecteurCourant = mPCCheminReel.front ();

      //     Calcul de la distance restante à parcourir sur le vecteur
      double DistanceRestante = sqrt ((double)((VecteurCourant.second.mX - mCoordonnee.mX) * (VecteurCourant.second.mX - mCoordonnee.mX))
                                    + (double)((VecteurCourant.second.mY - mCoordonnee.mY) * (VecteurCourant.second.mY - mCoordonnee.mY)));

      // Est-ce que l'ennemi est arrivé ?
      if (DistanceRestante < 5.0)
      {
         bEstArrive = true;
      }
   }

   return bEstArrive;
}

void CEnnemi::Touche (int aPuissance)
{
   mVie -= aPuissance;

   mLogger.debug () << "Vie restante = " << mVie;
}

bool CEnnemi::EstVivant (void)
{
   return (mVie > 0);
}
