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
      std::getline (Fichier, Ligne);

      if (false == Ligne.empty ())
      {
         Position = Ligne.find ('#');

         if (Position != std::string::npos)
         {
            Ligne = Ligne.substr(0, Position);
         }
      }

      // Sépare la clé de la valeur
      if (false == Ligne.empty ())
      {
         Position = Ligne.find ('=');

         if (Position != std::string::npos)
         {
            std::string Cle;
            std::string Valeur;

            Trim (Ligne.substr (0, Position), Cle);
            Trim (Ligne.substr (Position + 1), Valeur);

            if ((false == Cle.empty ()) && (false == Valeur.empty ()))
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
