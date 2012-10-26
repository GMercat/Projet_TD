#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "Defined.h"
#include "Rect.h"
#include <SDL/SDL_rotozoom.h>

class CSurface
{
public:
   typedef boost::shared_ptr<CSurface> Ptr;

public:
   CSurface    (bool bEstFenetre = false);
   ~CSurface   (void);

   void SetAlpha        (int aValeurAlpha);
   void Blit            (CSurface::Ptr& apEcran, CRect::Ptr& aPositionDestPtr);
   bool LoadBMP         (std::string aNom);
   void SetTransparence (int aValeurRouge, int aValeurVert, int aValeurBleu);
   void Flip            (void);
   void Free            (void);
   bool SetVideoMode    (const int aLargeur, const int aHauteur);
   void Rotation		   (double aAngleDegre);

protected:
   bool mbEstFenetre;
   
   SDL_Surface*   mpSurfaceSDLOrigine;
   SDL_Surface*   mpSurfaceSDLAffichable;

private:
   CLog           mLog;
};

#endif