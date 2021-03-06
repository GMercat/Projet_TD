#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "Defined.h"
#include <map>

/**
 * @brief   Structure contenant les caract�ristiques d'une tour
 */
struct TCaracsTour
{
   std::string mRessourceBase;      // Ressource graphique de la base de la tour
   std::string mRessourceTourelle;  // Ressource graphique de la tourelle de tire de la tour
   std::string mRessourcePortee;    // Ressource graphique de la port�e de tire de la tour
   int         mPortee;
   int         mPuissance;
   int         mVitesse;
   int         mCadence;

   void operator = (const TCaracsTour& aCaracsTour)
   {
      mRessourceBase       = aCaracsTour.mRessourceBase;
      mRessourceTourelle   = aCaracsTour.mRessourceTourelle;
      mRessourcePortee     = aCaracsTour.mRessourcePortee;
      mPortee              = aCaracsTour.mPortee;
      mPuissance           = aCaracsTour.mPuissance;
      mVitesse             = aCaracsTour.mVitesse;
      mCadence             = aCaracsTour.mCadence;
   };
};

/**
 * @brief   Structure contenant les caract�ristiques d'un ennemi
 */
struct TCaracsEnnemi
{
   std::string mRessource;
   int         mLargeur;
   int         mHauteur;
   int         mVitesse;
   int         mVie;

   void operator = (const TCaracsEnnemi& aCaracsEnnemi)
   {
      mRessource  = aCaracsEnnemi.mRessource;
      mLargeur    = aCaracsEnnemi.mLargeur;
      mHauteur    = aCaracsEnnemi.mHauteur;
      mVitesse    = aCaracsEnnemi.mVitesse;
      mVie        = aCaracsEnnemi.mVie;
   }
};

class CConfiguration
{
public:

   CConfiguration (void);
   ~CConfiguration (void);

   // Remise � z�ro
   void RaZ (void);

   // Chargement d'un fichier de configuration
   bool Chargement (const std::string& aNomFichier);

   // V�rifie si une valeur est associ�e � la cl� pass�e
   bool Contient (const std::string& aCle) const;

   // Getters
   bool Get (const std::string& aCle, std::string& aValeur) const;
   bool Get (const std::string& aCle, int&    aValeur) const;
   bool Get (const std::string& aCle, long&   aValeur) const;
   bool Get (const std::string& aCle, double& aValeur) const;
   bool Get (const std::string& aCle, bool&   aValeur) const;

   bool GetRessourceCaseParNom   (const std::string& aNom,  std::string& aRessource) const;
   bool GetCaracsTourParNom      (const std::string& aNom,  std::string& aRessourceBase, std::string& aRessourceTourelle, std::string& aRessourcePortee, int& aPortee, int& aPuissance, int& aVitesse, int& aCadence) const;
   bool GetCaracsTourParId       (const int aId,            std::string& aRessourceBase, std::string& aRessourceTourelle, std::string& aRessourcePortee, int& aPortee, int& aPuissance, int& aVitesse, int& aCadence) const;
   bool GetCaracsEnnemiParNom    (const std::string& aNom,  std::string& aRessource, int& aLargeur, int& aHauteur, int& aVitesse, int& aVie) const;
   bool GetCaracsEnnemiParId     (const int aId,            std::string& aRessource, int& aLargeur, int& aHauteur, int& aVitesse, int& aVie) const;
   bool GetRessourceEnnemiParType(const int aType,          std::string& aRessource) const;

   bool GetRessourcesCases    (std::vector<std::string>&    aRessources)      const;
   bool GetRessourcesMenuTours    (std::vector<std::string>&    aRessources)      const;
   bool GetRessourcesEnnemis  (std::vector<std::string>&    aRessources)      const;
   bool GetCaracsTours        (std::list<TCaracsTour>&      aCaracsTours)     const;
   bool GetCaracsEnnemis      (std::list<TCaracsEnnemi>&    aCaracsEnnemis)   const;

private:
   // Lecture d'une ligne
   bool LectureLigne (std::string& aLigne, std::string& aCle, std::string& aValeur);

   // Supprime les espaces
   void Trim (const std::string& aStringEntree, std::string& aStringSortie);

   // Lecture et enregistrement d'un �l�ment
   bool LectureEtEnregistrement (std::ifstream& aFichier, std::string& aElement);
   bool LectureEtEnregistrement (std::ifstream& aFichier, int& aElement);

   // Enregistrement de type de donn�es particulier
   void EnregistrementDonnee     (std::ifstream& aFichier, std::string& aStrType);
   void EnregistrementTypeCase   (std::ifstream& aFichier);
   void EnregistrementTypeTour   (std::ifstream& aFichier);
   void EnregistrementTypeEnnemi (std::ifstream& aFichier);

private:
   Log::Logger  mLogger;

   std::map<std::string, std::string>     mDonnees;
   std::map<std::string, std::string>     mDonneesCases;
   std::map<std::string, TCaracsTour>     mDonneesTours;
   std::map<std::string, TCaracsEnnemi>   mDonneesEnnemis;
};

#endif
