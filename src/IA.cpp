#include "../include/IA.h"
#include "../include/Plateau.h"

CIA::CIA (CPlateau& aPlateau):
   mPlateau (aPlateau)
{
   int IterLigne     = 0;
   int IterColonne   = 0;

   // Mise à zéro de la matrice du graph
   for (IterLigne; IterLigne < NB_CASE_LARGEUR * NB_CASE_HAUTEUR; IterLigne++)
   {
      for (IterColonne= 0; IterColonne < NB_CASE_LARGEUR * NB_CASE_HAUTEUR; IterColonne++)
      {
         if (IterLigne == IterColonne)
         {
            mMatriceGraph[IterColonne][IterLigne] = 0;
         }
         else
         {
            mMatriceGraph[IterColonne][IterLigne] = 999;
         }
      }
   }
}

CIA::~CIA (void)
{
   ;
}

void CIA::ConstruireMatriceGraphe (void)
{
   int IterLargeur = 0;
   int IterHauteur = 0;

   int NumCaseCourante = -1;

   // Parcours du plateau pour construire la matrice
   for (IterLargeur; IterLargeur < NB_CASE_LARGEUR; IterLargeur++)
   {
      for (IterHauteur = 0; IterHauteur < NB_CASE_HAUTEUR; IterHauteur++)
      {
         NumCaseCourante = IterLargeur + (IterHauteur * NB_CASE_LARGEUR);

         if (mPlateau.GetCase(IterLargeur, IterHauteur)->EstVide ())
         {
            // On observe les cases autour
            // Si on est pas sur la bordure gauche, 
            if (IterLargeur != 0)
            {
               // Est ce que la case de gauche est Vide ?
               if (mPlateau.GetCase(IterLargeur - 1, IterHauteur)->EstVide ())
               {
                  mMatriceGraph[NumCaseCourante][(IterLargeur - 1) + IterHauteur * NB_CASE_LARGEUR] = 1;
                  mMatriceGraph[(IterLargeur - 1) + IterHauteur * NB_CASE_LARGEUR][NumCaseCourante] = 1;
               }
               else
               {
                  mMatriceGraph[NumCaseCourante][(IterLargeur - 1) + IterHauteur * NB_CASE_LARGEUR] = 999;
                  mMatriceGraph[(IterLargeur - 1) + IterHauteur * NB_CASE_LARGEUR][NumCaseCourante] = 999;
               }
            }
            // Si on est pas sur la bordure droite, 
            if (IterLargeur != (NB_CASE_LARGEUR - 1))
            {
               // Est ce que la case de droite est Vide ?
               if (mPlateau.GetCase(IterLargeur + 1, IterHauteur)->EstVide ())
               {
                  mMatriceGraph[NumCaseCourante][(IterLargeur + 1) + IterHauteur * NB_CASE_LARGEUR] = 1;
                  mMatriceGraph[(IterLargeur + 1) + IterHauteur * NB_CASE_LARGEUR][NumCaseCourante] = 1;
               }
               else
               {
                  mMatriceGraph[NumCaseCourante][(IterLargeur + 1) + IterHauteur * NB_CASE_LARGEUR] = 999;
                  mMatriceGraph[(IterLargeur + 1) + IterHauteur * NB_CASE_LARGEUR][NumCaseCourante] = 999;
               }
            }
            // Si on est pas sur la bordure du haut, 
            if (IterHauteur != 0)
            {
               // Est ce que la case du haut est Vide ?
               if (mPlateau.GetCase(IterLargeur, IterHauteur - 1)->EstVide ())
               {
                  mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur - 1) * NB_CASE_LARGEUR] = 1;
                  mMatriceGraph[IterLargeur + (IterHauteur - 1) * NB_CASE_LARGEUR][NumCaseCourante] = 1;
               }
               else
               {
                  mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur - 1) * NB_CASE_LARGEUR] = 999;
                  mMatriceGraph[IterLargeur + (IterHauteur - 1) * NB_CASE_LARGEUR][NumCaseCourante] = 999;
               }
            }
            // Si on est pas sur la bordure du bas, 
            if (IterHauteur != (NB_CASE_HAUTEUR - 1))
            {
               // Est ce que la case du dessous est Vide ?
               if (mPlateau.GetCase(IterLargeur, IterHauteur + 1)->EstVide ())
               {
                  mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur + 1) * NB_CASE_LARGEUR] = 1;
                  mMatriceGraph[IterLargeur + (IterHauteur + 1) * NB_CASE_LARGEUR][NumCaseCourante] = 1;
               }
               else
               {
                  mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur + 1) * NB_CASE_LARGEUR] = 999;
                  mMatriceGraph[IterLargeur + (IterHauteur + 1) * NB_CASE_LARGEUR][NumCaseCourante] = 999;
               }
            }
         }
         else
         {
            // On observe les cases autour
            // Si on est pas sur la bordure gauche, 
            if (IterLargeur != 0)
            {
               mMatriceGraph[NumCaseCourante][(IterLargeur - 1) + IterHauteur * NB_CASE_LARGEUR] = 999;
               mMatriceGraph[(IterLargeur - 1) + IterHauteur * NB_CASE_LARGEUR][NumCaseCourante] = 999;
            }
            // Si on est pas sur la bordure droite, 
            if (IterLargeur != (NB_CASE_LARGEUR - 1))
            {
               mMatriceGraph[NumCaseCourante][(IterLargeur + 1) + IterHauteur * NB_CASE_LARGEUR] = 999;
               mMatriceGraph[(IterLargeur + 1) + IterHauteur * NB_CASE_LARGEUR][NumCaseCourante] = 999;
            }
            // Si on est pas sur la bordure du haut, 
            if (IterHauteur != 0)
            {
               mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur - 1) * NB_CASE_LARGEUR] = 999;
               mMatriceGraph[IterLargeur + (IterHauteur - 1) * NB_CASE_LARGEUR][NumCaseCourante] = 999;
            }
            // Si on est pas sur la bordure du bas, 
            if (IterHauteur != (NB_CASE_HAUTEUR - 1))
            {
               mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur + 1) * NB_CASE_LARGEUR] = 999;
               mMatriceGraph[IterLargeur + (IterHauteur + 1) * NB_CASE_LARGEUR][NumCaseCourante] = 999;
            }
         }
      }
   }
   
   CalculCheminMinimaux ();
}

