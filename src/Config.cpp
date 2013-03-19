#include "Config.h"

#include <fstream>
#include <sstream>

/**
 * @brief   Constructeur
 */
CConfiguration::CConfiguration (void):
   mLog ("Config")
{
   ;
}

/**
 * @brief   Destructeur
 */
CConfiguration::~CConfiguration (void)
{
   ;
}

/**
 * @brief   Remise à zéro de la configuration
 */
void CConfiguration::RaZ()
{
   mDonnees			   .clear();
   mDonneesCases	   .clear();
   mDonneesTours	   .clear();
   mDonneesEnnemis	.clear();
}

/**
 * @brief   Chargement d'un fichier de configuration
 *
 * @param[in] aNomFichier  Nom du fichier (avec chemin) à lire
 *
 * @return  True, si le chargement de la configuration s'est bien passé, false sinon.
 */
bool CConfiguration::Chargement (const std::string& aNomFichier)
{
   int Position = 0;

   std::ifstream Fichier (aNomFichier.c_str());

   if (false == Fichier.good())
   {
      mLog << Erreur << "Impossible d'ouvrir le fichier " << aNomFichier << EndLine;
      return false;
   }

   while (Fichier.good() && (false == Fichier.eof()))
   {
      std::string Ligne;
      std::string Cle;
      std::string Valeur;

      std::getline (Fichier, Ligne);
      if (false == Ligne.empty ())
      {
         bool ResultatLecture = LectureLigne (Ligne, Cle, Valeur);

         if (  (true == ResultatLecture)
            && ((false == Cle.empty ()) && (false == Valeur.empty ())))
         {
            // Test si on se trouve sur une ligne introduisant un type de données particulier
            if (Cle == "type")
            {
               EnregistrementDonnee (Fichier, Valeur);
            }
            else
            {
               mDonnees[Cle] = Valeur;
            }
         }
      }
   }

   return true;
}

/**
 * @brief   Test si un élément de configuration correspond à la clé passée en paramètre
 *
 * @param[in] aCle   Clé à tester
 *
 * @return True si un élément a été trouvé, false sinon.
 */
bool CConfiguration::Contient (const std::string& aCle) const
{
   return mDonnees.find (aCle) != mDonnees.end();
}

/**
 * @brief   Obtention d'une chaine de caractères correspondant à une clé
 *
 * @param[in]  aCle     Clé de l'élément à chercher
 * @param[out] aValeur  Valeur trouvée
 *
 * @return True si la valeur a été trouvée
 */
bool CConfiguration::Get(const std::string& aCle, std::string& aValeur) const
{
   std::map<std::string, std::string>::const_iterator IterDonnees = mDonnees.find(aCle);

   if (IterDonnees != mDonnees.end())
   {
      aValeur = IterDonnees->second;
      return true;
   }
   else
   {
      return false;
   }
}

/**
 * @brief   Obtention d'un entier correspondant à une clé
 *
 * @param[in]  aCle     Clé de l'élément à chercher
 * @param[out] aValeur  Valeur trouvée
 *
 * @return True si la valeur a été trouvée
 */
bool CConfiguration::Get(const std::string& aCle, int& aValeur) const
{
   std::string String;
   std::stringstream StringStream;


   if (Get(aCle, String))
   {
      StringStream << String;
      StringStream >> aValeur;

      return true;
   }
   else
   {
      return false;
   }
}

/**
 * @brief   Obtention d'un entier correspondant à une clé
 *
 * @param[in]  aCle     Clé de l'élément à chercher
 * @param[out] aValeur  Valeur trouvée
 *
 * @return True si la valeur a été trouvée
 */
bool CConfiguration::Get(const std::string& aCle, long& aValeur) const
{
   std::string String;
   std::stringstream StringStream;

   if (Get(aCle, String))
   {
      StringStream << String;
      StringStream >> aValeur;

      return true;
   }
   else
   {
      return false;
   }
}

/**
 * @brief   Obtention d'un double correspondant à une clé
 *
 * @param[in]  aCle     Clé de l'élément à chercher
 * @param[out] aValeur  Valeur trouvée
 *
 * @return True si la valeur a été trouvée
 */
bool CConfiguration::Get(const std::string& aCle, double& aValeur) const
{
   std::string String;
   std::stringstream StringStream;

   if (Get(aCle, String))
   {
      StringStream << String;
      StringStream >> aValeur;

      return true;
   }
   else
   {
      return false;
   }
}

/**
 * @brief   Obtention d'un booléen correspondant à une clé
 *
 * @param[in]  aCle     Clé de l'élément à chercher
 * @param[out] aValeur  Valeur trouvée
 *
 * @return True si la valeur a été trouvée
 */
