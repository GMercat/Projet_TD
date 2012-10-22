#ifndef _VAGUE_ENNEMIS_H_
#define _VAGUE_ENNEMI_H_

#include "Defined.h"
#include "Config.h"
#include "Ennemi.h"
#include "Timer.h"

class CIA;

class CVagueEnnemis
{
public:
   typedef boost::shared_ptr<CVagueEnnemis>  Ptr;
   typedef std::list<CVagueEnnemis::Ptr>     Liste;

public:
   CVagueEnnemis (void);
   ~CVagueEnnemis (void);

private:
   CConfiguration mConfig;
   CIA*           mpIA;

   CEnnemi::Liste mListEnnemi;      
   CTimer         mTimerEnnemi;

   int   mNbEnnemis;
   int   mTempsProchainEnnemi;
};

#endif