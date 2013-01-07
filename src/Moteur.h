#ifndef _MOTEUR_H_
#define _MOTEUR_H_

#include "Defined.h"

#include "Log.h"
#include "Jeu.h"

class CMoteur
{
public:
	// Constructeur/Destructeur
	 CMoteur (void);
	~CMoteur (void);
   	
	bool OnInit          (void);                    // La fonction d'initialisation
	void OnQuit          (void);                    // La fonction de quit
	void OnClic          (int aX, int aY);          // La fonction clic	
   void OnMotion        (int aX, int aY);          // La fonction motion
	void OnAffiche       (void);                    // La fonction d'affichage   
   void OnProgression   (void);                    // La fonction de progression des ennemis
   void OnTire          (void);                    // La fonction de tire des tours
	void OnInputEvent    (SDL_Event* apEvent);      // Recupere la touche pressee et ajuste la vitesse du point
	void OnDemande       (void);                    // La fonction de gestion des demandes en attente

private:
   CLog mLog;

	//Le plateau de jeu
	CJeu mJeu;
};

#endif
