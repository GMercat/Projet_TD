#include "../include/Ennemi.h"
#include "../include/IA.h"

CEnnemi::CEnnemi (CIA* apIA, int aNumCaseArrivee):
   mIA               (apIA),
   mNumCaseArrivee   (aNumCaseArrivee)
{
   switch (mType)
   {
      case eType1:
         mVitesse = 5;
         break;
      case eType2:
         mVitesse = 10;
         break;
      default:
         mVitesse = 1;
         break;
   }
}

CEnnemi::~CEnnemi (void)
{
   ;
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
   
   if(mpImage != NULL)
	{
		SDL_FreeSurface(mpImage), mpImage = NULL;
	}
	
	//On charge toutes les images dans les surfaces associées
	mpImage = SDL_LoadBMP ("../Ressources/Ennemi.bmp");
	
   //On teste le retour du chargement
	if ((mpImage == NULL))
	{
		std::cout << "Probleme de chargement de l'image" << std::endl;
		bReturn = false;
	}
	
	//Mis en place de la transparence
	if(SDL_SetColorKey (mpImage, SDL_SRCCOLORKEY, SDL_MapRGB(mpImage->format, 255, 255, 255)) == -1)
		std::cout << "Erreur avec la transparence" << std::endl;
		
	return bReturn;
}

bool CEnnemi::CalculPCChemin  (void)
{
   bool bReturn = false;

   bool bCalculCheminOk = false;
   std::vector <int> PCChemin;

   int NumCaseCourante = DetermineCaseCourante ();

   bCalculCheminOk = mIA->CalculPlusCourtChemin (NumCaseCourante, mNumCaseArrivee, PCChemin);

   if (bCalculCheminOk)
   {
      CalculPCCheminReel (PCChemin);
   }

   return bReturn;
}

void CEnnemi::CalculPCCheminReel (std::vector<int>& aPCChemin)
{
   std::list<TVecteurChemin>::iterator  IterCheminReel;
   std::vector<int>::iterator             IterPCChemin   = aPCChemin.begin ();

   TVecteurChemin VecteurChemin;
   VecteurChemin.first.first  = mCoordonnee.first;
   VecteurChemin.first.second = mCoordonnee.second;

   // Calcul du x, y de sortie de la case courante
   // Coin supérieur gauche de la case courante
   int XCase = ((*IterPCChemin) - ((int)((*IterPCChemin) / NB_CASE_LARGEUR)) * NB_CASE_LARGEUR) * LARGEUR_CASE;
   int YCase = ((int)((*IterPCChemin)/NB_CASE_LARGEUR)) * HAUTEUR_CASE;
   // Si la prochaine case est celle de gauche
   if ((*(IterPCChemin + 1)) == ((*IterPCChemin) - 1))
   {
      VecteurChemin.second.first  = XCase;
      VecteurChemin.second.second = YCase + HAUTEUR_CASE / 2;
   }
   // Si la prochaine case est celle de droite
   else if ((*(IterPCChemin + 1)) == ((*IterPCChemin) + 1))
   {
      VecteurChemin.second.first  = XCase + LARGEUR_CASE;
      VecteurChemin.second.second = YCase + HAUTEUR_CASE / 2;
   }
   // Si la prochaine case est celle du haut
   else if ((*(IterPCChemin + 1)) == ((*IterPCChemin) - NB_CASE_LARGEUR))
   {
      VecteurChemin.second.first  = XCase + LARGEUR_CASE / 2;
      VecteurChemin.second.second = YCase;
   }
   // Si la prochaine case est celle du bas
   else if ((*(IterPCChemin + 1)) == ((*IterPCChemin) + NB_CASE_LARGEUR))
   {
      VecteurChemin.second.first  = XCase + LARGEUR_CASE / 2;
      VecteurChemin.second.second = YCase + HAUTEUR_CASE;
   }
   else
   {
      // Cas d'erreur car impossible
   }

   mPCCheminReel.push_back (VecteurChemin);
   IterCheminReel = mPCCheminReel.begin ();
   IterPCChemin++;
   for (IterPCChemin; IterPCChemin != aPCChemin.end (); ++IterPCChemin)
   {
      VecteurChemin.first.first  = (*IterCheminReel).second.first + 1;
      VecteurChemin.first.second = (*IterCheminReel).second.second + 1;

      // Calcul du x, y de sortie de la case courante
      // Coin supérieur gauche de la case courante
      XCase = ((*IterPCChemin) - ((int)((*IterPCChemin) / NB_CASE_LARGEUR)) * NB_CASE_LARGEUR) * LARGEUR_CASE;
      YCase = ((int)((*IterPCChemin)/NB_CASE_LARGEUR)) * HAUTEUR_CASE;
      // Si la prochaine case est celle de gauche
      if ((*(IterPCChemin + 1)) == ((*IterPCChemin) - 1))
      {
         VecteurChemin.second.first  = XCase;
         VecteurChemin.second.second = YCase + HAUTEUR_CASE / 2;
      }
      // Si la prochaine case est celle de droite
      else if ((*(IterPCChemin + 1)) == ((*IterPCChemin) + 1))
      {
         VecteurChemin.second.first  = XCase + LARGEUR_CASE;
         VecteurChemin.second.second = YCase + HAUTEUR_CASE / 2;
      }
      // Si la prochaine case est celle du haut
      else if ((*(IterPCChemin + 1)) == ((*IterPCChemin) - NB_CASE_LARGEUR))
      {
         VecteurChemin.second.first  = XCase + LARGEUR_CASE / 2;
         VecteurChemin.second.second = YCase;
      }
      // Si la prochaine case est celle du bas
      else if ((*(IterPCChemin + 1)) == ((*IterPCChemin) + NB_CASE_LARGEUR))
      {
         VecteurChemin.second.first  = XCase + LARGEUR_CASE / 2;
         VecteurChemin.second.second = YCase + HAUTEUR_CASE;
      }
      else
      {
         // Cas d'erreur car impossible
      }
      
      mPCCheminReel.push_back (VecteurChemin);
      IterCheminReel++;
   }
}

