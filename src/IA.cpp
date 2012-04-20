#include "../include/IA.h"
#include "../include/Plateau.h"

CIA::CIA (CPlateau& aPlateau):
   mPlateau (aPlateau)
{
   ;
}

CIA::~CIA (void)
{
   int NbLigne    = mPlateau.GetNbCaseLargeur () * mPlateau.GetNbCaseHauteur ();
   
   for(int IterLigne = 0 ; IterLigne < NbLigne ; IterLigne++)
   {
      delete[] mMatriceGraph[IterLigne];
      delete[] mCheminsMinimaux[IterLigne];
   }
   delete[] mMatriceGraph;
   delete[] mCheminsMinimaux;
}

void CIA::OnInit (void)
{
   int IterLigne     = 0;
   int IterColonne   = 0;

   int NbLigne    = mPlateau.GetNbCaseLargeur () * mPlateau.GetNbCaseHauteur ();
   int NbColonne  = NbLigne;

   // Allocation dynamique de la matrice du graph et des celle des chemins minimaux
   mMatriceGraph     = new int* [NbLigne];
   mCheminsMinimaux  = new int* [NbLigne];
   for (IterLigne = 0; IterLigne < NbLigne ; IterLigne++)
   {
      mMatriceGraph[IterLigne]      = new int[NbColonne];
      mCheminsMinimaux[IterLigne]   = new int[NbColonne];
   }

   // Mise à zéro de la matrice du graph
   for (IterLigne= 0; IterLigne < NbLigne; IterLigne++)
   {
      for (IterColonne= 0; IterColonne < NbColonne; IterColonne++)
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

void CIA::ConstruireMatriceGraphe (void)
{
   int IterLargeur = 0;
   int IterHauteur = 0;

   int NumCaseCourante = -1;
   
   int NbCaseLargeur = mPlateau.GetNbCaseLargeur ();
   int NbCaseHauteur = mPlateau.GetNbCaseHauteur ();

   // Parcours du plateau pour construire la matrice
   for (IterLargeur; IterLargeur < NbCaseLargeur; IterLargeur++)
   {
      for (IterHauteur = 0; IterHauteur < NbCaseHauteur; IterHauteur++)
      {
         NumCaseCourante = IterLargeur + (IterHauteur * NbCaseLargeur);

         if (mPlateau.GetCase(IterLargeur, IterHauteur)->EstVide ())
         {
            // On observe les cases autour
            // Si on est pas sur la bordure gauche, 
            if (IterLargeur != 0)
            {
               // Est ce que la case de gauche est Vide ?
               if (mPlateau.GetCase(IterLargeur - 1, IterHauteur)->EstVide ())
               {
                  mMatriceGraph[NumCaseCourante][(IterLargeur - 1) + IterHauteur * NbCaseLargeur] = 1;
                  mMatriceGraph[(IterLargeur - 1) + IterHauteur * NbCaseLargeur][NumCaseCourante] = 1;
               }
               else
               {
                  mMatriceGraph[NumCaseCourante][(IterLargeur - 1) + IterHauteur * NbCaseLargeur] = 999;
                  mMatriceGraph[(IterLargeur - 1) + IterHauteur * NbCaseLargeur][NumCaseCourante] = 999;
               }
            }
            // Si on est pas sur la bordure droite, 
            if (IterLargeur != (NbCaseLargeur - 1))
            {
               // Est ce que la case de droite est Vide ?
               if (mPlateau.GetCase(IterLargeur + 1, IterHauteur)->EstVide ())
               {
                  mMatriceGraph[NumCaseCourante][(IterLargeur + 1) + IterHauteur * NbCaseLargeur] = 1;
                  mMatriceGraph[(IterLargeur + 1) + IterHauteur * NbCaseLargeur][NumCaseCourante] = 1;
               }
               else
               {
                  mMatriceGraph[NumCaseCourante][(IterLargeur + 1) + IterHauteur * NbCaseLargeur] = 999;
                  mMatriceGraph[(IterLargeur + 1) + IterHauteur * NbCaseLargeur][NumCaseCourante] = 999;
               }
            }
            // Si on est pas sur la bordure du haut, 
            if (IterHauteur != 0)
            {
               // Est ce que la case du haut est Vide ?
               if (mPlateau.GetCase(IterLargeur, IterHauteur - 1)->EstVide ())
               {
                  mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur - 1) * NbCaseLargeur] = 1;
                  mMatriceGraph[IterLargeur + (IterHauteur - 1) * NbCaseLargeur][NumCaseCourante] = 1;
               }
               else
               {
                  mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur - 1) * NbCaseLargeur] = 999;
                  mMatriceGraph[IterLargeur + (IterHauteur - 1) * NbCaseLargeur][NumCaseCourante] = 999;
               }
            }
            // Si on est pas sur la bordure du bas, 
            if (IterHauteur != (NbCaseHauteur - 1))
            {
               // Est ce que la case du dessous est Vide ?
               if (mPlateau.GetCase(IterLargeur, IterHauteur + 1)->EstVide ())
               {
                  mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur + 1) * NbCaseLargeur] = 1;
                  mMatriceGraph[IterLargeur + (IterHauteur + 1) * NbCaseLargeur][NumCaseCourante] = 1;
               }
               else
               {
                  mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur + 1) * NbCaseLargeur] = 999;
                  mMatriceGraph[IterLargeur + (IterHauteur + 1) * NbCaseLargeur][NumCaseCourante] = 999;
               }
            }
         }
         else
         {
            // On observe les cases autour
            // Si on est pas sur la bordure gauche, 
            if (IterLargeur != 0)
            {
               mMatriceGraph[NumCaseCourante][(IterLargeur - 1) + IterHauteur * NbCaseLargeur] = 999;
               mMatriceGraph[(IterLargeur - 1) + IterHauteur * NbCaseLargeur][NumCaseCourante] = 999;
            }
            // Si on est pas sur la bordure droite, 
            if (IterLargeur != (NbCaseLargeur - 1))
            {
               mMatriceGraph[NumCaseCourante][(IterLargeur + 1) + IterHauteur * NbCaseLargeur] = 999;
               mMatriceGraph[(IterLargeur + 1) + IterHauteur * NbCaseLargeur][NumCaseCourante] = 999;
            }
            // Si on est pas sur la bordure du haut, 
            if (IterHauteur != 0)
            {
               mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur - 1) * NbCaseLargeur] = 999;
               mMatriceGraph[IterLargeur + (IterHauteur - 1) * NbCaseLargeur][NumCaseCourante] = 999;
            }
            // Si on est pas sur la bordure du bas, 
            if (IterHauteur != (NbCaseHauteur - 1))
            {
               mMatriceGraph[NumCaseCourante][IterLargeur + (IterHauteur + 1) * NbCaseLargeur] = 999;
               mMatriceGraph[IterLargeur + (IterHauteur + 1) * NbCaseLargeur][NumCaseCourante] = 999;
            }
         }
      }
   }
   
   CalculCheminMinimaux ();
}

