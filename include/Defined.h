#ifndef _DEFINED_H_
#define _DEFINED_H_

#include <iostream>
#include <vector>
#include <list>
#include <SDL/SDL.h>

#include "../libs/boost/shared_ptr.hpp"

//#ifdef DEBUG
//#endif
//#define DEBUG

// Le nombre de frame par seconde
const int IMAGES_PAR_SECONDE = 50;

// Largeur menu
const int LARGEUR_MENU = 200;

// Largeur d'une case
const int LARGEUR_CASE = 50;

// Hauteur d'une case
const int HAUTEUR_CASE = 50;

// Base de vitesse
const int BASE_VITESSE = 2;

typedef std::pair<int, int>                  TCoordonnee;
typedef std::pair<TCoordonnee, TCoordonnee > TVecteurChemin ;

#endif
