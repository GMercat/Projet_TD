#include "Rect.h"

CRect::CRect (void)
{
   mSDLRect.x = 0;
   mSDLRect.y = 0;
   mSDLRect.h = 1;
   mSDLRect.w = 1;
}

CRect::~CRect (void)
{

}

void CRect::SetX (int aX)
{
   mSDLRect.x = aX;
}

void CRect::SetY (int aY)
{
   mSDLRect.y = aY;
}

void CRect::SetH (int aH)
{
   mSDLRect.h = aH;
}

void CRect::SetW (int aW)
{
   mSDLRect.w = aW;
}

int CRect::GetX (void)
{
   return mSDLRect.x;
}

int CRect::GetY (void)
{
   return mSDLRect.y;
}

int CRect::GetH (void)
{
   return mSDLRect.h;
}

int CRect::GetW (void)
{
   return mSDLRect.w;
}

SDL_Rect* CRect::GetSDLRect (void)
{
   return &mSDLRect;
}
