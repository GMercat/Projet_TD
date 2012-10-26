#ifndef _RECT_H_
#define _RECT_H_

#include "Defined.h"

class CRect
{
public:
   typedef boost::shared_ptr<CRect> Ptr;

public:
   CRect (void);
   ~CRect (void);

   void SetX (int aX);
   void SetY (int aY);
   void SetH (int aH);
   void SetW (int aW);

   int GetX (void);
   int GetY (void);
   int GetH (void);
   int GetW (void);

   SDL_Rect* GetSDLRect (void);

private:
   SDL_Rect mSDLRect;
};


#endif