#ifndef _LOG_H_
#define _LOG_H_

#include "Defined.h"

#define LOG_MAX_LENGTH       1000

// Enumeration des degrés de sévérités possibles pour un log
enum TSeverity
{
   LOG_DEBUG = 0,
   LOG_INFO,
   LOG_ERROR,
   LOG_CRITICAL,
   LOG_NB_SEVERITY
};

class CLog
{
public:
   // Type servant à clore un log
   enum TEndLine  {eEndLine};

public:
    CLog (void);
    CLog (const char* aName);
   ~CLog (void);
   
   // Méthodes pour démarrer un log en flux, par défaut niveau LOG_INFO
   const CLog& operator<< (const TSeverity aLevel) const;

   // Opérateur de flux : méthodes explicites pour quelques types nécessitant un traitement spécifique
   const CLog& operator<< (const char*           aValue) const;
   const CLog& operator<< (const std::string&    aValue) const;
   const CLog& operator<< (const int             aValue) const;

   // Pour terminer un log
   void        operator<< (const TEndLine        aValue) const;

private:
   /// Interdiction du constructeur par copie
   CLog (const CLog& aLog);
   /// Interdiction de la copie d'instances
   void operator = (const CLog& aLog);
   
   // Ecriture du log
   void EcrireLog (void) const;
   
   int GetSeverityEscapeColor (const int aLevel) const;
   
private:
   // Membres "mutable" pour que les méthodes flux soient "const" (pour pouvoir faire des logs dans une méthode const)
   const   std::string           mPrefix;       //!< Préfixe (a affiche au début de chaque log)
   mutable TSeverity             mLevel;        //!< Niveau du log
   mutable std::ostringstream    mFluxUtf16;    //!< Flux où stocker le log en cours de constitution (cad jusqu'au EndLine)
};

////////////////////////////////////////////////////////////////////////////////
// Définitions utilisées comme argument pour les logs
////////////////////////////////////////////////////////////////////////////////
extern TSeverity        Debug;
extern TSeverity        Info;
extern TSeverity        Erreur;
extern TSeverity        Critique;
extern CLog::TEndLine   EndLine;

#endif