bool CConfiguration::Get(const std::string& aCle, bool& aValeur) const
{
   std::string String;

   if (Get(aCle, String))
   {
      aValeur = (String == "true");
      return true;
   }
   else
   {
      return false;
   }
}

/**
 * @brief   Recupération du chemin d'une ressource graphique pour une case à partir du nom
 *
 * @param[in]  aNom        Nom de la case
 * @param[out] aRessource  Chemin du fichier
 *
 * @retrun  True si la ressource a été trouvée
 */
bool CConfiguration::GetRessourceCaseParNom (const std::string& aNom, std::string& aRessource) const
{
   std::map<std::string, std::string>::const_iterator IterDonnees = mDonneesCases.find(aNom);

   if (IterDonnees != mDonneesCases.end())
   {
      aRessource = IterDonnees->second;
      return true;
   }
   else
   {
      return false;
   }
}

/**
 * @brief   Recupération des caractéristiques d'une tour à partir du nom
 *
 * @param[in]  aNom        Nom de la tour
 * @param[out] aRessource  Chemin du fichier
 * @param[out] aPortee     Portée de tire de la tour
 * @param[out] aPuissance  Puissance de tire de la tour
 * @param[out] aVitesse    Vitesse des projectiles tirés par la tour
 * @param[out] aCadence    Cadence de tire de la tour 
 *
 * @retrun  True si les caractéristiques ont été trouvées
 */
bool CConfiguration::GetCaracsTourParNom (const std::string& aNom, std::string& aRessource, int& aPortee, int& aPuissance, int& aVitesse, int& aCadence) const
{
   std::map<std::string, TCaracsTour>::const_iterator IterDonnees = mDonneesTours.find (aNom);

   if (IterDonnees != mDonneesTours.end ())
   {
      aRessource  = IterDonnees->second.mRessource;
      aPortee     = IterDonnees->second.mPortee;
      aPuissance  = IterDonnees->second.mPuissance;
      aVitesse    = IterDonnees->second.mVitesse;
      aCadence    = IterDonnees->second.mCadence;

      return true;
   }
   else
   {
      return false;
   }
}


/**
 * @brief   Recupération des caractéristiques d'une tour à partir de son index
 *
 * @param[in]  aId         Index de la tour
 * @param[out] aRessource  Chemin du fichier
 * @param[out] aPortee     Portée de tire de la tour
 * @param[out] aPuissance  Puissance de tire de la tour
 * @param[out] aVitesse    Vitesse des projectiles tirés par la tour
 * @param[out] aCadence    Cadence de tire de la tour 
 *
 * @retrun  True si les caractéristiques ont été trouvées
 */
bool CConfiguration::GetCaracsTourParId (const int aId, std::string& aRessource, int& aPortee, int& aPuissance, int& aVitesse, int& aCadence) const
{
   int IndexTour = 0;
   std::map<std::string, TCaracsTour>::const_iterator IterDonnees = mDonneesTours.begin ();
   
   while ((IterDonnees != mDonneesTours.end ()) && (aId != IndexTour))
   {
      IndexTour++;
      IterDonnees++;
   }

   if ((IterDonnees != mDonneesTours.end ()) && (aId == IndexTour))
   {
      aRessource  = IterDonnees->second.mRessource;
      aPortee     = IterDonnees->second.mPortee;
      aPuissance  = IterDonnees->second.mPuissance;
      aVitesse    = IterDonnees->second.mVitesse;
      aCadence    = IterDonnees->second.mCadence;

      return true;
   }
   else
   {
      return false;
   }
}


/**
 * @brief   Recupération des caractéristiques d'un ennemi à partir du nom
 *
 * @param[in]  aNom        Nom de l'ennemi
 * @param[out] aRessource  Chemin du fichier
 * @param[out] aLargeur    Largeur d'un ennemi
 * @param[out] aHauteur    Hauteur d'un ennemi
 * @param[out] aVitesse    Vitesse de déplacement de l'ennemi
 * @param[out] aVie        Nombre de point de l'ennemi
 *
 * @retrun  True si les caractéristiques ont été trouvées
 */
bool CConfiguration::GetCaracsEnnemiParNom (const std::string& aNom, std::string& aRessource, int& aLargeur, int& aHauteur, int& aVitesse, int& aVie) const
{
   std::map<std::string, TCaracsEnnemi>::const_iterator IterDonnees = mDonneesEnnemis.find (aNom);

   if (IterDonnees != mDonneesEnnemis.end ())
   {
      aRessource  = IterDonnees->second.mRessource;
      aLargeur    = IterDonnees->second.mLargeur;
      aHauteur    = IterDonnees->second.mHauteur;
      aVitesse    = IterDonnees->second.mVitesse;
      aVie        = IterDonnees->second.mVie;

      return true;
   }
   else
   {
      return false;
   }
}

