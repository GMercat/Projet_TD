#include "../include/Ennemi.h"
#include "../include/IA.h"
#include <cmath>

CEnnemi::CEnnemi (CConfiguration& aConfig, CIA* apIA, EType aType, int aNumCaseDepart, int aNumCaseArrivee):
   mConfig           (aConfig),
   mLog              ("Ennemi"),
   mpIA              (apIA),
   mType             (aType),
   mNumCaseArrivee   (aNumCaseArrivee),
   mLargeur          (20), // TODO
   mHauteur          (20)  // TODO
{
   mpIA->GetCoordonneesCaseParNumero (aNumCaseDepart, mCoordonnee);
   
   switch (mType)
   {
      case eType1:
         mVitesse = 2;
         mVie     = 100;
         break;
      case eType2:
         mVitesse = 10;
         mVie     = 50;
         break;
      default:
         mVitesse = 1;
         mVie     = 100;
         break;
   }
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

bool CEnnemi::OnInit (void)
{
   bool bReturn = true;

   std::string CheminRessource;
   std::string NomFichier;

   bool bLectureConf = mConfig.Get ("ressourcesImages", CheminRessource);
   bLectureConf     &= mConfig.GetRessourceEnnemiParType ((int)mType,NomFichier);
   
   //On charge toutes les images dans les surfaces associées
   mImagePtr.reset (new CImage (CheminRessource));
   bReturn = mImagePtr->Load (NomFichier);
	mImagePtr->SetTransparence (255, 255, 255);
   
	return bReturn;
}

void CEnnemi::OnAffiche (CSurface::Ptr& aScreenPtr)
{
   mImagePtr->Afficher (aScreenPtr, mPosition);
}

void CEnnemi::SetPCCheminCase (std::list<int>& aPPCheminCase)
{
   mPCCheminCase = aPPCheminCase;
}

void CEnnemi::GetCentre (int& aXCentre, int& aYCentre)
{
   //TODO BUG quand ennemi mort
   aXCentre = mCoordonnee.first;
   aYCentre = mCoordonnee.second;
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
   DistanceRestante = sqrt ((double)((VecteurCourant.second.first  - mCoordonnee.first)  * (VecteurCourant.second.first  - mCoordonnee.first))
                                + (double)((VecteurCourant.second.second - mCoordonnee.second) * (VecteurCourant.second.second - mCoordonnee.second)));
   
   PourcentageVecteurParcouru = AvancementSurVecteur / DistanceRestante;
   
   if (AvancementSurVecteur > DistanceRestante)
   {
      // On passe à la case suivante
      mPCCheminCase.pop_front ();
      // On passe au vecteur suivant
      mPCCheminReel.pop_front ();
      VecteurCourant = mPCCheminReel.front ();
      AvancementSurVecteur -= DistanceRestante;

      mCoordonnee.first    = VecteurCourant.first.first;
      mCoordonnee.second   = VecteurCourant.first.second;

      //     Calcul de la distance restante à parcourir sur le vecteur
      DistanceRestante = sqrt ((double)((VecteurCourant.second.first  - mCoordonnee.first)  * (VecteurCourant.second.first  - mCoordonnee.first))
                                + (double)((VecteurCourant.second.second - mCoordonnee.second) * (VecteurCourant.second.second - mCoordonnee.second)));
   

      PourcentageVecteurParcouru = AvancementSurVecteur / DistanceRestante;
   }

   // TODO Arrondi à l'entier supérieur sinon à faible vitesse on avance pas
   mCoordonnee.first += /*ceil*/ ((VecteurCourant.second.first - mCoordonnee.first) * (PourcentageVecteurParcouru));
   mCoordonnee.second += /*ceil*/ ((VecteurCourant.second.second - mCoordonnee.second) * (PourcentageVecteurParcouru));
   (*mPCCheminReel.begin ()).first.first = mCoordonnee.first;
   (*mPCCheminReel.begin ()).first.second = mCoordonnee.second;

   mPosition.first   = mCoordonnee.first - (mLargeur / 2);
   mPosition.second  = mCoordonnee.second - (mHauteur / 2);

   mLog << Info << "X = " << mCoordonnee.first << ", Y = " << mCoordonnee.second << EndLine;

}

bool CEnnemi::EstArrive (void)
{
   bool bEstArrive = false;

   if (mPCCheminReel.size () == 1)
   {
      // Récupération du vecteur courant
      TVecteurChemin VecteurCourant = mPCCheminReel.front ();

      //     Calcul de la distance restante à parcourir sur le vecteur
      double DistanceRestante = sqrt ((double)((VecteurCourant.second.first  - mCoordonnee.first)  * (VecteurCourant.second.first  - mCoordonnee.first))
                                    + (double)((VecteurCourant.second.second - mCoordonnee.second) * (VecteurCourant.second.second - mCoordonnee.second)));

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

   mLog << Info << "Vie restante = " << mVie << EndLine;
}

bool CEnnemi::EstVivant (void)
{
   return (mVie > 0);
}
