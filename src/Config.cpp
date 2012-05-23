#include "../include/Config.h"

#include <fstream>
#include <sstream>

CConfiguration::CConfiguration (void)
{
   ;
}

CConfiguration::~CConfiguration (void)
{
   ;
}


void CConfiguration::RaZ()
{
   mDonnees.clear();
}

bool CConfiguration::Chargement (const std::string& aNomFichier)
{
   int Position = 0;

   std::ifstream Fichier (aNomFichier.c_str());

   if (false == Fichier.good())
   {
      std::cout << "Impossible d'ouvrir le fichier " << aNomFichier << std::endl;
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

bool CConfiguration::Contient (const std::string& aCle) const
{
   return mDonnees.find (aCle) != mDonnees.end();
}

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
      Last = aStringEntree.find_last_not_of(" \t");

      aStringSortie = aStringEntree.substr(First, Last - First + 1);
   }
   else
   {
      aStringSortie = "";
   }
}


void CConfiguration::EnregistrementDonnee (std::ifstream& aFichier, std::string& aStrType)
{
   // Suivant le type de données
   if (aStrType == "Case")
   {
      EnregistrementTypeCase (aFichier);
   }
   else if (aStrType == "Tour")
   {
      EnregistrementTypeTour (aFichier);
   }
   else
   {
      std::cout << "Type de données à charger inconnu" << std::endl;
   }
}

void CConfiguration::EnregistrementTypeCase (std::ifstream& aFichier)
{
   bool bResultatLecture = false;
   std::string Ligne;
   std::string Cle;
   std::string Valeur;
   std::string Nom;
   std::string Ressource;

   // Lecture du nom de la case
   std::getline (aFichier, Ligne);
   if (false == Ligne.empty ())
   {
      bResultatLecture = LectureLigne (Ligne, Cle, Valeur);
   }
   // Enregistrer le Nom
   if (  (true == bResultatLecture)
      && (false == Cle.empty ()) && (false == Valeur.empty ()))
   {
      Nom = Valeur;
   }

   // Lecture de la ressource associée
   std::getline (aFichier, Ligne);
   if (false == Ligne.empty ())
   {
      bResultatLecture = LectureLigne (Ligne, Cle, Valeur);
   }
   // Enregistrer la Ressource
      if (  (true == bResultatLecture)
         && (false == Cle.empty ()) && (false == Valeur.empty ()))
   {
      Ressource = Valeur;
   }
   
   mDonneesCases[Nom] = Ressource;
}

void CConfiguration::EnregistrementTypeTour   (std::ifstream& aFichier)
{
   bool bResultatLecture = false;
   std::string Ligne;
   std::string Cle;
   std::string Valeur;
   std::string Nom;
   std::stringstream Temp;
   
   TCaracsTour CaracsTour;

   // Lecture du nom de la tour
   std::getline (aFichier, Ligne);
   if (false == Ligne.empty ())
   {
      bResultatLecture = LectureLigne (Ligne, Cle, Valeur);
   }
   // Enregistrer le Nom
   if (  (true == bResultatLecture)
      && (false == Cle.empty ()) && (false == Valeur.empty ()))
   {
      Nom = Valeur;
   }

   // Lecture de la ressource associée
   std::getline (aFichier, Ligne);
   if (false == Ligne.empty ())
   {
      bResultatLecture = LectureLigne (Ligne, Cle, Valeur);
   }
   // Enregistrer la Ressource
   if (  (true == bResultatLecture)
      && (false == Cle.empty ()) && (false == Valeur.empty ()))
   {
      CaracsTour.mRessource = Valeur;
   }

   // Lecture de la portée de la tour
   std::getline (aFichier, Ligne);
   if (false == Ligne.empty ())
   {
      bResultatLecture = LectureLigne (Ligne, Cle, Valeur);
   }
   // Enregistrer la portée
   if (  (true == bResultatLecture)
      && (false == Cle.empty ()) && (false == Valeur.empty ()))
   {
      Temp << Valeur;
      Temp >> CaracsTour.mPortee;
   }

   // Lecture de la puissance des projectiles de la tour
   std::getline (aFichier, Ligne);
   if (false == Ligne.empty ())
   {
      bResultatLecture = LectureLigne (Ligne, Cle, Valeur);
   }
   // Enregistrer la puissance des projectiles
   if (  (true == bResultatLecture)
      && (false == Cle.empty ()) && (false == Valeur.empty ()))
   {
      Temp << Valeur;
      Temp >> CaracsTour.mPuissance;
   }

   // Lecture de la vitesse des projectiles de la tour
   std::getline (aFichier, Ligne);
   if (false == Ligne.empty ())
   {
      bResultatLecture = LectureLigne (Ligne, Cle, Valeur);
   }
   // Enregistrer la vitesse
   if (  (true == bResultatLecture)
      && (false == Cle.empty ()) && (false == Valeur.empty ()))
   {
      Temp << Valeur;
      Temp >> CaracsTour.mVitesse;
   }

   // Lecture de la cadence de tire de la tour
   std::getline (aFichier, Ligne);
   if (false == Ligne.empty ())
   {
      bResultatLecture = LectureLigne (Ligne, Cle, Valeur);
   }
   // Enregistrer la cadence
   if (  (true == bResultatLecture)
      && (false == Cle.empty ()) && (false == Valeur.empty ()))
   {
      Temp << Valeur;
      Temp >> CaracsTour.mCadence;
   }

   mDonneesTours [Nom] = CaracsTour;
}
