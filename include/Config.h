#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "Defined.h"
#include "Log.h"
#include <map>

/**
 * @brief   Structure contenant les caractéristiques d'une tour
 */
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

/**
 * @brief   Structure contenant les caractéristiques d'un ennemi
 */
struct TCaracsEnnemi
{
   std::string mRessource;
   int         mVitesse;
   int         mVie;

   void operator = (const TCaracsEnnemi& aCaracsEnnemi)
   {
      mRessource  = aCaracsEnnemi.mRessource;
      mVitesse    = aCaracsEnnemi.mVitesse;
      mVie        = aCaracsEnnemi.mVie;
   }
};

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

   bool GetRessourceCaseParNom   (const std::string& aNom,  std::string& aRessource) const;
   bool GetCaracsTourParNom      (const std::string& aNom,  std::string& aRessource, int& aPortee, int& aPuissance, int& aVitesse, int& aCadence) const;
   bool GetCaracsTourParId       (const int aId,            std::string& aRessource, int& aPortee, int& aPuissance, int& aVitesse, int& aCadence) const;
   bool GetCaracsEnnemiParNom    (const std::string& aNom,  std::string& aRessource, int& aVitesse, int& aVie) const;
   bool GetRessourceEnnemiParType(const int aType,          std::string& aRessource) const;

   bool GetRessourcesCases    (std::vector<std::string>&    aRessources)      const;
   bool GetRessourcesTours    (std::vector<std::string>&    aRessources)      const;
   bool GetRessourcesEnnemis  (std::vector<std::string>&    aRessources)      const;
   bool GetCaracsTours        (std::list<TCaracsTour>&      aCaracsTours)     const;
   bool GetCaracsEnnemis      (std::list<TCaracsEnnemi>&    aCaracsEnnemis)   const;

private:
   // Lecture d'une ligne
   bool LectureLigne (std::string& aLigne, std::string& aCle, std::string& aValeur);

   // Supprime les espaces
   void Trim (const std::string& aStringEntree, std::string& aStringSortie);

   // Enregistrement de type de données particulier
   void EnregistrementDonnee     (std::ifstream& aFichier, std::string& aStrType);
   void EnregistrementTypeCase   (std::ifstream& aFichier);
   void EnregistrementTypeTour   (std::ifstream& aFichier);
   void EnregistrementTypeEnnemi (std::ifstream& aFichier);

private:
   CLog  mLog;

   std::map<std::string, std::string>     mDonnees;
   std::map<std::string, std::string>     mDonneesCases;
   std::map<std::string, TCaracsTour>     mDonneesTours;
   std::map<std::string, TCaracsEnnemi>   mDonneesEnnemis;
};

#endif