void CIA::MiseAJourMatriceGraphe (int aNumCase, bool abEstOccuped)
{
   int NbCaseLargeur = mPlateau.GetNbCaseLargeur ();
   int NbCaseHauteur = mPlateau.GetNbCaseHauteur ();

   // Si on a ajouté une tour
   if (abEstOccuped)
   {
      // Si on est pas sur le bord supérieur
      if (aNumCase >= NbCaseLargeur)
      {   
         mMatriceGraph[aNumCase][aNumCase - NbCaseLargeur] = 999;
         mMatriceGraph[aNumCase - NbCaseLargeur][aNumCase] = 999;
      }
      // Si on est pas sur le bord droit
      if (((aNumCase + 1) % NbCaseLargeur ) != 0)
      {
         mMatriceGraph[aNumCase][aNumCase + 1] = 999;
         mMatriceGraph[aNumCase + 1][aNumCase] = 999;
      }
      // Si on est pas sur le bord inférieur
      if (aNumCase < (NbCaseLargeur * (NbCaseHauteur - 1)))
      {
         mMatriceGraph[aNumCase][aNumCase + NbCaseLargeur] = 999;
         mMatriceGraph[aNumCase + NbCaseLargeur][aNumCase] = 999;
      }
      // Si on est pas sur le bord gauche
      if ((aNumCase % NbCaseLargeur) != 0)
      {
         mMatriceGraph[aNumCase][aNumCase - 1] = 999;
         mMatriceGraph[aNumCase - 1][aNumCase] = 999;
      }
   }
   else
   {
      int Temp = (int)(aNumCase / (double)NbCaseLargeur);
      int IterLargeur = (aNumCase - Temp * NbCaseLargeur);
      int IterHauteur = ((int)(aNumCase / (double)NbCaseLargeur));
   
      // Si on est pas sur le bord supérieur ET que la case du haut est Vide
      if ((aNumCase >= NbCaseLargeur) && (mPlateau.GetCase(IterLargeur, IterHauteur - 1)->EstVide ()))
      {   
         mMatriceGraph[aNumCase][aNumCase - NbCaseLargeur] = 1;
         mMatriceGraph[aNumCase - NbCaseLargeur][aNumCase] = 1;
      }
      // Si on est pas sur le bord droit ET que la case de droite est Vide
      if ((((aNumCase + 1) % NbCaseLargeur ) != 0) && (mPlateau.GetCase(IterLargeur + 1, IterHauteur)->EstVide ()))
      {
         mMatriceGraph[aNumCase][aNumCase + 1] = 1;
         mMatriceGraph[aNumCase + 1][aNumCase] = 1;
      }
      // Si on est pas sur le bord inférieur ET que la case du dessous est Vide
      if ((aNumCase < (NbCaseLargeur * (NbCaseHauteur - 1))) && (mPlateau.GetCase(IterLargeur, IterHauteur + 1)->EstVide ()))
      {
         mMatriceGraph[aNumCase][aNumCase + NbCaseLargeur] = 1;
         mMatriceGraph[aNumCase + NbCaseLargeur][aNumCase] = 1;
      }
      // Si on est pas sur le bord gauche ET que la case de gauche est Vide
      if (((aNumCase % NbCaseLargeur) != 0) && (mPlateau.GetCase(IterLargeur - 1, IterHauteur)->EstVide ()))
      {
         mMatriceGraph[aNumCase][aNumCase - 1] = 1;
         mMatriceGraph[aNumCase - 1][aNumCase] = 1;
      }
   }

   CalculCheminMinimaux ();
}