void CIA::MiseAJourMatriceGraphe (int aNumCase, bool abEstOccuped)
{
   // Si on a ajouté une tour
   if (abEstOccuped)
   {
      // Si on est pas sur le bord supérieur
      if (aNumCase >= NB_CASE_LARGEUR)
      {   
         mMatriceGraph[aNumCase][aNumCase - NB_CASE_LARGEUR] = 999;
         mMatriceGraph[aNumCase - NB_CASE_LARGEUR][aNumCase] = 999;
      }
      // Si on est pas sur le bord droit
      if (((aNumCase + 1) % NB_CASE_LARGEUR ) != 0)
      {
         mMatriceGraph[aNumCase][aNumCase + 1] = 999;
         mMatriceGraph[aNumCase + 1][aNumCase] = 999;
      }
      // Si on est pas sur le bord inférieur
      if (aNumCase < (NB_CASE_LARGEUR * (NB_CASE_HAUTEUR - 1)))
      {
         mMatriceGraph[aNumCase][aNumCase + NB_CASE_LARGEUR] = 999;
         mMatriceGraph[aNumCase + NB_CASE_LARGEUR][aNumCase] = 999;
      }
      // Si on est pas sur le bord gauche
      if ((aNumCase % NB_CASE_LARGEUR) != 0)
      {
         mMatriceGraph[aNumCase][aNumCase - 1] = 999;
         mMatriceGraph[aNumCase - 1][aNumCase] = 999;
      }
   }
   else
   {
      int Temp = (int)(aNumCase / (double)NB_CASE_LARGEUR);
      int IterLargeur = (aNumCase - Temp * NB_CASE_LARGEUR);
      int IterHauteur = ((int)(aNumCase / (double)NB_CASE_LARGEUR));
   
      // Si on est pas sur le bord supérieur ET que la case du haut est Vide
      if ((aNumCase >= NB_CASE_LARGEUR) && (mPlateau.GetCase(IterLargeur, IterHauteur - 1)->EstVide ()))
      {   
         mMatriceGraph[aNumCase][aNumCase - NB_CASE_LARGEUR] = 1;
         mMatriceGraph[aNumCase - NB_CASE_LARGEUR][aNumCase] = 1;
      }
      // Si on est pas sur le bord droit ET que la case de droite est Vide
      if ((((aNumCase + 1) % NB_CASE_LARGEUR ) != 0) && (mPlateau.GetCase(IterLargeur + 1, IterHauteur)->EstVide ()))
      {
         mMatriceGraph[aNumCase][aNumCase + 1] = 1;
         mMatriceGraph[aNumCase + 1][aNumCase] = 1;
      }
      // Si on est pas sur le bord inférieur ET que la case du dessous est Vide
      if ((aNumCase < (NB_CASE_LARGEUR * (NB_CASE_HAUTEUR - 1))) && (mPlateau.GetCase(IterLargeur, IterHauteur + 1)->EstVide ()))
      {
         mMatriceGraph[aNumCase][aNumCase + NB_CASE_LARGEUR] = 1;
         mMatriceGraph[aNumCase + NB_CASE_LARGEUR][aNumCase] = 1;
      }
      // Si on est pas sur le bord gauche ET que la case de gauche est Vide
      if (((aNumCase % NB_CASE_LARGEUR) != 0) && (mPlateau.GetCase(IterLargeur - 1, IterHauteur)->EstVide ()))
      {
         mMatriceGraph[aNumCase][aNumCase - 1] = 1;
         mMatriceGraph[aNumCase - 1][aNumCase] = 1;
      }
   }

   CalculCheminMinimaux ();
}

