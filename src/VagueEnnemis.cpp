#include "VagueEnnemis.h"

// TODO TEMPORAIRE A REFAIRE
#define NB_ENNEMI_VAGUE       5
#define TPS_BASE_INTER_ENNEMI 750

CVagueEnnemis::CVagueEnnemis (void /*TypeEnnemi, nbEnnemis*/):
   mNbEnnemis           (NB_ENNEMI_VAGUE),
   mTempsProchainEnnemi (0)
{
   mTimerEnnemi.Start ();
   // TODO : Type d'ennemi en paramètre
   AjoutEnnemi (/*TypeEnnemi*/);
   mTempsProchainEnnemi = rand() % TPS_BASE_INTER_ENNEMI;
}

CVagueEnnemis::~CVagueEnnemis (void)
{

}