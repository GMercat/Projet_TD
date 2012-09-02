#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Defined.h"

class CImage
{
public:
   CImage (void);
   ~CImage (void);
   
   void  Afficher (SDL_Surface* apEcran, SDL_Rect& aPosition);
   bool  Load     (std::string& aNomFichier);
   
   void  SetAlpha    (int aValeurAlpha);
   
private:
   CLog           mLog;
   SDL_Surface*   mpSurface;
};

typedef boost::shared_ptr<CImage> CImagePtr;

#endif
