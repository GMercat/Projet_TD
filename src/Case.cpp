#include "Case.h"

/**
 * @brief   Constructeur de la class "CCase"
 */
CCase::CCase (void):
   mLog                 ("Case"),
	mIdPlateauX          (-1),
	mIdPlateauY          (-1),
	mType		            (eVide),
	mCourImage	         (0),
   mNumCase             (-1),
   mbEstPlusCourtChemin (false),
   mbEstSurvolee        (false)
{
	mPosition.x = 0;
	mPosition.y = 0;
	mPosition.w = 0;
}

/**
 * @brief   Destructeur de la class "CCase"
*/
CCase::~CCase (void)
{
	;
}

/**
 * @brief   Initialisation d'une case
 */
void CCase::OnInit (void)
{
	mCourImage = 0;
	mType = eVide;
}

/**
 * @brief   Méthode permettant l'affichage d'une case
 *
 * @param[in]  aSurfaceDestPtr  Surface SDL générale dans laquelle on affiche les case
 * @param[in]  aSurfaceCasePtr  Surface SDL dans laquelle la case est affichée
 */
void CCase::OnAffiche (CSurface::Ptr& aSurfaceDestPtr, CSurface::Ptr& aSurfaceCasePtr)
{   
   aSurfaceCasePtr->Blit (aSurfaceDestPtr, &mPosition);
}

/**
 * @brief   Méthode de contruction d'une tour dans la case
 *
 * @param[in]  aConfig     Configuration
 * @param[in]  aTypeTour   Type de la tour à construire
 * @param[in]  aPortee     Portée de la tour à construie
 * @param[in]  aPuissance  Puissance de tire de la tour à construire
 * @param[in]  aVitesse    Vitesse des projectiles tirés par la tour
 * @param[in]  aCadence    Cadence de tire de la tour à construire
 *
 * @return Pointeur intelligent sur la tour construite
 */
CTour::Ptr& CCase::ConstruireTour (CConfiguration& aConfig, int aTypeTour, int aPortee, int aPuissance, int aVitesse, int aCadence)
{
   TCoordonnee CoordCentre;
   
   CoordCentre.first = mPosition.x + (mPosition.w / 2);
   CoordCentre.second = mPosition.y + (mPosition.h / 2);

   mTourPtr = CTour::Ptr (new CTour (aConfig, CoordCentre, aTypeTour, aPortee, aPuissance, aVitesse, aCadence));
   return mTourPtr;
}

/**
 * @brief   Méthode permettant de tester si la position passée en paramètre se trouve dans la case
 * 
 * @param[in]  aX Coordonnée X de la position à tester
 * @param(in]  aY Coordonnée Y de la position à tester
 *
 * @return True si on se trouve bien dans la case, false sinon
 */
bool CCase::EstDedans (int aX, int aY)
{
	bool bReturn = true;

	bReturn  = (aX > mPosition.x);
	bReturn &= (aX < (mPosition.x + mPosition.w));
	bReturn &= (aY > mPosition.y);
	bReturn &= (aY < (mPosition.y + mPosition.h));
	
	return bReturn;
}

/**
 * @brief   Teste si la case est vide
 *
 * @return  True si la case est vide, false sinon.
 */
bool CCase::EstVide (void)
{
   return (mType == eVide);
}

/**
 * @brief   Getter du type de la case
 *
 * @return  Le type de la case
 */
const CCase::ETypeCase	CCase::GetType (void) const
{
	return mType;
}

/**
 * @brief   Muttator du type de la case
 *
 * @param[in] aeNouvelEtat Type de la case
 */
void CCase::SetType (CCase::ETypeCase aeNouvelType)
{
	mType = aeNouvelType;
	mCourImage = aeNouvelType;
}

/**
 * @brief   Renseigne la position de la case dans la fenêtre de jeu
 *
 * @parma[in]  apRect         Postion de la case
 * @parma[in]  aIdPlateauX    Index X de la case dans le plateau
 * @parma[in]  aIdPlateauy    Index Y de la case dans le plateau
 */
void CCase::SetPosition (SDL_Rect* apRect, int aIdPlateauX, int aIdPlateauY)
{ 
	mIdPlateauX = aIdPlateauX;
	mIdPlateauY = aIdPlateauY;
	mPosition = *apRect;
}

/**
 * @brief   Muttator du numéro de la case dans le plateau
 *
 * @param[in]  aNumCase Numéro de la case
 */
void  CCase::SetNumCase (int aNumCase)
{
   mNumCase = aNumCase;
}

/**
 * @brief   Getter du numéro de la case dans le plateau
 *
 * @return Numéro de la case
 */
int CCase::GetNumCase (void)
{
   return mNumCase;
}

/**
 * @brief   Coordonnée du centre de la case
 *
 * @param[out] aXCentre Coordonnée X du centre de la case
 * @param[out] aYCentre Coordonnée Y du centre de la case
 */
void CCase::GetCentre (int& aXCentre, int &aYCentre)
{
   aXCentre = mPosition.x + (mPosition.w / 2);
   aYCentre = mPosition.y + (mPosition.h / 2);
}

/**
 * @brief   Getter du type de tour si une tour est construite sur la case
 *
 * @return  Entier correspondant au type de la tour construite sur la case, -1 si pas de tour.
 */
int CCase::GetTypeTour (void)
{
   int TypeRetour = -1;
   if (mTourPtr)
   {
      TypeRetour = mTourPtr->GetTypeTour ();
   }
   return TypeRetour;
}

/**
 * @brief   Getter de la position de la case
 *
 * @return  Restangle SDL correspondant à la position de la case
 */
SDL_Rect& CCase::GetPosition (void)
{
   return mPosition;
}

/**
 * @brief   Renseigne le fait que le plus court chemin passe par cette case
 *
 * @param[in]  abEstPlusCourtChemin True si la case fait partie du plus court chemin
 */
void CCase::SetPlusCourtChemin (bool abEstPlusCourtChemin)
{
   mbEstPlusCourtChemin = abEstPlusCourtChemin;
   if (mbEstPlusCourtChemin)
   {
      mCourImage = 2;
   }
   else
   {
      mCourImage = mType;
   }
}

/**
 * @brief   Retourne le fait que la case fait partie ou non du plus court chemin
 *
 * @return  True si elle en fait partie, false sinon.
 */
bool CCase::EstPlusCourtChemin (void)
{
   return mbEstPlusCourtChemin;
}

/**
 * @brief   Récupération des index "X" et "Y" de la case dans le plateau
 *
 * @param[out] aIdPlateauX    Index X
 * @param[out] aIdPlateauY    Index Y
 */
void CCase::GetIdPlateau (int& aIdPlateauX, int& aIdPlateauY)
{
	aIdPlateauX = mIdPlateauX;
	aIdPlateauY = mIdPlateauY;
}

/**
 * @brief   Marque la case comme survolée par la souris
 *
 * @param[in] abEstSurvolee   Nouvelle valeur
 */
void CCase::MarqueSurvolee (bool abEstSurvolee)
{
   mbEstSurvolee = abEstSurvolee;
}

bool CCase::EstSurvolee (void)
{
   return mbEstSurvolee;
}