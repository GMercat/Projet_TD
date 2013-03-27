#ifndef _FENETRE_H_
#define _FENETRE_H_

#include "Defined.h"
#include "Surface.h"
#include "Image.h"

class CFenetre
{
public:
   typedef std::shared_ptr<CFenetre> Ptr;

public:
   CFenetre (void);
   virtual ~CFenetre (void);

   bool Init (int aLargeur, int aHauteur);
   void Affiche (void);
   void Fill (int aValeurRouge, int aValeurVert, int aValeurBleu);
   void Flip (void);

   inline CSurface::Ptr& GetSurface (void);

private:
   Log::Logger           mLogger;
   CSurface::Ptr  mSurfacePtr;
   CImage::Ptr    mImagePtr;

   int   mLargeur;
   int   mHauteur;
};

CSurface::Ptr& CFenetre::GetSurface (void)
{
   return mSurfacePtr;
}

#endif