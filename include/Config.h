#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "Defined.h"
#include <map>

struct TCaracsTour
{
   std::string mRessource; // Ressource graphique
   int         mPortee;
   int         mPuissance;
   int         mVitesse;
   int         mCadence;

   void operator = (const TCaracsTour& aCaracsTour)
   {
      mRessource  = aCaracsTour.mRessource;
      mPortee     = aCaracsTour.mPortee;
      mPuissance  = aCaracsTour.mPuissance;
      mVitesse    = aCaracsTour.mVitesse;
      mCadence    = aCaracsTour.mCadence;
   };
};
   
struct TCaracsEnnemi
{
   std::string mRessource;
   int         mVitesse;
   int         mVie;
};

// Typedefs
typedef std::map<std::string, TCaracsTour>   TDonneesTours;    // Nom - [Ressource, Portee=75, Puissance=2, Cadence=1]
typedef std::map<std::string, TCaracsEnnemi> TDonneesEnnemis;  // Nom - [Ressource, Vitesse=2, Vie=50]

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
   // Lecture d'une ligne
   bool LectureLigne (std::string& aLigne, std::string& aCle, std::string& aValeur);

   // Supprime les espaces
   void Trim (const std::string& aStringEntree, std::string& aStringSortie);

   // Enregistrement de type de données particulier
   void EnregistrementDonnee     (std::ifstream& aFichier, std::string& aStrType);
   void EnregistrementTypeCase   (std::ifstream& aFichier);
   void EnregistrementTypeTour   (std::ifstream& aFichier);

private:
   std::map<std::string, std::string>  mDonnees;
   std::map<std::string, std::string>  mDonneesCases;
   std::map<std::string, TCaracsTour>  mDonneesTours;
   std::map<std::string, TCaracsEnnemi> mDonneesEnnemis;
};

#endif