bool CConfiguration::GetRessourceEnnemiParType (const int aType, std::string& aRessource) const
{
   int IndexEnnemi = 0;
   std::map<std::string, TCaracsEnnemi>::const_iterator IterDonnees = mDonneesEnnemis.begin ();
   
   while ((IterDonnees != mDonneesEnnemis.end ()) && (aType != IndexEnnemi))
   {
      IndexEnnemi++;
      IterDonnees++;
   }

   if ((IterDonnees != mDonneesEnnemis.end ()) && (aType == IndexEnnemi))
   {
      aRessource  = IterDonnees->second.mRessource;
      
      return true;
   }
   else
   {
      return false;
   }
}

bool CConfiguration::GetRessourcesCases (std::vector<std::string>& aRessources) const
{
   bool bResultat = false;
   
   std::map<std::string, std::string>::const_iterator IterRessource;
   for (IterRessource = mDonneesCases.begin (); IterRessource != mDonneesCases.end (); IterRessource++)
   {
      aRessources.push_back((*IterRessource).second);
      bResultat = true;
   }
   return bResultat;
}

bool CConfiguration::GetRessourcesTours (std::vector<std::string>& aRessources) const
{
   bool bResultat = false;
   
   std::map<std::string, TCaracsTour>::const_iterator IterCaracs;
   for (IterCaracs = mDonneesTours.begin (); IterCaracs != mDonneesTours.end (); IterCaracs++)
   {
      aRessources.push_back((*IterCaracs).second.mRessource);
      bResultat = true;
   }
   return bResultat;
}

bool CConfiguration::GetRessourcesEnnemis (std::vector<std::string>& aRessources) const
{
   bool bResultat = false;
   
   std::map<std::string, TCaracsEnnemi>::const_iterator IterCaracs;
   for (IterCaracs = mDonneesEnnemis.begin (); IterCaracs != mDonneesEnnemis.end (); IterCaracs++)
   {
      aRessources.push_back((*IterCaracs).second.mRessource);
      bResultat = true;
   }
   return bResultat;
}

bool CConfiguration::GetCaracsTours (std::list<TCaracsTour>& aCaracsTours) const
{
   bool bResultat = false;

   std::map<std::string, TCaracsTour>::const_iterator IterCarac;
   for (IterCarac = mDonneesTours.begin (); IterCarac != mDonneesTours.end (); IterCarac++)
   {
      aCaracsTours.push_back ((*IterCarac).second);
      bResultat = true;
   }
   return bResultat;
}

bool CConfiguration::GetCaracsEnnemis (std::list<TCaracsEnnemi>& aCaracsEnnemis) const
{
   bool bResultat = false;

   std::map<std::string, TCaracsEnnemi>::const_iterator IterCarac;
   for (IterCarac = mDonneesEnnemis.begin (); IterCarac != mDonneesEnnemis.end (); IterCarac++)
   {
      aCaracsEnnemis.push_back ((*IterCarac).second);
      bResultat = true;
   }
   return bResultat;
}

bool CConfiguration::LectureLigne (std::string& aLigne, std::string& aCle, std::string& aValeur)
{
   bool bResultatLecture = false;

   int Position = aLigne.find ('#');

   if (Position != std::string::npos)
   {
      aLigne = aLigne.substr(0, Position);
   }
   
   if (false == aLigne.empty ())
   {
      // Sépare la clé de la valeur
      Position = aLigne.find ('=');

      if (Position != std::string::npos)
      {
         Trim (aLigne.substr (0, Position), aCle);
         Trim (aLigne.substr (Position + 1), aValeur);
         
         bResultatLecture = true;
      }
   }
   
   return bResultatLecture;
}

void CConfiguration::Trim (const std::string& aStringEntree, std::string& aStringSortie)
{
   int Last  = 0;
   int First = aStringEntree.find_first_not_of (" \t");

   if (First != std::string::npos)
   {
      Last = aStringEntree.find_last_not_of(" \t\r\n");

      aStringSortie = aStringEntree.substr(First, Last - First + 1);
   }
   else
   {
      aStringSortie = "";
   }
}

bool CConfiguration::LectureEtEnregistrement (std::ifstream& aFichier, std::string& aElement)
{
   bool bResultat = false;
   
   std::string Ligne;
   std::string Cle;
   std::string Valeur;

   std::getline (aFichier, Ligne);
   // Lecture de la ligne si elle n'est pas vide
   if (false == Ligne.empty ())
   {
      bResultat = LectureLigne (Ligne, Cle, Valeur);
   }
   // Enregistrement de la valeur
   if (  (true == bResultat)
      && (false == Cle.empty ()) && (false == Valeur.empty ()))
   {
      aElement = Valeur;
   }

   return bResultat;
}

