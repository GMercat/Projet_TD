#include "../include/Defined.h"
#include "../include/Timer.h"

CTimer::CTimer (void):
   mNbStartTicks  (0),
   mNbPausedTicks (0),
   mbPaused       (false),
   mbStarted      (false)
{
}

CTimer::~CTimer (void)
{

}

void CTimer::Start (void)
{
    //On demarre le timer
    mbStarted = true;

    //On enlève la pause du timer
    mbPaused = false;

    //On récupére le temps courant
    mNbStartTicks = SDL_GetTicks();
}

void CTimer::Stop (void)
{
    //On stoppe le timer
    mbStarted = false;

    //On enlève la pause
    mbPaused = false;
}

void CTimer::Pause (void)
{
    //Si le timer est en marche et pas encore en pause
    if( mbStarted && (mbPaused == false) )
    {
        //On met en pause le timer
        mbPaused = true;

        //On calcul le pausedTicks
        mNbPausedTicks = SDL_GetTicks() - mNbStartTicks;
    }
}

void CTimer::UnPause (void)
{
    //Si le timer est en pause
    if (mbPaused)
    {
        //on enlève la pause du timer
        mbPaused = false;

        //On remet à zero le startTicks
        mNbStartTicks = SDL_GetTicks() - mNbPausedTicks;

        //Remise à zero du pausedTicks
        mNbPausedTicks = 0;
    }
}

int CTimer::GetNbTicks (void)
{
    //Si le timer est en marche
    if (mbStarted)
    {
        //Si le timer est en pause
        if (mbPaused)
        {
            //On retourne le nombre de ticks quand le timer a été mis en pause
            return mNbPausedTicks;
        }
        else
        {
            //On retourne le temps courant moins le temps quand il a démarré
            return SDL_GetTicks() - mNbStartTicks;
        }
    }

    //Si le timer n'est pas en marche
    return 0;
}

bool CTimer::IsStarted (void)
{
    return mbStarted;
}

bool CTimer::IsPaused (void)
{
    return mbPaused;
}
