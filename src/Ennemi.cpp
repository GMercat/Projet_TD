#include "../include/Ennemi.h"
#include "../include/IA.h"

CEnnemi::CEnnemi (CIA* apIA, int aNumCaseDepart, int aNumCaseArrivee):
   mpImage           (NULL),
   mIA               (apIA),
   mNumCaseArrivee   (aNumCaseArrivee)
{
   mType = eType1;
   mCoordonnee.first  = (aNumCaseDepart - ((int)(aNumCaseDepart / NB_CASE_LARGEUR)) * NB_CASE_LARGEUR) * LARGEUR_CASE + (LARGEUR_CASE / 2);
   mCoordonnee.second = ((int)(aNumCaseDepart / NB_CASE_LARGEUR)) * HAUTEUR_CASE + (HAUTEUR_CASE / 2);
   switch (mType)
   {
      case eType1:
         mVitesse = 1;
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
		
   mPosition.w = mpImage->w;
   mPosition.h = mpImage->h;

	return bReturn;
}

void CEnnemi::OnAffiche (SDL_Surface* apScreen)
{
   SDL_BlitSurface (mpImage,NULL,apScreen,&mPosition);
}

void CEnnemi::SetPCCheminCase (std::list<int>& aPPCheminCase)
{
   mPCCheminCase = aPPCheminCase;
}

void CEnnemi::CalculPCChemin  (void)
{
   CalculPCCheminReel (mPCCheminCase);
}

void CEnnemi::CalculPCCheminReel (std::list<int>& aPCChemin)
{
   std::list<TVecteurChemin>::iterator  IterCheminReel;
   std::list<int>::iterator             IterPCChemin   = aPCChemin.begin ();

   std::list<int>::iterator   IterPCCheminNext = IterPCChemin;
   IterPCCheminNext++;

   TVecteurChemin VecteurChemin;
   VecteurChemin.first.first  = mCoordonnee.first;
   VecteurChemin.first.second = mCoordonnee.second;

   mPCCheminReel.clear ();

   // Calcul du x, y de sortie de la case courante
   // Coin supérieur gauche de la case courante
   int Temp = (int)((*IterPCChemin) / (double)NB_CASE_LARGEUR);
   int XCase = ((*IterPCChemin) - Temp * NB_CASE_LARGEUR) * LARGEUR_CASE;
   int YCase = ((int)((*IterPCChemin) / (double)NB_CASE_LARGEUR)) * HAUTEUR_CASE;
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
   else if ((*IterPCCheminNext) == ((*IterPCChemin) - NB_CASE_LARGEUR))
   {
      VecteurChemin.second.first  = XCase + LARGEUR_CASE / 2;
      VecteurChemin.second.second = YCase;
   }
   // Si la prochaine case est celle du bas
   else if ((*IterPCCheminNext) == ((*IterPCChemin) + NB_CASE_LARGEUR))
   {
      VecteurChemin.second.first  = XCase + LARGEUR_CASE / 2;
      VecteurChemin.second.second = YCase + HAUTEUR_CASE - 1;
   }
   else
   {
      // Cas d'erreur car impossible
   }

   mPCCheminReel.push_back (VecteurChemin);
   IterCheminReel = mPCCheminReel.begin ();
   IterPCChemin++;
   std::list<int>::iterator IterLast = aPCChemin.end ();
   IterLast--;
   for (IterPCChemin; IterPCChemin != IterLast; ++IterPCChemin)
   {
      IterPCCheminNext = IterPCChemin;
      IterPCCheminNext++;

      // Calcul du x, y de sortie de la case courante
      // Coin supérieur gauche de la case courante
      XCase = ((*IterPCChemin) - ((int)((*IterPCChemin) / (double)NB_CASE_LARGEUR)) * NB_CASE_LARGEUR) * LARGEUR_CASE;
      YCase = ((int)((*IterPCChemin) / (double)NB_CASE_LARGEUR)) * HAUTEUR_CASE;
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
      else if ((*IterPCCheminNext) == ((*IterPCChemin) - NB_CASE_LARGEUR))
      {
         VecteurChemin.first.first  = (*IterCheminReel).second.first;
         VecteurChemin.first.second = (*IterCheminReel).second.second - 1;

         VecteurChemin.second.first  = XCase + LARGEUR_CASE / 2;
         VecteurChemin.second.second = YCase;
      }
      // Si la prochaine case est celle du bas
      else if ((*IterPCCheminNext) == ((*IterPCChemin) + NB_CASE_LARGEUR))
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
      
      mPCCheminReel.push_back (VecteurChemin);
      IterCheminReel++;
   }

   // TODO PAS DE +1 tout le temps
   VecteurChemin.first.first  = (*IterCheminReel).second.first + 1;
   VecteurChemin.first.second = (*IterCheminReel).second.second;
   VecteurChemin.second.first  = VecteurChemin.first.first + LARGEUR_CASE;
   VecteurChemin.second.second = VecteurChemin.first.second;
}

int CEnnemi::DetermineCaseCourante (void)
{
   return ((int)(mCoordonnee.first / LARGEUR_CASE) + (int)(mCoordonnee.second / HAUTEUR_CASE) * NB_CASE_LARGEUR);
}

void CEnnemi::Avance (void)
{
   double PourcentageVecteurParcouru   = 0.0;
   double DistanceRestante             = 0.0;

   // Calcul du chemin réel
   CalculPCChemin ();

   // Récupération du vecteur courant
   TVecteurChemin VecteurCourant = mPCCheminReel.front ();

   // Calcul de la nouvelle position en fonction de la vitesse
   // 1 - Calcul de l'avancement de l'ennemi sur les vecteurs
   double AvancementSurVecteur = mVitesse * LARGEUR_CASE * ((double)BASE_VITESSE / 100.0);

   // 2 - Test si on reste sur le meme vecteur ou pas (changement de case courante)
   //     Calcul de la distance restante à parcourir sur le vecteur
   DistanceRestante = sqrt ((double)((VecteurCourant.second.first  - mCoordonnee.first)  * (VecteurCourant.second.first  - mCoordonnee.first))
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

   
   mCoordonnee.first += (int)((VecteurCourant.second.first - mCoordonnee.first) * PourcentageVecteurParcouru);
   mCoordonnee.second += (int)((VecteurCourant.second.second - mCoordonnee.second) * PourcentageVecteurParcouru);
   (*mPCCheminReel.begin ()).first.first = mCoordonnee.first;
   (*mPCCheminReel.begin ()).first.second = mCoordonnee.second;

   mPosition.x = mCoordonnee.first - (mpImage->w / 2);
   mPosition.y = mCoordonnee.second - (mpImage->h / 2);
}