int CEnnemi::DetermineCaseCourante (void)
{
   return ((int)(mCoordonnee.first / LARGEUR_CASE) + (int)(mCoordonnee.second / HAUTEUR_CASE) * NB_CASE_LARGEUR);
}

void CEnnemi::Avance (void)
{
   // Récupération du vecteur courant
   TVecteurChemin VecteurCourant = mPCCheminReel.front ();

   // Calcul de la nouvelle position en fonction de la vitesse
   // 1 - Calcul de l'avancement de l'ennemi sur les vecteurs
   double AvancementSurVecteur = mVitesse * LARGEUR_CASE * (BASE_VITESSE / 100);

   // 2 - Test si on reste sur le meme vecteur ou pas (changement de case courante)
   //     Calcul de la distance restante à parcourir sur le vecteur
   double DistanceRestante = sqrt ((double)((VecteurCourant.second.first  - mCoordonnee.first)  * (VecteurCourant.second.first  - mCoordonnee.first))
                                + (double)((VecteurCourant.second.second - mCoordonnee.second) * (VecteurCourant.second.second - mCoordonnee.second)));
   
/*   if (AvancementSurVecteur <= DistanceRestante)
   {
      // 2 - A - On reste sur le même vecteur
      double PourcentageVecteurParcouru = AvancementSurVecteur / DistanceRestante;
      mCoordonnee.first += (VecteurCourant.second.first - mCoordonnee.first) * PourcentageVecteurParcouru;
      mCoordonnee.second += (VecteurCourant.second.second - mCoordonnee.second) * PourcentageVecteurParcouru;
      (*mPCCheminReel.begin ()).first.first = mCoordonnee.first;
      (*mPCCheminReel.begin ()).first.second = mCoordonnee.second;
   }
   */
   if (AvancementSurVecteur > DistanceRestante)
   {
      // On passe au vecteur suivant
      mPCCheminReel.pop_front ();
      VecteurCourant = mPCCheminReel.front ();
      AvancementSurVecteur -= DistanceRestante;
   }

   double PourcentageVecteurParcouru = AvancementSurVecteur / DistanceRestante;
   mCoordonnee.first += (int)((VecteurCourant.second.first - mCoordonnee.first) * PourcentageVecteurParcouru);
   mCoordonnee.second += (int)((VecteurCourant.second.second - mCoordonnee.second) * PourcentageVecteurParcouru);
   (*mPCCheminReel.begin ()).first.first = mCoordonnee.first;
   (*mPCCheminReel.begin ()).first.second = mCoordonnee.second;
}