void CIA::CalculCheminMinimaux (void)
{
   int MatriceGraphCalcul [NB_CASE_LARGEUR * NB_CASE_HAUTEUR][NB_CASE_LARGEUR * NB_CASE_HAUTEUR];

   for (int IterLigne = 0; IterLigne < NB_CASE_LARGEUR * NB_CASE_HAUTEUR; IterLigne++)
   {
      for (int IterColonne = 0; IterColonne < NB_CASE_LARGEUR * NB_CASE_HAUTEUR; IterColonne++)
      {
         MatriceGraphCalcul[IterLigne][IterColonne] = mMatriceGraph[IterLigne][IterColonne];
         if ((IterLigne != IterColonne) && (mMatriceGraph[IterLigne][IterColonne] != 999))
         {
            mCheminsMinimaux[IterLigne][IterColonne] = IterLigne;
         }
         else
         {
            mCheminsMinimaux[IterLigne][IterColonne] = 999;
         }
      }
   }

   for (int IterInterm = 0; IterInterm < NB_CASE_LARGEUR * NB_CASE_HAUTEUR; IterInterm++)
   {
      for (int IterLigne = 0; IterLigne < NB_CASE_LARGEUR * NB_CASE_HAUTEUR; IterLigne++)
      {
         for (int IterColonne = 0; IterColonne < NB_CASE_LARGEUR * NB_CASE_HAUTEUR; IterColonne++)
         {
            int Cheminik = MatriceGraphCalcul[IterLigne][IterInterm];
            int Cheminkj = MatriceGraphCalcul[IterInterm][IterColonne];
            if ((Cheminik != 999) && (Cheminkj != 999))
            {
               int Cheminij = Cheminik + Cheminkj;
               if (Cheminij < MatriceGraphCalcul[IterLigne][IterColonne])
               {
                  MatriceGraphCalcul[IterLigne][IterColonne] = Cheminij;
                  mCheminsMinimaux[IterLigne][IterColonne] = mCheminsMinimaux[IterInterm][IterColonne];
               }
            }
         }
      }
   }
}

bool CIA::CalculPlusCourtChemin (int aNumCaseDepart, int aNumCaseArrivee, std::list<int>& aPlusCourtChemin)
{
   bool bReturn = false;

   // Récupération du plus court chemin
   int NumCaseCourante  = aNumCaseDepart;
   int NbIterMax = NB_CASE_HAUTEUR * NB_CASE_LARGEUR;
   int NbIter = 0;

   aPlusCourtChemin.push_back (NumCaseCourante);
   while ((NbIter != NbIterMax) && (NumCaseCourante != aNumCaseArrivee))
   {
      NumCaseCourante = mCheminsMinimaux[aNumCaseArrivee][NumCaseCourante];
      aPlusCourtChemin.push_back (NumCaseCourante);

      ++NbIter;
   }

   bReturn = (NbIter != NbIterMax);

#ifdef DEBUG
   std::cout << "Nombre d'iteration : " << NbIter << std::endl;

   std::list <int>::iterator IterPlusCourtChemin = aPlusCourtChemin.begin ();
   for (IterPlusCourtChemin; IterPlusCourtChemin != aPlusCourtChemin.end (); IterPlusCourtChemin++)
   {
      std::cout << (*IterPlusCourtChemin) << " " << std::endl;
   }
#endif

   return bReturn;
}

void CIA::AfficherMatrice (void)
{
   for (int IterLigne = 0; IterLigne < NB_CASE_LARGEUR * NB_CASE_HAUTEUR; IterLigne++)
   {
      for (int IterColonne= 0; IterColonne < NB_CASE_LARGEUR * NB_CASE_HAUTEUR; IterColonne++)
      {
         std::cout << mMatriceGraph[IterLigne][IterColonne] << " ";
      }
      std::cout << std::endl;
   }
}
