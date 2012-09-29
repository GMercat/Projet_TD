#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Defined.h"

class CImage
{
public:
   typedef boost::shared_ptr<CImage> Ptr;

public:
   CImage (void);
   CImage (std::string& aCheminRessources);
   ~CImage (void);

   inline const int GetLargeur (void) const;
   inline const int GetHauteur (void) const;
   
   void  Afficher (SDL_Surface* apEcran, SDL_Rect& aPosition);
   bool  Load     (std::string& aNomFichier);
   
   void  SetAlpha          (int aValeurAlpha);
   void  SetTransparence   (void);
   
private:
   CLog           mLog;
   SDL_Surface*   mpSurface;

   std::string    mCheminRessources;
};

inline const int CImage::GetLargeur (void) const
{
   return mpSurface->w;
}

inline const int CImage::GetHauteur (void) const
{
   return mpSurface->h;
}

#endif
