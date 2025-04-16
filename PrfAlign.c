/****************************************************************************/
/*																			*/
/*	But: Implementation des routines d'alignement							*/
/*																			*/
/****************************************************************************/

#include <stdlib.h>
#include "PrfAlign.h"

/**************/
/* CONSTANTES */
/**************/

/*-------------------------*/
/* Coordonnes non definies */
/*-------------------------*/

const TCoord PA_COORD_NOT_DEF = {PD_POS_IDX_NOT_DEF, SD_MOL_IDX_NOT_DEF};


/*******************************/
/* IMPLEMENTATION DES ROUTINES */
/*******************************/

/*======================================================*/
/* Manipulation des vecteur de booleen // a la sequence */
/*======================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un vecteur de booleens									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| BooleanNbr				| Nombre de booleens				*/
/* Sortie:	| I_BooleanVect				| Vecteur de booleens				*/
/* Erreur:	| I_BooleanVect=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TBooleanVectPtr I_BooleanVect(TMolIndex BooleanNbr)
{
	TBooleanVectPtr BooleanVectPtr;
	
	BooleanVectPtr = (TBooleanVectPtr)malloc(sizeof(TBooleanVect));
	if (!BooleanVectPtr) {
		/* Erreur allocation */
		return NULL;
	}
	BooleanVectPtr->BooleanArray = (TBoolean*)calloc(BooleanNbr,
	sizeof(TBoolean));
	if (!(BooleanVectPtr->BooleanArray)) {
		/* Erreur allocation */
		free(BooleanVectPtr);
		return NULL;
	}
	BooleanVectPtr->BooleanNbr = BooleanNbr;
	return BooleanVectPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de booleens										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| BooleanVectPtr			| Vecteur de booleens				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_BooleanVect(TBooleanVectPtr BooleanVectPtr)
{
	free(BooleanVectPtr->BooleanArray);
	free(BooleanVectPtr);
}

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Mise a faux du vecteur de booleens		 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| BooleanVectPtr			| Vecteur de booleens				*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void BooleanVect_Reset(TBooleanVectPtr BooleanVectPtr)
{
	TMolIndex BooleanIndex;
	TBoolean *BooleanArray;
	
	BooleanArray = BooleanVect_Array(BooleanVectPtr);
	for (BooleanIndex = 1; BooleanIndex <=
	BooleanVect_BooleanNbr(BooleanVectPtr); BooleanIndex++) {
		BooleanArray_PutBooleanNth(BooleanArray, FALSE, BooleanIndex);
	}
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de booleens										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| BooleanVectPtr			| Vecteur de booleens				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_BooleanVect(TBooleanVectPtr BooleanVectPtr)
{
	TMolIndex BooleanIndex;
	
	for (BooleanIndex = 1; BooleanIndex <=
	BooleanVect_BooleanNbr(BooleanVectPtr); BooleanIndex++) {
		Print_Boolean(BooleanVect_BooleanNth(BooleanVectPtr, BooleanIndex));
		printf("\n");
	}
}

/*=============================*/
/* Routine des type de sommets */
/*=============================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un type de sommet											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Vertex					| Type de sommet					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Vertex(TVertex Vertex)
{
	switch (Vertex) {
	  case PA_B: printf("B"); break;
	  case PA_M: printf("M"); break;
	  case PA_I: printf("I"); break;
	  case PA_D: printf("D"); break;
	  case PA_E: printf("E"); break;
	  case PA_VTX_NOT_DEF: printf("*");
	}
}

/*=========================================*/
/* Routines de manipulation de coordonnees */
/*=========================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression de coordonnees				 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| OutPutFile				| Fichier de sortie					*/
/*			| CoordPtr					| Coordonnees						*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Out_Coord(FILE *OutPutFile, TCoordPtr CoordPtr)
{
 Out_PosIndex(OutPutFile, Coord_PosIndex(CoordPtr));
 fprintf(OutPutFile, "  ");
 Out_MolIndex(OutPutFile, Coord_MolIndex(CoordPtr));
}

/*--------------------------------------------------------------------------*/
/* Impression de coordonnees				 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CoordPtr					| Coordonnees						*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_Coord(TCoordPtr CoordPtr)
{
 printf("(");
 Print_PosIndex(Coord_PosIndex(CoordPtr));
 printf(",");
 Print_MolIndex(Coord_MolIndex(CoordPtr));
 printf(")");
}

/*=====================================*/
/* Routines de manipulation des noeuds */
/*=====================================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul de s(M+)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodePtr					| Noeud								*/
/*			| NodeCoordPtr				| Coord. du noeud					*/
/*			| FirstNode					| Indique s'il s'agit du 1er noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| StartCoordPtr				| f(M+)								*/
/*			| Node_CalcMPlus			| s(M+)								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore Node_CalcMPlus(TNodePtr NodePtr, TCoordPtr NodeCoordPtr, TBoolean
FirstNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr)
{
	TScore B;				/* Score d'initiation			*/
	TScore BM, DM, MM, IM;	/* Score de transition vers M	*/
	TScore Score;			/* Score calcule				*/
	TScore ScoreMPlus;		/* s(M+)						*/
	
	ScoreMPlus = PD_INFINITE;
	Coord_Reset(StartCoordPtr);
	/* Par B */
	if (((B = (FirstNode) ? InsPos_B0(InsPosPtr) :
	InsPos_B1(InsPosPtr)) != PD_INFINITE) &&
	((BM = InsPos_BM(InsPosPtr)) != PD_INFINITE)) {
		ScoreMPlus = B + BM;
		*StartCoordPtr = *NodeCoordPtr;
	}
	/* Par D */
	if ((Node_D(NodePtr) != PD_INFINITE) &&
	((DM = InsPos_DM(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_D(NodePtr) + DM) > ScoreMPlus)) {
		ScoreMPlus = Score;
		*StartCoordPtr = Node_DStartCoord(NodePtr);
	}
	/* Par M */
	if ((Node_M(NodePtr) != PD_INFINITE) &&
	((MM = InsPos_MM(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_M(NodePtr) + MM) > ScoreMPlus)) {
		ScoreMPlus = Score;
		*StartCoordPtr = Node_MStartCoord(NodePtr);
	}
	/* Par I */
	if ((Node_I(NodePtr) != PD_INFINITE) &&
	((IM = InsPos_IM(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_I(NodePtr) + IM) > ScoreMPlus)) {
		ScoreMPlus = Score;
		*StartCoordPtr = Node_IStartCoord(NodePtr);
	}
	return ScoreMPlus;
}

/*--------------------------------------------------------------------------*/
/* Calcul de s(I+)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodePtr					| Noeud								*/
/*			| NodeCoordPtr				| Coord. du noeud					*/
/*			| FirstNode					| Indique s'il s'agit du 1er noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| StartCoordPtr				| f(I+)								*/
/*			| Node_CalcIPlus			| s(I+)								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore Node_CalcIPlus(TNodePtr NodePtr, TCoordPtr NodeCoordPtr, TBoolean
FirstNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr)
{
	TScore B;				/* Score d'initiation			*/
	TScore BI, DI, MI, II;	/* Score de transition vers I	*/
	TScore Score;			/* Score calcule				*/
	TScore ScoreIPlus;		/* s(I+)						*/
	
	ScoreIPlus = PD_INFINITE;
	Coord_Reset(StartCoordPtr);
	/* Par B */
	if (((B = (FirstNode) ? InsPos_B0(InsPosPtr) :
	InsPos_B1(InsPosPtr)) != PD_INFINITE) &&
	((BI = InsPos_BI(InsPosPtr)) != PD_INFINITE)) {
		ScoreIPlus = B + BI;
		*StartCoordPtr = *NodeCoordPtr;
	}
	/* Par D */
	if ((Node_D(NodePtr) != PD_INFINITE) &&
	((DI = InsPos_DI(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_D(NodePtr) + DI) > ScoreIPlus)) {
		ScoreIPlus = Score;
		*StartCoordPtr = Node_DStartCoord(NodePtr);
	}
	/* Par M */
	if ((Node_M(NodePtr) != PD_INFINITE) &&
	((MI = InsPos_MI(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_M(NodePtr) + MI) > ScoreIPlus)) {
		ScoreIPlus = Score;
		*StartCoordPtr = Node_MStartCoord(NodePtr);
	}
	/* Par I */
	if ((Node_I(NodePtr) != PD_INFINITE) &&
	((II = InsPos_II(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_I(NodePtr) + II) > ScoreIPlus)) {
		ScoreIPlus = Score;
		*StartCoordPtr = Node_IStartCoord(NodePtr);
	}
	return ScoreIPlus;
}

/*--------------------------------------------------------------------------*/
/* Calcul de s(D+)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodePtr					| Noeud								*/
/*			| NodeCoordPtr				| Coord. du noeud					*/
/*			| FirstNode					| Indique s'il s'agit du 1er noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| StartCoordPtr				| f(D+)								*/
/*			| Node_CalcDPlus			| s(D+)								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore Node_CalcDPlus(TNodePtr NodePtr, TCoordPtr NodeCoordPtr, TBoolean
FirstNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr)
{
	TScore B;				/* Score d'initiation			*/
	TScore BD, DD, MD, ID;	/* Score de transition vers D	*/
	TScore Score;			/* Score calcule				*/
	TScore ScoreDPlus;		/* s(D+)						*/
	
	ScoreDPlus = PD_INFINITE;
	Coord_Reset(StartCoordPtr);
	/* Par B */
	if (((B = (FirstNode) ? InsPos_B0(InsPosPtr) :
	InsPos_B1(InsPosPtr)) != PD_INFINITE) &&
	((BD = InsPos_BD(InsPosPtr)) != PD_INFINITE)) {
		ScoreDPlus = B + BD;
		*StartCoordPtr = *NodeCoordPtr;
	}
	/* Par D */
	if ((Node_D(NodePtr) != PD_INFINITE) &&
	((DD = InsPos_DD(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_D(NodePtr) + DD) > ScoreDPlus)) {
		ScoreDPlus = Score;
		*StartCoordPtr = Node_DStartCoord(NodePtr);
	}
	/* Par M */
	if ((Node_M(NodePtr) != PD_INFINITE) &&
	((MD = InsPos_MD(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_M(NodePtr) + MD) > ScoreDPlus)) {
		ScoreDPlus = Score;
		*StartCoordPtr = Node_MStartCoord(NodePtr);
	}
	/* Par I */
	if ((Node_I(NodePtr) != PD_INFINITE) &&
	((ID = InsPos_ID(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_I(NodePtr) + ID) > ScoreDPlus)) {
		ScoreDPlus = Score;
		*StartCoordPtr = Node_IStartCoord(NodePtr);
	}
	return ScoreDPlus;
}

/*--------------------------------------------------------------------------*/
/* Calcul de s(E+)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodePtr					| Noeud								*/
/*			| NodeCoordPtr				| Coord. du noeud					*/
/*			| FirstNode					| Indique s'il s'agit du 1er noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| StartCoordPtr				| f(E+)								*/
/*			| Node_CalcEPlus			| s(E+)								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore Node_CalcEPlus(TNodePtr NodePtr, TCoordPtr NodeCoordPtr, TBoolean
FirstNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr)
{
	TScore B;				/* Score d'initiation			*/
	TScore BE, DE, ME, IE;	/* Score de transition vers E	*/
	TScore Score;			/* Score calcule				*/
	TScore ScoreEPlus;		/* s(E+)						*/
	
	ScoreEPlus = PD_INFINITE;
	Coord_Reset(StartCoordPtr);
	/* Par B */
	if (((B = (FirstNode) ? InsPos_B0(InsPosPtr) :
	InsPos_B1(InsPosPtr)) != PD_INFINITE) &&
	((BE = InsPos_BE(InsPosPtr)) != PD_INFINITE)) {
		ScoreEPlus = B + BE;
		*StartCoordPtr = *NodeCoordPtr;
	}
	/* Par D */
	if ((Node_D(NodePtr) != PD_INFINITE) &&
	((DE = InsPos_DE(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_D(NodePtr) + DE) > ScoreEPlus)) {
		ScoreEPlus = Score;
		*StartCoordPtr = Node_DStartCoord(NodePtr);
	}
	/* Par M */
	if ((Node_M(NodePtr) != PD_INFINITE) &&
	((ME = InsPos_ME(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_M(NodePtr) + ME) > ScoreEPlus)) {
		ScoreEPlus = Score;
		*StartCoordPtr = Node_MStartCoord(NodePtr);
	}
	/* Par I */
	if ((Node_I(NodePtr) != PD_INFINITE) &&
	((IE = InsPos_IE(InsPosPtr)) != PD_INFINITE) &&
	((Score = Node_I(NodePtr) + IE) > ScoreEPlus)) {
		ScoreEPlus = Score;
		*StartCoordPtr = Node_IStartCoord(NodePtr);
	}
	return ScoreEPlus;
}

/*--------------------------------------------------------------------------*/
/* Calcul d'un noeud						 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodePtr					| Noeud								*/
/*			| NodeCoordPtr				| Coordonnees du noeud				*/
/*			| SecondNode				| Indique s'il s'agit du 2e noeud	*/
/*			| LastNode					| Ind. s'il s'agit du dern. noeud	*/
/*			| InsPosPtr1				| 1ere position d'insertion			*/
/*			| MatchPosPtr				| Position match					*/
/*			| InsPosPtr2				| 2eme position d'insertion			*/
/*			| Mol						| Molecule							*/
/*			| NodePtr11					| Noeud (1,1)						*/
/*			| NodePtr12					| Noeud (1,2)						*/
/*			| NodePtr21					| Noeud (2,1)						*/
/* Sortie:	| StartCoordPtr				| f(E) par ce noeud					*/
/*			| Node_Calc					| s(E) par ce noeud					*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore Node_Calc(TNodePtr NodePtr, TCoordPtr NodeCoordPtr, TBoolean SecondNode,
TBoolean LastNode, TInsPosPtr InsPosPtr1, TMatchPosPtr MatchPosPtr, TInsPosPtr
InsPosPtr2, TMol Mol, TNodePtr NodePtr11, TNodePtr NodePtr12, TNodePtr
NodePtr21, TCoordPtr StartCoordPtr)
{
	TScore ScoreMPlus;		/* Score de M+								*/
	TScore ScoreIPlus;		/* Score de I+								*/
	TScore ScoreDPlus;		/* Score de D+								*/
	TScore M, I, D;			/* Score match, d'insertion, de deletion	*/
	TScore ScoreEPlus;		/* Score de E+								*/
	TScore ScoreE;			/* Score de E								*/
	TScore E;				/* Score de terminaison						*/
	TCoord StartCoord;		/* Coord. de depart							*/
	TCoord NodeCoord;		/* Coord. d'un noeud						*/
	
	/* Calcul de s(M) */
	if ((NodePtr11) && ((M = ScoreVect_ScoreNth(MatchPos_M(MatchPosPtr), Mol))
	!= PD_INFINITE)) {
		/* Il y a un acces a M */
		/* Calcul de s(M+) */
		Coord_PutPosIndex(&NodeCoord, Coord_PosIndex(NodeCoordPtr) - 1);
		Coord_PutMolIndex(&NodeCoord, Coord_MolIndex(NodeCoordPtr) - 1);
		ScoreMPlus = Node_CalcMPlus(NodePtr11, &NodeCoord, SecondNode,
		InsPosPtr1, &StartCoord);
		if (ScoreMPlus != PD_INFINITE) Node_PutM(NodePtr, ScoreMPlus + M)
		else Node_PutM(NodePtr, PD_INFINITE);
		Node_PutMStartCoord(NodePtr, StartCoord)
	}
	else {
		Node_PutM(NodePtr, PD_INFINITE);
		Coord_Reset(&Node_MStartCoord(NodePtr));
	}

	/* Calcul de s(I) */
	if ((NodePtr21) && ((I = ScoreVect_ScoreNth(InsPos_I(InsPosPtr2), Mol))
	!= PD_INFINITE)) {
		/* Il y a un acces a I */
		/* Calcul de s(I+) */
		Coord_PutPosIndex(&NodeCoord, Coord_PosIndex(NodeCoordPtr));
		Coord_PutMolIndex(&NodeCoord, Coord_MolIndex(NodeCoordPtr) - 1);
		ScoreIPlus = Node_CalcIPlus(NodePtr21, &NodeCoord, SecondNode,
		InsPosPtr2, &StartCoord);
		if (ScoreIPlus != PD_INFINITE) Node_PutI(NodePtr, ScoreIPlus + I)
		else Node_PutI(NodePtr, PD_INFINITE);
		Node_PutIStartCoord(NodePtr, StartCoord)
	}
	else {
		Node_PutI(NodePtr, PD_INFINITE);
		Coord_Reset(&Node_IStartCoord(NodePtr));
	}
	
	/* Calcul de s(D) */
	if ((NodePtr12) && ((D = MatchPos_D(MatchPosPtr)) != PD_INFINITE)) {
		/* Il y a un acces a D */
		/* Calcul de s(D+) */
		Coord_PutPosIndex(&NodeCoord, Coord_PosIndex(NodeCoordPtr) - 1);
		Coord_PutMolIndex(&NodeCoord, Coord_MolIndex(NodeCoordPtr));
		ScoreDPlus = Node_CalcDPlus(NodePtr12, &NodeCoord,
		(TBoolean)!NodePtr11, InsPosPtr1, &StartCoord);
		if (ScoreDPlus != PD_INFINITE) Node_PutD(NodePtr, ScoreDPlus + D)
		else Node_PutD(NodePtr, PD_INFINITE);
		Node_PutDStartCoord(NodePtr, StartCoord)
	}
	else {
		Node_PutD(NodePtr, PD_INFINITE);
		Coord_Reset(&Node_DStartCoord(NodePtr));
	}

	/* Calcul de s(E) */
	if ((E = (LastNode) ? InsPos_E0(InsPosPtr2) : InsPos_E1(InsPosPtr2))
	!= PD_INFINITE) {
		/* Il y a un acces a E */
		/* Calcul de s(E+) */
		ScoreEPlus = Node_CalcEPlus(NodePtr, NodeCoordPtr,
		(TBoolean)!NodePtr21, InsPosPtr2, StartCoordPtr);
		if (ScoreEPlus != PD_INFINITE) ScoreE = ScoreEPlus + E;
		else ScoreE = PD_INFINITE;
	}
	else {
		ScoreE = PD_INFINITE;
		Coord_Reset(StartCoordPtr);
	}
	return ScoreE;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un noeud					 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodePtr					| Noeud								*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_Node(TNodePtr NodePtr)
{
	printf("(");
	Print_Score(Node_M(NodePtr));
	printf(",");
	Print_Score(Node_I(NodePtr));
	printf(",");
	Print_Score(Node_D(NodePtr));
	printf(")\n");
	printf("[");
	Print_Coord(&Node_MStartCoord(NodePtr));
	printf(",");
	Print_Coord(&Node_IStartCoord(NodePtr));
	printf(",");
	Print_Coord(&Node_DStartCoord(NodePtr));
	printf("]\n");
}

/*=============================================*/
/* Routines de manipulation des noeuds etendus */
/*=============================================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul de s(M+)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodePtr				| Noeud etendu						*/
/*			| ExtNodeCoordPtr			| Coord. du noeud etendu			*/
/*			| FirstExtNode				| Indique s'il s'agit du 1er noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| StartCoordPtr				| f(M+)								*/
/*			| InCoordPtr				| fp(M+)							*/
/*			| ExtNode_CalcMPlus			| s(M+)								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore ExtNode_CalcMPlus(TExtNodePtr ExtNodePtr, TCoordPtr ExtNodeCoordPtr,
TBoolean FirstExtNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr,
TCoordPtr InCoordPtr)
{
	TScore B;				/* Score d'initiation			*/
	TScore BM, DM, MM, IM;	/* Score de transition vers M	*/
	TScore Score;			/* Score calcule				*/
	TScore ScoreMPlus;		/* s(M+)						*/
	
	ScoreMPlus = PD_INFINITE;
	Coord_Reset(StartCoordPtr);
	Coord_Reset(InCoordPtr);
	/* Par B */
	if (((B = (FirstExtNode) ? InsPos_B0(InsPosPtr) :
	InsPos_B1(InsPosPtr)) != PD_INFINITE) &&
	((BM = InsPos_BM(InsPosPtr)) != PD_INFINITE)) {
		ScoreMPlus = B + BM;
		*StartCoordPtr = *ExtNodeCoordPtr;
		*InCoordPtr = *ExtNodeCoordPtr;
	}
	/* Par D */
	if ((ExtNode_D(ExtNodePtr) != PD_INFINITE) &&
	((DM = InsPos_DM(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_D(ExtNodePtr) + DM) > ScoreMPlus)) {
		ScoreMPlus = Score;
		*StartCoordPtr = ExtNode_DStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_DInCoord(ExtNodePtr);
	}
	/* Par M */
	if ((ExtNode_M(ExtNodePtr) != PD_INFINITE) &&
	((MM = InsPos_MM(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_M(ExtNodePtr) + MM) > ScoreMPlus)) {
		ScoreMPlus = Score;
		*StartCoordPtr = ExtNode_MStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_MInCoord(ExtNodePtr);
	}
	/* Par I */
	if ((ExtNode_I(ExtNodePtr) != PD_INFINITE) &&
	((IM = InsPos_IM(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_I(ExtNodePtr) + IM) > ScoreMPlus)) {
		ScoreMPlus = Score;
		*StartCoordPtr = ExtNode_IStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_IInCoord(ExtNodePtr);
	}
	return ScoreMPlus;
}

/*--------------------------------------------------------------------------*/
/* Calcul de s(I+)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodePtr				| Noeud etendu						*/
/*			| ExtNodeCoordPtr			| Coord. du noeud etendu			*/
/*			| FirstExtNode				| Indique s'il s'agit du 1er noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| StartCoordPtr				| f(I+)								*/
/*			| InCoordPtr				| fp(I+)							*/
/*			| ExtNode_CalcIPlus			| s(I+)								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore ExtNode_CalcIPlus(TExtNodePtr ExtNodePtr, TCoordPtr ExtNodeCoordPtr,
TBoolean FirstExtNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr,
TCoordPtr InCoordPtr)
{
	TScore B;				/* Score d'initiation			*/
	TScore BI, DI, MI, II;	/* Score de transition vers I	*/
	TScore Score;			/* Score calcule				*/
	TScore ScoreIPlus;		/* s(I+)						*/
	
	ScoreIPlus = PD_INFINITE;
	Coord_Reset(StartCoordPtr);
	Coord_Reset(InCoordPtr);
	/* Par B */
	if (((B = (FirstExtNode) ? InsPos_B0(InsPosPtr) :
	InsPos_B1(InsPosPtr)) != PD_INFINITE) &&
	((BI = InsPos_BI(InsPosPtr)) != PD_INFINITE)) {
		ScoreIPlus = B + BI;
		*StartCoordPtr = *ExtNodeCoordPtr;
		*InCoordPtr = *ExtNodeCoordPtr;
	}
	/* Par D */
	if ((ExtNode_D(ExtNodePtr) != PD_INFINITE) &&
	((DI = InsPos_DI(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_D(ExtNodePtr) + DI) > ScoreIPlus)) {
		ScoreIPlus = Score;
		*StartCoordPtr = ExtNode_DStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_DInCoord(ExtNodePtr);
	}
	/* Par M */
	if ((ExtNode_M(ExtNodePtr) != PD_INFINITE) &&
	((MI = InsPos_MI(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_M(ExtNodePtr) + MI) > ScoreIPlus)) {
		ScoreIPlus = Score;
		*StartCoordPtr = ExtNode_MStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_MInCoord(ExtNodePtr);
	}
	/* Par I */
	if ((ExtNode_I(ExtNodePtr) != PD_INFINITE) &&
	((II = InsPos_II(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_I(ExtNodePtr) + II) > ScoreIPlus)) {
		ScoreIPlus = Score;
		*StartCoordPtr = ExtNode_IStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_IInCoord(ExtNodePtr);
	}
	return ScoreIPlus;
}

/*--------------------------------------------------------------------------*/
/* Calcul de s(D+)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodePtr				| Noeud etendu						*/
/*			| ExtNodeCoordPtr			| Coord. du noeud etendu			*/
/*			| FirstExtNode				| Indique s'il s'agit du 1er noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| StartCoordPtr				| f(D+)								*/
/*			| InCoordPtr				| fp(D+)							*/
/*			| ExtNode_CalcDPlus			| s(D+)								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore ExtNode_CalcDPlus(TExtNodePtr ExtNodePtr, TCoordPtr ExtNodeCoordPtr,
TBoolean FirstExtNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr,
TCoordPtr InCoordPtr)
{
	TScore B;				/* Score d'initiation			*/
	TScore BD, DD, MD, ID;	/* Score de transition vers D	*/
	TScore Score;			/* Score calcule				*/
	TScore ScoreDPlus;		/* s(D+)						*/
	
	ScoreDPlus = PD_INFINITE;
	Coord_Reset(StartCoordPtr);
	Coord_Reset(InCoordPtr);
	/* Par B */
	if (((B = (FirstExtNode) ? InsPos_B0(InsPosPtr) :
	InsPos_B1(InsPosPtr)) != PD_INFINITE) &&
	((BD = InsPos_BD(InsPosPtr)) != PD_INFINITE)) {
		ScoreDPlus = B + BD;
		*StartCoordPtr = *ExtNodeCoordPtr;
		*InCoordPtr = *ExtNodeCoordPtr;
	}
	/* Par D */
	if ((ExtNode_D(ExtNodePtr) != PD_INFINITE) &&
	((DD = InsPos_DD(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_D(ExtNodePtr) + DD) > ScoreDPlus)) {
		ScoreDPlus = Score;
		*StartCoordPtr = ExtNode_DStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_DInCoord(ExtNodePtr);
	}
	/* Par M */
	if ((ExtNode_M(ExtNodePtr) != PD_INFINITE) &&
	((MD = InsPos_MD(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_M(ExtNodePtr) + MD) > ScoreDPlus)) {
		ScoreDPlus = Score;
		*StartCoordPtr = ExtNode_MStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_MInCoord(ExtNodePtr);
	}
	/* Par I */
	if ((ExtNode_I(ExtNodePtr) != PD_INFINITE) &&
	((ID = InsPos_ID(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_I(ExtNodePtr) + ID) > ScoreDPlus)) {
		ScoreDPlus = Score;
		*StartCoordPtr = ExtNode_IStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_IInCoord(ExtNodePtr);
	}
	return ScoreDPlus;
}

/*--------------------------------------------------------------------------*/
/* Calcul de s(E+)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodePtr				| Noeud								*/
/*			| ExtNodeCoordPtr			| Coord. du noeud					*/
/*			| FirstExtNode				| Indique s'il s'agit du 1er noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| StartCoordPtr				| f(E+)								*/
/*			| InCoordPtr				| fp(E+)							*/
/*			| ExtNode_CalcEPlus			| s(E+)								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore ExtNode_CalcEPlus(TExtNodePtr ExtNodePtr, TCoordPtr ExtNodeCoordPtr,
TBoolean FirstExtNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr, TCoordPtr
InCoordPtr)
{
	TScore B;				/* Score d'initiation			*/
	TScore BE, DE, ME, IE;	/* Score de transition vers E	*/
	TScore Score;			/* Score calcule				*/
	TScore ScoreEPlus;		/* s(E+)						*/
	
	ScoreEPlus = PD_INFINITE;
	Coord_Reset(StartCoordPtr);
	Coord_Reset(InCoordPtr);
	/* Par B */
	if (((B = (FirstExtNode) ? InsPos_B0(InsPosPtr) :
	InsPos_B1(InsPosPtr)) != PD_INFINITE) &&
	((BE = InsPos_BE(InsPosPtr)) != PD_INFINITE)) {
		ScoreEPlus = B + BE;
		*StartCoordPtr = *ExtNodeCoordPtr;
		*InCoordPtr = *ExtNodeCoordPtr;
	}
	/* Par D */
	if ((ExtNode_D(ExtNodePtr) != PD_INFINITE) &&
	((DE = InsPos_DE(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_D(ExtNodePtr) + DE) > ScoreEPlus)) {
		ScoreEPlus = Score;
		*StartCoordPtr = ExtNode_DStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_DInCoord(ExtNodePtr);
	}
	/* Par M */
	if ((ExtNode_M(ExtNodePtr) != PD_INFINITE) &&
	((ME = InsPos_ME(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_M(ExtNodePtr) + ME) > ScoreEPlus)) {
		ScoreEPlus = Score;
		*StartCoordPtr = ExtNode_MStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_MInCoord(ExtNodePtr);
	}
	/* Par I */
	if ((ExtNode_I(ExtNodePtr) != PD_INFINITE) &&
	((IE = InsPos_IE(InsPosPtr)) != PD_INFINITE) &&
	((Score = ExtNode_I(ExtNodePtr) + IE) > ScoreEPlus)) {
		ScoreEPlus = Score;
		*StartCoordPtr = ExtNode_IStartCoord(ExtNodePtr);
		*InCoordPtr = ExtNode_IInCoord(ExtNodePtr);
	}
	return ScoreEPlus;
}

/*--------------------------------------------------------------------------*/
/* Calcul d'un noeud etendu					 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodePtr				| Noeud etendu						*/
/*			| ExtNodeCoordPtr			| Coordonnees du noeud etendu		*/
/*			| SecondExtNode				| Indique s'il s'agit du 2e noeud	*/
/*			| LastExtNode				| Ind. s'il s'agit du dern. noeud	*/
/*			| InsPosPtr1				| 1ere position d'insertion			*/
/*			| MatchPosPtr				| Position match					*/
/*			| InsPosPtr2				| 2eme position d'insertion			*/
/*			| Mol						| Molecule							*/
/*			| ExtNodePtr11				| Noeud (1,1)						*/
/*			| ExtNodePtr12				| Noeud (1,2)						*/
/*			| ExtNodePtr21				| Noeud (2,1)						*/
/* Sortie:	| StartCoordPtr				| f(E) par ce noeud					*/
/*			| InCoordPtr				| fp(E) par ce noeud				*/
/*			| ExtNode_Calc				| s(E) par ce noeud					*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore ExtNode_Calc(TExtNodePtr ExtNodePtr, TCoordPtr ExtNodeCoordPtr,
TBoolean SecondExtNode, TBoolean LastExtNode, TInsPosPtr InsPosPtr1,
TMatchPosPtr MatchPosPtr, TInsPosPtr InsPosPtr2, TMol Mol, TExtNodePtr
ExtNodePtr11, TExtNodePtr ExtNodePtr12, TExtNodePtr ExtNodePtr21, TCoordPtr
StartCoordPtr, TCoordPtr InCoordPtr)
{
	TScore ScoreMPlus;		/* Score de M+								*/
	TScore ScoreIPlus;		/* Score de I+								*/
	TScore ScoreDPlus;		/* Score de D+								*/
	TScore M, I, D;			/* Score match, d'insertion, de deletion	*/
	TScore ScoreEPlus;		/* Score de E+								*/
	TScore ScoreE;			/* Score de E								*/
	TScore E;				/* Score de terminaison						*/
	TCoord StartCoord;		/* Coord. de depart							*/
	TCoord InCoord;			/* Coord. d'entree							*/
	TCoord ExtNodeCoord;	/* Coord. d'un noeud etendu					*/
	
	/* Calcul de s(M) */
	if ((ExtNodePtr11) && ((M = ScoreVect_ScoreNth(MatchPos_M(MatchPosPtr),
	Mol)) != PD_INFINITE)) {
		/* Il y a un acces a M */
		/* Calcul de s(M+) */
		Coord_PutPosIndex(&ExtNodeCoord, Coord_PosIndex(ExtNodeCoordPtr) - 1);
		Coord_PutMolIndex(&ExtNodeCoord, Coord_MolIndex(ExtNodeCoordPtr) - 1);
		ScoreMPlus = ExtNode_CalcMPlus(ExtNodePtr11, &ExtNodeCoord,
		SecondExtNode, InsPosPtr1, &StartCoord, &InCoord);
		if (ScoreMPlus != PD_INFINITE)
		ExtNode_PutM(ExtNodePtr, ScoreMPlus + M)
		else ExtNode_PutM(ExtNodePtr, PD_INFINITE);
		ExtNode_PutMStartCoord(ExtNodePtr, StartCoord);
		ExtNode_PutMInCoord(ExtNodePtr, InCoord);
	}
	else {
		ExtNode_PutM(ExtNodePtr, PD_INFINITE);
		Coord_Reset(&ExtNode_MStartCoord(ExtNodePtr));
		Coord_Reset(&ExtNode_MInCoord(ExtNodePtr));
	}

	/* Calcul de s(I) */
	if ((ExtNodePtr21) && ((I = ScoreVect_ScoreNth(InsPos_I(InsPosPtr2), Mol))
	!= PD_INFINITE)) {
		/* Il y a un acces a I */
		/* Calcul de s(I+) */
		Coord_PutPosIndex(&ExtNodeCoord, Coord_PosIndex(ExtNodeCoordPtr));
		Coord_PutMolIndex(&ExtNodeCoord, Coord_MolIndex(ExtNodeCoordPtr) - 1);
		ScoreIPlus = ExtNode_CalcIPlus(ExtNodePtr21, &ExtNodeCoord,
		SecondExtNode, InsPosPtr2, &StartCoord, &InCoord);
		if (ScoreIPlus != PD_INFINITE)
		ExtNode_PutI(ExtNodePtr, ScoreIPlus + I)
		else ExtNode_PutI(ExtNodePtr, PD_INFINITE);
		ExtNode_PutIStartCoord(ExtNodePtr, StartCoord);
		ExtNode_PutIInCoord(ExtNodePtr, InCoord);
	}
	else {
		ExtNode_PutI(ExtNodePtr, PD_INFINITE);
		Coord_Reset(&ExtNode_IStartCoord(ExtNodePtr));
		Coord_Reset(&ExtNode_IInCoord(ExtNodePtr));
	}
	
	/* Calcul de s(D) */
	if ((ExtNodePtr12) && ((D = MatchPos_D(MatchPosPtr)) != PD_INFINITE)) {
		/* Il y a un acces a D */
		/* Calcul de s(D+) */
		Coord_PutPosIndex(&ExtNodeCoord, Coord_PosIndex(ExtNodeCoordPtr) - 1);
		Coord_PutMolIndex(&ExtNodeCoord, Coord_MolIndex(ExtNodeCoordPtr));
		ScoreDPlus = ExtNode_CalcDPlus(ExtNodePtr12, &ExtNodeCoord,
		(TBoolean)!ExtNodePtr11, InsPosPtr1, &StartCoord, &InCoord);
		if (ScoreDPlus != PD_INFINITE) ExtNode_PutD(ExtNodePtr,
		ScoreDPlus + D)
		else ExtNode_PutD(ExtNodePtr, PD_INFINITE);
		ExtNode_PutDStartCoord(ExtNodePtr, StartCoord);
		ExtNode_PutDInCoord(ExtNodePtr, InCoord);
	}
	else {
		ExtNode_PutD(ExtNodePtr, PD_INFINITE);
		Coord_Reset(&ExtNode_DStartCoord(ExtNodePtr));
		Coord_Reset(&ExtNode_DInCoord(ExtNodePtr));
	}

	/* Calcul de s(E) */
	if ((E = (LastExtNode) ? InsPos_E0(InsPosPtr2) : InsPos_E1(InsPosPtr2))
	!= PD_INFINITE) {
		/* Il y a un acces a E */
		/* Calcul de s(E+) */
		ScoreEPlus = ExtNode_CalcEPlus(ExtNodePtr, ExtNodeCoordPtr,
		(TBoolean)!ExtNodePtr21, InsPosPtr2, StartCoordPtr, InCoordPtr);
		if (ScoreEPlus != PD_INFINITE) ScoreE = ScoreEPlus + E;
		else ScoreE = PD_INFINITE;
	}
	else {
		ScoreE = PD_INFINITE;
		Coord_Reset(StartCoordPtr);
		Coord_Reset(InCoordPtr);
	}
	return ScoreE;
}


/*--------------------------------------------------------------------------*/
/* Calcul d'un noeud etendu limite			 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodePtr				| Noeud etendu						*/
/*			| ExtNodeCoordPtr			| Coordonnees du noeud etendu		*/
/*			| SecondExtNode				| Indique s'il s'agit du 2e noeud	*/
/*			| LastExtNode				| Ind. s'il s'agit du dern. noeud	*/
/*			| MatchPosPtr				| Position match					*/
/*			| InsPosPtr					| Position d'insertion				*/
/*			| Mol						| Molecule							*/
/*			| SubPlusNodePtr11			| Sous-noeud+ (1,1)					*/
/*			| SubPlusNodePtr12			| Sous-noeud+ (1,2)					*/
/*			| ExtNodePtr21				| Noeud (2,1)						*/
/* Sortie:	| StartCoordPtr				| f(E) par ce noeud					*/
/*			| Node_LimCalc				| s(E) par ce noeud					*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore ExtNode_LimCalc(TExtNodePtr ExtNodePtr, TCoordPtr ExtNodeCoordPtr,
TBoolean SecondExtNode, TBoolean LastExtNode, TMatchPosPtr MatchPosPtr,
TInsPosPtr InsPosPtr, TMol Mol, TSubPlusNodePtr SubPlusNodePtr11,
TSubPlusNodePtr SubPlusNodePtr12, TExtNodePtr ExtNodePtr21, TCoordPtr
StartCoordPtr, TCoordPtr InCoordPtr)
{
	TScore ScoreIPlus;		/* Score de I+								*/
	TScore M, I, D;			/* Score match, d'insertion, de deletion	*/
	TScore ScoreEPlus;		/* Score de E+								*/
	TScore ScoreE;			/* Score de E								*/
	TScore E;				/* Score de terminaison						*/
	TCoord StartCoord;		/* Coord. de depart							*/
	TCoord InCoord;			/* Coord. d'entree							*/
	TCoord ExtNodeCoord;	/* Coord. d'un noeud etendu					*/
			
	/* Calcul de s(M) */
	if ((SubPlusNodePtr11) && (SubPlusNode_MPlus(SubPlusNodePtr11)
	!= PD_INFINITE) && ((M = ScoreVect_ScoreNth
	(MatchPos_M(MatchPosPtr), Mol)) != PD_INFINITE)) {
		/* s(M) fini */
		ExtNode_PutM(ExtNodePtr, SubPlusNode_MPlus(SubPlusNodePtr11) + M);
		ExtNode_PutMStartCoord(ExtNodePtr,
		SubPlusNode_MPlusStartCoord(SubPlusNodePtr11));
		Coord_PutPosIndex(&ExtNode_MInCoord(ExtNodePtr),
		Coord_PosIndex(ExtNodeCoordPtr) - 1);
		Coord_PutMolIndex(&ExtNode_MInCoord(ExtNodePtr),
		Coord_MolIndex(ExtNodeCoordPtr) - 1);
	}
	else {
		ExtNode_PutM(ExtNodePtr, PD_INFINITE);
		Coord_Reset(&ExtNode_MStartCoord(ExtNodePtr));
		Coord_Reset(&ExtNode_MInCoord(ExtNodePtr));
	}
	
	/* Calcul de s(I) */
	if ((ExtNodePtr21) && ((I = ScoreVect_ScoreNth(InsPos_I(InsPosPtr), Mol))
	!= PD_INFINITE)) {
		/* Il y a un acces a I */
		/* Calcul de s(I+) */
		Coord_PutPosIndex(&ExtNodeCoord, Coord_PosIndex(ExtNodeCoordPtr));
		Coord_PutMolIndex(&ExtNodeCoord, Coord_MolIndex(ExtNodeCoordPtr) - 1);
		ScoreIPlus = ExtNode_CalcIPlus(ExtNodePtr21, &ExtNodeCoord,
		SecondExtNode, InsPosPtr, &StartCoord, &InCoord);
		if (ScoreIPlus != PD_INFINITE)
		ExtNode_PutI(ExtNodePtr, ScoreIPlus + I)
		else ExtNode_PutI(ExtNodePtr, PD_INFINITE);
		ExtNode_PutIStartCoord(ExtNodePtr, StartCoord);
		ExtNode_PutIInCoord(ExtNodePtr, InCoord);
	}
	else {
		ExtNode_PutI(ExtNodePtr, PD_INFINITE);
		Coord_Reset(&ExtNode_IStartCoord(ExtNodePtr));
		Coord_Reset(&ExtNode_IInCoord(ExtNodePtr));
	}
	
	/* Calcul de s(D) */
	if ((SubPlusNodePtr12) && (SubPlusNode_DPlus(SubPlusNodePtr12)
	!= PD_INFINITE) && ((D = MatchPos_D(MatchPosPtr)) != PD_INFINITE)) {
		/* s(D) fini */
		ExtNode_PutD(ExtNodePtr, SubPlusNode_DPlus(SubPlusNodePtr12) + D);
		ExtNode_PutDStartCoord(ExtNodePtr,
		SubPlusNode_DPlusStartCoord(SubPlusNodePtr12));
		Coord_PutPosIndex(&ExtNode_DInCoord(ExtNodePtr),
		Coord_PosIndex(ExtNodeCoordPtr) - 1);
		Coord_PutMolIndex(&ExtNode_DInCoord(ExtNodePtr),
		Coord_MolIndex(ExtNodeCoordPtr));
	}
	else {
		ExtNode_PutD(ExtNodePtr, PD_INFINITE);
		Coord_Reset(&ExtNode_DStartCoord(ExtNodePtr));
		Coord_Reset(&ExtNode_DInCoord(ExtNodePtr));
	}

	/* Calcul de s(E) */
	if ((E = (LastExtNode) ? InsPos_E0(InsPosPtr) : InsPos_E1(InsPosPtr))
	!= PD_INFINITE) {
		/* Il y a un acces a E */
		/* Calcul de s(E+) */
		ScoreEPlus = ExtNode_CalcEPlus(ExtNodePtr, ExtNodeCoordPtr,
		(TBoolean)!ExtNodePtr21, InsPosPtr, StartCoordPtr, InCoordPtr);
		if (ScoreEPlus != PD_INFINITE) ScoreE = ScoreEPlus + E;
		else ScoreE = PD_INFINITE;
	}
	else {
		ScoreE = PD_INFINITE;
		Coord_Reset(StartCoordPtr);
		Coord_Reset(InCoordPtr);
	}

	return ScoreE;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Plus petit index de molecule du noeud etendu				 				*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodePtr				| Noeud etendu						*/
/*			| ExtNodeCoordPtr			| Coord. du noeud etendu			*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TMolIndex ExtNode_FirstMolIndex(TExtNodePtr ExtNodePtr, TCoordPtr
ExtNodeCoordPtr)
{
	TMolIndex FirstMolIndex;
	TMolIndex MInMolIndex;
	TMolIndex IInMolIndex;
	
	MInMolIndex = Coord_MolIndex(&ExtNode_MInCoord(ExtNodePtr));
	IInMolIndex = Coord_MolIndex(&ExtNode_IInCoord(ExtNodePtr));
	FirstMolIndex = MInMolIndex < IInMolIndex ? MInMolIndex : IInMolIndex;
	if (FirstMolIndex == SD_MOL_IDX_NOT_DEF)
		FirstMolIndex = Coord_MolIndex(ExtNodeCoordPtr);
	return FirstMolIndex;
}


/*--------------------------------------------------------------------------*/
/* Impression d'un noeud etendu				 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodePtr				| Noeud etendu						*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_ExtNode(TExtNodePtr ExtNodePtr)
{
	Print_Node(&(ExtNodePtr->Node));
	printf("[");
	Print_Coord(&ExtNode_MInCoord(ExtNodePtr));
	printf(",");
	Print_Coord(&ExtNode_IInCoord(ExtNodePtr));
	printf(",");
	Print_Coord(&ExtNode_DInCoord(ExtNodePtr));
	printf("]\n");
}


/*=======================================*/
/* Routines de manipulation des noeuds + */
/*=======================================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul de s(M)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PlusNodePtr				| Noeud +							*/
/*			| PlusNodeCoordPtr			| Coord. du noeud +					*/
/*			| LastNode					| Ind. s'il s'agit du dernier noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| EndCoordPtr				| l(M) par ce noeud					*/
/*			| PlusNode_CalcM			| u(M) par ce noeud					*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore PlusNode_CalcM(TPlusNodePtr PlusNodePtr, TCoordPtr PlusNodeCoordPtr,
TBoolean LastNode, TInsPosPtr InsPosPtr, TCoordPtr EndCoordPtr)
{
	TScore E;				/* Score de teminaison		*/
	TScore MM, MI, MD, ME;	/* Score de transition de M	*/
	TScore Score;			/* Score calcule			*/
	TScore ScoreM;			/* s(M)						*/
	
	ScoreM = PD_INFINITE;
	Coord_Reset(EndCoordPtr);
	/* Par E+ */
	if (((E = (LastNode) ? InsPos_E0(InsPosPtr) :
	InsPos_E1(InsPosPtr)) != PD_INFINITE) &&
	((ME = InsPos_ME(InsPosPtr)) != PD_INFINITE)) {
		ScoreM = E + ME;
		*EndCoordPtr = *PlusNodeCoordPtr;
	}
	/* Par D+ */
	if ((PlusNode_DPlus(PlusNodePtr) != PD_INFINITE) &&
	((MD = InsPos_MD(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_DPlus(PlusNodePtr) + MD) > ScoreM)) {
		ScoreM = Score;
		*EndCoordPtr = PlusNode_DPlusEndCoord(PlusNodePtr);
	}
	/* Par M+ */
	if ((PlusNode_MPlus(PlusNodePtr) != PD_INFINITE) &&
	((MM = InsPos_MM(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_MPlus(PlusNodePtr) + MM) > ScoreM)) {
		ScoreM = Score;
		*EndCoordPtr = PlusNode_MPlusEndCoord(PlusNodePtr);
	}
	/* Par I+ */
	if ((PlusNode_IPlus(PlusNodePtr) != PD_INFINITE) &&
	((MI = InsPos_MI(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_IPlus(PlusNodePtr) + MI) > ScoreM)) {
		ScoreM = Score;
		*EndCoordPtr = PlusNode_IPlusEndCoord(PlusNodePtr);
	}
	return ScoreM;
}

/*--------------------------------------------------------------------------*/
/* Calcul de s(I)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PlusNodePtr				| Noeud +							*/
/*			| PlusNodeCoordPtr			| Coord. du noeud +					*/
/*			| LastNode					| Ind. s'il s'agit du dernier noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| EndCoordPtr				| l(I) par ce noeud					*/
/*			| PlusNode_CalcI			| u(I) par ce noeud					*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore PlusNode_CalcI(TPlusNodePtr PlusNodePtr, TCoordPtr PlusNodeCoordPtr,
TBoolean LastNode, TInsPosPtr InsPosPtr, TCoordPtr EndCoordPtr)
{
	TScore E;				/* Score de terminaison			*/
	TScore IE, ID, IM, II;	/* Score de transition de I		*/
	TScore Score;			/* Score calcule				*/
	TScore ScoreI;			/* s(I)							*/
	
	ScoreI = PD_INFINITE;
	Coord_Reset(EndCoordPtr);
	/* Par E+ */
	if (((E = (LastNode) ? InsPos_E0(InsPosPtr) :
	InsPos_E1(InsPosPtr)) != PD_INFINITE) &&
	((IE = InsPos_IE(InsPosPtr)) != PD_INFINITE)) {
		ScoreI = E + IE;
		*EndCoordPtr = *PlusNodeCoordPtr;
	}
	/* Par D+ */
	if ((PlusNode_DPlus(PlusNodePtr) != PD_INFINITE) &&
	((ID = InsPos_ID(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_DPlus(PlusNodePtr) + ID) > ScoreI)) {
		ScoreI = Score;
		*EndCoordPtr = PlusNode_DPlusEndCoord(PlusNodePtr);
	}
	/* Par M+ */
	if ((PlusNode_MPlus(PlusNodePtr) != PD_INFINITE) &&
	((IM = InsPos_IM(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_MPlus(PlusNodePtr) + IM) > ScoreI)) {
		ScoreI = Score;
		*EndCoordPtr = PlusNode_MPlusEndCoord(PlusNodePtr);
	}
	/* Par I+ */
	if ((PlusNode_IPlus(PlusNodePtr) != PD_INFINITE) &&
	((II = InsPos_II(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_IPlus(PlusNodePtr) + II) > ScoreI)) {
		ScoreI = Score;
		*EndCoordPtr = PlusNode_IPlusEndCoord(PlusNodePtr);
	}
	return ScoreI;
}

/*--------------------------------------------------------------------------*/
/* Calcul de s(D)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PlusNodePtr				| Noeud								*/
/*			| PlusNodeCoordPtr			| Coord. du noeud +					*/
/*			| LastNode					| Indique s'il s'agit du 1er noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| EndCoordPtr				| l(I) par ce noeud					*/
/*			| PlusNode_CalcD			| u(D) par ce noeud					*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore PlusNode_CalcD(TPlusNodePtr PlusNodePtr, TCoordPtr PlusNodeCoordPtr,
TBoolean LastNode, TInsPosPtr InsPosPtr, TCoordPtr EndCoordPtr)
{
	TScore E;				/* Score de terminaison		*/
	TScore DE, DD, DM, DI;	/* Score de transition de D	*/
	TScore Score;			/* Score calcule			*/
	TScore ScoreD;			/* s(D)						*/
	
	ScoreD = PD_INFINITE;
	Coord_Reset(EndCoordPtr);
	/* Par E+ */
	if (((E = (LastNode) ? InsPos_E0(InsPosPtr) :
	InsPos_E1(InsPosPtr)) != PD_INFINITE) &&
	((DE = InsPos_DE(InsPosPtr)) != PD_INFINITE)) {
		ScoreD = E + DE;
		*EndCoordPtr = *PlusNodeCoordPtr;
	}
	/* Par D+ */
	if ((PlusNode_DPlus(PlusNodePtr) != PD_INFINITE) &&
	((DD = InsPos_DD(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_DPlus(PlusNodePtr) + DD) > ScoreD)) {
		ScoreD = Score;
		*EndCoordPtr = PlusNode_DPlusEndCoord(PlusNodePtr);
	}
	/* Par M+ */
	if ((PlusNode_MPlus(PlusNodePtr) != PD_INFINITE) &&
	((DM = InsPos_DM(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_MPlus(PlusNodePtr) + DM) > ScoreD)) {
		ScoreD = Score;
		*EndCoordPtr = PlusNode_MPlusEndCoord(PlusNodePtr);
	}
	/* Par I+ */
	if ((PlusNode_IPlus(PlusNodePtr) != PD_INFINITE) &&
	((DI = InsPos_DI(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_IPlus(PlusNodePtr) + DI) > ScoreD)) {
		ScoreD = Score;
		*EndCoordPtr = PlusNode_IPlusEndCoord(PlusNodePtr);
	}
	return ScoreD;
}

/*--------------------------------------------------------------------------*/
/* Calcul de s(B)							 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PlusNodePtr				| Noeud +							*/
/*			| PlusNodeCoordPtr			| Coord. du noeud +					*/
/*			| LastNode					| Ind. s'il s'agit du dernier noeud	*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| EndCoordPtr				| l(D) par ce noeud					*/
/*			| PlusNode_CalcB			| u(D) par ce noeud					*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore PlusNode_CalcB(TPlusNodePtr PlusNodePtr, TCoordPtr PlusNodeCoordPtr,
TBoolean LastNode, TInsPosPtr InsPosPtr, TCoordPtr EndCoordPtr)
{
	TScore E;				/* Score de terminaison		*/
	TScore BE, BD, BM, BI;	/* Score de transition de B	*/
	TScore Score;			/* Score calcule			*/
	TScore ScoreB;			/* s(B)						*/
	
	ScoreB = PD_INFINITE;
	Coord_Reset(EndCoordPtr);
	/* Par E+ */
	if (((E = (LastNode) ? InsPos_E0(InsPosPtr) :
	InsPos_E1(InsPosPtr)) != PD_INFINITE) &&
	((BE = InsPos_BE(InsPosPtr)) != PD_INFINITE)) {
		ScoreB = E + BE;
		*EndCoordPtr = *PlusNodeCoordPtr;
	}
	/* Par D+ */
	if ((PlusNode_DPlus(PlusNodePtr) != PD_INFINITE) &&
	((BD = InsPos_BD(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_DPlus(PlusNodePtr) + BD) > ScoreB)) {
		ScoreB = Score;
		*EndCoordPtr = PlusNode_DPlusEndCoord(PlusNodePtr);
	}
	/* Par M+ */
	if ((PlusNode_MPlus(PlusNodePtr) != PD_INFINITE) &&
	((BM = InsPos_BM(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_MPlus(PlusNodePtr) + BM) > ScoreB)) {
		ScoreB = Score;
		*EndCoordPtr = PlusNode_MPlusEndCoord(PlusNodePtr);
	}
	/* Par I+ */
	if ((PlusNode_IPlus(PlusNodePtr) != PD_INFINITE) &&
	((BI = InsPos_BI(InsPosPtr)) != PD_INFINITE) &&
	((Score = PlusNode_IPlus(PlusNodePtr) + BI) > ScoreB)) {
		ScoreB = Score;
		*EndCoordPtr = PlusNode_MPlusEndCoord(PlusNodePtr);
	}
	return ScoreB;
}

/*--------------------------------------------------------------------------*/
/* Calcul d'un noeud +						 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PlusNodePtr				| Noeud +							*/
/*			| PlusNodeCoordPtr			| Coordonnees du noeud +			*/
/*			| BLastNode					| Ind. s'il s'agit de l'a-d noeud	*/
/*			| FirstNode					| Ind. s'il s'agit du 1er noeud		*/
/*			| InsPosPtr1				| 1ere position d'insertion			*/
/*			| MatchPosPtr				| Position match					*/
/*			| InsPosPtr2				| 2eme position d'insertion			*/
/*			| Mol						| Molecule							*/
/*			| PlusNodePtr12				| Noeud+ (1,2)						*/
/*			| PlusNodePtr21				| Noeud+ (2,1)						*/
/*			| PlusNodePtr22				| Noeud+ (2,2)						*/
/* Sortie:	| EndCoordPtr				| l(B+) par ce noeud				*/
/*			| PlusNode_Calc				| u(B+) par ce noeud				*/
/*--------------------------------------------------------------------------*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore PlusNode_Calc(TPlusNodePtr PlusNodePtr, TCoordPtr PlusNodeCoordPtr,
TBoolean BLastNode, TBoolean FirstNode, TInsPosPtr InsPosPtr1, TMatchPosPtr
MatchPosPtr, TInsPosPtr InsPosPtr2, TMol Mol, TPlusNodePtr PlusNodePtr12,
TPlusNodePtr PlusNodePtr21, TPlusNodePtr PlusNodePtr22,
TCoordPtr EndCoordPtr)
{
	TScore ScoreM;				/* Score de M								*/
	TScore ScoreI;				/* Score de I								*/
	TScore ScoreD;				/* Score de D								*/
	TScore M, I, D;				/* Score match, d'insertion, de deletion	*/
	TScore ScoreB;				/* Score de B								*/
	TScore ScoreBPlus;			/* Score de B+								*/
	TScore B;					/* Score d'initiation						*/
	TCoord EndCoord;			/* Coord. de fin							*/
	TCoord PlusNodeCoord;		/* Coord. d'un noeud +						*/
	
	/* Calcul de s(M+) */
	if ((PlusNodePtr22) && ((M =
	ScoreVect_ScoreNth(MatchPos_M(MatchPosPtr), Mol))
	!= PD_INFINITE)) {
		/* Il y a un acces a M+ */
		/* Calcul de s(M) */
		Coord_PutPosIndex(&PlusNodeCoord,
		Coord_PosIndex(PlusNodeCoordPtr) + 1);
		Coord_PutMolIndex(&PlusNodeCoord,
		Coord_MolIndex(PlusNodeCoordPtr) + 1);
		ScoreM = PlusNode_CalcM(PlusNodePtr22, &PlusNodeCoord, BLastNode,
		InsPosPtr2, &EndCoord);
		if (ScoreM != PD_INFINITE) PlusNode_PutMPlus(PlusNodePtr, ScoreM + M)
		else PlusNode_PutMPlus(PlusNodePtr, PD_INFINITE);
		PlusNode_PutMPlusEndCoord(PlusNodePtr, EndCoord)
	}
	
	else {
		PlusNode_PutMPlus(PlusNodePtr, PD_INFINITE);
		Coord_Reset(&PlusNode_MPlusEndCoord(PlusNodePtr));
	}
	
	/* Calcul de s(I+) */
	if ((PlusNodePtr12) && ((I = ScoreVect_ScoreNth(InsPos_I(InsPosPtr1), Mol))
	!= PD_INFINITE)) {
		/* Il y a un acces a I+ */
		/* Calcul de s(I) */
		Coord_PutPosIndex(&PlusNodeCoord,
		Coord_PosIndex(PlusNodeCoordPtr));
		Coord_PutMolIndex(&PlusNodeCoord,
		Coord_MolIndex(PlusNodeCoordPtr) + 1);
		ScoreI = PlusNode_CalcI(PlusNodePtr12, &PlusNodeCoord, BLastNode,
		InsPosPtr1, &EndCoord);
		if (ScoreI != PD_INFINITE) PlusNode_PutIPlus(PlusNodePtr, ScoreI + I)
		else PlusNode_PutIPlus(PlusNodePtr, PD_INFINITE);
		PlusNode_PutIPlusEndCoord(PlusNodePtr, EndCoord)
	}
	else {
		PlusNode_PutIPlus(PlusNodePtr, PD_INFINITE);
		Coord_Reset(&PlusNode_IPlusEndCoord(PlusNodePtr));
	}	

	/* Calcul de s(D+) */
	if ((PlusNodePtr21) && ((D = MatchPos_D(MatchPosPtr)) != PD_INFINITE)) {
		/* Il y a un acces a D+ */
		/* Calcul de s(D) */
		Coord_PutPosIndex(&PlusNodeCoord,
		Coord_PosIndex(PlusNodeCoordPtr) + 1);
		Coord_PutMolIndex(&PlusNodeCoord,
		Coord_MolIndex(PlusNodeCoordPtr));
		ScoreD = PlusNode_CalcD(PlusNodePtr21, &PlusNodeCoord,
		(TBoolean)!PlusNodePtr22, InsPosPtr2, &EndCoord);
		if (ScoreD != PD_INFINITE) PlusNode_PutDPlus(PlusNodePtr, ScoreD + D)
		else PlusNode_PutDPlus(PlusNodePtr, PD_INFINITE);
		PlusNode_PutDPlusEndCoord(PlusNodePtr, EndCoord)
	}
	else {
		PlusNode_PutDPlus(PlusNodePtr, PD_INFINITE);
		Coord_Reset(&PlusNode_DPlusEndCoord(PlusNodePtr));
	}
	
	/* Calcul de s(B+) */
	if ((B = (FirstNode) ? InsPos_B0(InsPosPtr1) : InsPos_B1(InsPosPtr1))
	!= PD_INFINITE) {
		/* Il y a un acces a B+ */
		/* Calcul de s(B) */
		ScoreB = PlusNode_CalcB(PlusNodePtr, PlusNodeCoordPtr,
		(TBoolean)!PlusNodePtr12, InsPosPtr1, EndCoordPtr);
		if (ScoreB != PD_INFINITE) ScoreBPlus = ScoreB + B;
		else ScoreBPlus = PD_INFINITE;
	}
	else {
		ScoreBPlus = PD_INFINITE;
		Coord_Reset(EndCoordPtr);
	}
	return ScoreBPlus;
}

/*--------------------------------------------------------------------------*/
/* Calcul d'un noeud + limite				 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PlusNodePtr				| Noeud								*/
/*			| PlusNodeCoordPtr			| Coordonnees du noeud +			*/
/*			| BLastNode					| Ind. s'il s'agit de l'a-d noeud	*/
/*			| FirstNode					| Ind. s'il s'agit du 1er noeud		*/
/*			| MatchPosPtr				| Position match					*/
/*			| InsPosPtr					| Position d'insertion				*/
/*			| Mol						| Molecule							*/
/*			| SubNodePtr21				| Sous-noeud (2,1)					*/
/*			| SubNodePtr22				| Sous-noeud (2,2)					*/
/*			| PlusNodePtr12				| Noeud + (1,2)						*/
/* Sortie:	| EndCoordPtr				| l(B+) par ce noeud				*/
/*			| PlusNode_LimCalc			| u(B+) par ce noeud				*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore PlusNode_LimCalc(TPlusNodePtr PlusNodePtr, TCoordPtr PlusNodeCoordPtr,
TBoolean BLastNode, TBoolean FirstNode, TMatchPosPtr MatchPosPtr, TInsPosPtr
InsPosPtr, TMol Mol, TSubNodePtr SubNodePtr21, TSubNodePtr SubNodePtr22,
TPlusNodePtr PlusNodePtr12, TCoordPtr EndCoordPtr)
{
	TScore ScoreI;				/* Score de I								*/
	TScore M, I, D;				/* Score match, d'insertion, de deletion	*/
	TScore ScoreB;				/* Score de B								*/
	TScore ScoreBPlus;			/* Score de B+								*/
	TScore B;					/* Score d'initiation						*/
	TCoord EndCoord;			/* Coord. de fin							*/
	TCoord PlusNodeCoord;		/* Coord. d'un noeud +						*/
	
	/* Calcul de s(M+) */
	if ((SubNodePtr22) && (SubNode_M(SubNodePtr22) != PD_INFINITE) &&
	((M = ScoreVect_ScoreNth(MatchPos_M(MatchPosPtr), Mol)) !=
	PD_INFINITE)) {
		/* s(M+) fini */
		PlusNode_PutMPlus(PlusNodePtr, SubNode_M(SubNodePtr22) + M);
		PlusNode_PutMPlusEndCoord(PlusNodePtr,
		SubNode_MEndCoord(SubNodePtr22));
	}
	else {
		PlusNode_PutMPlus(PlusNodePtr, PD_INFINITE);
		Coord_Reset(&PlusNode_MPlusEndCoord(PlusNodePtr));
	}
	/* Calcul de s(I+) */
	if ((PlusNodePtr12) && ((I = ScoreVect_ScoreNth(InsPos_I(InsPosPtr), Mol))
	!= PD_INFINITE)) {
		/* Il y a un acces a I+ */
		/* Calcul de s(I) */
		Coord_PutPosIndex(&PlusNodeCoord,
		Coord_PosIndex(PlusNodeCoordPtr));
		Coord_PutMolIndex(&PlusNodeCoord,
		Coord_MolIndex(PlusNodeCoordPtr) + 1);
		ScoreI = PlusNode_CalcI(PlusNodePtr12, &PlusNodeCoord, BLastNode,
		InsPosPtr, &EndCoord);
		if (ScoreI != PD_INFINITE) PlusNode_PutIPlus(PlusNodePtr, ScoreI + I)
		else PlusNode_PutIPlus(PlusNodePtr, PD_INFINITE);
		PlusNode_PutIPlusEndCoord(PlusNodePtr, EndCoord);
	}
	else {
		PlusNode_PutIPlus(PlusNodePtr, PD_INFINITE);
		Coord_Reset(&PlusNode_IPlusEndCoord(PlusNodePtr));
	}
	
	/* Calcul de s(D+) */
	if ((SubNodePtr21) && (SubNode_D(SubNodePtr21) != PD_INFINITE) &&
	((D = MatchPos_D(MatchPosPtr)) != PD_INFINITE)) {
		/* s(D+) fini */
		PlusNode_PutDPlus(PlusNodePtr, SubNode_D(SubNodePtr21) + D)
		PlusNode_PutDPlusEndCoord(PlusNodePtr,
		SubNode_DEndCoord(SubNodePtr21));
	}
	else {
		PlusNode_PutDPlus(PlusNodePtr, PD_INFINITE);
		Coord_Reset(&PlusNode_DPlusEndCoord(PlusNodePtr));
	}

	/* Calcul de s(B+) */
	if ((B = (FirstNode) ? InsPos_B0(InsPosPtr) : InsPos_B1(InsPosPtr))
	!= PD_INFINITE) {
		/* Il y a un acces a B+ */
		/* Calcul de s(B) */
		ScoreB = PlusNode_CalcB(PlusNodePtr, PlusNodeCoordPtr,
		(TBoolean)!PlusNodePtr12, InsPosPtr, EndCoordPtr);
		if (ScoreB != PD_INFINITE) ScoreBPlus = ScoreB + B;
		else ScoreBPlus = PD_INFINITE;
	}
	else {
		ScoreBPlus = PD_INFINITE;
		Coord_Reset(EndCoordPtr);
	}

	return ScoreBPlus;
}


/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un noeud+					 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PlusNodePtr				| Noeud+							*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_PlusNode(TPlusNodePtr PlusNodePtr)
{
	printf("(");
	Print_Score(PlusNode_MPlus(PlusNodePtr));
	printf(",");
	Print_Score(PlusNode_IPlus(PlusNodePtr));
	printf(",");
	Print_Score(PlusNode_DPlus(PlusNodePtr));
	printf(")\n");
	printf("[");
	Print_Coord(&PlusNode_MPlusEndCoord(PlusNodePtr));
	printf(",");
	Print_Coord(&PlusNode_IPlusEndCoord(PlusNodePtr));
	printf(",");
	Print_Coord(&PlusNode_DPlusEndCoord(PlusNodePtr));
	printf("]\n");
}

/*==============================*/
/* Manipulation des sous-noeuds */
/*==============================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul d'un sous-noeud													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubNodePtr				| Sous-noeud						*/
/*			| PlusNodePtr				| Noeud +							*/
/*			| PlusNodeCoordPtr			| Coordonnees du noeud +			*/
/*			| InsPosPtr					| Position d'insertion				*/
/*			| LastPlusNode				| Ind. s'il s'agit du dern. noeud +	*/
/* Sortie:	| SubNode_Calc				| Sous-Noeud calcule				*/
/*			| SubNodePtr				| Idem								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TSubNodePtr SubNode_Calc(TSubNodePtr SubNodePtr, TPlusNodePtr PlusNodePtr,
TCoordPtr PlusNodeCoordPtr, TInsPosPtr InsPosPtr, TBoolean LastPlusNode)
{
	TScore ScoreM;				/* Score du sommet M	*/
	TScore ScoreD;				/* Score du sommet D	*/
	TCoord EndCoord;			/* l(V)					*/
			
	/* Calcul de M */
	ScoreM = PlusNode_CalcM(PlusNodePtr, PlusNodeCoordPtr, LastPlusNode,
	InsPosPtr, &EndCoord);
	SubNode_PutM(SubNodePtr, ScoreM);
	SubNode_PutMEndCoord(SubNodePtr, EndCoord);

	/* Calcule de D */
	ScoreD = PlusNode_CalcD(PlusNodePtr, PlusNodeCoordPtr, LastPlusNode,
	InsPosPtr, &EndCoord);
	SubNode_PutD(SubNodePtr, ScoreD);
	SubNode_PutDEndCoord(SubNodePtr, EndCoord);
	
	return SubNodePtr;
}

/*--------------------------------------------------------------------------*/
/* Calcul des alignements prolonges par un sous-noeuds						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubNodePtr				| Sous-noeud V						*/
/*			| SubNodeCoordPtr			| Coord de V						*/
/*			| SubPlusNodePtr11			| Sous-noeud + (1,1)				*/
/*			| SubPlusNodePtr12			| Sous-noeud + (1,2)				*/
/*			| Mol						| Molecule							*/
/*			| MatchPosPtr				| Position match					*/
/* Sortie:	| AlignPtr					| A^ par ce sous-noeud				*/
/*			| FirstMolIndex				| f(V).j							*/
/*			| SubNode_ExtAlign			| Meilleur score rencontre			*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TScore SubNode_ExtAlign(TSubNodePtr SubNodePtr, TCoordPtr SubNodeCoordPtr,
TSubPlusNodePtr SubPlusNodePtr11, TSubPlusNodePtr SubPlusNodePtr12, TMol Mol,
TMatchPosPtr MatchPosPtr, TAlignPtr AlignPtr, TMolIndex *FirstMolIndexPtr)
{
	TScore Score;		/* Score temporaire	*/
	TScore ScoreD;		/* Score de D		*/
	TScore ScoreM;		/* Score de M		*/
	TScore ScoreDPlus;	/* Score de D+		*/
	TScore ScoreMPlus;	/* Score de M+		*/
	TScore D;			/* Score de D		*/
	TScore M;			/* Score de M		*/

	/* Initialisation de A^ */
	Align_Reset(AlignPtr);

	/* Par D+->D */

	if (((ScoreD = SubNode_D(SubNodePtr)) != PD_INFINITE) && ((ScoreDPlus =
	SubPlusNode_DPlus(SubPlusNodePtr12)) != PD_INFINITE) &&
	((D = MatchPos_D(MatchPosPtr)) != PD_INFINITE)) {
	
		Align_PutScore(AlignPtr, ScoreD + D + ScoreDPlus);
		Align_PutStartCoord(AlignPtr,
		SubPlusNode_DPlusStartCoord(SubPlusNodePtr12));
		Align_PutEndCoord(AlignPtr, SubNode_DEndCoord(SubNodePtr));
		Coord_PutPosIndex(&Align_InCoord(AlignPtr),
		Coord_PosIndex(SubNodeCoordPtr) - 1);
		Coord_PutMolIndex(&Align_InCoord(AlignPtr),
		Coord_MolIndex(SubNodeCoordPtr));
		Align_PutOutCoord(AlignPtr, *SubNodeCoordPtr);
	}

	/* Par M+->M */
			
	if ((SubPlusNodePtr11) && ((ScoreM = SubNode_M(SubNodePtr)) !=
	PD_INFINITE) && ((ScoreMPlus = SubPlusNode_MPlus(SubPlusNodePtr11))
	!= PD_INFINITE) && ((M = ScoreVect_ScoreNth(MatchPos_M(MatchPosPtr), Mol))
	!= PD_INFINITE) && ((Score = ScoreMPlus + M + ScoreM) >
	Align_Score(AlignPtr))) {
		/* Un meilleur score a ete trouve */
		Align_PutScore(AlignPtr, Score);
		Align_PutStartCoord(AlignPtr,
		SubPlusNode_MPlusStartCoord(SubPlusNodePtr11));
		Align_PutEndCoord(AlignPtr, SubNode_MEndCoord(SubNodePtr));
		Coord_PutPosIndex(&Align_InCoord(AlignPtr),
		Coord_PosIndex(SubNodeCoordPtr) - 1);
		Coord_PutMolIndex(&Align_InCoord(AlignPtr),
		Coord_MolIndex(SubNodeCoordPtr) - 1);
		Align_PutOutCoord(AlignPtr, *SubNodeCoordPtr);
	}
	
	/* calcul de j_first = j(V) */
	*FirstMolIndexPtr = Coord_MolIndex(SubNodeCoordPtr);

	return Align_Score(AlignPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un sous-noeud				 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubNodePtr				| Sous-noeud						*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_SubNode(TSubNodePtr SubNodePtr)
{
	printf("(");
	Print_Score(SubNode_M(SubNodePtr));
	printf(",");
	Print_Score(SubNode_D(SubNodePtr));
	printf(")\n");
	printf("[");
	Print_Coord(&SubNode_MEndCoord(SubNodePtr));
	printf(",");
	Print_Coord(&SubNode_DEndCoord(SubNodePtr));
	printf("]\n");
}

/*============================================*/
/* Routines de manipulation des sous-noeuds + */
/*============================================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul d'un sous-noeud +													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubPlusNodePtr			| Sous-noeud +						*/
/*			| NodePtr					| Noeud								*/
/*			| NodeCoordPtr				| Coordonnees du noeud				*/
/*			| InsPosPtr					| Position d'insertion				*/
/*			| FirstNode					| Indique s'il s'agit du 1er noeud	*/
/* Sortie:	| SubPlusNode_Calc			| Sous-noeud + calcule				*/
/*			| SubPlusNodePtr			| Idem								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TSubPlusNodePtr SubPlusNode_Calc(TSubPlusNodePtr SubPlusNodePtr, TNodePtr
NodePtr, TCoordPtr NodeCoordPtr, TInsPosPtr InsPosPtr, TBoolean FirstNode)
{
	TScore ScoreMPlus;		/* Score du sommet M+	*/
	TScore ScoreDPlus;		/* Score du sommet D+	*/
	TCoord StartCoord;		/* f(V+)				*/
			
	/* Calcul de M+ */
	ScoreMPlus = Node_CalcMPlus(NodePtr, NodeCoordPtr, FirstNode, InsPosPtr,
	&StartCoord);
	SubPlusNode_PutMPlus(SubPlusNodePtr, ScoreMPlus);
	SubPlusNode_PutMPlusStartCoord(SubPlusNodePtr, StartCoord);

	/* Calcule de D+ */
	ScoreDPlus = Node_CalcDPlus(NodePtr, NodeCoordPtr, FirstNode, InsPosPtr,
	&StartCoord);
	SubPlusNode_PutDPlus(SubPlusNodePtr, ScoreDPlus);
	SubPlusNode_PutDPlusStartCoord(SubPlusNodePtr, StartCoord);
	
	return SubPlusNodePtr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un sous-noeud+				 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubPlusNodePtr			| Sous-noeud+						*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_SubPlusNode(TSubPlusNodePtr SubPlusNodePtr)
{
	printf("(");
	Print_Score(SubPlusNode_MPlus(SubPlusNodePtr));
	printf(",");
	Print_Score(SubPlusNode_DPlus(SubPlusNodePtr));
	printf(")\n");
	printf("[");
	Print_Coord(&SubPlusNode_MPlusStartCoord(SubPlusNodePtr));
	printf(",");
	Print_Coord(&SubPlusNode_DPlusStartCoord(SubPlusNodePtr));
	printf("]\n");
}


/*===================================================*/
/* Manipulations des vecteurs de noeuds // au profil */
/*===================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodeNbr					| Nombre de noeuds					*/
/* Sortie:	| I_NodeVect				| Vecteur de noeuds					*/
/* Erreur:	| I_NodeVect=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TNodeVectPtr I_NodeVect(TPosIndex NodeNbr)
{
	TNodeVectPtr NodeVectPtr;
	
	NodeVectPtr = (TNodeVectPtr)malloc(sizeof(TNodeVect));
	if (!NodeVectPtr) {
		/* Erreur allocation */
		return NULL;
	}
	NodeVectPtr->NodeArray = (TNodePtr)calloc(NodeNbr, sizeof(TNode));
	if (!(NodeVectPtr->NodeArray)) {
		/* Erreur allocation */
		free(NodeVectPtr);
		return NULL;
	}
	NodeVectPtr->NodeNbr = NodeNbr;
	return NodeVectPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodeVectPtr				| Vecteur de noeuds etendu			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_NodeVect(TNodeVectPtr NodeVectPtr)
{
	free(NodeVectPtr->NodeArray);
	free(NodeVectPtr);
}

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul d'un vecteur de noeuds											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| InNodeVectPtr				| Vecteur de noeuds	d'entree		*/
/*			| SecondVect				| Indique s'il s'agit du 2eme vect.	*/
/*			| LastVect					| Ind. s'il s'agit du dern.  vect.	*/
/*			| Mol						| Molecule							*/
/*			| MolIndex					| Index de la molecule				*/
/*			| PrfMatrixPtr				| Matrice de profil					*/
/* Sortie:	| OutNodeVectPtr			| Vecteur de noeuds de sortie		*/
/*			| StartCoord				| F(A^)								*/
/*			| EndCoord					| L(A^)								*/
/*			| NodeVect_Calc				| Meilleur score rencontre			*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TScore NodeVect_Calc(TNodeVectPtr InNodeVectPtr, TBoolean SecondVect,
TBoolean LastVect, TMol Mol, TMolIndex MolIndex, TPrfMatrixPtr PrfMatrixPtr,
TNodeVectPtr OutNodeVectPtr, TCoordPtr StartCoordPtr, TCoordPtr EndCoordPtr)
{
	/* Acces au profil */
	TInsPosPtr *InsPosList;			/* Liste des positions d'insertion		*/
	TMatchPosPtr *MatchPosList;		/* Liste des positions match			*/
	TPosIndex PosIndex;				/* Index de Position					*/
	TPosIndex PosNbr;				/* Nombre de noeuds						*/

	/* Acces au vecteur de noeuds etendus */
	TNodePtr InNodeArray;			/* Tableau de noeuds d'entree			*/
	TNodePtr OutNodeArray;			/* Tableau de noeuds de sortie			*/
	
	/* Pointeurs sur les noeuds etendus */
	TNodePtr NodePtr21;				/* Noeud gauche							*/
	TNodePtr NodePtr11;				/* Noeud haut gauche					*/
	
	/* Donnees de l'algorithme */
	TNode OldNode;					/* Noeud (i-1,j-1)						*/
	TNode NewNode;					/* Noeud (i,j)							*/
	TScore Score;					/* Score temporaire						*/
	TScore BestScore;				/* S(A^);								*/
	TCoord NodeCoord;				/* Coordonnees du noeud					*/
	TCoord StartCoord;				/* f(E)									*/
	
	/* Initialisation des variables de deferenciation */

	/* Acces a la matrice de profil */
	InsPosList = PrfMatrix_InsPosList(PrfMatrixPtr);
	MatchPosList = PrfMatrix_MatchPosList(PrfMatrixPtr);
	
	/* Acces au vecteur de noeuds */
	if (InNodeVectPtr) InNodeArray = NodeVect_Array(InNodeVectPtr);
	else InNodeArray = NULL;
	PosNbr = NodeVect_NodeNbr(OutNodeVectPtr);
	OutNodeArray = NodeVect_Array(OutNodeVectPtr);
	
	/* Initialisation des coord. */
	Coord_PutMolIndex(&NodeCoord, MolIndex);
	Coord_PutPosIndex(&NodeCoord, 0);

	/* Calcul du vecteur */

	/* Calcul du premier noeud */

	if (InNodeVectPtr) NodePtr21 = &NodeArray_NodeNth(InNodeArray, 0);
	else NodePtr21 = NULL;

	BestScore = Node_Calc(&NewNode, &NodeCoord, SecondVect,
	LastVect, NULL, MatchPosList_PosNth(MatchPosList, 0),
	InsPosList_PosNth(InsPosList, 0), Mol, NULL, NULL, NodePtr21,
	StartCoordPtr);

	*EndCoordPtr = NodeCoord;
	
	/* Mise a jour des noeuds */
	if (InNodeVectPtr) OldNode = *NodePtr21;
	NodeArray_PutNodeNth(OutNodeArray, NewNode, 0);

	/* Affichage du noeud calcule */
	/*printf("\n");*/
	/*Print_PosIndex(StartInsPos);*/
	/*printf(" Nth Node\n");*/
	/*Print_Node(&NewNode);*/
	/*printf("\n");*/

	/* Calcul des autres noeuds */
	for (PosIndex = 1; PosIndex <= PosNbr - 1; PosIndex++) { /* PosNbr >= 1 */
	
		Coord_PutPosIndex(&NodeCoord, PosIndex);
	
		if (InNodeVectPtr) {
			NodePtr21 = &NodeArray_NodeNth(InNodeArray, PosIndex);
			NodePtr11 = &OldNode;
		}
		else {
			NodePtr21 = NULL;
			NodePtr11 = NULL;			
		}	

		Score = Node_Calc(&NewNode, &NodeCoord, SecondVect,
		LastVect, InsPosList_PosNth(InsPosList, PosIndex - 1),
		MatchPosList_PosNth(MatchPosList, PosIndex),
		InsPosList_PosNth(InsPosList, PosIndex), Mol, NodePtr11,
		&NodeArray_NodeNth(OutNodeArray, PosIndex - 1), NodePtr21,
		&StartCoord);
		
		/* Affichage du noeud calcule */
		/*printf("\n");*/
		/*Print_PosIndex(PosIndex);*/
		/*printf(" Nth Node\n");*/
		/*Print_Node(&NewNode);*/
		/*printf("\n");*/
		
		/* Essai de depasser le meilleur score precedent */
		if (Score > BestScore) {
			/* Le nouveau score est meilleur */
			BestScore = Score;
			*StartCoordPtr = StartCoord;
			*EndCoordPtr = NodeCoord;
		}
		
		/* Mise a jour des noeuds */
		if (InNodeVectPtr) OldNode = *NodePtr21;
		NodeArray_PutNodeNth(OutNodeArray, NewNode, PosIndex);
	}

	return BestScore;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodeVectPtr				| Vecteur de noeuds					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_NodeVect(TNodeVectPtr NodeVectPtr)
{
	TPosIndex NodeIndex;
	
	for (NodeIndex = 0; NodeIndex < NodeVect_NodeNbr(NodeVectPtr);
	NodeIndex++) {
		Print_Node(&NodeVect_NodeNth(NodeVectPtr, NodeIndex));
	}
}


/*===========================================================*/
/* Manipulations des vecteurs de noeuds etendus // au profil */
/*===========================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodeNbr				| Nombre de noeuds etendus			*/
/* Sortie:	| I_ExtNodeVect				| Vecteur de noeuds etendus			*/
/* Erreur:	| I_ExtNodeVect=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TExtNodeVectPtr I_ExtNodeVect(TPosIndex ExtNodeNbr)
{
	TExtNodeVectPtr ExtNodeVectPtr;
	
	ExtNodeVectPtr = (TExtNodeVectPtr)malloc(sizeof(TExtNodeVect));
	if (!ExtNodeVectPtr) {
		/* Erreur allocation */
		return NULL;
	}
	ExtNodeVectPtr->ExtNodeArray = (TExtNodePtr)calloc(ExtNodeNbr,
	sizeof(TExtNode));
	if (!(ExtNodeVectPtr->ExtNodeArray)) {
		/* Erreur allocation */
		free(ExtNodeVectPtr);
		return NULL;
	}
	ExtNodeVectPtr->ExtNodeNbr = ExtNodeNbr;
	return ExtNodeVectPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de noeuds etendu								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodeVectPtr			| Vecteur de noeuds etendu			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_ExtNodeVect(TExtNodeVectPtr ExtNodeVectPtr)
{
	free(ExtNodeVectPtr->ExtNodeArray);
	free(ExtNodeVectPtr);
}

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul d'un vecteur de noeuds etendus									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| InExtNodeVectPtr			| Vecteur de noeuds	d'entree		*/
/*			| FirstVect					| Indique s'il s'agit du 1er vect.	*/
/*			| SecondVect				| Indique s'il s'agit du 2eme vect.	*/
/*			| LastVect					| Ind. s'il s'agit du dern.  vect.	*/
/*			| SubPlusNodePtr11			| Sous-noeud + (1,1)				*/
/*			| SubPlusNodePtr12			| Sous-noeud + (1,2)				*/
/*			| SubNodePtr21				| Sous-noeud (2,1)					*/
/*			| Mol						| Molecule							*/
/*			| MolIndex					| Index de la molecule				*/
/*			| PrfMatrixPtr				| Matrice de profil					*/
/*			| StartInsPos				| Pos. Ins.de depart dans le prof.	*/
/* Sortie:	| OutExtNodeVectPtr			| Vecteur de noeuds de sortie		*/
/*			| AlignPtr					| A^ par ce vecteur					*/
/*			| FirstMolIndex				| min(f(V).j)						*/
/*			| ExtNodeVect_Calc			| Meilleur score rencontre			*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TScore ExtNodeVect_Calc(TExtNodeVectPtr InExtNodeVectPtr, TBoolean FirstVect,
TBoolean SecondVect, TBoolean LastVect, TSubPlusNodePtr SubPlusNodePtr11,
TSubPlusNodePtr SubPlusNodePtr12, TSubNodePtr SubNodePtr21, TMol Mol,
TMolIndex MolIndex, TPrfMatrixPtr PrfMatrixPtr, TPosIndex StartInsPos,
TExtNodeVectPtr OutExtNodeVectPtr, TAlignPtr AlignPtr, TMolIndex
*FirstMolIndexPtr)
{
	/* Acces au profil */
	TInsPosPtr *InsPosList;			/* Liste des positions d'insertion		*/
	TMatchPosPtr *MatchPosList;		/* Liste des positions match			*/
	TInsPosPtr InsPosPtr;			/* Position d'insertion					*/
	TMatchPosPtr MatchPosPtr;		/* Position match						*/
	TPosIndex PosIndex;				/* Index de Position					*/
	TPosIndex PosNbr;				/* Nombre de noeuds						*/
	TPosIndex Index;				/* Index temporaire						*/

	/* Acces au vecteur de noeuds etendus */
	TExtNodePtr InExtNodeArray;		/* Tableau de noeuds d'entree			*/
	TExtNodePtr OutExtNodeArray;	/* Tableau de noeuds de sortie			*/
	
	/* Pointeurs sur les noeuds etendus */
	TExtNodePtr ExtNodePtr21;		/* Noeud gauche							*/
	TExtNodePtr ExtNodePtr11;		/* Noeud haut gauche					*/
	
	/* Donnees de l'algorithme */
	TExtNode OldExtNode;			/* Noeud (i-1,j-1)						*/
	TExtNode NewExtNode;			/* Noeud (i,j)							*/
	TScore Score;					/* Score temporaire						*/
	TScore ScoreDPlus;				/* Score de D+							*/
	TScore ScoreMPlus;				/* Score de M+							*/
	TScore ScoreD;					/* Score de D							*/
	TScore ScoreM;					/* Score de M							*/
	TScore D;						/* Score de deletion					*/
	TScore M;						/* Score match							*/					
	TCoord ExtNodeCoord;			/* Coordonnees du noeud					*/
	TCoord StartCoord;				/* f(E)									*/
	TCoord InCoord;					/* fp(E)								*/
	TMolIndex FirstMolIndex;		/* min (f(V).j)							*/
	
	/* Initialisation des variables de deferenciation */

	/* Acces a la matrice de profil */
	InsPosList = PrfMatrix_InsPosList(PrfMatrixPtr);
	MatchPosList = PrfMatrix_MatchPosList(PrfMatrixPtr);
	
	/* Acces au vecteur de noeuds */
	if (InExtNodeVectPtr) InExtNodeArray = ExtNodeVect_Array(InExtNodeVectPtr);
	else InExtNodeArray = NULL;
	PosNbr = ExtNodeVect_ExtNodeNbr(OutExtNodeVectPtr);
	OutExtNodeArray = ExtNodeVect_Array(OutExtNodeVectPtr);
	
	/* Initialisation de la position du vecteur ds la coord. */
	Coord_PutMolIndex(&ExtNodeCoord, MolIndex);
	Coord_PutPosIndex(&ExtNodeCoord, StartInsPos);

	/* Calcul du vecteur */

	/* Calcul du premier noeud */

	if (InExtNodeVectPtr) ExtNodePtr21 =
	&ExtNodeArray_ExtNodeNth(InExtNodeArray, 0);
	else ExtNodePtr21 = NULL;

	Score = ExtNode_LimCalc(&NewExtNode, &ExtNodeCoord, SecondVect,
	LastVect, MatchPosList_PosNth(MatchPosList, StartInsPos),
	InsPosList_PosNth(InsPosList, StartInsPos),
	Mol, SubPlusNodePtr11, SubPlusNodePtr12, ExtNodePtr21, 
	&Align_StartCoord(AlignPtr), &Align_InCoord(AlignPtr));

	Align_PutScore(AlignPtr, Score);
	Align_PutEndCoord(AlignPtr, ExtNodeCoord);
	Align_PutOutCoord(AlignPtr, ExtNodeCoord);

	*FirstMolIndexPtr = ExtNode_FirstMolIndex(&NewExtNode, &ExtNodeCoord);
	
	/* Mise a jour des noeuds */
	if (InExtNodeVectPtr) OldExtNode = *ExtNodePtr21;
	ExtNodeArray_PutExtNodeNth(OutExtNodeArray, NewExtNode, 0);

	/* Affichage du noeud calcule */
	/*printf("\n");*/
	/*Print_PosIndex(StartInsPos);*/
	/*printf(" Nth Node\n");*/
	/*Print_Node(&NewExtNode);*/
	/*printf("\n");*/

	/* Calcul des autres noeuds */
	for (Index = 1; Index <= PosNbr - 1; Index++) { /* PosNbr >= 1 */
	
		PosIndex = Index + StartInsPos;
		Coord_PutPosIndex(&ExtNodeCoord, PosIndex);
	
		if (InExtNodeVectPtr) {
			ExtNodePtr21 = &ExtNodeArray_ExtNodeNth(InExtNodeArray, Index);
			ExtNodePtr11 = &OldExtNode;
		}
		else {
			ExtNodePtr21 = NULL;
			ExtNodePtr11 = NULL;			
		}	

		Score = ExtNode_Calc(&NewExtNode, &ExtNodeCoord, SecondVect,
		LastVect, InsPosList_PosNth(InsPosList, PosIndex - 1),
		MatchPosList_PosNth(MatchPosList, PosIndex),
		InsPosList_PosNth(InsPosList, PosIndex), Mol, ExtNodePtr11,
		&ExtNodeArray_ExtNodeNth(OutExtNodeArray, Index - 1), ExtNodePtr21,
		&StartCoord, &InCoord);
		
		if ((FirstMolIndex = ExtNode_FirstMolIndex(&NewExtNode,
		&ExtNodeCoord)) < *FirstMolIndexPtr)
			*FirstMolIndexPtr = FirstMolIndex;
		
		/* Affichage du noeud calcule */
		/*printf("\n");*/
		/*Print_PosIndex(PosIndex);*/
		/*printf(" Nth Node\n");*/
		/*Print_Node(&NewExtNode);*/
		/*printf("\n");*/
		
		/* Essai de depasser le meilleur score precedent */
		if (Score > Align_Score(AlignPtr)) {
			/* Le nouveau score est meilleur */
			Align_PutScore(AlignPtr, Score);
			Align_PutStartCoord(AlignPtr, StartCoord);
			Align_PutEndCoord(AlignPtr, ExtNodeCoord);
			Align_PutInCoord(AlignPtr, InCoord);
			Align_PutOutCoord(AlignPtr, ExtNodeCoord);
		}
		
		/* Mise a jour des noeuds */
		if (InExtNodeVectPtr) OldExtNode = *ExtNodePtr21;
		ExtNodeArray_PutExtNodeNth(OutExtNodeArray, NewExtNode, Index);
	}

	/* Calcul des scores des alignements prolonges */
	
	if (SubNodePtr21) {
		/* il existe des alignements prolonges */

		InsPosPtr = InsPosList_PosNth(InsPosList, StartInsPos + PosNbr - 1);
		MatchPosPtr = MatchPosList_PosNth(MatchPosList, StartInsPos + PosNbr);

		/* Par D+->D */

		if ((ScoreD = SubNode_D(SubNodePtr21)) != PD_INFINITE) {

			/* Calcul de s(D+) */
			ScoreDPlus = ExtNode_CalcDPlus(&NewExtNode, &ExtNodeCoord,
			FirstVect, InsPosPtr, &StartCoord, &InCoord);

			/* Calcul de la longueur totale de l'alignement */
			if ((ScoreDPlus != PD_INFINITE) && ((D = MatchPos_D(MatchPosPtr))
			!= PD_INFINITE) && ((Score = ScoreDPlus + D + ScoreD)
			> Align_Score(AlignPtr))) {
				/* Un meilleur score a ete trouve */
				Align_PutScore(AlignPtr, Score);
				Align_PutStartCoord(AlignPtr, StartCoord);
				Align_PutEndCoord(AlignPtr, SubNode_DEndCoord(SubNodePtr21));
				Align_PutInCoord(AlignPtr, InCoord);
				Coord_PutPosIndex(&Align_OutCoord(AlignPtr),
				Coord_PosIndex(&ExtNodeCoord) + 1);
				Coord_PutMolIndex(&Align_OutCoord(AlignPtr),
				Coord_MolIndex(&ExtNodeCoord));
			}
		}

		/* Par M+->M */
			
		if ((InExtNodeVectPtr) && ((ScoreM = SubNode_M(SubNodePtr21)) !=
		PD_INFINITE)) {
		
			/* ExtNodeCoord contient les coord. de OldExtNode */
			Coord_PutMolIndex(&ExtNodeCoord,
			Coord_MolIndex(&ExtNodeCoord) - 1);	

			ScoreMPlus = ExtNode_CalcMPlus(&OldExtNode, &ExtNodeCoord,
			SecondVect, InsPosPtr, &StartCoord, &InCoord);
		
			/* Calcul de la longueur totale de l'alignement */
			if ((ScoreMPlus != PD_INFINITE) &&
			((M = ScoreVect_ScoreNth(MatchPos_M(MatchPosPtr), Mol))
			!= PD_INFINITE) && ((Score = ScoreMPlus + M + ScoreM) >
			Align_Score(AlignPtr))) {
				/* Un meilleur score a ete trouve */
				Align_PutScore(AlignPtr, Score);
				Align_PutStartCoord(AlignPtr, StartCoord);
				Align_PutEndCoord(AlignPtr, SubNode_MEndCoord(SubNodePtr21));
				Align_PutInCoord(AlignPtr, InCoord);
				Coord_PutPosIndex(&Align_OutCoord(AlignPtr),
				Coord_PosIndex(&ExtNodeCoord) + 1);
				Coord_PutMolIndex(&Align_OutCoord(AlignPtr),
				Coord_MolIndex(&ExtNodeCoord) + 1);
			}
		}
	}
	return Align_Score(AlignPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de noeuds etendus								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodeVectPtr			| Vecteur de noeuds etendus			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_ExtNodeVect(TExtNodeVectPtr ExtNodeVectPtr)
{
	TPosIndex ExtNodeIndex;
	
	for (ExtNodeIndex = 0; ExtNodeIndex <
	ExtNodeVect_ExtNodeNbr(ExtNodeVectPtr); ExtNodeIndex++) {
		Print_ExtNode(&ExtNodeVect_ExtNodeNth(ExtNodeVectPtr, ExtNodeIndex));
	}
}

/*======================================================*/
/* Manipulation des vecteurs de noeuds // a la sequence */
/*======================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodeNbr					| Nombre de noeuds					*/
/* Sortie:	| I_SeqNodeVect				| Vecteur de noeuds					*/
/* Erreur:	| I_SeqNodeVect=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSeqNodeVectPtr I_SeqNodeVect(TMolIndex NodeNbr)
{
	TSeqNodeVectPtr SeqNodeVectPtr;
	
	SeqNodeVectPtr = (TSeqNodeVectPtr)malloc(sizeof(TSeqNodeVect));
	if (!SeqNodeVectPtr) {
		/* Erreur allocation */
		return NULL;
	}
	SeqNodeVectPtr->NodeArray = (TNodePtr)calloc(NodeNbr, sizeof(TNode));
	if (!(SeqNodeVectPtr->NodeArray)) {
		/* Erreur allocation */
		free(SeqNodeVectPtr);
		return NULL;
	}
	SeqNodeVectPtr->NodeNbr = NodeNbr;
	return SeqNodeVectPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqNodeVectPtr			| Vecteur de noeuds					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SeqNodeVect(TSeqNodeVectPtr SeqNodeVectPtr)
{
	free(SeqNodeVectPtr->NodeArray);
	free(SeqNodeVectPtr);
}

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul d'un vecteur de noeuds											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqNodeVectPtr			| Vecteur de noeuds					*/
/*			| MolSeqPtr					| Sequence de molecules				*/
/*			| PosIndex					| Index de position					*/
/*			| InsPosPtr1				| 1ere position d'insertion			*/
/*			| MatchPosPtr				| Position match					*/
/*			| InsPosPtr2				| 2eme position d'insertion			*/
/* Sortie:	| SeqNodeVectPtr			| Vecteur de noeuds					*/
/*			| BestStartCoordPtr			| F(A^) en ce vecteur				*/
/*			| BestEndCoordPtr			| L(A^) en ce vecteur				*/
/*			| SeqNodeVect_Calc			| Meilleur score rencontre			*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TScore SeqNodeVect_Calc(TSeqNodeVectPtr SeqNodeVectPtr, TMolSeqPtr MolSeqPtr,
TPosIndex PosIndex, TInsPosPtr InsPosPtr1, TMatchPosPtr MatchPosPtr,
TInsPosPtr InsPosPtr2, TCoordPtr BestStartCoordPtr, TCoordPtr
BestEndCoordPtr)
{
	/* Acces a la sequence */
	TMol *MolStr;					/* Chaine de molecules					*/
	TMolIndex MolNbr;				/* Nombre de molecules de la sequence	*/
	TMolIndex MolIndex;				/* Index de molecule					*/

	/* Acces au vecteur de noeuds */
	TNodePtr NodeArray;				/* Tableau de noeuds					*/
	
	/* Pointeurs sur les noeuds */
	TNodePtr NodePtr11;				/* Noeud (1,1)							*/
	TNodePtr NodePtr12;				/* Noeud (1,2)							*/
	
	/* Donnees de l'algorithme */
	TNode OldNode;					/* Noeud (i-1,j-1)						*/
	TNode NewNode;					/* Noeud (i,j)							*/
	TCoord NodeCoord;				/* Coordonnee du noeud a calculer		*/
	TScore ScoreE;					/* s(E)									*/
	TScore MaxScore;				/* Score maximum						*/
	TCoord StartCoord;				/* Coord. de depart						*/

	/* Initialisation des variables de deferenciation */
	
	/* Acces a la sequence */
	MolStr = MolSeq_MolStr(MolSeqPtr);
	MolNbr = MolSeq_MolNbr(MolSeqPtr);
	
	/* Acces au vecteur de noeuds */
	NodeArray = SeqNodeVect_Array(SeqNodeVectPtr);
		
	/* Calcul du vecteur */
	
	/* Calcul du noeud (i,0) */

	Coord_PutPosIndex(&NodeCoord, PosIndex);
	Coord_PutMolIndex(&NodeCoord, 0);
	NodePtr12 = InsPosPtr1 ? &SeqNodeArray_NodeNth(NodeArray, 0) : NULL;
	
	MaxScore = Node_Calc(&NewNode, &NodeCoord, FALSE, FALSE, InsPosPtr1,
	MatchPosPtr, InsPosPtr2, SD_MOL_NOT_DEF, NULL, NodePtr12, NULL,
	BestStartCoordPtr);
	*BestEndCoordPtr = NodeCoord;
	
	/* Mise a jour des noeuds */
	
	if (InsPosPtr1) OldNode = *NodePtr12;
	SeqNodeArray_PutNodeNth(NodeArray, NewNode, 0);

	/* Calcul des autres noeuds */
	
	for (MolIndex = 1; MolIndex <= MolNbr; MolIndex++) { /* MolNbr >= 0 */

		Coord_PutPosIndex(&NodeCoord, PosIndex);
		Coord_PutMolIndex(&NodeCoord, MolIndex);
		
		if (InsPosPtr1) {
			NodePtr11 = &OldNode;
			NodePtr12 = &SeqNodeArray_NodeNth(NodeArray, MolIndex);
		}
		else {
			NodePtr11 = NULL;
			NodePtr12 = NULL;
		}
		
		ScoreE = Node_Calc(&NewNode, &NodeCoord, MolIndex == 1,
		MolIndex == MolNbr, InsPosPtr1, MatchPosPtr, InsPosPtr2,
		MolStr_MolNth(MolStr, MolIndex), NodePtr11, NodePtr12,
		&SeqNodeArray_NodeNth(NodeArray, MolIndex - 1), &StartCoord);

		/* Essai de depasser le meilleur score precedent */
		if (ScoreE > MaxScore) {
			/* Le nouveau score est meilleur */
			MaxScore = ScoreE;
			*BestStartCoordPtr = StartCoord;
			*BestEndCoordPtr = NodeCoord;
		}
		
		/* Mise a jour des noeuds */
		if (InsPosPtr1) OldNode = *NodePtr12;
		SeqNodeArray_PutNodeNth(NodeArray, NewNode, MolIndex);
	}
	return MaxScore;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqNodeVectPtr			| Vecteur de noeuds					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_SeqNodeVect(TSeqNodeVectPtr SeqNodeVectPtr)
{
	TMolIndex NodeIndex;
	
	for (NodeIndex = 0; NodeIndex < SeqNodeVect_NodeNbr(SeqNodeVectPtr);
	NodeIndex++) {
		Print_MolIndex(NodeIndex);
		printf("Nth Node:");
		Print_Node(&SeqNodeVect_NodeNth(SeqNodeVectPtr, NodeIndex));
		printf("\n");
	}
}

/*=======================================================*/
/* Manipulation des vecteurs de noeuds+ // a la sequence */
/*=======================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un vecteur de noeuds+										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PlusNodeNbr				| Nombre de noeuds+					*/
/* Sortie:	| I_SeqPlusNodeVect			| Vecteur de noeuds+				*/
/* Erreur:	| I_SeqPlusNodeVect=NULL	| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSeqPlusNodeVectPtr I_SeqPlusNodeVect(TMolIndex PlusNodeNbr)
{
	TSeqPlusNodeVectPtr SeqPlusNodeVectPtr;
	
	SeqPlusNodeVectPtr = (TSeqPlusNodeVectPtr)malloc(sizeof(TSeqPlusNodeVect));
	if (!SeqPlusNodeVectPtr) {
		/* Erreur allocation */
		return NULL;
	}
	SeqPlusNodeVectPtr->PlusNodeArray = (TPlusNodePtr)calloc(PlusNodeNbr,
	sizeof(TPlusNode));
	if (!(SeqPlusNodeVectPtr->PlusNodeArray)) {
		/* Erreur allocation */
		free(SeqPlusNodeVectPtr);
		return NULL;
	}
	SeqPlusNodeVectPtr->PlusNodeNbr = PlusNodeNbr;
	return SeqPlusNodeVectPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de noeuds+										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqPlusNodeVectPtr		| Vecteur de noeuds+				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SeqPlusNodeVect(TSeqPlusNodeVectPtr SeqPlusNodeVectPtr)
{
	free(SeqPlusNodeVectPtr->PlusNodeArray);
	free(SeqPlusNodeVectPtr);
}

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul d'un vecteur de noeuds+											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqPlusNodeVectPtr		| Vecteur de noeuds+				*/
/*			| MolSeqPtr					| Sequence de molecules				*/
/*			| PosIndex					| Index de position					*/
/*			| InsPosPtr1				| 1ere position d'insertion			*/
/*			| MatchPosPtr				| Position match					*/
/*			| InsPosPtr2				| 2eme position d'insertion			*/
/* Sortie:	| SeqPlusNodeVectPtr		| Vecteur de noeuds+				*/
/*			| BestStartCoordPtr			| F(A^) en ce vecteur				*/
/*			| BestEndCoordPtr			| L(A^) en ce vecteur				*/
/*			| SeqPlusNodeVect_Calc		| Meilleur score rencontre			*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TScore SeqPlusNodeVect_Calc(TSeqPlusNodeVectPtr SeqPlusNodeVectPtr,
TMolSeqPtr MolSeqPtr, TPosIndex PosIndex, TInsPosPtr InsPosPtr1, TMatchPosPtr
MatchPosPtr, TInsPosPtr InsPosPtr2, TCoordPtr BestStartCoordPtr, TCoordPtr
BestEndCoordPtr)
{
	/* Acces a la sequence */
	TMol *MolStr;					/* Chaine de molecules					*/
	TMolIndex MolNbr;				/* Nombre de molecules de la sequence	*/
	TMolIndex MolIndex;				/* Index de molecule					*/
	TMolIndex Index;				/* Index de molecule					*/

	/* Acces au vecteur de noeuds+ */
	TPlusNodePtr PlusNodeArray;		/* Tableau de noeuds+					*/
	
	/* Pointeurs sur les noeuds+ */
	TPlusNodePtr PlusNodePtr21;		/* Noeud+ (2,1)							*/
	TPlusNodePtr PlusNodePtr22;		/* Noeud+ (2,2)							*/
	
	/* Donnees de l'algorithme */
	TPlusNode OldPlusNode;			/* Noeud+ (i+1,j+1)						*/
	TPlusNode NewPlusNode;			/* Noeud+ (i,j)							*/
	TCoord PlusNodeCoord;			/* Coordonnee du noeud+ a calculer		*/
	TScore ScoreBPlus;				/* u(B+)								*/
	TScore MaxScore;				/* Score maximum						*/
	TCoord EndCoord;				/* Coord. d'arrivee						*/

	/* Initialisation des variables de deferenciation */
	
	/* Acces a la sequence */
	MolStr = MolSeq_MolStr(MolSeqPtr);
	MolNbr = MolSeq_MolNbr(MolSeqPtr);
	
	/* Acces au vecteur de noeuds */
	PlusNodeArray = SeqPlusNodeVect_Array(SeqPlusNodeVectPtr);
		
	/* Calcul du vecteur */
	
	/* Calcul du noeud (i,n) */

	Coord_PutPosIndex(&PlusNodeCoord, PosIndex);
	Coord_PutMolIndex(&PlusNodeCoord, MolNbr);
	
	PlusNodePtr21 = InsPosPtr2 ?
	&SeqPlusNodeArray_PlusNodeNth(PlusNodeArray, MolNbr) : NULL;
	
	MaxScore = PlusNode_Calc(&NewPlusNode, &PlusNodeCoord, FALSE, FALSE,
	InsPosPtr1, MatchPosPtr, InsPosPtr2, SD_MOL_NOT_DEF, NULL, PlusNodePtr21,
	NULL, BestEndCoordPtr);
	*BestStartCoordPtr = PlusNodeCoord;
	
	/* Mise a jour des noeuds */
	
	if (InsPosPtr2) OldPlusNode = *PlusNodePtr21;
	SeqPlusNodeArray_PutPlusNodeNth(PlusNodeArray, NewPlusNode, MolNbr);

	/* Calcul des autres noeuds */
	
	for (Index = 1; Index <= MolNbr; Index++) { /* MolNbr >= 0 */
		MolIndex = MolNbr - Index;
		
/*		printf("Molecule index:");*/
/*		Print_MolIndex(MolIndex);*/
/*		printf("\n");*/
/*		fflush(stdout);*/

		Coord_PutPosIndex(&PlusNodeCoord, PosIndex);
		Coord_PutMolIndex(&PlusNodeCoord, MolIndex);
		
		if (InsPosPtr2) {
			PlusNodePtr22 = &OldPlusNode;
			PlusNodePtr21 =
			&SeqPlusNodeArray_PlusNodeNth(PlusNodeArray, MolIndex);
		}
		else {
			PlusNodePtr22 = NULL;
			PlusNodePtr21 = NULL;
		}
		
		ScoreBPlus = PlusNode_Calc(&NewPlusNode, &PlusNodeCoord, Index == 1,
		Index == MolNbr, InsPosPtr1, MatchPosPtr, InsPosPtr2,
		MolStr_MolNth(MolStr, MolIndex + 1),
		&SeqPlusNodeArray_PlusNodeNth(PlusNodeArray, MolIndex + 1),
		PlusNodePtr21, PlusNodePtr22, &EndCoord);

		/* Essai de depasser le meilleur score precedent */
		if (ScoreBPlus > MaxScore) {
			/* Le nouveau score est meilleur */
			MaxScore = ScoreBPlus;
			*BestStartCoordPtr = PlusNodeCoord;
			*BestEndCoordPtr = EndCoord;
		}
		
		/* Mise a jour des noeuds */
		if (InsPosPtr2) OldPlusNode = *PlusNodePtr21;
		SeqPlusNodeArray_PutPlusNodeNth(PlusNodeArray, NewPlusNode, MolIndex);
	}
	return MaxScore;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de noeuds+										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqPlusNodeVectPtr		| Vecteur de noeuds+				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_SeqPlusNodeVect(TSeqPlusNodeVectPtr SeqPlusNodeVectPtr)
{
	TMolIndex PlusNodeIndex;
	
	for (PlusNodeIndex = 0; PlusNodeIndex <
	SeqPlusNodeVect_PlusNodeNbr(SeqPlusNodeVectPtr); PlusNodeIndex++) {
		Print_MolIndex(PlusNodeIndex);
		printf("Nth Node+:");
		Print_PlusNode(
		&SeqPlusNodeVect_PlusNodeNth(SeqPlusNodeVectPtr, PlusNodeIndex));
		printf("\n");
	}
}

/*======================================================*/
/* Manipulation des vecteurs de sous-noeuds				*/
/*======================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un vecteur de sous-noeuds									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubNodeNbr				| Nombre de sous-noeuds				*/
/* Sortie:	| I_SubNodeVect				| Vecteur de sous-noeuds			*/
/* Erreur:	| I_SubNodeVect=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSubNodeVectPtr I_SubNodeVect(TMolIndex SubNodeNbr)
{
	TSubNodeVectPtr SubNodeVectPtr;
	
	SubNodeVectPtr = (TSubNodeVectPtr)malloc(sizeof(TSubNodeVect));
	if (!SubNodeVectPtr) {
		/* Erreur allocation */
		return NULL;
	}
	SubNodeVectPtr->SubNodeArray = (TSubNodePtr)calloc(SubNodeNbr,
	sizeof(TSubNode));
	if (!(SubNodeVectPtr->SubNodeArray)) {
		/* Erreur allocation */
		free(SubNodeVectPtr);
		return NULL;
	}
	SubNodeVectPtr->SubNodeNbr = SubNodeNbr;
	return SubNodeVectPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de sous-noeuds									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubNodeVectPtr			| Vecteur de sous-noeuds			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SubNodeVect(TSubNodeVectPtr SubNodeVectPtr)
{
	free(SubNodeVectPtr->SubNodeArray);
	free(SubNodeVectPtr);
}

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul d'un vecteur de sous-noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqPlusNodeVectPtr		| Vecteur de noeuds+ // a la seq.	*/
/*			| PosIndex					| Index de position					*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| SubNodeVectPtr			| Vecteur de sous-noeuds			*/
/*			| SubNodeVect_Calc			| Vecteur de sous-noeuds			*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TSubNodeVectPtr SubNodeVect_Calc(TSeqPlusNodeVectPtr SeqPlusNodeVectPtr,
TSubNodeVectPtr SubNodeVectPtr, TPosIndex PosIndex, TInsPosPtr InsPosPtr)
{
	/* Acces au vecteur de sous-noeuds */
	TSubNodePtr SubNodeArray;
	TMolIndex SubNodeNbr;
	TMolIndex SubNodeIndex;
	TSubNodePtr SubNodePtr;
	
	/* Acces au vecteur de noeuds + */
	TPlusNodePtr PlusNodeArray;
	TCoord PlusNodeCoord;
	
	/* Initialisations */
	SubNodeArray = SubNodeVect_Array(SubNodeVectPtr);
	SubNodeNbr = SubNodeVect_SubNodeNbr(SubNodeVectPtr);
	PlusNodeArray = SeqPlusNodeVect_Array(SeqPlusNodeVectPtr);
	
	/* Calculs */
	for (SubNodeIndex = 0; SubNodeIndex <= SubNodeNbr - 1; SubNodeIndex++) {
		/* SubNodeNbr >= 1 */
		
		Coord_PutPosIndex(&PlusNodeCoord, PosIndex);
		Coord_PutMolIndex(&PlusNodeCoord, SubNodeIndex);
		
		SubNodePtr = SubNode_Calc(&SubNodeArray_SubNodeNth(SubNodeArray,
		SubNodeIndex), &SeqPlusNodeArray_PlusNodeNth(PlusNodeArray,
		SubNodeIndex), &PlusNodeCoord, InsPosPtr, SubNodeIndex ==
		SubNodeNbr - 1);
	}		
	return SubNodeVectPtr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de sous-noeuds									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubNodeVectPtr			| Vecteur de sous-noeuds			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_SubNodeVect(TSubNodeVectPtr SubNodeVectPtr)
{
	TMolIndex SubNodeIndex;
	
	for (SubNodeIndex = 0; SubNodeIndex <
	SubNodeVect_SubNodeNbr(SubNodeVectPtr); SubNodeIndex++) {
		Print_SubNode(&SubNodeVect_SubNodeNth(SubNodeVectPtr, SubNodeIndex));
	}
}

/*============================================*/
/* Manipulation des vecteurs de sous-noeuds + */
/*============================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un vecteur de sous-noeuds +								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubNodeNbr				| Nombre de sous-noeuds +			*/
/* Sortie:	| I_SubPlusNodeVect			| Vecteur de sous-noeuds +			*/
/* Erreur:	| I_SubPlusNodeVect=NULL	| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSubPlusNodeVectPtr I_SubPlusNodeVect(TMolIndex SubPlusNodeNbr)
{
	TSubPlusNodeVectPtr SubPlusNodeVectPtr;
	
	SubPlusNodeVectPtr = (TSubPlusNodeVectPtr)malloc(sizeof(TSubPlusNodeVect));
	if (!SubPlusNodeVectPtr) {
		/* Erreur allocation */
		return NULL;
	}
	SubPlusNodeVectPtr->SubPlusNodeArray = (TSubPlusNodePtr)
	calloc(SubPlusNodeNbr, sizeof(TSubPlusNode));
	if (!(SubPlusNodeVectPtr->SubPlusNodeArray)) {
		/* Erreur allocation */
		free(SubPlusNodeVectPtr);
		return NULL;
	}
	SubPlusNodeVectPtr->SubPlusNodeNbr = SubPlusNodeNbr;
	return SubPlusNodeVectPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de sous-noeuds +								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubPlusNodeVectPtr		| Vecteur de sous-noeuds +			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SubPlusNodeVect(TSubPlusNodeVectPtr SubPlusNodeVectPtr)
{
	free(SubPlusNodeVectPtr->SubPlusNodeArray);
	free(SubPlusNodeVectPtr);
}

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de sous-noeuds +									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubPlusNodeVectPtr		| Vecteur de sous-noeuds +			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_SubPlusNodeVect(TSubPlusNodeVectPtr SubPlusNodeVectPtr)
{
	TMolIndex SubPlusNodeIndex;
	
	for (SubPlusNodeIndex = 0; SubPlusNodeIndex <
	SubPlusNodeVect_SubPlusNodeNbr(SubPlusNodeVectPtr); SubPlusNodeIndex++) {
		Print_SubPlusNode(&SubPlusNodeVect_SubPlusNodeNth(SubPlusNodeVectPtr,
		SubPlusNodeIndex));
	}
}


/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul d'un vecteur de sous-noeuds+										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqNodeVectPtr			| Vecteur de noeuds // a la seq.	*/
/*			| PosIndex					| Index de position					*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| SubPlusNodeVectPtr		| Vecteur de sous-noeuds+			*/
/*			| SubPlusNodeVect_Calc		| Vecteur de sous-noeuds+			*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TSubPlusNodeVectPtr SubPlusNodeVect_Calc(TSeqNodeVectPtr SeqNodeVectPtr,
TSubPlusNodeVectPtr SubPlusNodeVectPtr, TPosIndex PosIndex, TInsPosPtr
InsPosPtr)
{
	/* Acces au vecteur de sous-noeuds */
	TSubPlusNodePtr SubPlusNodeArray;
	TMolIndex SubPlusNodeNbr;
	TMolIndex SubPlusNodeIndex;
	TSubPlusNodePtr SubPlusNodePtr;
	
	/* Acces au vecteur de noeuds + */
	TNodePtr NodeArray;
	TCoord NodeCoord;
	
	/* Initialisations */
	SubPlusNodeArray = SubPlusNodeVect_Array(SubPlusNodeVectPtr);
	SubPlusNodeNbr = SubPlusNodeVect_SubPlusNodeNbr(SubPlusNodeVectPtr);
	NodeArray = SeqNodeVect_Array(SeqNodeVectPtr);
	
	/* Calculs */
	for (SubPlusNodeIndex = 0; SubPlusNodeIndex <= SubPlusNodeNbr - 1;
	SubPlusNodeIndex++) {
		/* SubPlusNodeNbr >= 1 */
	
		Coord_PutPosIndex(&NodeCoord, PosIndex);
		Coord_PutMolIndex(&NodeCoord, SubPlusNodeIndex);
		
		SubPlusNodePtr = SubPlusNode_Calc(&SubPlusNodeArray_SubPlusNodeNth(
		SubPlusNodeArray, SubPlusNodeIndex), &SeqNodeArray_NodeNth(
		NodeArray, SubPlusNodeIndex), &NodeCoord, InsPosPtr, SubPlusNodeIndex
		== 0);
	}

	return SubPlusNodeVectPtr;
}

/*==========================*/
/* Routines des alignements */
/*==========================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un alignement												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| -							| -									*/
/* Sortie:	| I_Align					| Alignement						*/
/* Erreur:	| I_Align=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TAlignPtr I_Align()
{
	TAlignPtr AlignPtr;
	
	AlignPtr = (TAlignPtr)malloc(sizeof(TAlign));
	if (!AlignPtr) {
		/* Erreur allocation */
		return NULL;
	}
	return AlignPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'un alignement												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlignPtr					| Alignement						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Align(TAlignPtr AlignPtr)
{
	free(AlignPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un alignement												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlignPtr					| Alignement						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Align(TAlignPtr AlignPtr)
{
	printf("Start position: ");
	Print_Coord(&Align_StartCoord(AlignPtr));
	printf("\nEnd position: ");
	Print_Coord(&Align_EndCoord(AlignPtr));
	printf("\nIn position: ");
	Print_Coord(&Align_InCoord(AlignPtr));
	printf("\nOut position: ");
	Print_Coord(&Align_OutCoord(AlignPtr));
	printf("\nScore: ");
	Print_Score(Align_Score(AlignPtr));
	printf("\n");
}

/*===================================*/
/* Routines des listes d'alignements */
/*===================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Destruction d'une liste d'alignements									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlignListPtr				| Liste d'alignements				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_AlignList(TAlignListPtr AlignListPtr)
{
	TAlignIndex AlignIndex;
	
	for (AlignIndex = 0; AlignIndex < AlignList_AlignNbr(AlignListPtr);
	AlignIndex++) {
		Free_Align(AlignList_AlignNth(AlignListPtr, AlignIndex));
	}
	Free_List((TListPtr)AlignListPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une liste d'alignements										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlignListPtr				| Liste d'alignements				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_AlignList(TAlignListPtr AlignListPtr)
{
	TAlignIndex AlignIndex;
	
	for (AlignIndex = 0; AlignIndex < AlignList_AlignNbr(AlignListPtr);
	AlignIndex++) {
		Print_Align(AlignList_AlignNth(AlignListPtr, AlignIndex));
		printf("\n");
	}
}

/*===================================*/
/* Routines des donnees d'alignement */
/*===================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction des donnees d'alignement									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqDataPtr				| Donnees de sequence				*/
/*			| PrfDataPtr				| Donnees de profil					*/
/*			| MaxAlignNbr				| Nombre maximum d'alignements		*/
/* Sortie:	| I_PrfAlign				| Donnees d'alignement				*/
/* Erreur:	| I_PrfAlign=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TPrfAlignPtr I_PrfAlign(TSeqDataPtr SeqDataPtr, TPrfDataPtr PrfDataPtr,
TAlignIndex MaxAlignNbr)
{
	/* Attention, les alphabets de la sequence et du profil sont consideres	*/
	/* commet etant les memes												*/
	
	TPrfAlignPtr PrfAlignPtr;
	
	PrfAlignPtr = (TPrfAlignPtr)malloc(sizeof(TPrfAlign));
	if (!PrfAlignPtr) {
		/* Erreur allocation */
		return NULL;
	}
	
	PrfAlignPtr->AlignListPtr = I_AlignList(MaxAlignNbr);
	if (!PrfAlignPtr->AlignListPtr) {
		/* Erreur allocation */
		free(PrfAlignPtr);
		return NULL;
	}
	PrfAlignPtr->SeqDataPtr = SeqDataPtr;
	PrfAlignPtr->PrfDataPtr = PrfDataPtr;
	return PrfAlignPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction des donnees d'alignement sans la sequence ni le profil		*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfAlignPtr				| Donnees d'alignement				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PrfAlign(TPrfAlignPtr PrfAlignPtr)
{
	Free_AlignList(PrfAlignPtr->AlignListPtr);	
	free(PrfAlignPtr);
}

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Recherche du meilleur alignement											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfMatrixPtr				| Matrice de profil					*/
/*			| MolSeqPtr					| Sequence de molecules				*/
/* Sortie:	| PrfAlign_BestAlign		| A^								*/
/* Erreur:	| PrfAlign_BestAlign=NULL	| =>								*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PA_MEM_ERR				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TAlignPtr PrfAlign_BestAlign(TPrfMatrixPtr PrfMatrixPtr, TMolSeqPtr MolSeqPtr,
TErrIndex *ErrIndexPtr)
{
	/* Acces a la sequence */
	TMol *MolStr;					/* Chaine de molecule					*/
	TMolIndex MolNbr;				/* Nombre de molecules					*/
	TMolIndex MolIndex;				/* Index de molecule					*/

	/* Donnees de l'algorithme */
	TNodeVectPtr NodeVectPtr;		/* Vecteur de noeuds // au prf			*/
	TAlignPtr AlignPtr;				/* Meilleur alignement					*/
	TScore Score;					/* S(A)									*/
	TCoord StartCoord;				/* F(A)									*/
	TCoord EndCoord;				/* L(A)									*/
	
	/* Initialisation des variables de deferenciation */
	
	/* Acces a la sequence */
	MolStr = MolSeq_MolStr(MolSeqPtr);
	MolNbr = MolSeq_MolNbr(MolSeqPtr);
	
	/* algorithme */
	/*------------*/

	/* Construction du meilleur alignement */
	AlignPtr = I_Align();
	if (!AlignPtr) {
		/* Erreur d'allocation */
		*ErrIndexPtr = PA_MEM_ERR;
		return NULL;
	}
	
	/* Construction des vecteurs de noeuds // au profil */
	NodeVectPtr = I_NodeVect(PrfMatrix_PosNbr(PrfMatrixPtr) + 1);
	if (!NodeVectPtr) {
		/* Erreur d'allocation */
		*ErrIndexPtr = PA_MEM_ERR;
		return NULL;
	}

	/* Calcul du 1er vecteur */
	Score = NodeVect_Calc(NULL, FALSE, FALSE, SD_MOL_NOT_DEF, 0,
	PrfMatrixPtr, NodeVectPtr, &StartCoord, &EndCoord);
	Align_PutScore(AlignPtr, Score);
	Align_PutStartCoord(AlignPtr, StartCoord);
	Align_PutEndCoord(AlignPtr, EndCoord);
	Align_PutInCoord(AlignPtr, PA_COORD_NOT_DEF);
	Align_PutOutCoord(AlignPtr, PA_COORD_NOT_DEF);
	
	/* Parcours de la sequence de molecules */
	for (MolIndex = 1; MolIndex <= MolNbr; MolIndex++) {

		Score = NodeVect_Calc(NodeVectPtr, MolIndex == 1, MolIndex == MolNbr,
		MolStr_MolNth(MolStr, MolIndex), MolIndex, PrfMatrixPtr, NodeVectPtr,
		&StartCoord, &EndCoord);
		
		if (Score > Align_Score(AlignPtr)) {
			/* Nouveau A^ */
			Align_PutScore(AlignPtr, Score);
			Align_PutStartCoord(AlignPtr, StartCoord);
			Align_PutEndCoord(AlignPtr, EndCoord);
		}

	}
	
	/* Destruction des vecteurs */
	Free_NodeVect(NodeVectPtr);

	return AlignPtr;
}

/*--------------------------------------------------------------------------*/
/* Execution de l'algorithme d'alignement									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfAlignPtr				| Donnees d'alignement				*/
/*			| CutOff					| Valeur de coupure					*/
/*			| TestProt					| Test ou pas les align. non prot.	*/
/* Sortie:	| PrfAlign_Align			| Donnees d'alignement				*/
/* Erreur:	| PrfAlign_Align=NULL		| =>								*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PA_MEM_ERR				| Allocation memoire				*/
/*			| PA_ALI_NBR_OVF			| Trop d'alignements				*/
/*--------------------------------------------------------------------------*/
TPrfAlignPtr PrfAlign_Align(TPrfAlignPtr PrfAlignPtr, TScore CutOff,
TBoolean TestProt, TErrIndex *ErrIndexPtr)
{
	/* Acces a la sequence */
	TMolSeqPtr MolSeqPtr;			/* Sequence de molecules				*/
	TMolIndex MolNbr;				/* Nombre de molecules					*/
	TMol *MolStr;					/* Chaine de molecule					*/
	TMol Mol;						/* Molecule								*/
	TMolIndex MolIndex;				/* Index de molecule					*/
	
	/* Acces au profil */
	TPrfMatrixPtr PrfMatrixPtr;		/* Matrice de profil					*/
	TPosIndex StartMatchPos;		/* Index de la 1ere pos. match			*/
	TPosIndex EndMatchPos;			/* Index de la dern. pos. match			*/
	TInsPosPtr *InsPosList;			/* Liste des positions d'insertion		*/
	TMatchPosPtr *MatchPosList;		/* Liste des positions match			*/
	TInsPosPtr InsPosPtr1;			/* 1ere position d'insertion			*/
	TMatchPosPtr MatchPosPtr;		/* Position match						*/
	TInsPosPtr InsPosPtr2;			/* 2eme position d'insertion			*/
	TPosIndex PosNbr;				/* Nombre de positions (match)			*/
	TPosIndex PosIndex; 			/* Index de position 					*/
	TPosIndex RPosIndex;			/* Index de position inverse			*/

	/* Donnees de l'algorithme */
	TSeqNodeVectPtr SeqNodeVectPtr;			/* Vect. de noeuds // a la seq.	*/
	TSeqPlusNodeVectPtr SeqPlusNodeVectPtr; /* Vect. de n. + // a la seq.	*/
	TSubPlusNodeVectPtr SubPlusNodeVectPtr;	/* Vecteur de sous-noeuds+		*/
	TSubNodeVectPtr SubNodeVectPtr;			/* Vecteur de sous-noeuds		*/
	TSubPlusNodePtr SubPlusNodeArray;		/* Tableau de sous-noeuds+		*/
	TSubNodePtr SubNodeArray;				/* Tableau de sous-noeuds		*/
	TExtNodeVectPtr ExtNodeVectPtr1;		/* Vecteur de noeuds // au prf	*/
	TExtNodeVectPtr ExtNodeVectPtr2;		/* Vecteur de noeuds // au prf	*/
	TExtNodeVectPtr InExtNodeVectPtr;		/* Vecteur de noeuds // au prf	*/
	TExtNodeVectPtr OutExtNodeVectPtr;		/* Vecteur de noeuds // au prf	*/
	TExtNodeVectPtr TmpExtNodeVectPtr;		/* Vecteur de noeuds // au prf	*/
	TBooleanVectPtr ProtResVectPtr;			/* Vecteur de booleens			*/
	TBoolean *ProtResArray;					/* Tableau de boolens			*/
	TBooleanVectPtr TestColVectPtr;			/* Vecteur de booleens			*/
	TBoolean *TestColArray;					/* Tableau de boolens			*/
	TAlign Align1;							/* A							*/
	TAlign Align2;							/* A							*/
	TAlignPtr AlignPtr;						/* A							*/
	TAlignPtr NewAlignPtr;					/* A							*/
	TAlignPtr BackAlignPtr;					/* A stocke						*/
	TAlignPtr TmpAlignPtr;					/* A temporaire					*/
	TAlignPtr TestAlignPtr;					/* A teste						*/
	TAlign BestAlign;						/* A^							*/
	TScore Score;							/* S(A)							*/
	TCoord StartCoord;						/* F(A)							*/
	TCoord EndCoord;						/* L(A)							*/
	TCoord SubNodeCoord;					/* Lp(A) (1 pos. match)			*/
	TMolIndex FirstAdmMolIndex;				/* min j(V) avec f(V) > co		*/
	TMolIndex FirstVectMolIndex;			/* min j(f(V)) sur un vecteur	*/
	TMolIndex BackFirstVectMolIndex;		/* min j(f(V)) de retour		*/
	TAlignListPtr AlignListPtr;				/* Liste d'alignements			*/
	TSubPlusNodePtr SubPlusNodePtr11;		/* Sous-noeud+ (1,1)			*/
	TBoolean NotProt;						/* Existe ali. non. prot.		*/
	TBoolean Back;							/* Indicateur de retour			*/
	TBoolean NoAlign = TRUE;				/* Indic. si aucun ali. trouve	*/
	TMolIndex ScanMolNbr = 0;
	
	/* Initialisation des variables de deferenciation */
	
	/* Acces a la sequence */
	MolSeqPtr = SeqData_MolSeq(PrfAlign_SeqData(PrfAlignPtr));
	MolNbr = MolSeq_MolNbr(MolSeqPtr);
	MolStr = MolSeq_MolStr(MolSeqPtr);
	
	/* Acces au profil */
	PrfMatrixPtr = PrfData_PrfMatrix(PrfAlign_PrfData(PrfAlignPtr));
	StartMatchPos = DisjointParList_ParNth(Disjoint_ParList(
	PrfData_Disjoint(PrfAlign_PrfData(PrfAlignPtr))), 1);
	EndMatchPos = DisjointParList_ParNth(Disjoint_ParList(
	PrfData_Disjoint(PrfAlign_PrfData(PrfAlignPtr))), 2);
	InsPosList = PrfMatrix_InsPosList(PrfMatrixPtr);
	MatchPosList = PrfMatrix_MatchPosList(PrfMatrixPtr);
	PosNbr = PrfMatrix_PosNbr(PrfMatrixPtr);
	AlignListPtr = PrfAlign_AlignList(PrfAlignPtr);
	
	/* algorithme */
	/*------------*/

	/* Calcul du vecteur de sous-noeuds + */
	/*------------------------------------*/

	/* Allocation du vecteur des noeuds */
	SeqNodeVectPtr = I_SeqNodeVect(MolNbr + 1);
	if (!SeqNodeVectPtr) {
		/* Erreur d'allocation */
		*ErrIndexPtr = PA_MEM_ERR;
		return NULL;
	}

	for (PosIndex = 0; PosIndex <= StartMatchPos - 1; PosIndex++) {
		/* StartMatchPos >= 1 */
		
		/* Initialisation des positions */
		if (PosIndex != 0) {
			/* Ce n'est pas le premier vecteur de noeuds */
			InsPosPtr1 = InsPosList_PosNth(InsPosList, PosIndex - 1);
			MatchPosPtr = MatchPosList_PosNth(MatchPosList, PosIndex);
		}
		else {
			InsPosPtr1 = NULL;
			MatchPosPtr = NULL;
		}
		InsPosPtr2 = InsPosList_PosNth(InsPosList, PosIndex);
		
		/* Calcul du vecteur */
		Score =  SeqNodeVect_Calc(SeqNodeVectPtr, MolSeqPtr, PosIndex,
		InsPosPtr1, MatchPosPtr, InsPosPtr2, &StartCoord, &EndCoord);
		if ((TestProt) && (Score >= CutOff)) {
			/* Alignement acceptable non prot. */
			Free_SeqNodeVect(SeqNodeVectPtr);
			*ErrIndexPtr = PA_ALI_NOT_PROT;
			return NULL;
		}
		
		/* Affichage du vecteur de noeuds */
		/* Print_PosIndex(PosIndex); */
		/* printf("Nth Vector:\n\n"); */
		/* Print_SeqNodeVect(SeqNodeVectPtr); */
	}
	
	/* Construction du vecteur de sous-noeuds+ */
	SubPlusNodeVectPtr = I_SubPlusNodeVect(MolNbr + 1);
	if (!SubPlusNodeVectPtr) {
		/* Erreur d'allocation */
		Free_SeqNodeVect(SeqNodeVectPtr);
		*ErrIndexPtr = PA_MEM_ERR;
		return NULL;
	}
	
	/* Calcul du vecteur de sous-noeuds+ */
	SubPlusNodeVectPtr = SubPlusNodeVect_Calc(SeqNodeVectPtr,
	SubPlusNodeVectPtr, StartMatchPos - 1, InsPosPtr2);

	/* Destruction du vecteur de noeuds */
	Free_SeqNodeVect(SeqNodeVectPtr);

	/* Affichage du vecteur de sous-noeuds+ */
	/*Print_SubPlusNodeVect(SubPlusNodeVectPtr);*/
	/*printf("\n");*/
	
	/* Calcul du vecteur de sous-noeuds */
	/*----------------------------------*/
	
	/* Allocation du vecteur des noeuds+ */
	SeqPlusNodeVectPtr = I_SeqPlusNodeVect(MolNbr + 1);
	if (!SeqPlusNodeVectPtr) {
		/* Erreur d'allocation */
		Free_SubPlusNodeVect(SubPlusNodeVectPtr);
		*ErrIndexPtr = PA_MEM_ERR;
		return NULL;
	}
	
	for (RPosIndex = EndMatchPos; RPosIndex <= PosNbr; RPosIndex++) {
		PosIndex = PosNbr - RPosIndex +	EndMatchPos;
		
		/* Initialisation des positions */
		if (PosIndex != PosNbr) {
			/* Ce n'est pas le dernier vecteur de noeuds+ */
			InsPosPtr2 = InsPosList_PosNth(InsPosList, PosIndex + 1);
			MatchPosPtr = MatchPosList_PosNth(MatchPosList, PosIndex + 1);
		}
		else {
			InsPosPtr2 = NULL;
			MatchPosPtr = NULL;
		}
		InsPosPtr1 = InsPosList_PosNth(InsPosList, PosIndex);
		
		/* Calcul du vecteur */
		Score =  SeqPlusNodeVect_Calc(SeqPlusNodeVectPtr, MolSeqPtr,
		PosIndex, InsPosPtr1, MatchPosPtr, InsPosPtr2, &StartCoord,
		&EndCoord);
		if ((TestProt) && (Score >= CutOff)) {
			/* Alignement acceptable non prot. */
			Free_SubPlusNodeVect(SubPlusNodeVectPtr);
			Free_SeqPlusNodeVect(SeqPlusNodeVectPtr);
			*ErrIndexPtr = PA_ALI_NOT_PROT;
			return NULL;
		}
	}
	
	/* Construction du vecteur de sous-noeuds */
	SubNodeVectPtr = I_SubNodeVect(MolNbr + 1);
	if (!SubNodeVectPtr) {
		/* Erreur d'allocation */
		Free_SubPlusNodeVect(SubPlusNodeVectPtr);
		Free_SeqPlusNodeVect(SeqPlusNodeVectPtr);
		*ErrIndexPtr = PA_MEM_ERR;
		return NULL;
	}

	/* Affichage du vecteur de noeuds+ */
	/*Print_SeqPlusNodeVect(SeqPlusNodeVectPtr);*/
	/*printf("\n");*/
	
	/* Calcul du vecteur de sous-noeuds */
	SubNodeVectPtr = SubNodeVect_Calc(SeqPlusNodeVectPtr, SubNodeVectPtr,
	EndMatchPos, InsPosPtr1);

	/* Destruction du vecteur de noeuds */
	Free_SeqPlusNodeVect(SeqPlusNodeVectPtr);
	
	/* Affichage du vecteur de sous-noeuds */
	/*Print_SubNodeVect(SubNodeVectPtr);*/
	/*printf("\n");*/

	/* Parcours le long de la sequence dans la zone protegee */ 
	/*-------------------------------------------------------*/
	
	if (EndMatchPos > StartMatchPos) {
		/* Il y a plus d'une position M protegee */
		/* Construction des vecteurs de noeuds // au profil */
		ExtNodeVectPtr1 = I_ExtNodeVect(EndMatchPos - StartMatchPos);
		if (!ExtNodeVectPtr1) {
			/* Erreur d'allocation */
			Free_SubPlusNodeVect(SubPlusNodeVectPtr);
			Free_SubNodeVect(SubNodeVectPtr);
			*ErrIndexPtr = PA_MEM_ERR;
			return NULL;
		}
		ExtNodeVectPtr2 = I_ExtNodeVect(EndMatchPos - StartMatchPos);
		if (!ExtNodeVectPtr2) {
			/* Erreur d'allocation */
			Free_SubPlusNodeVect(SubPlusNodeVectPtr);
			Free_SubNodeVect(SubNodeVectPtr);
			Free_ExtNodeVect(ExtNodeVectPtr1);
			*ErrIndexPtr = PA_MEM_ERR;
			return NULL;
		}
	}
	else {
		ExtNodeVectPtr1 = NULL;
		ExtNodeVectPtr2 = NULL;
	}

	/* Construction du vecteur de booleens */
	ProtResVectPtr = I_BooleanVect(MolSeq_MolNbr(MolSeqPtr));
	if (!ProtResVectPtr) {
		/* Erreur d'allocation */
		Free_SubPlusNodeVect(SubPlusNodeVectPtr);
		Free_SubNodeVect(SubNodeVectPtr);
		if (ExtNodeVectPtr1) Free_ExtNodeVect(ExtNodeVectPtr1);
		if (ExtNodeVectPtr2) Free_ExtNodeVect(ExtNodeVectPtr2);
		*ErrIndexPtr = PA_MEM_ERR;
		return NULL;
	}

	/* Construction du vecteur de booleens */
	TestColVectPtr = I_BooleanVect(MolSeq_MolNbr(MolSeqPtr) + 1);
	if (!TestColVectPtr) {
		/* Erreur d'allocation */
		Free_SubPlusNodeVect(SubPlusNodeVectPtr);
		Free_SubNodeVect(SubNodeVectPtr);
		if (ExtNodeVectPtr1) Free_ExtNodeVect(ExtNodeVectPtr1);
		if (ExtNodeVectPtr2) Free_ExtNodeVect(ExtNodeVectPtr2);
		Free_BooleanVect(ProtResVectPtr);
		*ErrIndexPtr = PA_MEM_ERR;
		return NULL;
	}
	
	/* Acces aux vecteurs */
	SubNodeArray = SubNodeVect_Array(SubNodeVectPtr);
	SubPlusNodeArray = SubPlusNodeVect_Array(SubPlusNodeVectPtr);
	ProtResArray = BooleanVect_Array(ProtResVectPtr);
	TestColArray = BooleanVect_Array(TestColVectPtr);
		
	/* Molecule */
	Mol = SD_MOL_NOT_DEF;

	/* Sous-noeuds extremes */
	SubPlusNodePtr11 = NULL;
	
	/* Vecteurs d'entre-sortie */
	OutExtNodeVectPtr = ExtNodeVectPtr1;
	InExtNodeVectPtr = NULL;
	
	/* Alignements */
	AlignPtr = &Align1;
	BackAlignPtr = &Align2;

	/* Reset de F(A).j et A^ */
	Align_Reset(&BestAlign);
	FirstAdmMolIndex = SD_MOL_IDX_NOT_DEF;

	/* Temoin de retour */
	Back = FALSE;
	
	/* Parcours de la sequence de molecules */
	for (MolIndex = 0; TRUE;) {
		
		/* Calcul de A, j_first */			
		if (Back) {
			Back = FALSE;
			/* On est revenu en arriere */
			/* Recuperation de l'alignement stocke */
			TestAlignPtr = BackAlignPtr;
			FirstVectMolIndex = BackFirstVectMolIndex;
			OutExtNodeVectPtr = ExtNodeVectPtr1;
			InExtNodeVectPtr = ExtNodeVectPtr2;
		}
		else if (OutExtNodeVectPtr) {
			ScanMolNbr++;
			/* Plus de 1 pos. match protegee */
			Score = ExtNodeVect_Calc(InExtNodeVectPtr, MolIndex == 0,
			MolIndex == 1, MolIndex == MolNbr, SubPlusNodePtr11,
			&SubPlusNodeArray_SubPlusNodeNth(SubPlusNodeArray, MolIndex),
			&SubNodeArray_SubNodeNth(SubNodeArray, MolIndex), Mol, MolIndex,
			PrfMatrixPtr, StartMatchPos, OutExtNodeVectPtr, AlignPtr,
			&FirstVectMolIndex);
			TestAlignPtr = AlignPtr;
			OutExtNodeVectPtr = ExtNodeVectPtr1;
			InExtNodeVectPtr = ExtNodeVectPtr1;
		}
		else {
			/* 1 position match protegee */
			Coord_PutMolIndex(&SubNodeCoord, MolIndex);
			Coord_PutPosIndex(&SubNodeCoord, StartMatchPos);
			Score = SubNode_ExtAlign(&SubNodeArray_SubNodeNth(SubNodeArray,
			MolIndex), &SubNodeCoord, SubPlusNodePtr11,
			&SubPlusNodeArray_SubPlusNodeNth(SubPlusNodeArray, MolIndex), Mol,
			MatchPosList_PosNth(MatchPosList, StartMatchPos), AlignPtr,
			&FirstVectMolIndex);
			TestAlignPtr = AlignPtr;
		}

		if ((TestProt) && (!BooleanArray_BooleanNth0(TestColArray, MolIndex))
		&& (Score >= CutOff)) {
			/* Test des alignements non proteges */
			NotProt = Align_NotProt(CutOff,
			&SubPlusNodeArray_SubPlusNodeNth(SubPlusNodeArray, MolIndex),
			&SubNodeArray_SubNodeNth(SubNodeArray, MolIndex), MolIndex == 0,
			MolIndex == MolNbr, PrfMatrixPtr, StartMatchPos, EndMatchPos);
			BooleanArray_PutBooleanNth0(TestColArray,  TRUE, MolIndex);
			if (NotProt) {
				Free_SubPlusNodeVect(SubPlusNodeVectPtr);
				Free_SubNodeVect(SubNodeVectPtr);
				if (ExtNodeVectPtr1) Free_ExtNodeVect(ExtNodeVectPtr1);
				if (ExtNodeVectPtr2) Free_ExtNodeVect(ExtNodeVectPtr2);
				Free_BooleanVect(ProtResVectPtr);
				Free_BooleanVect(TestColVectPtr);
				*ErrIndexPtr = PA_ALI_NOT_PROT;
				return NULL;
			}
		}
		
/*		if ((Score >= CutOff) && (Score > Align_Score(&BestAlign))) {*/
		if (Score > Align_Score(&BestAlign)) {
			/* Nouveau A^ */
			Align_Copy(TestAlignPtr, &BestAlign);
			/*printf("\nNouveau A^:\n");*/
			/*Print_Align(&BestAlign);*/
			/*printf("\n");*/
		}

		if ((Align_Score(&BestAlign) >= CutOff) &&
		((MolIndex == MolNbr) ||
		(BooleanArray_BooleanNth(ProtResArray, MolIndex + 1)) ||
		(Coord_MolIndex(&Align_OutCoord(&BestAlign)) <= FirstVectMolIndex))) {

			/* S(A^) >= cut-off */
			/* fin de seq., mol. marquee ou Lp(A^).j <= f^(A).j */
			/* Acceptation de A^ */
			if (AlignList_Full(AlignListPtr)) {
				/* Liste d'alignements pleine */
				Free_SubPlusNodeVect(SubPlusNodeVectPtr);
				Free_SubNodeVect(SubNodeVectPtr);
				if (ExtNodeVectPtr1) Free_ExtNodeVect(ExtNodeVectPtr1);
				if (ExtNodeVectPtr2) Free_ExtNodeVect(ExtNodeVectPtr2);
				Free_BooleanVect(ProtResVectPtr);
				Free_BooleanVect(TestColVectPtr);
				*ErrIndexPtr = PA_ALI_NBR_OVF;
				return NULL;
			}
			
			/* Contruction de l'alignement */
			NewAlignPtr = I_Align();
			if (!NewAlignPtr) {
				/* Erreur allocation */
				Free_SubPlusNodeVect(SubPlusNodeVectPtr);
				Free_SubNodeVect(SubNodeVectPtr);
				if (ExtNodeVectPtr1) Free_ExtNodeVect(ExtNodeVectPtr1);
				if (ExtNodeVectPtr2) Free_ExtNodeVect(ExtNodeVectPtr2);
				Free_BooleanVect(ProtResVectPtr);
				Free_BooleanVect(TestColVectPtr);
				*ErrIndexPtr = PA_MEM_ERR;
				return NULL;
			}
			
			/* Ajout de l'alignement dans la liste */
			/*Print_Align(&BestAlign);*/
			Align_Copy(&BestAlign, NewAlignPtr);
			AlignList_AddAlign(AlignListPtr, NewAlignPtr);
			NoAlign = FALSE;

			/* Marquer la zone */
			for (MolIndex = Coord_MolIndex(&Align_InCoord(&BestAlign)) + 1;
			MolIndex <= Coord_MolIndex(&Align_OutCoord(&BestAlign));
			MolIndex++) {
				BooleanArray_PutBooleanNth(ProtResArray, TRUE, MolIndex);
			}
			
			/* Retour en arriere */
			if (FirstAdmMolIndex >
			Coord_MolIndex(&Align_InCoord(&BestAlign))) {
				/* L'index de retour est dans la zone marquee */
				/* ou non initialise */
				MolIndex = Coord_MolIndex(&Align_OutCoord(&BestAlign));
				OutExtNodeVectPtr = ExtNodeVectPtr1;
				InExtNodeVectPtr = NULL;
				Mol = SD_MOL_NOT_DEF;
				SubPlusNodePtr11 = NULL;
				FirstAdmMolIndex = SD_MOL_IDX_NOT_DEF;
			}
			else {
				/* L'index est avant la zone marquee */
				MolIndex = FirstAdmMolIndex;
				/* MolIndex >= 1 */
				Mol = MolStr_MolNth(MolStr, MolIndex);
				SubPlusNodePtr11 = &SubPlusNodeArray_SubPlusNodeNth(
				SubPlusNodeArray, MolIndex - 1);
				Back = TRUE;
			}

			/* Reset de A^ */
			Align_Reset(&BestAlign);			
		}
		else {

			/* Pas d'acceptation de A^ */
			if (MolIndex == MolNbr) {
				/* fin de parcours */
				break;
			}

			if ((FirstAdmMolIndex == SD_MOL_IDX_NOT_DEF) &&
			(Score >= CutOff)) {
				/* Initialistion de F(A).j */
				FirstAdmMolIndex = MolIndex;
				TmpExtNodeVectPtr = ExtNodeVectPtr1;
				ExtNodeVectPtr1 = ExtNodeVectPtr2;
				ExtNodeVectPtr2 = TmpExtNodeVectPtr;
				OutExtNodeVectPtr = ExtNodeVectPtr1;
				InExtNodeVectPtr = ExtNodeVectPtr2;
				TmpAlignPtr = AlignPtr;
				AlignPtr = BackAlignPtr;
				BackAlignPtr = TmpAlignPtr;
				BackFirstVectMolIndex = FirstVectMolIndex;
			}

			/* On continue le parcours de la sequence */
			if (BooleanArray_BooleanNth(ProtResArray, MolIndex + 1)) {
				/* Saut d'une zone protegee */
				MolIndex++;
				while ((MolIndex < MolSeq_MolNbr(MolSeqPtr)) &&
				(BooleanArray_BooleanNth(ProtResArray, MolIndex + 1))) {
					MolIndex++;
				}
				OutExtNodeVectPtr = ExtNodeVectPtr1;
				InExtNodeVectPtr = NULL;
				Mol = SD_MOL_NOT_DEF;
				SubPlusNodePtr11 = NULL;
				FirstAdmMolIndex = SD_MOL_IDX_NOT_DEF;
			}
			else {
				MolIndex++;
				Mol = MolStr_MolNth(MolStr, MolIndex);
				SubPlusNodePtr11 = &SubPlusNodeArray_SubPlusNodeNth(
				SubPlusNodeArray, MolIndex - 1);
			}
		}
	}
	
	/* Destruction des vecteurs */
	Free_SubPlusNodeVect(SubPlusNodeVectPtr);
	Free_SubNodeVect(SubNodeVectPtr);
	if (ExtNodeVectPtr1) Free_ExtNodeVect(ExtNodeVectPtr1);
	if (ExtNodeVectPtr2) Free_ExtNodeVect(ExtNodeVectPtr2);
	Free_BooleanVect(ProtResVectPtr);
	Free_BooleanVect(TestColVectPtr);

	/*printf("Number of scanned molecules:");*/
	/*Print_MolIndex(ScanMolNbr); printf("\n");*/
	return PrfAlignPtr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression des donnees d'alignement										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfAlignPtr				| Donnees d'alignement				*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_PrfAlign(TPrfAlignPtr PrfAlignPtr)
{
	printf("Sequence data:\n\n");
	Print_SeqData(PrfAlign_SeqData(PrfAlignPtr));
	printf("\nProfile data:\n\n");
	Print_PrfData(PrfAlign_PrfData(PrfAlignPtr));
	printf("\nAlignments:\n\n");
	Print_AlignList(PrfAlign_AlignList(PrfAlignPtr));
	printf("\n");
}

/*--------------------------------------------------------------------------*/
/* Existence d'un alignement non protege acceptable							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOff					| Valeur de coupure					*/
/*			| SubPlusNodePtr			| Sous-noeud+						*/
/*			| SubNodePtr				| Sous-noeud						*/
/*			| FirstColumn				| Ind. 1er colonne ou pas			*/
/*			| LastColumn				| Ind. dern. colonne ou pas			*/
/*			| PrfMatrixPtr				| Matrice de profil					*/
/*			| StartMatchPosIndex		| Index 1ere pos. match prot.		*/
/*			| EndMatchPosIndex			| Index dern. pos. d'insert. prot.	*/
/* Sortie:	| Align_NotProt				| Indication						*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TBoolean Align_NotProt(TScore CutOff, TSubPlusNodePtr SubPlusNodePtr,
TSubNodePtr SubNodePtr, TBoolean FirstColumn, TBoolean LastColumn,
TPrfMatrixPtr PrfMatrixPtr, TPosIndex StartMatchPosIndex, TPosIndex
EndMatchPosIndex)
{
	TScore B;						/* b									*/
	TScore E;						/* e									*/
	TScore D;						/* d									*/
	TScore BD, BE, DD, DE;			/* t_(X->X)								*/
	TScore ScoreD;					/* p(B+,D)								*/
	TScore RScoreD;					/* u(D)									*/
	TScore ScoreDPlus;				/* p(B+,D+)								*/
	TScore Score;					/* Score								*/
	TInsPosPtr *InsPosList;			/* Liste des positions d'insertion		*/
	TMatchPosPtr *MatchPosList;		/* Liste des positions match			*/
	TInsPosPtr InsPosPtr;			/* Position d'insertion					*/
	TPosIndex PosIndex;				/* Index de position					*/

	/* Acces a la matrice de profil */
	MatchPosList = PrfMatrix_MatchPosList(PrfMatrixPtr);
	InsPosList = PrfMatrix_InsPosList(PrfMatrixPtr);

	for (PosIndex = StartMatchPosIndex; PosIndex <= EndMatchPosIndex;
	PosIndex++) {

		/* Calcul de p(B+,D) */
		if ((D = MatchPos_D(MatchPosList_PosNth(MatchPosList, PosIndex)))
		!= PD_INFINITE) {
			/* Calcul de p(B+,D+) */
			if (PosIndex == StartMatchPosIndex) {
				/* Premier noeud */
				ScoreDPlus = SubPlusNode_DPlus(SubPlusNodePtr);
			}
			else {
				InsPosPtr = InsPosList_PosNth(InsPosList, PosIndex - 1);
				/* Par B */
				if (((B = (FirstColumn) ? InsPos_B0(InsPosPtr) :
				InsPos_B1(InsPosPtr)) != PD_INFINITE) &&
				((BD = InsPos_BD(InsPosPtr)) != PD_INFINITE)) {
					ScoreDPlus = B + BD;
				}
				else ScoreDPlus = PD_INFINITE;	
				/* Par D */
				if ((ScoreD != PD_INFINITE) && ((DD = InsPos_DD(InsPosPtr))
				!= PD_INFINITE) && ((Score = ScoreD + DD) > ScoreDPlus)) {
					ScoreDPlus = Score;
				}
			}
			/* Calcul de p(B+,D) */
			if (ScoreDPlus != PD_INFINITE) {
				ScoreD = ScoreDPlus + D;
			}
		}
		else ScoreD = PD_INFINITE;
		
		/* Calcul de p(B+,E) */
		InsPosPtr = InsPosList_PosNth(InsPosList, PosIndex);
		if ((PosIndex == EndMatchPosIndex) && (ScoreD != PD_INFINITE) &&
		((RScoreD = SubNode_D(SubNodePtr)) != PD_INFINITE) &&
		(ScoreD + RScoreD >= CutOff)) {
			/* Alignement prolonge si dernier noeud */
			return TRUE;
		}
		else if ((E = (LastColumn) ? InsPos_E0(InsPosPtr) :
		InsPos_E1(InsPosPtr)) != PD_INFINITE) {
			/* Par B */			
			if (((B = (FirstColumn) ? InsPos_B0(InsPosPtr) :
			InsPos_B1(InsPosPtr)) != PD_INFINITE) && ((BE =
			InsPos_BE(InsPosPtr))  != PD_INFINITE) && (B + BE + E >= CutOff)) {
				return TRUE;
			}
			/* Par D */
			if ((ScoreD != PD_INFINITE) && ((DE = InsPos_DE(InsPosPtr))
			!= PD_INFINITE) && (ScoreD + DE + E >= CutOff)) {
				return TRUE;
			}
		}		
	}
	return FALSE;
}

/*==========================================*/
/* Routine des noeuds avec trace du chemin	*/
/*==========================================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Calcul du noeud de fin dans un alignement global	 						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| InsPosPtr					| Position d'insertion				*/
/*			| LastPathNode				| Indique si dernier noeud			*/
/* Sortie:	| PathNodePtr				| Noeud								*/
/*			| PathNode_GEndCalc			| Noeud								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TPathNodePtr PathNode_GEndCalc(TPathNodePtr PathNodePtr,
TInsPosPtr InsPosPtr, TBoolean LastPathNode)
{
	TScore E;			/* e		*/
	TScore ME, IE, DE;	/* t_(X->E)	*/
	
	PathNode_Reset(PathNodePtr);

	if ((E = (LastPathNode) ? InsPos_E0(InsPosPtr) : InsPos_E1(InsPosPtr))
	!= PD_INFINITE) {		
		if ((ME = InsPos_ME(InsPosPtr))!= PD_INFINITE) {
			PathNode_PutM(PathNodePtr, ME + E);
			PathNode_PutMNext(PathNodePtr, PA_E);
		}
		if ((IE = InsPos_IE(InsPosPtr)) != PD_INFINITE) {
			PathNode_PutI(PathNodePtr, IE + E);
			PathNode_PutINext(PathNodePtr, PA_E);
		}
		if ((DE = InsPos_DE(InsPosPtr)) != PD_INFINITE) {
			PathNode_PutD(PathNodePtr, DE + E);
			PathNode_PutDNext(PathNodePtr, PA_E);
		}
	}
	return PathNodePtr;
}

/*--------------------------------------------------------------------------*/
/* Calcul d'un noeud dans un alignement global		 						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PathNodePtr22				| Noeud (2,2)						*/
/*			| PathNodePtr21				| Noeud (2,1)						*/
/*			| PathNodePtr12				| Noeud (1,2)						*/
/*			| Mol						| Molecule							*/
/*			| MatchPosPtr				| Position match					*/
/*			| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| PathNodePtr				| Noeud (1,1)						*/
/*			| PathNode_GCalc			| Noeud (1,1)						*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TPathNodePtr PathNode_GCalc(TPathNodePtr PathNodePtr, TPathNodePtr
PathNodePtr22, TPathNodePtr PathNodePtr21, TPathNodePtr PathNodePtr12, TMol
Mol, TMatchPosPtr MatchPosPtr, TInsPosPtr InsPosPtr)
{
	TScore ScoreMPlus;	/* s_g(M+)			*/
	TScore ScoreIPlus;	/* s_g(I+)			*/
	TScore ScoreDPlus;	/* s_g(D+)			*/
	TScore ScoreM;		/* s_g(M)			*/
	TScore ScoreI;		/* s_g(I)			*/
	TScore ScoreD;		/* s_g(D)			*/
	TScore M;			/* m				*/
	TScore I;			/* i				*/
	TScore D;			/* d				*/
	TScore	MM, MI, MD,	/* t_(X->X)			*/
			IM, II, ID,
			DM, DI, DD;
	TScore Score;		/* Score temporaire	*/

	/* Calcul de s_g(M+) */
	if ((PathNodePtr22) && ((ScoreM = PathNode_M(PathNodePtr22))
	!= PD_INFINITE) && ((M = ScoreVect_ScoreNth(MatchPos_M(MatchPosPtr), Mol))
	!= PD_INFINITE)) {
		ScoreMPlus = ScoreM + M;
	}
	else ScoreMPlus = PD_INFINITE;

	/* Calcul de s_g(I+) */
	if ((PathNodePtr12) && ((ScoreI = PathNode_I(PathNodePtr12))
	!= PD_INFINITE) && ((I = ScoreVect_ScoreNth(InsPos_I(InsPosPtr), Mol))
	!= PD_INFINITE)) {
		ScoreIPlus = ScoreI + I;
	}
	else ScoreIPlus = PD_INFINITE;
	
	/* Calcul de s_g(D+) */
	if ((PathNodePtr21) && ((ScoreD = PathNode_D(PathNodePtr21))
	!= PD_INFINITE) && ((D = MatchPos_D(MatchPosPtr)) != PD_INFINITE)) {
		ScoreDPlus = ScoreD + D;
	}
	else ScoreDPlus = PD_INFINITE;
	
	/* Calcul de s_g(M), s_g(I), s_g(D) */

	PathNode_Reset(PathNodePtr);

	/* Par D+ */
	if (ScoreDPlus != PD_INFINITE) {
		if ((MD = InsPos_MD(InsPosPtr)) != PD_INFINITE) {
			PathNode_PutM(PathNodePtr, MD +ScoreDPlus);
			PathNode_PutMNext(PathNodePtr, PA_D_PLUS);
		}
		if ((ID = InsPos_ID(InsPosPtr)) != PD_INFINITE) {
			PathNode_PutI(PathNodePtr, ID + ScoreDPlus);
			PathNode_PutINext(PathNodePtr, PA_D_PLUS);
		}
		if ((DD = InsPos_DD(InsPosPtr)) != PD_INFINITE) {
			PathNode_PutD(PathNodePtr, DD + ScoreDPlus);
			PathNode_PutDNext(PathNodePtr, PA_D_PLUS);
		}
	}
	
	/* Par M+ */
	if (ScoreMPlus != PD_INFINITE) {
		if (((MM = InsPos_MM(InsPosPtr)) != PD_INFINITE) &&
		((Score = MM + ScoreMPlus) > PathNode_M(PathNodePtr))) {
			PathNode_PutM(PathNodePtr, Score);
			PathNode_PutMNext(PathNodePtr, PA_M_PLUS);
		}
		if (((IM = InsPos_IM(InsPosPtr)) != PD_INFINITE) &&
		((Score = IM + ScoreMPlus) > PathNode_I(PathNodePtr))) {
			PathNode_PutI(PathNodePtr, Score);
			PathNode_PutINext(PathNodePtr, PA_M_PLUS);
		}
		if (((DM = InsPos_DM(InsPosPtr)) != PD_INFINITE) &&
		((Score = DM + ScoreMPlus) > PathNode_D(PathNodePtr))) {
			PathNode_PutD(PathNodePtr, Score);
			PathNode_PutDNext(PathNodePtr, PA_M_PLUS);
		}
	}
	
	/* Par I+ */
	if (ScoreIPlus != PD_INFINITE) {
		if (((MI = InsPos_MI(InsPosPtr)) != PD_INFINITE) &&
		((Score = MI + ScoreIPlus) > PathNode_M(PathNodePtr))) {
			PathNode_PutM(PathNodePtr, Score);
			PathNode_PutMNext(PathNodePtr, PA_I_PLUS);
		}
		if (((II = InsPos_II(InsPosPtr)) != PD_INFINITE) &&
		((Score = II + ScoreIPlus) > PathNode_I(PathNodePtr))) {
			PathNode_PutI(PathNodePtr, Score);
			PathNode_PutINext(PathNodePtr, PA_I_PLUS);
		}
		if (((DI = InsPos_DI(InsPosPtr)) != PD_INFINITE) &&
		((Score = DI + ScoreIPlus) > PathNode_D(PathNodePtr))) {
			PathNode_PutD(PathNodePtr, Score);
			PathNode_PutDNext(PathNodePtr, PA_I_PLUS);
		}
	}
	
	return PathNodePtr;
}

/*--------------------------------------------------------------------------*/
/* Calcul du score d'un alignement global sur le noeud de depart			*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PathNodePtr22				| Noeud (2,2)						*/
/*			| PathNodePtr21				| Noeud (2,1)						*/
/*			| PathNodePtr12				| Noeud (1,2)						*/
/*			| Mol						| Molecule							*/
/*			| MatchPosPtr				| Position match					*/
/*			| InsPosPtr					| Position d'insertion				*/
/*			| FirstColumn				| Ind. si 1ere col.					*/
/*			| LastColumn				| Ind. si deniere col.				*/
/* Sortie:	| PathNode_GStartScore		| Score de l'align. global			*/
/*			| BNextPtr					| sommet suivant B					*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore PathNode_GStartScore(TPathNodePtr PathNodePtr22, TPathNodePtr
PathNodePtr21, TPathNodePtr PathNodePtr12, TMol Mol, TMatchPosPtr MatchPosPtr,
TInsPosPtr InsPosPtr, TBoolean FirstColumn, TBoolean LastColumn,
TVertex *BNextPtr)
{
	TScore ScoreMPlus;		/* s_g(M+)			*/
	TScore ScoreIPlus;		/* s_g(I+)			*/
	TScore ScoreDPlus;		/* s_g(D+)			*/
	TScore ScoreBPlus;		/* s_g(B+)			*/
	TScore ScoreM;			/* s_g(M)			*/
	TScore ScoreI;			/* s_g(I)			*/
	TScore ScoreD;			/* s_g(D)			*/
	TScore ScoreB;			/* s_g(B)			*/
	TScore E;				/* e				*/
	TScore M;				/* m				*/
	TScore I;				/* i				*/
	TScore D;				/* d				*/
	TScore B;				/* b				*/
	TScore	BM, BI, BD, BE;	/* t_(B->X)			*/
	TScore Score;			/* Score temporaire	*/

	/* Initialisation des valeurs */
	ScoreBPlus = PD_INFINITE;
	ScoreB = PD_INFINITE;
	*BNextPtr = PA_VTX_NOT_DEF;

	if (((B = (FirstColumn) ? InsPos_B0(InsPosPtr) : InsPos_B1(InsPosPtr)) ==
	PD_INFINITE)) {
		/* b = -infini */
		return ScoreBPlus;
	}
	
	if (!PathNodePtr22 && !PathNodePtr21 && !PathNodePtr12) {
		/* Noeud isole */
		if (((E = (LastColumn) ? InsPos_E0(InsPosPtr) : InsPos_E1(InsPosPtr))
		!= PD_INFINITE) && ((BE = InsPos_BE(InsPosPtr)) != PD_INFINITE)) {
			ScoreBPlus = B + BE + E;
			*BNextPtr = PA_E;
		}
		return ScoreBPlus;
	}
	
	/* Calcul de s_g(M+) */
	if ((PathNodePtr22) && ((ScoreM = PathNode_M(PathNodePtr22))
	!= PD_INFINITE) && ((M = ScoreVect_ScoreNth(MatchPos_M(MatchPosPtr), Mol))
	!= PD_INFINITE)) {
		ScoreMPlus = M + ScoreM;
	}
	else ScoreMPlus = PD_INFINITE;

	/* Calcul de s_g(I+) */
	if ((PathNodePtr12) && ((ScoreI = PathNode_I(PathNodePtr12))
	!= PD_INFINITE) && ((I = ScoreVect_ScoreNth(InsPos_I(InsPosPtr), Mol))
	!= PD_INFINITE)) {
		ScoreIPlus = I + ScoreI;
	}
	else ScoreIPlus = PD_INFINITE;
	
	/* Calcul de s_g(D+) */
	if ((PathNodePtr21) && ((ScoreD = PathNode_D(PathNodePtr21))
	!= PD_INFINITE) && ((D = MatchPos_D(MatchPosPtr)) != PD_INFINITE)) {
		ScoreDPlus = D + ScoreD;
	}
	else ScoreDPlus = PD_INFINITE;

	/* Calcul de s_g(B) */
	/* Par D+ */
	if ((ScoreDPlus != PD_INFINITE) && ((BD = InsPos_BD(InsPosPtr))
	!= PD_INFINITE)) {
		ScoreB = BD + ScoreDPlus;
		*BNextPtr = PA_D;
	}
	/* Par M+ */
	if ((ScoreMPlus != PD_INFINITE) && ((BM = InsPos_BM(InsPosPtr))
	!= PD_INFINITE) && ((Score = BM + ScoreMPlus) > ScoreB)) {
		ScoreB = Score;
		*BNextPtr = PA_M;
	}	
	/* Par I+ */
	if ((ScoreIPlus != PD_INFINITE) && ((BI = InsPos_BI(InsPosPtr))
	!= PD_INFINITE) && ((Score = BI + ScoreIPlus) > ScoreB)) {
		ScoreB = Score;
		*BNextPtr = PA_I;
	}
	
	/* Calcul de s_g(B+) */
	if (ScoreB != PD_INFINITE) ScoreBPlus = B + ScoreB;	
	return ScoreBPlus;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un noeud+ avec trace du chemin								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PathNodePtr				| Noeud+							*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_PathNode(TPathNodePtr PathNodePtr)
{
	printf("(");
	Print_Score(PathNode_M(PathNodePtr));
	printf(",");
	Print_Score(PathNode_I(PathNodePtr));
	printf(",");
	Print_Score(PathNode_D(PathNodePtr));
	printf(")\n");
	printf("[");
	Print_Vertex(PathNode_MNext(PathNodePtr));
	printf(",");
	Print_Vertex(PathNode_INext(PathNodePtr));
	printf(",");
	Print_Vertex(PathNode_DNext(PathNodePtr));
	printf("]\n");
}

/*==================================*/
/* Routines des matrices de chemin	*/
/*==================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une matrice de chemin										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| RowNbr					| Nombre de lignes					*/
/*			| ColumnNbr					| Nombre de colonnes				*/
/*			| StartCoordPtr				| Coord. de depart					*/
/* Sortie:	| I_PathMatrix				| Matrice de chemin					*/
/* Erreur:	| I_PathMatrix=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TPathMatrixPtr I_PathMatrix(TMolIndex RowNbr, TPosIndex ColumnNbr, TCoordPtr
StartCoordPtr)
{
	TPathMatrixPtr PathMatrixPtr;
	
	PathMatrixPtr = (TPathMatrixPtr)malloc(sizeof(TPathMatrix));
	if (!PathMatrixPtr) {
		/* Erreur d'allocation */
		return NULL;
	}
	PathMatrixPtr->Matrix = (TPathNodePtr)calloc(ColumnNbr*RowNbr,
	sizeof(TPathNode));
	if (!(PathMatrixPtr->Matrix)) {
		/* Erreur d'allocation */
		free(PathMatrixPtr);
		return NULL;
	}
	PathMatrixPtr->RowNbr = RowNbr;
	PathMatrixPtr->ColumnNbr = ColumnNbr;
	PathMatrixPtr->StartCoord = *StartCoordPtr;
	PathMatrixPtr->ScoreBPlus = PD_INFINITE;
	PathMatrixPtr->BNext = PA_VTX_NOT_DEF;
	return PathMatrixPtr;
}	

/*--------------------------------------------------------------------------*/
/* Destruction d'une matrice de chemin										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PathMatrixPtr				| Matrice de chemin					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PathMatrix(TPathMatrixPtr PathMatrixPtr)
{
	free(PathMatrixPtr->Matrix);
	free(PathMatrixPtr);
}

/*--------------*/
/* Contructeurs */
/*--------------*/

/*--------------------------------------------------------------------------*/
/* Calcul d'une matrice de meilleur chemin									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PathMatrixPtr				| Matrice de chemin					*/
/*			| AlignPtr					| Alignement						*/
/*			| PrfMatrixPtr				| Matrice de profil					*/
/*			| MolSeqPtr					| Sequence de molecules				*/
/* Sortie:	| PathMatrix_BestCalc		| s_g(B+)							*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TScore PathMatrix_BestCalc(TPathMatrixPtr PathMatrixPtr, TAlignPtr AlignPtr,
TPrfMatrixPtr PrfMatrixPtr, TMolSeqPtr MolSeqPtr)
{
	TPosIndex PosIndex;				/* Index de pos. ds la mat. de prf.		*/
	TPosIndex RPosIndex;			/* Index de pos. inverse				*/
	TMolIndex MolIndex;				/* Index de mol. ds la mat. de prf.		*/
	TMolIndex RMolIndex;			/* Index de mol. inverse				*/
	TInsPosPtr *InsPosList;			/* Liste de positions d'insertion		*/
	TMatchPosPtr *MatchPosList;		/* Liste de positions match				*/
	TInsPosPtr InsPosPtr;			/* Position d'insertion					*/
	TMatchPosPtr MatchPosPtr;		/* Position match						*/
	TMol *MolStr;					/* Chaine de molecules					*/
	TMol Mol;						/* Molecule								*/
	TPathNodePtr PathNodePtr;		/* Noeud avec trace						*/
	TPathNodePtr PathNodePtr22;		/* Noeud (2,2)							*/
	TPathNodePtr PathNodePtr12;		/* Noeud (2,1)							*/
	TPathNodePtr PathNodePtr21;		/* Noeud (1,2)							*/
	TMolIndex ColumnNbr;			/* Nombre de colonnes					*/
	TPosIndex RowNbr;				/* Nombre de lignes						*/
	TCoordPtr StartCoordPtr;		/* Coordonnees de depart				*/
	TScore ScoreBPlus;				/* s_g(B+)								*/
	TVertex BNext;					/* Sommet suivant B						*/
	TPosIndex i_start;				/* Coord. de depart						*/
	TMolIndex j_start;				/*										*/
	TPosIndex i_end;				/* Coord. de fin						*/
	TMolIndex j_end;				/*										*/
	
	/* Acces a la matrice de profil */
	InsPosList = PrfMatrix_InsPosList(PrfMatrixPtr);
	MatchPosList = PrfMatrix_MatchPosList(PrfMatrixPtr);
	
	/* Acces a la sequence */
	MolStr = MolSeq_MolStr(MolSeqPtr);
	
	/* Acces a la matrice de chemin */
	ColumnNbr = PathMatrix_ColumnNbr(PathMatrixPtr);
	RowNbr = PathMatrix_RowNbr(PathMatrixPtr);
	StartCoordPtr = PathMatrix_StartCoord(PathMatrixPtr);
	
	/* Acces a l'alignement */
	i_start = Coord_PosIndex(&Align_StartCoord(AlignPtr));
	j_start = Coord_MolIndex(&Align_StartCoord(AlignPtr));
	i_end = Coord_PosIndex(&Align_EndCoord(AlignPtr));
	j_end = Coord_MolIndex(&Align_EndCoord(AlignPtr));
		
	/* Calcul des noeuds (i,j) i: i_end -> i_start, j: j_end -> j_start */
	/*------------------------------------------------------------------*/
	
	InsPosPtr = InsPosList_PosNth(InsPosList, i_end);
	
	/* Calcul du noeud (i_end,j_end) */
	
	PathNodePtr = PathNode_GEndCalc(PathMatrix_PathNode(PathMatrixPtr,
	i_end - i_start, j_end - j_start), InsPosPtr,
	j_end == MolSeq_MolNbr(MolSeqPtr));
	
	/* Calcul des noeuds (i_end,j) j: j_end - 1 -> j_start */
	
	for (RMolIndex = j_start; RMolIndex < j_end; RMolIndex++) {
		MolIndex = j_start + j_end - 1 - RMolIndex;

		PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
		i_end - i_start, MolIndex - j_start), NULL, NULL, PathNodePtr,
		MolStr_MolNth(MolStr, MolIndex + 1), NULL, InsPosPtr);
	}
	
	/* Calcul des noeuds (i,j) i: i_end - 1 -> i_start, j: j_end -> j_start */
	for (RPosIndex = i_start; RPosIndex < i_end; RPosIndex++) {
		PosIndex = i_start + i_end - 1 - RPosIndex; 
		InsPosPtr = InsPosList_PosNth(InsPosList, PosIndex);
		MatchPosPtr = MatchPosList_PosNth(MatchPosList, PosIndex + 1);
		
		/* Calcul du noeud (i,j_end) */
		
		PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
		PosIndex - i_start, j_end - j_start), NULL,
		PathMatrix_PathNode(PathMatrixPtr, PosIndex + 1 - i_start,
		j_end - j_start), NULL, SD_MOL_NOT_DEF, MatchPosPtr, InsPosPtr);
		
		/* Calcul des noeuds (i,j) j: j_end - 1 -> j_start */
		for (RMolIndex = j_start; RMolIndex < j_end; RMolIndex++) {
			MolIndex = j_start + j_end - 1 - RMolIndex;
					
			PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
			PosIndex - i_start, MolIndex - j_start ),
			PathMatrix_PathNode(PathMatrixPtr,
			PosIndex + 1 - i_start, MolIndex + 1 - j_start),
			PathMatrix_PathNode(PathMatrixPtr,
			PosIndex + 1 - i_start, MolIndex - j_start), PathNodePtr,
			MolStr_MolNth(MolStr, MolIndex + 1), MatchPosPtr, InsPosPtr);
		}
	}
	
	/* Calcul de s_g(B+) et du sommet suivant de B */
	
	if ((RowNbr > 1) && (ColumnNbr > 1)) {
		PathNodePtr22 = PathMatrix_PathNode(PathMatrixPtr, 1, 1);
		PathNodePtr21 = PathMatrix_PathNode(PathMatrixPtr, 1, 0);
		PathNodePtr12 = PathMatrix_PathNode(PathMatrixPtr, 0, 1);
		Mol = MolStr_MolNth(MolStr, Coord_MolIndex(StartCoordPtr) + 1);
		MatchPosPtr = MatchPosList_PosNth(MatchPosList,
		Coord_PosIndex(StartCoordPtr) + 1);
	}
	else if (RowNbr > 1) /* 1 colonne */ {
		PathNodePtr22 = NULL;
		PathNodePtr21 = PathMatrix_PathNode(PathMatrixPtr, 1, 0);
		PathNodePtr12 = NULL;
		Mol = SD_MOL_NOT_DEF;
		MatchPosPtr = MatchPosList_PosNth(MatchPosList,
		Coord_PosIndex(StartCoordPtr) + 1);
	}
	else if (ColumnNbr > 1) /* 1 ligne */ {
		PathNodePtr22 = NULL;
		PathNodePtr21 = NULL;
		PathNodePtr12 = PathMatrix_PathNode(PathMatrixPtr, 0, 1);
		Mol = MolStr_MolNth(MolStr, Coord_MolIndex(StartCoordPtr) + 1);
		MatchPosPtr = NULL;
	}
	else {
		PathNodePtr22 = NULL;
		PathNodePtr21 = NULL;
		PathNodePtr12 = NULL;
		Mol = SD_MOL_NOT_DEF;
		MatchPosPtr = NULL;
	}

	ScoreBPlus = PathNode_GStartScore(PathNodePtr22, PathNodePtr21,
	PathNodePtr12, Mol, MatchPosPtr, InsPosList_PosNth(InsPosList,
	Coord_PosIndex(StartCoordPtr)), Coord_MolIndex(StartCoordPtr) == 0,
	Coord_MolIndex(StartCoordPtr) == MolSeq_MolNbr(MolSeqPtr), &BNext);
	
	PathMatrix_PutScoreBPlus(PathMatrixPtr, ScoreBPlus);
	PathMatrix_PutBNext(PathMatrixPtr, BNext);
	
	return ScoreBPlus;
}

/*--------------------------------------------------------------------------*/
/* Calcul d'une matrice de chemin											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PathMatrixPtr				| Matrice de chemin					*/
/*			| AlignPtr					| Alignement						*/
/*			| PrfMatrixPtr				| Matrice de profil					*/
/*			| MolSeqPtr					| Sequence de molecules				*/
/* Sortie:	| PathMatrix_Calc			| s_g(B+)							*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TScore PathMatrix_Calc(TPathMatrixPtr PathMatrixPtr, TAlignPtr AlignPtr,
TPrfMatrixPtr PrfMatrixPtr, TMolSeqPtr MolSeqPtr)
{
	TPosIndex PosIndex;				/* Index de pos. ds la mat. de prf.		*/
	TPosIndex RPosIndex;			/* Index de pos. inverse				*/
	TMolIndex MolIndex;				/* Index de mol. ds la mat. de prf.		*/
	TMolIndex RMolIndex;			/* Index de mol. inverse				*/
	TInsPosPtr *InsPosList;			/* Liste de positions d'insertion		*/
	TMatchPosPtr *MatchPosList;		/* Liste de positions match				*/
	TInsPosPtr InsPosPtr;			/* Position d'insertion					*/
	TMatchPosPtr MatchPosPtr;		/* Position match						*/
	TMol *MolStr;					/* Chaine de molecules					*/
	TMol Mol;						/* Molecule								*/
	TPathNodePtr PathNodePtr;		/* Noeud avec trace						*/
	TPathNodePtr PathNodePtr22;		/* Noeud (2,2)							*/
	TPathNodePtr PathNodePtr12;		/* Noeud (2,1)							*/
	TPathNodePtr PathNodePtr21;		/* Noeud (1,2)							*/
	TMolIndex ColumnNbr;			/* Nombre de colonnes					*/
	TPosIndex RowNbr;				/* Nombre de lignes						*/
	TCoordPtr StartCoordPtr;		/* Coordonnees de depart				*/
	TScore ScoreBPlus;				/* s_g(B+)								*/
	TVertex BNext;					/* Sommet suivant B						*/
	TPosIndex i_start;				/* Coord. de depart						*/
	TMolIndex j_start;				/*										*/
	TPosIndex i_end;				/* Coord. de fin						*/
	TMolIndex j_end;				/*										*/
	TPosIndex i_in;					/* Coord. d'entree						*/
	TMolIndex j_in;					/*										*/
	TPosIndex i_out;				/* Coord. de sortie						*/
	TMolIndex j_out;				/*										*/

	
	
	/* Acces a la matrice de profil */
	InsPosList = PrfMatrix_InsPosList(PrfMatrixPtr);
	MatchPosList = PrfMatrix_MatchPosList(PrfMatrixPtr);
	
	/* Acces a la sequence */
	MolStr = MolSeq_MolStr(MolSeqPtr);
	
	/* Acces a la matrice de chemin */
	ColumnNbr = PathMatrix_ColumnNbr(PathMatrixPtr);
	RowNbr = PathMatrix_RowNbr(PathMatrixPtr);
	StartCoordPtr = PathMatrix_StartCoord(PathMatrixPtr);
	
	/* Acces a l'alignement */
	i_start = Coord_PosIndex(&Align_StartCoord(AlignPtr));
	j_start = Coord_MolIndex(&Align_StartCoord(AlignPtr));
	i_end = Coord_PosIndex(&Align_EndCoord(AlignPtr));
	j_end = Coord_MolIndex(&Align_EndCoord(AlignPtr));
	i_in = Coord_PosIndex(&Align_InCoord(AlignPtr));
	j_in = Coord_MolIndex(&Align_InCoord(AlignPtr));
	i_out = Coord_PosIndex(&Align_OutCoord(AlignPtr));
	j_out = Coord_MolIndex(&Align_OutCoord(AlignPtr));
		
	/* Calcul des noeuds (i,j) i: i_end -> i_out, j: j_end -> j_out */
	/*--------------------------------------------------------------*/
	
	InsPosPtr = InsPosList_PosNth(InsPosList, i_end);
	
	/* Calcul du noeud (i_end,j_end) */
	
	PathNodePtr = PathNode_GEndCalc(PathMatrix_PathNode(PathMatrixPtr,
	i_end - i_start, j_end - j_start), InsPosPtr,
	j_end == MolSeq_MolNbr(MolSeqPtr));
	
	/* Calcul des noeuds (i_end,j) j: j_end - 1 -> j_out */
	
	for (RMolIndex = j_out; RMolIndex < j_end; RMolIndex++) {
		MolIndex = j_out + j_end - 1 - RMolIndex;

		PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
		i_end - i_start, MolIndex - j_start), NULL, NULL, PathNodePtr,
		MolStr_MolNth(MolStr, MolIndex + 1), NULL, InsPosPtr);
	}
	
	/* Calcul des noeuds (i,j) i: i_end - 1 -> i_out, j: j_end -> j_out */
	for (RPosIndex = i_out; RPosIndex < i_end; RPosIndex++) {
		PosIndex = i_out + i_end - 1 - RPosIndex; 
		InsPosPtr = InsPosList_PosNth(InsPosList, PosIndex);
		MatchPosPtr = MatchPosList_PosNth(MatchPosList, PosIndex + 1);
		
		/* Calcul du noeud (i,j_end) */
		
		PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
		PosIndex - i_start, j_end - j_start), NULL,
		PathMatrix_PathNode(PathMatrixPtr, PosIndex + 1 - i_start,
		j_end - j_start), NULL, SD_MOL_NOT_DEF, MatchPosPtr, InsPosPtr);
		
		/* Calcul des noeuds (i,j) j: j_end - 1 -> j_out */
		for (RMolIndex = j_out; RMolIndex < j_end; RMolIndex++) {
			MolIndex = j_out + j_end - 1 - RMolIndex;
					
			PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
			PosIndex - i_start, MolIndex - j_start ),
			PathMatrix_PathNode(PathMatrixPtr,
			PosIndex + 1 - i_start, MolIndex + 1 - j_start),
			PathMatrix_PathNode(PathMatrixPtr,
			PosIndex + 1 - i_start, MolIndex - j_start), PathNodePtr,
			MolStr_MolNth(MolStr, MolIndex + 1), MatchPosPtr, InsPosPtr);
		}
	}
	
	/* Calcul des noeuds (i,j) i: i_out -> i_in, j: j_out -> j_in */
	/*------------------------------------------------------------*/
	
	/* Noeud (i_out, j_out) deja calcule */
	
	InsPosPtr = InsPosList_PosNth(InsPosList, i_out);
		
	/* Calcul des noeuds (i_out,j) j: j_out - 1 -> j_in */
	for (RMolIndex = j_in; RMolIndex <  j_out; RMolIndex++) {
		MolIndex = j_in + j_out - 1 - RMolIndex;
		
		PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
		i_out - i_start, MolIndex - j_start), NULL, NULL, PathNodePtr,
		MolStr_MolNth(MolStr, MolIndex + 1), NULL, InsPosPtr);
	}
	
	/* Calcul des noeuds (i,j) i: i_out - 1 -> i_in, j: j_out -> j_in */
	for (RPosIndex = i_in; RPosIndex < i_out; RPosIndex++) {
		PosIndex = i_in + i_out - 1 - RPosIndex; 
		InsPosPtr = InsPosList_PosNth(InsPosList, PosIndex);
		MatchPosPtr = MatchPosList_PosNth(MatchPosList, PosIndex + 1);
		
		/* Calcul du noeud (i,j_out) */
		
		PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
		PosIndex - i_start, j_out - j_start), NULL,
		PathMatrix_PathNode(PathMatrixPtr, PosIndex + 1 - i_start,
		j_out - j_start), NULL, SD_MOL_NOT_DEF, MatchPosPtr, InsPosPtr);

		/* Calcul des noeuds (i,j) j: j_out - 1 -> j_in */
		for (RMolIndex = j_in; RMolIndex < j_out; RMolIndex++) {
			MolIndex = j_in + j_out - 1 - RMolIndex;
					
			PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
			PosIndex - i_start, MolIndex - j_start ),
			PathMatrix_PathNode(PathMatrixPtr,
			PosIndex + 1 - i_start, MolIndex + 1 - j_start),
			PathMatrix_PathNode(PathMatrixPtr,
			PosIndex + 1 - i_start, MolIndex - j_start), PathNodePtr,
			MolStr_MolNth(MolStr, MolIndex + 1), MatchPosPtr, InsPosPtr);
		}
	}

	/* Calcul des noeuds (i,j) i: i_in -> i_start, j: j_in -> j_start */
	/*----------------------------------------------------------------*/
	
	/* Noeud (i_in, j_in) deja calcule */
	
	InsPosPtr = InsPosList_PosNth(InsPosList, i_in);
		
	/* Calcul des noeuds (i_in,j) j: j_in - 1 -> j_start */
	for (RMolIndex = j_start; RMolIndex <  j_in; RMolIndex++) {
		MolIndex = j_start + j_in - 1 - RMolIndex;
		
		PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
		i_in - i_start, MolIndex - j_start), NULL, NULL, PathNodePtr,
		MolStr_MolNth(MolStr, MolIndex + 1), NULL, InsPosPtr);
	}
	
	/* Calcul des noeuds (i,j) i: i_in - 1 -> i_start, j: j_in -> 0 */
	for (RPosIndex = i_start; RPosIndex < i_in; RPosIndex++) {
		PosIndex = i_start + i_in - 1 - RPosIndex; 
		InsPosPtr = InsPosList_PosNth(InsPosList, PosIndex);
		MatchPosPtr = MatchPosList_PosNth(MatchPosList, PosIndex + 1);
		
		/* Calcul du noeud (i,j_in) */
		
		PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
		PosIndex - i_start, j_in - j_start), NULL,
		PathMatrix_PathNode(PathMatrixPtr, PosIndex + 1 - i_start,
		j_in - j_start), NULL, SD_MOL_NOT_DEF, MatchPosPtr, InsPosPtr);

		/* Calcul des noeuds (i,j) j: j_in - 1 -> j_start */
		for (RMolIndex = j_start; RMolIndex < j_in; RMolIndex++) {
			MolIndex = j_start + j_in - 1 - RMolIndex;
					
			/*if ((PosIndex == 0) && (MolIndex == 0)) {*/
				/*exit(0);*/
			/*}*/
			PathNodePtr = PathNode_GCalc(PathMatrix_PathNode(PathMatrixPtr,
			PosIndex - i_start, MolIndex - j_start ),
			PathMatrix_PathNode(PathMatrixPtr,
			PosIndex + 1 - i_start, MolIndex + 1 - j_start),
			PathMatrix_PathNode(PathMatrixPtr,
			PosIndex + 1 - i_start, MolIndex - j_start), PathNodePtr,
			MolStr_MolNth(MolStr, MolIndex + 1), MatchPosPtr, InsPosPtr);
		}
	}
	
	/* Calcul de s_g(B+) et du sommet suivant de B */
	
	if ((RowNbr > 1) && (ColumnNbr > 1)) {
		PathNodePtr22 = PathMatrix_PathNode(PathMatrixPtr, 1, 1);
		PathNodePtr21 = PathMatrix_PathNode(PathMatrixPtr, 1, 0);
		PathNodePtr12 = PathMatrix_PathNode(PathMatrixPtr, 0, 1);
		Mol = MolStr_MolNth(MolStr, Coord_MolIndex(StartCoordPtr) + 1);
		MatchPosPtr = MatchPosList_PosNth(MatchPosList,
		Coord_PosIndex(StartCoordPtr) + 1);
	}
	else if (RowNbr > 1) /* 1 colonne */ {
		PathNodePtr22 = NULL;
		PathNodePtr21 = PathMatrix_PathNode(PathMatrixPtr, 1, 0);
		PathNodePtr12 = NULL;
		Mol = SD_MOL_NOT_DEF;
		MatchPosPtr = MatchPosList_PosNth(MatchPosList,
		Coord_PosIndex(StartCoordPtr) + 1);
	}
	else if (ColumnNbr > 1) /* 1 ligne */ {
		PathNodePtr22 = NULL;
		PathNodePtr21 = NULL;
		PathNodePtr12 = PathMatrix_PathNode(PathMatrixPtr, 0, 1);
		Mol = MolStr_MolNth(MolStr, Coord_MolIndex(StartCoordPtr) + 1);
		MatchPosPtr = NULL;
	}
	else {
		PathNodePtr22 = NULL;
		PathNodePtr21 = NULL;
		PathNodePtr12 = NULL;
		Mol = SD_MOL_NOT_DEF;
		MatchPosPtr = NULL;
	}

	ScoreBPlus = PathNode_GStartScore(PathNodePtr22, PathNodePtr21,
	PathNodePtr12, Mol, MatchPosPtr, InsPosList_PosNth(InsPosList,
	Coord_PosIndex(StartCoordPtr)), Coord_MolIndex(StartCoordPtr) == 0,
	Coord_MolIndex(StartCoordPtr) == MolSeq_MolNbr(MolSeqPtr), &BNext);
	
	PathMatrix_PutScoreBPlus(PathMatrixPtr, ScoreBPlus);
	PathMatrix_PutBNext(PathMatrixPtr, BNext);
	
	return ScoreBPlus;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une matrice de chemin										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PathMatrixPtr				| Matrice de chemin					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_PathMatrix(TPathMatrixPtr PathMatrixPtr)
{
	TPosIndex PosIndex;
	TMolIndex MolIndex;
	
	printf("Score = ");
	Print_Score(PathMatrix_ScoreBPlus(PathMatrixPtr));
	printf("\n");
	printf("Vertex following B = ");
	Print_Vertex(PathMatrix_BNext(PathMatrixPtr));
	printf("\n\n");
	
	for (PosIndex = 0; PosIndex < PathMatrix_RowNbr(PathMatrixPtr);
	PosIndex++) {
		printf("Row Nth");
		Print_PosIndex(PosIndex);
		printf("\n");
		
		for (MolIndex = 0; MolIndex < PathMatrix_ColumnNbr(PathMatrixPtr);
		MolIndex++) {
			printf("Column Nth"); Print_MolIndex(MolIndex); printf("\n\n");
			Print_PathNode(PathMatrix_PathNode(PathMatrixPtr, PosIndex,
			MolIndex));
			printf("\n");
		}
		printf("\n");
	}
}