void CIA::CalculCheminMinimaux (void)
{
   int NbCaseLargeur = mPlateau.GetNbCaseLargeur ();
   int NbCaseHauteur = mPlateau.GetNbCaseHauteur ();
   int NbLigneColonne = NbCaseLargeur * NbCaseHauteur;

   int IterLigne = 0;
   int **MatriceGraphCalcul;

   MatriceGraphCalcul = new int* [NbLigneColonne];
   for (IterLigne = 0; IterLigne < NbLigneColonne ; IterLigne++)
   {
      MatriceGraphCalcul[IterLigne] = new int[NbLigneColonne];
   }

   for (IterLigne = 0; IterLigne < NbCaseLargeur * NbCaseHauteur; IterLigne++)
   {
      for (int IterColonne = 0; IterColonne < NbCaseLargeur * NbCaseHauteur; IterColonne++)
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

   for (int IterInterm = 0; IterInterm < NbCaseLargeur * NbCaseHauteur; IterInterm++)
   {
      for (IterLigne = 0; IterLigne < NbCaseLargeur * NbCaseHauteur; IterLigne++)
      {
         for (int IterColonne = 0; IterColonne < NbCaseLargeur * NbCaseHauteur; IterColonne++)
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

   for(IterLigne = 0 ; IterLigne < NbLigneColonne ; IterLigne++)
   {
      delete[] MatriceGraphCalcul[IterLigne];
   }
   delete[] MatriceGraphCalcul;
}

bool CIA::CalculPlusCourtChemin (int aNumCaseDepart, int aNumCaseArrivee, std::list<int>& aPlusCourtChemin)
{
   bool bReturn = false;
   
   int NbCaseLargeur = mPlateau.GetNbCaseLargeur ();
   int NbCaseHauteur = mPlateau.GetNbCaseHauteur ();

   // Récupération du plus court chemin
   int NumCaseCourante  = aNumCaseDepart;
   int NbIterMax = NbCaseHauteur * NbCaseLargeur;
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

void CIA::CalculPCCheminReel (std::list<int>& aPCChemin, TCoordonnee& aCoordonnees, std::list<TVecteurChemin>& aPCCheminReel)
{
   int NbCaseLargeur = mPlateau.GetNbCaseLargeur ();

   std::list<TVecteurChemin>::iterator  IterCheminReel;
   std::list<int>::iterator             IterPCChemin   = aPCChemin.begin ();

   std::list<int>::iterator   IterPCCheminNext = IterPCChemin;
   IterPCCheminNext++;

   TVecteurChemin VecteurChemin;
   VecteurChemin.first.first  = aCoordonnees.first;
   VecteurChemin.first.second = aCoordonnees.second;

   aPCCheminReel.clear ();

   // Calcul du x, y de sortie de la case courante
   // Coin supérieur gauche de la case courante
   int Temp = (int)((*IterPCChemin) / (double)NbCaseLargeur);
   int XCase = ((*IterPCChemin) - Temp * NbCaseLargeur) * LARGEUR_CASE;
   int YCase = ((int)((*IterPCChemin) / (double)NbCaseLargeur)) * HAUTEUR_CASE;

   // Si il y a une prochaine case
   if (IterPCCheminNext != aPCChemin.end ())
   {
      // Si la prochaine case est celle de gauche
      if ((*IterPCCheminNext) == ((*IterPCChemin) - 1))
      {
         VecteurChemin.second.first  = XCase;
         VecteurChemin.second.second = YCase + HAUTEUR_CASE / 2;
      }
      // Si la prochaine case est celle de droite
      else if ((*IterPCCheminNext) == ((*IterPCChemin) + 1))
      {
         VecteurChemin.second.first  = XCase + LARGEUR_CASE - 1;
         VecteurChemin.second.second = YCase + HAUTEUR_CASE / 2;
      }
      // Si la prochaine case est celle du haut
      else if ((*IterPCCheminNext) == ((*IterPCChemin) - NbCaseLargeur))
      {
         VecteurChemin.second.first  = XCase + LARGEUR_CASE / 2;
         VecteurChemin.second.second = YCase;
      }
      // Si la prochaine case est celle du bas
      else if ((*IterPCCheminNext) == ((*IterPCChemin) + NbCaseLargeur))
      {
         VecteurChemin.second.first  = XCase + LARGEUR_CASE / 2;
         VecteurChemin.second.second = YCase + HAUTEUR_CASE - 1;
      }
      else
      {
         // Cas d'erreur car impossible
      }

      aPCCheminReel.push_back (VecteurChemin);
      IterCheminReel = aPCCheminReel.begin ();
      IterPCChemin++;
      std::list<int>::iterator IterLast = aPCChemin.end ();
      IterLast--;
      for (IterPCChemin; IterPCChemin != IterLast; ++IterPCChemin)
      {
         IterPCCheminNext = IterPCChemin;
         IterPCCheminNext++;

         // Calcul du x, y de sortie de la case courante
         // Coin supérieur gauche de la case courante
         XCase = ((*IterPCChemin) - ((int)((*IterPCChemin) / (double)NbCaseLargeur)) * NbCaseLargeur) * LARGEUR_CASE;
         YCase = ((int)((*IterPCChemin) / (double)NbCaseLargeur)) * HAUTEUR_CASE;
         // Si la prochaine case est celle de gauche
         if ((*IterPCCheminNext) == ((*IterPCChemin) - 1))
         {
            VecteurChemin.first.first  = (*IterCheminReel).second.first - 1;
            VecteurChemin.first.second = (*IterCheminReel).second.second;

            VecteurChemin.second.first  = XCase;
            VecteurChemin.second.second = YCase + HAUTEUR_CASE / 2;
         }
         // Si la prochaine case est celle de droite
         else if ((*IterPCCheminNext) == ((*IterPCChemin) + 1))
         {
            VecteurChemin.first.first  = (*IterCheminReel).second.first + 1;
            VecteurChemin.first.second = (*IterCheminReel).second.second;

            VecteurChemin.second.first  = XCase + LARGEUR_CASE - 1;
            VecteurChemin.second.second = YCase + HAUTEUR_CASE / 2;
         }
         // Si la prochaine case est celle du haut
         else if ((*IterPCCheminNext) == ((*IterPCChemin) - NbCaseLargeur))
         {
            VecteurChemin.first.first  = (*IterCheminReel).second.first;
            VecteurChemin.first.second = (*IterCheminReel).second.second - 1;

            VecteurChemin.second.first  = XCase + LARGEUR_CASE / 2;
            VecteurChemin.second.second = YCase;
         }
         // Si la prochaine case est celle du bas
         else if ((*IterPCCheminNext) == ((*IterPCChemin) + NbCaseLargeur))
         {
            VecteurChemin.first.first  = (*IterCheminReel).second.first;
            VecteurChemin.first.second = (*IterCheminReel).second.second + 1;

            VecteurChemin.second.first  = XCase + LARGEUR_CASE / 2;
            VecteurChemin.second.second = YCase + HAUTEUR_CASE - 1;
         }
         else
         {
            // Cas d'erreur car impossible
         }
      
         aPCCheminReel.push_back (VecteurChemin);
         IterCheminReel++;
      }

      VecteurChemin.first.first  = (*IterCheminReel).second.first + 1;
      VecteurChemin.first.second = (*IterCheminReel).second.second;
      VecteurChemin.second.first  = VecteurChemin.first.first + LARGEUR_CASE;
      VecteurChemin.second.second = VecteurChemin.first.second;

      aPCCheminReel.push_back (VecteurChemin);
   }
   else
   {
      VecteurChemin.second.first  = XCase + LARGEUR_CASE - 1;
      VecteurChemin.second.second = YCase + HAUTEUR_CASE / 2;

      aPCCheminReel.push_back (VecteurChemin);
   }
}

int CIA::GetNumCaseParCoordonnees (TCoordonnee& aCoordonnees)
{
   return mPlateau.GetNumCaseParCoordonnees (aCoordonnees);
}

void CIA::GetCoordonneesCaseParNumero (int aNumero, TCoordonnee& aCoordonnees)
{
   mPlateau.GetCoordonneesCaseParNumero (aNumero, aCoordonnees);
}

void CIA::AfficherMatrice (void)
{
   int NbCaseLargeur = mPlateau.GetNbCaseLargeur ();
   int NbCaseHauteur = mPlateau.GetNbCaseHauteur ();

   for (int IterLigne = 0; IterLigne < NbCaseLargeur * NbCaseHauteur; IterLigne++)
   {
      for (int IterColonne= 0; IterColonne < NbCaseLargeur * NbCaseHauteur; IterColonne++)
      {
         std::cout << mMatriceGraph[IterLigne][IterColonne] << " ";
      }
      std::cout << std::endl;
   }
}
