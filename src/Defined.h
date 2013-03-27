#ifndef _DEFINED_H_
#define _DEFINED_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <SDL/SDL.h>

//#include "Log.h"

//#define LOGGER_USE_BOOST_SHARED_PTR

//#include <boost/shared_ptr.hpp>

#include <LoggerCpp/src/LoggerCpp.h>


// Le nombre de frame par seconde
const int IMAGES_PAR_SECONDE = 50;

// Definition du nombre Pi
#define PI     3.14159265

struct TIndexTableau
{
   int mIndLargeur;
   int mIndHauteur;

   TIndexTableau ()
   {
      RaZ ();
   };

   TIndexTableau (int aIndexLargeur, int aIndexHauteur)
   {
      mIndLargeur = aIndexLargeur;
      mIndHauteur = aIndexHauteur;
   };

   TIndexTableau& operator = (const TIndexTableau& aIndex)
   {
      this->mIndLargeur = aIndex.mIndLargeur;
      this->mIndHauteur = aIndex.mIndHauteur;

      return *this;
   };

   void RaZ (void)
   {
      mIndLargeur = -1;
      mIndHauteur = -1;
   };
};

struct TCoordonnee
{
   int mX;
   int mY;

   TCoordonnee ()
   {
      mX = 0;
      mY = 0;
   };

   TCoordonnee (int aX, int aY)
   {
      mX = aX;
      mY = aY;
   };

   TCoordonnee& operator = (const TCoordonnee& aCoordonnee)
   {
      this->mX = aCoordonnee.mX;
      this->mY = aCoordonnee.mY;

      return *this;
   };
};

typedef std::pair<TCoordonnee, TCoordonnee > TVecteurChemin ;

#endif
