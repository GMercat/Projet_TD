#ifndef _TIMER_H_
#define _TIMER_H_

class CTimer
{
public:
    //Initialise les variables (le constructeur)
    CTimer   (void);
    ~CTimer  (void);

    //Les différentes actions du timer
    void Start(void);
    void Stop(void);
    void Pause(void);
    void UnPause(void);

    //recupére le nombre de ticks depuis que le timer a été lancé
    //ou récupére le nombre de ticks depuis que le timer a été mis en pause
    int GetNbTicks (void);

    //Fonctions de vérification du status du timer
    bool IsStarted(void);
    bool IsPaused(void);
    
private:
    //Le temps quand le timer est lancé
    int mNbStartTicks;

    //Les "ticks" enregistré quand le Timer a été mit en pause
    int mNbPausedTicks;

    //Le status du Timer
    bool mbPaused;
    bool mbStarted;
};

#endif