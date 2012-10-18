#ifndef _DEFINED_H_
#define _DEFINED_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>
#include <cstdlib>
#include <SDL/SDL.h>

#include "Log.h"

#include "../libs/boost/shared_ptr.hpp"

// Pour activer ou non les traces DEBUG
//#define DEBUG

// Le nombre de frame par seconde
const int IMAGES_PAR_SECONDE = 50;

typedef std::pair<int, int>                  TCoordonnee;
typedef std::pair<TCoordonnee, TCoordonnee > TVecteurChemin ;

#endif
