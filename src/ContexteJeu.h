#ifndef _CONTEXTE_JEU_H_
#define _CONTEXTE_JEU_H_

#include "Defined.h"

class CContexteJeu
{
public:
    CContexteJeu (void);
   ~CContexteJeu (void);

public:
   int   mTypeTourSelectMenu; // Type de la tour sélectionné dans le menu
   bool  mbPartieEnCours;     // Flag indiquant si une partie est en cours

   bool  mbDemandeReset;   // Flag indiquant qu'un reset de la partie est demandé
   bool  mbDemandeQuit;    // Flag indiquant qu'une fermeture du programme est demandé
};

#endif