#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "Defined.h"
#include "Rect.h"

class CSurface
{
public:
   typedef std::shared_ptr<CSurface> Ptr;

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
   void Fill            (int aValeurRouge, int aValeurVert, int aValeurBleu);

protected:
   bool mbEstFenetre;
   
   SDL_Surface*   mpSurfaceSDLOrigine;
   SDL_Surface*   mpSurfaceSDLAffichable;

private:
   Log::Logger           mLogger;
};

#endif