bool CConfiguration::LectureEtEnregistrement (std::ifstream& aFichier, int& aElement)
{
   bool bResultat = false;

   std::string Ligne;
   std::string Cle;
   std::string Valeur;
   std::stringstream Temp;

   std::getline (aFichier, Ligne);
   // Lecture de la ligne si elle n'est pas vide
   if (false == Ligne.empty ())
   {
      bResultat = LectureLigne (Ligne, Cle, Valeur);
   }
   // Enregistrement de la valeur
   if (  (true == bResultat)
      && (false == Cle.empty ()) && (false == Valeur.empty ()))
   {
      Temp << Valeur;
      Temp >> aElement;
   }

   return bResultat;
}

void CConfiguration::EnregistrementDonnee (std::ifstream& aFichier, std::string& aStrType)
{
   std::string StrCase     ("Case");
   std::string StrTour     ("Tour");
   std::string StrEnnemi   ("Ennemi");
   
   // Suivant le type de données
   if (0 == aStrType.compare (StrCase))
   {
      EnregistrementTypeCase (aFichier);
   }
   else if (0 == aStrType.compare (StrTour))
   {
      EnregistrementTypeTour (aFichier);
   }
   else if (0 == aStrType.compare (StrEnnemi))
   {
      EnregistrementTypeEnnemi (aFichier);
   }
   else
   {
      mLog << Erreur << "Type de données à charger inconnu : " << aStrType << EndLine;
   }
}

void CConfiguration::EnregistrementTypeCase (std::ifstream& aFichier)
{
   bool bResultatLecture = false;

   std::string Nom;
   std::string Ressource;

   // Lecture du nom de la case
   bResultatLecture = LectureEtEnregistrement (aFichier, Nom);

   if (bResultatLecture)
   {
      // Lecture de la ressource associée
      bResultatLecture = LectureEtEnregistrement (aFichier, Ressource);
   }
   
   if (bResultatLecture)
   {
      mDonneesCases[Nom] = Ressource;
   }
   else
   {
      // TODO LOG
   }
}

void CConfiguration::EnregistrementTypeTour   (std::ifstream& aFichier)
{
   bool bResultatLecture = false;
   
   std::string Nom;
   TCaracsTour CaracsTour;

   // Lecture du nom de la tour
   bResultatLecture = LectureEtEnregistrement (aFichier, Nom);

   if (bResultatLecture)
   {
      // Lecture de la ressource associée
      bResultatLecture = LectureEtEnregistrement (aFichier, CaracsTour.mRessource);
   }

   if (bResultatLecture)
   {
      // Lecture de la portée de la tour
      bResultatLecture = LectureEtEnregistrement (aFichier, CaracsTour.mPortee);
   }

   if (bResultatLecture)
   {
      // Lecture de la puissance des projectiles de la tour
      bResultatLecture = LectureEtEnregistrement (aFichier, CaracsTour.mPuissance);
   }
   
   if (bResultatLecture)
   {   
      // Lecture de la vitesse des projectiles de la tour
      bResultatLecture = LectureEtEnregistrement (aFichier, CaracsTour.mVitesse);
   }

   if (bResultatLecture)
   {   
      // Lecture de la cadence de tire de la tour
      bResultatLecture = LectureEtEnregistrement (aFichier, CaracsTour.mCadence);
   }

   if (bResultatLecture)
   {
      mDonneesTours [Nom] = CaracsTour;
   }
   else
   {
      //TODO LOG
   }
}

void CConfiguration::EnregistrementTypeEnnemi (std::ifstream& aFichier)
{
   bool bResultatLecture = false;

   std::string    Nom;
   TCaracsEnnemi CaracsEnnemi;

   // Lecture du nom de l'ennemi
   bResultatLecture = LectureEtEnregistrement (aFichier, Nom);

   if (bResultatLecture)
   {
      // Lecture de la ressource associée
      bResultatLecture = LectureEtEnregistrement (aFichier, CaracsEnnemi.mRessource);
   }

   // Lecture de la taille de l'ennemi
   // - Largeur
   if (bResultatLecture)
   {
      bResultatLecture = LectureEtEnregistrement (aFichier, CaracsEnnemi.mLargeur);
   }
   // - Hauteur
   if (bResultatLecture)
   {
      bResultatLecture = LectureEtEnregistrement (aFichier, CaracsEnnemi.mHauteur);
   }
   
   if (bResultatLecture)
   {
      // Lecture de la vitesse de l'ennemi
      bResultatLecture = LectureEtEnregistrement (aFichier, CaracsEnnemi.mVitesse);
   }

   if (bResultatLecture)
   {
      // Lecture du nombre de point de vie de l'ennemi
      bResultatLecture = LectureEtEnregistrement (aFichier, CaracsEnnemi.mVie);
   }
   
   if (bResultatLecture)
   {
      mDonneesEnnemis [Nom] = CaracsEnnemi;
   }
   else
   {
      // TODO LOG
   }
}