/*==========================================*/
/* Manipulation des vecteurs de coordonnees	*/
/*==========================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un vecteur de coordonnees									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CoordMaxNbr				| Nombre max. de coord.				*/
/* Sortie:	| I_PathMatrix				| Matrice de chemin					*/
/* Erreur:	| I_PathMatrix=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TCoordVectPtr I_CoordVect(TCoordIndex CoordMaxNbr)
{
	TCoordVectPtr CoordVectPtr;
	
	CoordVectPtr = (TCoordVectPtr)malloc(sizeof(TCoordVect));
	if (!CoordVectPtr) {
		/* Erreur allocation */
		return NULL;
	}
	
	CoordVectPtr->Array = (TCoordPtr)calloc(CoordMaxNbr, sizeof(TCoord));
	if (!(CoordVectPtr->Array)) {
		/* Erreur allocation */
		free(CoordVectPtr);
		return NULL;
	}
	CoordVectPtr->CoordMaxNbr = CoordMaxNbr;
	CoordVectPtr->CoordNbr = 0;
	CoordVectPtr->ScoreBPlus = PD_INFINITE;
	return CoordVectPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de coordonnees									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CoordVectPtr				| Vecteur de coord.					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_CoordVect(TCoordVectPtr CoordVectPtr)
{
	free(CoordVectPtr->Array);
	free(CoordVectPtr);
}

