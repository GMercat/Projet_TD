#include "Case.h"

/**
 * @brief   Constructeur de la class "CCase"
 */
CCase::CCase (void):
   mLog                 ("Case"),
   mType                (eVide),
   mNumCase             (-1),
   mbEstPlusCourtChemin (false),
   mbEstSurvolee        (false),
	mCourImage	         (0),
   mPositionPtr         (new CRect)
{
;
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
 */
void CCase::OnAffiche (CSurface::Ptr& aSurfaceDestPtr)
{
   mTourPtr->Afficher (aSurfaceDestPtr);
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
CTour::Ptr& CCase::ConstruireTour (CConfiguration& aConfig, int aTypeTour)
{
   TCoordonnee CoordCentre;
   
   CoordCentre.mX = mPositionPtr->GetX () + (mPositionPtr->GetW () / 2);
   CoordCentre.mY = mPositionPtr->GetY () + (mPositionPtr->GetH () / 2);

   mTourPtr = CTour::Ptr (new CTour (aConfig, CoordCentre, aTypeTour));
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

	bReturn  = (aX >  mPositionPtr->GetX ());
	bReturn &= (aX < (mPositionPtr->GetX () + mPositionPtr->GetW ()));
	bReturn &= (aY >  mPositionPtr->GetY ());
	bReturn &= (aY < (mPositionPtr->GetY () + mPositionPtr->GetH ()));
	
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
CCase::ETypeCase	CCase::GetType (void) const
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
 * @param[in]  aRectPtr       Position de la case
 * @param[in]  aIdPlateauX    Index X de la case dans le plateau
 * @param[in]  aIdPlateauy    Index Y de la case dans le plateau
 */
void CCase::SetPosition (CRect::Ptr& aRectPtr, int aIdPlateauX, int aIdPlateauY)
{ 
   mIdPlateau.mIndLargeur  = aIdPlateauX;
   mIdPlateau.mIndHauteur  = aIdPlateauY;
	mPositionPtr = aRectPtr;
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
 * @param[out] aCoordonneeCentre Coordonnée du centre de la case
 */
void CCase::GetCentre (TCoordonnee& aCoordonneeCentre)
{
   aCoordonneeCentre.mX = mPositionPtr->GetX () + (mPositionPtr->GetW () / 2);
   aCoordonneeCentre.mY = mPositionPtr->GetY () + (mPositionPtr->GetH () / 2);
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
CRect::Ptr& CCase::GetPosition (void)
{
   return mPositionPtr;
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
 * @return L'index de la case dans le tableau
 */
TIndexTableau& CCase::GetIdPlateau (void)
{
	return mIdPlateau;
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
