#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "Defined.h"
#include <map>


class CConfiguration
{
public:

   CConfiguration (void);
   ~CConfiguration (void);

   // Remise à zéro
   void RaZ (void);

   // Chargement d'un fichier de configuration
   bool Chargement (const std::string& aNomFichier);

   // Vérifie si une valeur est associée à la clé passée
   bool Contient (const std::string& aCle) const;

   // Getters
   bool Get (const std::string& aCle, std::string& aValeur) const;
   bool Get (const std::string& aCle, int&    aValeur) const;
   bool Get (const std::string& aCle, long&   aValeur) const;
   bool Get (const std::string& aCle, double& aValeur) const;
   bool Get (const std::string& aCle, bool&   aValeur) const;

private:
   // Supprime les espaces
   void Trim (const std::string& aStringEntree, std::string& aStringSortie);

private:
   std::map<std::string, std::string> mDonnees;
};

#endif