/*--------------*/
/* Contructeurs */
/*--------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un vect. de coord. a partir d'une matrice de chemin		*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CoordVectPtr				| Vecteur de coord.					*/
/*			| PathMatrixPtr				| Matrice de chemin					*/
/* Sortie:	| CoordVectPtr				| Vecteur de coord.					*/
/*			| CoordVect_FromPathMatrix	| Vecteur de coord.					*/
/* Erreur:	| CoordVect_FromPathMatrix	| =NULL => ErrIndex=				*/
/*			| PA_COORD_NBR_OVF			| Trop de coord. ds le vect.		*/
/*--------------------------------------------------------------------------*/
TCoordVectPtr CoordVect_FromPathMatrix(TCoordVectPtr CoordVectPtr,
TPathMatrixPtr PathMatrixPtr, TErrIndex *ErrIndexPtr)
{
	TCoord Coord;				/* Coordonnees courantes	*/
	TVertex Next;				/* Prochain sommet			*/
	TCoordPtr StartCoordPtr;	/* Coordonnees de depart	*/

	/* Acces a la matrice de chemin */	
	StartCoordPtr = PathMatrix_StartCoord(PathMatrixPtr);
	
	/* Copie de s_g(B+) */
	CoordVect_PutScoreBPlus(CoordVectPtr,
	PathMatrix_ScoreBPlus(PathMatrixPtr));

	/* Initialisation de la coordonnee et du prochain sommet */	
	Next = PathMatrix_BNext(PathMatrixPtr);
	Coord = *StartCoordPtr;
	
	/* Ajout de la 1ere coordonnee */
	if (CoordVect_Full(CoordVectPtr)) {
		/* Vecteur de coord. plein */
		*ErrIndexPtr = PA_COORD_NBR_OVF;
		return NULL;
	}
	CoordVect_AddCoord(CoordVectPtr, &Coord);
	
	/* Deplacement ds la matrice */
	while (Next != PA_E) {
		/* Deplacement */
		switch (Next) {
			case PA_M:
				Coord_PutMolIndex(&Coord, Coord_MolIndex(&Coord) + 1);
				Coord_PutPosIndex(&Coord, Coord_PosIndex(&Coord) + 1);
				Next = PathNode_MNext(PathMatrix_PathNode(PathMatrixPtr,
				Coord_PosIndex(&Coord) - Coord_PosIndex(StartCoordPtr),
				Coord_MolIndex(&Coord) - Coord_MolIndex(StartCoordPtr)));
				break;
			case PA_I:
				Coord_PutMolIndex(&Coord, Coord_MolIndex(&Coord) + 1);
				Next = PathNode_INext(PathMatrix_PathNode(PathMatrixPtr,
				Coord_PosIndex(&Coord) - Coord_PosIndex(StartCoordPtr),
				Coord_MolIndex(&Coord) - Coord_MolIndex(StartCoordPtr)));
				break;
			case PA_D:
				Coord_PutPosIndex(&Coord, Coord_PosIndex(&Coord) + 1);
				Next = PathNode_DNext(PathMatrix_PathNode(PathMatrixPtr,
				Coord_PosIndex(&Coord) - Coord_PosIndex(StartCoordPtr),
				Coord_MolIndex(&Coord) - Coord_MolIndex(StartCoordPtr)));
		}
		
		/* Ajout de la coordonnee */
		if (CoordVect_Full(CoordVectPtr)) {
			/* Vecteur de coord. plein */
			*ErrIndexPtr = PA_COORD_NBR_OVF;
			return NULL;
		}
		CoordVect_AddCoord(CoordVectPtr, &Coord);
	}
	return CoordVectPtr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Sortie d'un vecteur de coordonnees										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| OutPutFile				| Fichier de sortie					*/
/*			| CoordVectPtr				| Vecteur de coord.					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Out_CoordVect(FILE *OutPutFile, TCoordVectPtr CoordVectPtr)
{
	TCoordIndex CoordIndex;
		
	for (CoordIndex = 0; CoordIndex < CoordVect_CoordNbr(CoordVectPtr);
	CoordIndex++) {
		fprintf(OutPutFile, "  ");
		Out_Coord(OutPutFile, CoordVect_CoordNth(CoordVectPtr, CoordIndex));
		fprintf(OutPutFile, "\n");
	}
}

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de coordonnees									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CoordVectPtr				| Vecteur de coord.					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_CoordVect(TCoordVectPtr CoordVectPtr)
{
	TCoordIndex CoordIndex;
	
	printf("Score = ");
	Print_Score(CoordVect_ScoreBPlus(CoordVectPtr));
	printf("\n\n");
	
	for (CoordIndex = 0; CoordIndex <= CoordVect_CoordNbr(CoordVectPtr) - 1;
	CoordIndex++) {
	
		Print_Coord(CoordVect_CoordNth(CoordVectPtr, CoordIndex));
		printf("\n");
	}
}

/*======================================================================*/
/* Manipulation des chaines d'alignements								*/
/*======================================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une chaine d'alignement									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AliCharMaxNbr				| Nombre max. de caracteres			*/
/* Sortie:	| I_AliStr					| Chaine d'alignement				*/
/* Erreur:	| I_AliStr=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TAliStrPtr I_AliStr(TAliCharIndex AliCharMaxNbr)
{
	TAliStrPtr AliStrPtr;
	
	AliStrPtr = (TAliStrPtr)malloc(sizeof(TAliStr));
	if (!AliStrPtr) {
		/* Erreur allocation */
		return NULL;
	}
	AliStrPtr->SeqStr = (TAliChar*)calloc(AliCharMaxNbr, sizeof(TAliChar));
	if (!(AliStrPtr->SeqStr)) {
		/* Erreur allocation */
		free(AliStrPtr);
		return NULL;
	}
	AliStrPtr->LinkStr = (TAliChar*)calloc(AliCharMaxNbr, sizeof(TAliChar));
	if (!(AliStrPtr->LinkStr)) {
		/* Erreur allocation */
		free(AliStrPtr->SeqStr);
		free(AliStrPtr);	
		return NULL;
	}
	AliStrPtr->PrfStr = (TAliChar*)calloc(AliCharMaxNbr, sizeof(TAliChar));
	if (!(AliStrPtr->PrfStr)) {
		/* Erreur allocation */
		free(AliStrPtr->LinkStr);
		free(AliStrPtr->SeqStr);
		free(AliStrPtr);	
		return NULL;
	}
	AliStrPtr->AliCharMaxNbr = AliCharMaxNbr;
	AliStrPtr->AliCharNbr = 0;
	Coord_Reset(&(AliStrPtr->StartCoord));
	Coord_Reset(&(AliStrPtr->EndCoord));
	AliStrPtr->ScoreBPlus = PD_INFINITE;
	return AliStrPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une chaine d'alignement									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AliStrPtr					| Chaine d'alignement				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_AliStr(TAliStrPtr AliStrPtr)
{
	free(AliStrPtr->PrfStr);
	free(AliStrPtr->LinkStr);
	free(AliStrPtr->SeqStr);
	free(AliStrPtr);	
}

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une chaine d'alignement a partir d'une matrice de chemin	*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CoordVectPtr				| Vecteur de coord.					*/
/*			| PathMatrixPtr				| Matrice de chemin					*/
/*			| PrfMatrixPtr				| Matrice de profil					*/
/*			| SeqDataPtr				| Donnees de sequence				*/
/* Sortie:	| AliStrPtr					| Chaine d'alignement				*/
/*			| AliStr_FromPathMatrix		| Vecteur de coord.					*/
/* Erreur:	| AliStr_FromPathMatrix		| =NULL => ErrIndex=				*/
/*			| PA_CHAR_NBR_OVF			| Trop de caract. dans la chaine	*/
/*--------------------------------------------------------------------------*/
TAliStrPtr AliStr_FromPathMatrix(TAliStrPtr AliStrPtr, TPathMatrixPtr
PathMatrixPtr, TPrfMatrixPtr PrfMatrixPtr, TSeqDataPtr SeqDataPtr,
TErrIndex *ErrIndexPtr)
{
	TPosIndex PosIndex;			/* Index de position courant		*/
	TMolIndex MolIndex;			/* Index de molecule courant		*/
	TVertex Next;				/* Prochain sommet					*/
	TCoordPtr StartCoordPtr;	/* Coordonnees de depart			*/
	TMatchPosPtr *MatchPosList;	/* Liste des position match			*/
	TInsPosPtr *InsPosList;		/* Liste des positions d'insertion	*/
	TMol *MolStr;				/* Chaine de molecule				*/
	TAlphPtr AlphPtr;			/* Alphabet							*/
	TAliChar PrfChar;			/* Caractere du profil				*/
	TAliChar SeqChar;			/* Caractere de la sequence			*/
	TAliChar LinkChar;			/* Caractere de lien				*/
	
	/* Acces a la sequence */
	MolStr = MolSeq_MolStr(SeqData_MolSeq(SeqDataPtr));
	AlphPtr = SeqData_Alph(SeqDataPtr);
	
	/* Acces a la matrice de profil */
	MatchPosList = PrfMatrix_MatchPosList(PrfMatrixPtr);
	InsPosList = PrfMatrix_InsPosList(PrfMatrixPtr);
	
	/* Acces a la matrice de chemin */	
	StartCoordPtr = PathMatrix_StartCoord(PathMatrixPtr);
		
	/* Copie des coord. de depart */
	AliStr_PutStartCoord(AliStrPtr, StartCoordPtr);
	
	/* Copie de s_g(B+) */
	AliStr_PutScoreBPlus(AliStrPtr, PathMatrix_ScoreBPlus(PathMatrixPtr));

	/* Initialisation de la coordonnee et du prochain sommet */	
	Next = PathMatrix_BNext(PathMatrixPtr);
	PosIndex = Coord_PosIndex(StartCoordPtr);
	MolIndex = Coord_MolIndex(StartCoordPtr);
		
	/* Deplacement ds la matrice */
	while (Next != PA_E) {
		/* Deplacement */
		switch (Next) {
			case PA_M:
				PosIndex++; MolIndex++;
				Next = PathNode_MNext(PathMatrix_PathNode(PathMatrixPtr,
				PosIndex - Coord_PosIndex(StartCoordPtr),
				MolIndex - Coord_MolIndex(StartCoordPtr)));
				PrfChar = (TAliChar)MatchPos_Symb(MatchPosList_PosNth(
				MatchPosList, PosIndex));
				SeqChar = (TAliChar)Alph_LetNth(AlphPtr,
				MolStr_MolNth(MolStr, MolIndex));
				LinkChar = (ScoreVect_ScoreNth(MatchPos_M(
				MatchPosList_PosNth(MatchPosList, PosIndex)),
				MolStr_MolNth(MolStr, MolIndex)) > 0) ? '|' : ' ';
				break;
			case PA_I:
				MolIndex++;
				Next = PathNode_INext(PathMatrix_PathNode(PathMatrixPtr,
				PosIndex - Coord_PosIndex(StartCoordPtr),
				MolIndex - Coord_MolIndex(StartCoordPtr)));
				PrfChar = (TAliChar)InsPos_Symb(InsPosList_PosNth(
				InsPosList, PosIndex));
				SeqChar = (TAliChar)Alph_LetNth(AlphPtr,
				MolStr_MolNth(MolStr, MolIndex));
				LinkChar = ' ';
				break;
			case PA_D:
				PosIndex++;
				Next = PathNode_DNext(PathMatrix_PathNode(PathMatrixPtr,
				PosIndex - Coord_PosIndex(StartCoordPtr),
				MolIndex - Coord_MolIndex(StartCoordPtr)));
				PrfChar = (TAliChar)MatchPos_Symb(MatchPosList_PosNth(
				MatchPosList, PosIndex));
				SeqChar = '-';
				LinkChar = ' ';
		}
		
		/* Ajout des caracteres dans les chaines */
		if (AliStr_Full(AliStrPtr)) {
			/* Chaine d'alignement pleine */
			printf("char nbr:%d\n", AliStr_CharNbr(AliStrPtr));
			Out_AliStr(stdout, AliStrPtr);
			Print_PathMatrix(PathMatrixPtr);
			*ErrIndexPtr = PA_CHAR_NBR_OVF;
			return NULL;
		}
		AliStr_AddChar(AliStrPtr, PrfChar, SeqChar, LinkChar);
	}
	/* Affectation des coord. de fin */
	Coord_PutPosIndex(AliStr_EndCoord(AliStrPtr), PosIndex);
	Coord_PutMolIndex(AliStr_EndCoord(AliStrPtr), MolIndex);
	return AliStrPtr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Sortie d'une chaine d'alignement											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| OutPutFile				| Fichier de sortie					*/
/*			| AliStrPtr					| Chaine d'alignement				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Out_AliStr(FILE *OutPutFile, TAliStrPtr AliStrPtr)
{
	TAliCharIndex AliCharIndex;
	TAliCharIndex LineIndex;
	TAliCharIndex LineNbr;
	TAliCharIndex LineWidth;
	TAliCharIndex LastIndex;
	TBoolean Over;
	
	/* Calcul du nombre de lignes */
	LineNbr = AliStr_CharNbr(AliStrPtr)/PA_LINE_WIDTH;
	if (LineNbr*PA_LINE_WIDTH < AliStr_CharNbr(AliStrPtr)) LineNbr++;
	
	/* Calcul de la largeur de la ligne */
	LineWidth = AliStr_CharNbr(AliStrPtr)/LineNbr;
	if (LineWidth*LineNbr < AliStr_CharNbr(AliStrPtr)) LineWidth++;
	
	LineIndex = 1;
	Over = FALSE;

	while (!Over) {
		for (AliCharIndex = (LineIndex - 1)*LineWidth + 1; (AliCharIndex
		<= LineIndex*LineWidth) && (AliCharIndex <=
		AliStr_CharNbr(AliStrPtr)); AliCharIndex++) {
			Out_AliChar(OutPutFile, AliStr_PrfCharNth(AliStrPtr,
			AliCharIndex));
		}
		if (AliCharIndex > AliStr_CharNbr(AliStrPtr)) Over = TRUE;		
		fprintf(OutPutFile, "\n");
		LastIndex = AliCharIndex - 1;
		for (AliCharIndex = (LineIndex - 1)*LineWidth + 1;
		AliCharIndex <= LastIndex; AliCharIndex++) {
			Out_AliChar(OutPutFile, AliStr_LinkCharNth(AliStrPtr,
			AliCharIndex));
		}
		fprintf(OutPutFile, "\n");
		for (AliCharIndex = (LineIndex - 1)*LineWidth + 1;
		AliCharIndex <= LastIndex; AliCharIndex++) {
			Out_AliChar(OutPutFile, AliStr_SeqCharNth(AliStrPtr,
			AliCharIndex));
		}
		fprintf(OutPutFile, "\n"); fflush(OutPutFile);
		if (!Over) fprintf(OutPutFile, "\n");  fflush(OutPutFile);
		LineIndex++;
	}
}
