#ifndef _MOTEUR_H_
#define _MOTEUR_H_

#include "Defined.h"

#include "Jeu.h"
#include "IA.h"

class CMoteur
{
public:
	// Constructeur/Destructeur
	CMoteur();
	~CMoteur();
   	
	bool OnInit          (void);                    // La fonction d'initialisation	
	void OnClic          (int aX, int aY);          // La fonction clic	
	void OnAffiche       (SDL_Surface* apScreen);   // La fonction d'affichage   
   void OnProgression   (void);                    // La fonction de progression des ennemis
	void handle_input    (SDL_Event* apEvent);      // Recupere la touche pressee et ajuste la vitesse du point
	
private:
	//Le plateau de jeu
	CJeu mJeu;
   CIA mIA;
};

#endif