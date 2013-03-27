#include "Fenetre.h"
#include "Rect.h"

CFenetre::CFenetre (void):
   mLogger ("Fenetre"),
   mLargeur (1),
   mHauteur (1)
{

}

CFenetre::~CFenetre (void)
{

}

bool CFenetre::Init (int aLargeur, int aHauteur)
{
   bool bReturn = true;

   mLargeur = aLargeur;
   mHauteur = aHauteur;

   //Initialisation de la SDL
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
   {
      mLogger.error () << "Probleme pour initialiser SDL: " << SDL_GetError();
      bReturn = false;
   }

   // Mettre un titre à la fenêtre
   SDL_WM_SetCaption("TowerDefense by Guit00n 0.2", NULL);

   //Ouvrir une fenetre
   mSurfacePtr.reset (new CSurface (true));
   bReturn = mSurfacePtr->SetVideoMode (mLargeur, mHauteur);
   
   std::string NomImage("../../ressources/Fond.bmp");
   mImagePtr.reset (new CImage ());
   mImagePtr->Load (NomImage);

   return bReturn;
}

void CFenetre::Affiche (void)
{
   CRect::Ptr RectPtr (new CRect ());
   RectPtr->SetX (0);
   RectPtr->SetY (0);
   RectPtr->SetW (mLargeur);
   RectPtr->SetH (mHauteur);
   mImagePtr->Afficher (mSurfacePtr, RectPtr);
}

void CFenetre::Fill (int aValeurRouge, int aValeurVert, int aValeurBleu)
{
   mSurfacePtr->Fill (aValeurRouge, aValeurVert, aValeurBleu);
}

void CFenetre::Flip (void)
{
   mSurfacePtr->Flip ();
}