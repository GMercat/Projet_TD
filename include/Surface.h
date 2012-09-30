#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "Defined.h"

class CSurface
{
public:
   typedef boost::shared_ptr<CSurface> Ptr;

public:
   CSurface    (void);
   virtual ~CSurface   (void);

   void SetAlpha        (int aValeurAlpha);
   void Blit            (CSurface::Ptr& apEcran, SDL_Rect* aPositionDest);
   bool LoadBMP         (std::string aNom);
   void SetTransparence (int aValeurRouge, int aValeurVert, int aValeurBleu);
   void Flip            (void);
   void Free            (void);

protected:
   CLog           mLog;

   SDL_Surface*   mpSurfaceSDL;
};

#endif