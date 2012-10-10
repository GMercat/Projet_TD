#ifndef _FENETRE_H_
#define _FENETRE_H_

#include "Defined.h"
#include "Surface.h"

class CFenetre
{
public:
   typedef boost::shared_ptr<CFenetre> Ptr;

public:
   CFenetre (void);
   virtual ~CFenetre (void);

   bool Init (int aLargeur, int aHauteur);
   void Flip (void);

   inline CSurface::Ptr& GetSurface (void);

private:
   CLog           mLog;
   CSurface::Ptr  mSurfacePtr;
};

CSurface::Ptr& CFenetre::GetSurface (void)
{
   return mSurfacePtr;
}

#endif