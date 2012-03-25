#ifndef _MOTEUR_H_
#define _MOTEUR_H_

#include "Defined.h"

#include "Jeu.h"
#include "IA.h"

class CMoteur
{
public:
	//Constructeur/Destructeur
	CMoteur();
	~CMoteur();

	//La fonction d'initialisation
	bool OnInit (void);
	//La fonction clic
	void OnClic (int aX, int aY);
	//La fonction d'affichage
	void OnAffiche (SDL_Surface* apScreen);
	
	//Recupere la touche pressee et ajuste la vitesse du point
   void handle_input(SDL_Event* apEvent);
	
private:
	//Le plateau de jeu
	CJeu mJeu;
   CIA mIA;
};

#endif