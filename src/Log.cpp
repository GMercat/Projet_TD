#include "Log.h"

////////////////////////////////////////////////////////////////////////////////
// Définitions utilisées comme argument
TSeverity         Debug    = LOG_DEBUG;
TSeverity         Info     = LOG_INFO;
TSeverity         Erreur   = LOG_ERROR;
TSeverity         Critique = LOG_CRITICAL;
CLog::TEndLine    EndLine  = CLog::eEndLine;
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief  
 */ 
CLog::CLog (void):
   mPrefix ("Defaut")
{

}

/**
 * @brief 
 */  
CLog::CLog (const char* aName):
   mPrefix (aName)   
{

}

/**
 * @brief   
 */
CLog::~CLog (void)
{

}
   
/**
 * @brief    Méthodes pour démarrer un log en flux
 */
const CLog& CLog::operator<< (const TSeverity aLevel) const
{
   // Ré-initialisation du flux
   mLevel = aLevel;

   mFluxUtf16.str("");
   mFluxUtf16 << std::setfill(' ') << std::setw(0) << std::right << std::dec;
   
   return (*this);
}

/**
 * @brief   Opérateur de flux : méthodes explicites pour quelques types nécessitant un traitement spécifique
 */
const CLog& CLog::operator<< (const char* aValue) const
{
   if (NULL != aValue)
   {
      mFluxUtf16 << aValue;
   }
   else
   {
      mFluxUtf16 << "(NULL)";
   }
   
   return (*this);
}
   
/**
 * @brief   
 */
const CLog& CLog::operator<< (const std::string& aValue) const
{
   mFluxUtf16 << aValue.c_str ();
   
   return (*this);
}

/**
 * @brief   
 */
const CLog& CLog::operator<< (const int aValue) const
{
   mFluxUtf16 << aValue;

   return (*this);
}

/**
 * @brief   Pour terminer un log
 */
void CLog::operator<< (const TEndLine aValue) const
{
   // Ecriture du log
   EcrireLog ();

   // Ré-initialisation du flux
   mLevel = LOG_INFO;
   mFluxUtf16.str("");
   mFluxUtf16 << std::setfill(' ') << std::setw(0) << std::right << std::dec;
}

/**
 * @brief Ecriture du log
 */
void CLog::EcrireLog (void) const
{
   if (mLevel >= LOG_INFO) // TODO a définir le niveau des log
   {
      std::cout << std::setfill(' ') << std::setw(10) << std::left << mPrefix.c_str ()
                << ": "
                << std::setfill(' ') << std::setw(0) << mFluxUtf16.str ().c_str () << std::endl;

      /*std::cout << (char) 27 << "[" << GetSeverityEscapeColor (mLevel) << "m"
                << std::setfill(' ') << std::setw(10) << std::left << mPrefix.c_str ()
                << " "
                << std::setfill(' ') << std::setw(0) << mFluxUtf16.str ().c_str ()
                << (char) 27 << "[39m" << std::endl;*/
   }
}

/**
 * @brief Récupération du code d'échapement ANSI couleur assigné au niveau d'erreur
 *
 * @param[in] aLevel Niveau de sévérité dont on souhaite obtenir le code couleur
 *
 * @return
 *  - Code couleur correspondant au niveau de sévérité fourni en paramètre
 *  - 39 ('reset') si le niveau fourni en paramètre ne correspond pas à un niveau connu.
*/
int CLog::GetSeverityEscapeColor  (const int aLevel) const
{
   int code;

   switch (aLevel)
   {
      case LOG_DEBUG      : code = 39; break;  // Blanc
      case LOG_INFO       : code = 32; break;  // Vert d'intensité normale
      case LOG_ERROR      : code = 31; break;  // Rouge d'intensité normale
      case LOG_CRITICAL   : code = 35; break;  // Magenta d'intensité normale (Rouge intense 91 ne marche pas en telnet natif Windows)
      default             : code = 39; break;  // 'reset' de la couleur (Blanc sur fond noir par exemple)
   }

   return (code);
}

