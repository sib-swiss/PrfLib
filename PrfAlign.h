/****************************************************************************/
/*																			*/
/*	But: definition des routines d'alignement de profil						*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*										|									*/
/****************************************************************************/

#ifndef _PRFALIGN_
#define _PRFALIGN_

#include "GeneralTypes.h"
#include "SeqData.h"
#include "PrfData.h"

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*======================*/
/* Constantes d'erreurs */
/*======================*/

#define PA_NO_ERROR			0
#define PA_MEM_ERR			1
#define PA_ALI_NBR_OVF		2
#define PA_BAD_DISJ			3
#define PA_ALI_NOT_PROT 	4
#define PA_COORD_NBR_OVF	5
#define PA_CHAR_NBR_OVF		6

/*================================*/
/* Constantes de types de sommets */
/*================================*/

#define PA_VTX_NOT_DEF	0
#define PA_B			1
#define PA_M			2
#define PA_I			3
#define PA_D			4
#define PA_E			5

/*==================================*/
/* Constantes de types de sommets + */
/*==================================*/

#define PA_VTX_PLUS_NOT_DEF	0
#define PA_E_PLUS			1
#define PA_M_PLUS			2
#define PA_I_PLUS			3
#define PA_D_PLUS			4

/*=====================*/
/* Constantes diverses */
/*=====================*/

#define PA_LINE_WIDTH	79

/**************************/
/* DEFINITION DES DONNEES */
/**************************/

/*====================================================*/
/* Structure d'un vecteur de booleen // a la sequence */
/*====================================================*/

typedef struct TBooleanVect {
	TBoolean *BooleanArray;		/* Tableau de booleens					*/
	TMolIndex BooleanNbr;		/* Nombre de booleens					*/
} TBooleanVect;
typedef TBooleanVect *TBooleanVectPtr;

/*================*/
/* Type de sommet */
/*================*/

typedef unsigned char TVertex;

/*==================*/
/* Type de sommet+ */
/*==================*/

typedef unsigned char TPlusVertex;

/*==========================*/
/* Structure de coordonnees */
/*==========================*/

typedef struct TCoord {
	TPosIndex PosIndex;	/* Position dans le profil		*/
	TMolIndex MolIndex;	/* Position dans la sequence	*/
} TCoord;
typedef TCoord *TCoordPtr;

/*======================*/
/* Structure d'un noeud */
/*======================*/

typedef struct TNode {
	TCoord MStartCoord;		/* Coordonnees sources de M		*/
	TCoord IStartCoord;		/* Coordonnees sources de I		*/
	TCoord DStartCoord;		/* Coordonnees sources de D		*/
	TScore M;				/* Score etat M					*/
	TScore I;				/* Score etat I					*/
	TScore D;				/* Score etat D					*/
} TNode;
typedef TNode *TNodePtr;

/*=============================*/
/* Structure d'un noeud etendu */
/*=============================*/

typedef struct TExtNode {
	TNode Node;				/* Noeud						*/
	TCoord MInCoord;		/* Coordonnees d'entree de M	*/
	TCoord IInCoord;		/* Coordonnees d'entree de I	*/
	TCoord DInCoord;		/* Coordonnees d'entree de D	*/
} TExtNode;
typedef TExtNode *TExtNodePtr;

/*========================*/
/* Structure d'un noeud + */
/*========================*/

typedef struct TPlusNode {
	TCoord MPlusEndCoord;		/* Coordonnees dest. de M+	*/
	TCoord IPlusEndCoord;		/* Coordonnees dest. de I+	*/
	TCoord DPlusEndCoord;		/* Coordonnees dest. de D+	*/
	TScore MPlus;				/* Score etat M+			*/
	TScore IPlus;				/* Score etat I+			*/
	TScore DPlus;				/* Score etat D+			*/
} TPlusNode;
typedef TPlusNode *TPlusNodePtr;

/*===========================*/
/* Structure d'un sous-noeud */
/*===========================*/

typedef struct TSubNode {
	TCoord MEndCoord;		/* Coordonnees dest. de M	*/
	TCoord DEndCoord;		/* Coordonnees dest. de D	*/
	TScore M;				/* Score etat M				*/
	TScore D;				/* Score etat D				*/
} TSubNode;
typedef TSubNode *TSubNodePtr;

/*=============================*/
/* Structure d'un sous-noeud + */
/*=============================*/

typedef struct TSubPlusNode {
	TCoord MPlusStartCoord;		/* Coordonnees sources de M+	*/
	TCoord DPlusStartCoord;		/* Coordonnees sources de D+	*/
	TScore MPlus;				/* Score etat M+				*/
	TScore DPlus;				/* Score etat D+				*/
} TSubPlusNode;
typedef TSubPlusNode *TSubPlusNodePtr;

/*===============================================*/
/* Structure d'un vecteur de noeuds // au profil */
/*===============================================*/

typedef struct TNodeVect {
	TNodePtr NodeArray;		/* Tableau de noeuds etendus	*/
	TPosIndex NodeNbr;		/* Nombre de noeuds etendus		*/
} TNodeVect;
typedef TNodeVect *TNodeVectPtr;

/*=======================================================*/
/* Structure d'un vecteur de noeuds etendus // au profil */
/*=======================================================*/

typedef struct TExtNodeVect {
	TExtNodePtr ExtNodeArray;	/* Tableau de noeuds etendus	*/
	TPosIndex ExtNodeNbr;		/* Nombre de noeuds etendus		*/
} TExtNodeVect;
typedef TExtNodeVect *TExtNodeVectPtr;

/*===================================================*/
/* Structure d'un vecteur de noeuds // a la sequence */
/*===================================================*/

typedef struct TSeqNodeVect {
	TNodePtr NodeArray;			/* Tableau de noeuds	*/
	TMolIndex NodeNbr;			/* Nombre de noeuds		*/
} TSeqNodeVect;
typedef TSeqNodeVect *TSeqNodeVectPtr;

/*====================================================*/
/* Structure d'un vecteur de noeuds+ // a la sequence */
/*====================================================*/

typedef struct TSeqPlusNodeVect {
	TPlusNodePtr PlusNodeArray;	/* Tableau de noeuds+	*/
	TMolIndex PlusNodeNbr;		/* Nombre de noeuds+	*/
} TSeqPlusNodeVect;
typedef TSeqPlusNodeVect *TSeqPlusNodeVectPtr;

/*========================================================*/
/* Structure d'un vecteur de sous-noeuds // a la sequence */
/*========================================================*/

typedef struct TSubNodeVect {
	TSubNodePtr SubNodeArray;	/* Tableau de sous-noeuds	*/
	TMolIndex SubNodeNbr;		/* Nombre de sous-noeuds	*/
} TSubNodeVect;
typedef TSubNodeVect *TSubNodeVectPtr;

/*=========================================================*/
/* Structure d'un vecteur de sous-noeuds+ // a la sequence */
/*=========================================================*/

typedef struct TSubPlusNodeVect {
	TSubPlusNodePtr SubPlusNodeArray;	/* Tableau de sous-noeuds+	*/
	TMolIndex SubPlusNodeNbr;			/* Nombre de noeuds+		*/
} TSubPlusNodeVect;
typedef TSubPlusNodeVect *TSubPlusNodeVectPtr;

/*===========================*/
/* Structure d'un alignement */
/*===========================*/

typedef struct TAlign {
	TCoord StartCoord;	/* F(A)		*/
	TCoord EndCoord;	/* L(A)		*/
	TCoord InCoord;		/* Fp(A)	*/
	TCoord OutCoord;	/* Lp(A)	*/
	TScore Score;		/* S(A)		*/
} TAlign;
typedef TAlign *TAlignPtr;


/*==============================*/
/* Type d'un index d'alignement */
/*==============================*/

typedef TPtrIndex TAlignIndex;

/*================================*/
/* Type d'une liste d'alignements */
/*================================*/

typedef TListPtr TAlignListPtr;

/*=======================================================================*/
/* Structure des donnees d'un alignement entre une sequence et un profil */
/*=======================================================================*/

typedef struct TPrfAlign {
	TSeqDataPtr SeqDataPtr;		/* Donnees de sequence					*/
	TPrfDataPtr PrfDataPtr;		/* Donnees de profil					*/
	TAlignListPtr AlignListPtr;	/* Liste des alignements				*/
} TPrfAlign;
typedef TPrfAlign *TPrfAlignPtr;

/*======================================================================*/
/* Structure d'un noeud avec trace du chemin							*/
/*======================================================================*/

typedef struct TPathNode {
	TScore M;			/* Score de M		*/
	TScore I;			/* Score de I		*/
	TScore D;			/* Score de D		*/
	TVertex MNext;		/* Sommet suivant M	*/
	TVertex INext;		/* Sommet suivant I	*/
	TVertex DNext;		/* Sommet suivant D	*/
} TPathNode;
typedef TPathNode *TPathNodePtr;

/*======================================================================*/
/* Structure d'une matrice de chemin									*/
/*======================================================================*/

typedef struct TPathMatrix {
	TPathNodePtr Matrix;	/* Matrice de noeuds +	*/
	TMolIndex ColumnNbr;	/* Nombre de colonnes	*/
	TPosIndex RowNbr;		/* Nombre de lignes		*/
	TCoord StartCoord;		/* Coord. de depart		*/
	TScore ScoreBPlus;		/* s_g(B+)				*/
	TVertex BNext;			/* Sommet suivant B		*/
} TPathMatrix;
typedef TPathMatrix *TPathMatrixPtr;

/*======================================================================*/
/* Type d'un index de coordonnee										*/
/*======================================================================*/

typedef unsigned int TCoordIndex;

/*======================================================================*/
/* Structure d'un vecteur de coordonnees								*/
/*======================================================================*/

typedef struct TCoordVect {
	TCoordPtr Array;			/* Tableau de coord.	*/
	TCoordIndex CoordNbr;		/* Nbr de coord.		*/
	TCoordIndex CoordMaxNbr;	/* Nbr max. de coord.	*/
	TScore ScoreBPlus;			/* Score de B+			*/
} TCoordVect;
typedef TCoordVect *TCoordVectPtr;

/*======================================================================*/
/* Type d'un caractere d'un alignement									*/
/*======================================================================*/

typedef char TAliChar;

/*======================================================================*/
/* Type d'un index de caractere											*/
/*======================================================================*/

typedef unsigned int TAliCharIndex;

/*======================================================================*/
/* Structure d'une chaine d'alignement									*/
/*======================================================================*/

typedef struct TAliStr {
	TAliChar *SeqStr;					/* Chaine de la sequence		*/
	TAliChar *LinkStr;					/* Chaine de lien				*/
	TAliChar *PrfStr;					/* Chaine du profil				*/
	TAliCharIndex AliCharMaxNbr;		/* Nbr max. de caracteres		*/
	TAliCharIndex AliCharNbr;			/* Nbr de caracteres			*/
	TCoord StartCoord;					/* Coord. de depart				*/
	TCoord EndCoord;					/* Coord. de fin				*/
	TScore ScoreBPlus;					/* Score de B+					*/
} TAliStr;
typedef TAliStr *TAliStrPtr;

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

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
TBooleanVectPtr I_BooleanVect(TMolIndex BooleanNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de booleens										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| BooleanVectPtr			| Vecteur de booleens				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_BooleanVect(TBooleanVectPtr BooleanVectPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant un booleen du tableau indexe de 1						*/
/*--------------------------------------------------------------------------*/
#define BooleanVect_PutBooleanNth(BooleanVectPtr, TheBoolean, MolIndex)\
{BooleanVectPtr->BooleanArray[MolIndex - 1] = (TheBoolean);}

/*--------------------------------------------------------------------------*/
/* Macro affectant un booleen du tableau indexe de 1						*/
/*--------------------------------------------------------------------------*/
#define BooleanArray_PutBooleanNth(BooleanArray, TheBoolean, MolIndex)\
{(BooleanArray)[MolIndex - 1] = (TheBoolean);}

/*--------------------------------------------------------------------------*/
/* Macro affectant un booleen du tableau indexe de 0						*/
/*--------------------------------------------------------------------------*/
#define BooleanArray_PutBooleanNth0(BooleanArray, TheBoolean, MolIndex)\
{(BooleanArray)[MolIndex] = (TheBoolean);}

/*--------------------------------------------------------------------------*/
/* Mise a faux du vecteur de booleens		 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| BooleanVectPtr			| Vecteur de booleens				*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void BooleanVect_Reset(TBooleanVectPtr BooleanVectPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un booleen du vecteur indexe de 1						*/
/*--------------------------------------------------------------------------*/
#define BooleanVect_BooleanNth(BooleanVectPtr, MolIndex)\
((BooleanVectPtr)->BooleanArray[MolIndex - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant le tableau de booleens									*/
/*--------------------------------------------------------------------------*/
#define BooleanVect_Array(BooleanVectPtr)\
((BooleanVectPtr)->BooleanArray)

/*--------------------------------------------------------------------------*/
/* Macro retournant un booleen du tableau indexe de 1						*/
/*--------------------------------------------------------------------------*/
#define BooleanArray_BooleanNth(BooleanArray, MolIndex)\
((BooleanArray)[(MolIndex) - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant un booleen du tableau indexe de 0						*/
/*--------------------------------------------------------------------------*/
#define BooleanArray_BooleanNth0(BooleanArray, MolIndex)\
((BooleanArray)[MolIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de booleens du vecteur						*/
/*--------------------------------------------------------------------------*/
#define BooleanVect_BooleanNbr(BooleanVectPtr)\
((BooleanVectPtr)->BooleanNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de booleens										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| BooleanVectPtr			| Vecteur de booleens				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_BooleanVect(TBooleanVectPtr BooleanVectPtr);

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
void Print_Vertex(TVertex Vertex);

/*=============================*/
/* Manipulation de coordonnees */
/*=============================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'affectation de la position dans le profil						*/
/*--------------------------------------------------------------------------*/
#define Coord_PutPosIndex(CoordPtr, ThePosIndex)\
{(CoordPtr)->PosIndex = (ThePosIndex);}

/*--------------------------------------------------------------------------*/
/* Macro d'affectation de la position dans le molecule						*/
/*--------------------------------------------------------------------------*/
#define Coord_PutMolIndex(CoordPtr, TheMolIndex)\
{(CoordPtr)->MolIndex = (TheMolIndex);}

/*--------------------------------------------------------------------------*/
/* Macro d'initialisation de coordonnees									*/
/*--------------------------------------------------------------------------*/
#define Coord_Reset(CoordPtr)\
{\
	(CoordPtr)->PosIndex = PD_POS_IDX_NOT_DEF;\
	(CoordPtr)->MolIndex = SD_MOL_IDX_NOT_DEF;\
}


/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant la position dans le profil								*/
/*--------------------------------------------------------------------------*/
#define Coord_PosIndex(CoordPtr)\
((CoordPtr)->PosIndex)

/*--------------------------------------------------------------------------*/
/* Macro retournant la position dans la molecule							*/
/*--------------------------------------------------------------------------*/
#define Coord_MolIndex(CoordPtr)\
((CoordPtr)->MolIndex)

/*--------------------------------------------------------------------------*/
/* Impression de coordonnees				 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| OutPutFile				| Fichier de sortie					*/
/*			| CoordPtr					| Coordonnees						*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Out_Coord(FILE *OutPutFile, TCoordPtr CoordPtr);

/*--------------------------------------------------------------------------*/
/* Impression de coordonnees				 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CoordPtr					| Coordonnees						*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_Coord(TCoordPtr CoordPtr);

/*=====================================*/
/* Routines de manipulation des noeuds */
/*=====================================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet M du noeud							*/
/*--------------------------------------------------------------------------*/
#define Node_PutM(NodePtr, Score)\
{(NodePtr)->M = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet I du noeud							*/
/*--------------------------------------------------------------------------*/
#define Node_PutI(NodePtr, Score)\
{(NodePtr)->I = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet D du noeud							*/
/*--------------------------------------------------------------------------*/
#define Node_PutD(NodePtr, Score)\
{(NodePtr)->D = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de depart du sommet M du noeud				*/
/*--------------------------------------------------------------------------*/
#define Node_PutMStartCoord(NodePtr, TheCoord)\
{(NodePtr)->MStartCoord = (TheCoord);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de depart du sommet I du noeud				*/
/*--------------------------------------------------------------------------*/
#define Node_PutIStartCoord(NodePtr, TheCoord)\
{(NodePtr)->IStartCoord = (TheCoord);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de depart du sommet D du noeud				*/
/*--------------------------------------------------------------------------*/
#define Node_PutDStartCoord(NodePtr, TheCoord)\
{(NodePtr)->DStartCoord = (TheCoord);}

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
FirstNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr);

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
FirstNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr);

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
FirstNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr);

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
FirstNode, TInsPosPtr InsPosPtr, TCoordPtr StartCoordPtr);

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
NodePtr21, TCoordPtr StartCoordPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet M du noeud							*/
/*--------------------------------------------------------------------------*/
#define Node_M(NodePtr)\
((NodePtr)->M)

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet I du noeud							*/
/*--------------------------------------------------------------------------*/
#define Node_I(NodePtr)\
((NodePtr)->I)

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet D du noeud							*/
/*--------------------------------------------------------------------------*/
#define Node_D(NodePtr)\
((NodePtr)->D)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de depart du sommet M du noeud				*/
/*--------------------------------------------------------------------------*/
#define Node_MStartCoord(NodePtr)\
((NodePtr)->MStartCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de depart du sommet I du noeud				*/
/*--------------------------------------------------------------------------*/
#define Node_IStartCoord(NodePtr)\
((NodePtr)->IStartCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de depart du sommet D du noeud				*/
/*--------------------------------------------------------------------------*/
#define Node_DStartCoord(NodePtr)\
((NodePtr)->DStartCoord)

/*--------------------------------------------------------------------------*/
/* Impression d'un noeud					 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodePtr					| Noeud								*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_Node(TNodePtr NodePtr);

/*=============================================*/
/* Routines de manipulation des noeuds etendus */
/*=============================================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet M du noeud etendu						*/
/*--------------------------------------------------------------------------*/
#define ExtNode_PutM(ExtNodePtr, Score)\
Node_PutM(&((ExtNodePtr)->Node), Score)

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet I du noeud etendu						*/
/*--------------------------------------------------------------------------*/
#define ExtNode_PutI(ExtNodePtr, Score)\
Node_PutI(&((ExtNodePtr)->Node), Score)

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet D du noeud etendu						*/
/*--------------------------------------------------------------------------*/
#define ExtNode_PutD(ExtNodePtr, Score)\
Node_PutD(&((ExtNodePtr)->Node), Score)

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de depart du sommet M du noeud etendu			*/
/*--------------------------------------------------------------------------*/
#define ExtNode_PutMStartCoord(ExtNodePtr, TheCoord)\
Node_PutMStartCoord(&((ExtNodePtr)->Node), TheCoord)

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de depart du sommet I du noeud etendu			*/
/*--------------------------------------------------------------------------*/
#define ExtNode_PutIStartCoord(ExtNodePtr, TheCoord)\
Node_PutIStartCoord(&((ExtNodePtr)->Node), TheCoord)

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de depart du sommet D du noeud etendu			*/
/*--------------------------------------------------------------------------*/
#define ExtNode_PutDStartCoord(ExtNodePtr, TheCoord)\
Node_PutDStartCoord(&((ExtNodePtr)->Node), TheCoord)


/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. d'entree du sommet M du noeud etendu			*/
/*--------------------------------------------------------------------------*/
#define ExtNode_PutMInCoord(ExtNodePtr, TheCoord)\
{(ExtNodePtr)->MInCoord = (TheCoord);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. d'entree du sommet I du noeud etendu			*/
/*--------------------------------------------------------------------------*/
#define ExtNode_PutIInCoord(ExtNodePtr, TheCoord)\
{(ExtNodePtr)->IInCoord = (TheCoord);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. d'entree du sommet D du noeud etendu			*/
/*--------------------------------------------------------------------------*/
#define ExtNode_PutDInCoord(ExtNodePtr, TheCoord)\
{(ExtNodePtr)->DInCoord = (TheCoord);}

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
TCoordPtr InCoordPtr);

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
TCoordPtr InCoordPtr);

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
TCoordPtr InCoordPtr);

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
InCoordPtr);

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
StartCoordPtr, TCoordPtr InCoordPtr);

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
/*			| InCoordPtr				| fp(E) par ce noeud				*/
/*			| ExtNode_LimCalc			| s(E) par ce noeud					*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TScore ExtNode_LimCalc(TExtNodePtr ExtNodePtr, TCoordPtr ExtNodeCoordPtr,
TBoolean SecondExtNode, TBoolean LastExtNode, TMatchPosPtr MatchPosPtr,
TInsPosPtr InsPosPtr, TMol Mol, TSubPlusNodePtr SubPlusNodePtr11,
TSubPlusNodePtr SubPlusNodePtr12, TExtNodePtr ExtNodePtr21, TCoordPtr
StartCoordPtr, TCoordPtr InCoordPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet M du noeud etendu					*/
/*--------------------------------------------------------------------------*/
#define ExtNode_M(ExtNodePtr)\
Node_M(&((ExtNodePtr)->Node))

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet I du noeud etendu					*/
/*--------------------------------------------------------------------------*/
#define ExtNode_I(ExtNodePtr)\
Node_I(&((ExtNodePtr)->Node))

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet D du noeud etendu					*/
/*--------------------------------------------------------------------------*/
#define ExtNode_D(ExtNodePtr)\
Node_D(&((ExtNodePtr)->Node))

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de depart du sommet M du noeud etendu		*/
/*--------------------------------------------------------------------------*/
#define ExtNode_MStartCoord(ExtNodePtr)\
Node_MStartCoord(&((ExtNodePtr)->Node))

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de depart du sommet I du noeud etendu		*/
/*--------------------------------------------------------------------------*/
#define ExtNode_IStartCoord(ExtNodePtr)\
Node_IStartCoord(&((ExtNodePtr)->Node))

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de depart du sommet D du noeud etendu		*/
/*--------------------------------------------------------------------------*/
#define ExtNode_DStartCoord(ExtNodePtr)\
Node_DStartCoord(&((ExtNodePtr)->Node))

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. d'entree du sommet M du noeud etendu			*/
/*--------------------------------------------------------------------------*/
#define ExtNode_MInCoord(ExtNodePtr)\
((ExtNodePtr)->MInCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. d'entree du sommet I du noeud etendu			*/
/*--------------------------------------------------------------------------*/
#define ExtNode_IInCoord(ExtNodePtr)\
((ExtNodePtr)->IInCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. d'entree du sommet D du noeud etendu			*/
/*--------------------------------------------------------------------------*/
#define ExtNode_DInCoord(ExtNodePtr)\
((ExtNodePtr)->DInCoord)

/*--------------------------------------------------------------------------*/
/* Plus petit index de molecule du noeud etendu				 				*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodePtr				| Noeud etendu						*/
/*			| ExtNodeCoordPtr			| Coord. du noeud etendu			*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TMolIndex ExtNode_FirstMolIndex(TExtNodePtr ExtNodePtr, TCoordPtr
ExtNodeCoordPtr);

/*--------------------------------------------------------------------------*/
/* Impression d'un noeud etendu				 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodePtr				| Noeud etendu						*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_ExtNode(TExtNodePtr ExtNodePtr);


/*=======================================*/
/* Routines de manipulation des noeuds + */
/*=======================================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet M+ du noeud +							*/
/*--------------------------------------------------------------------------*/
#define PlusNode_PutMPlus(PlusNodePtr, Score)\
{(PlusNodePtr)->MPlus = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet I+ du noeud +							*/
/*--------------------------------------------------------------------------*/
#define PlusNode_PutIPlus(PlusNodePtr, Score)\
{(PlusNodePtr)->IPlus = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet D+ du noeud +							*/
/*--------------------------------------------------------------------------*/
#define PlusNode_PutDPlus(PlusNodePtr, Score)\
{(PlusNodePtr)->DPlus = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de fin du sommet M+ du noeud					*/
/*--------------------------------------------------------------------------*/
#define PlusNode_PutMPlusEndCoord(GjefNodePtr, TheCoord)\
{(PlusNodePtr)->MPlusEndCoord = (TheCoord);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de fin du sommet I+ du noeud					*/
/*--------------------------------------------------------------------------*/
#define PlusNode_PutIPlusEndCoord(PlusNodePtr, TheCoord)\
{(PlusNodePtr)->IPlusEndCoord = (TheCoord);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de fin du sommet D+ du noeud					*/
/*--------------------------------------------------------------------------*/
#define PlusNode_PutDPlusEndCoord(PlusNodePtr, TheCoord)\
{(PlusNodePtr)->DPlusEndCoord = (TheCoord);}

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
TBoolean LastNode, TInsPosPtr InsPosPtr, TCoordPtr EndCoordPtr);

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
TBoolean LastNode, TInsPosPtr InsPosPtr, TCoordPtr EndCoordPtr);

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
TBoolean LastNode, TInsPosPtr InsPosPtr, TCoordPtr EndCoordPtr);

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
TBoolean LastNode, TInsPosPtr InsPosPtr, TCoordPtr EndCoordPtr);

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
TCoordPtr EndCoordPtr);

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
TPlusNodePtr PlusNodePtr12, TCoordPtr EndCoordPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet M+ du noeud +						*/
/*--------------------------------------------------------------------------*/
#define PlusNode_MPlus(PlusNodePtr)\
((PlusNodePtr)->MPlus)

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet I+ du noeud +						*/
/*--------------------------------------------------------------------------*/
#define PlusNode_IPlus(PlusNodePtr)\
((PlusNodePtr)->IPlus)

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet D+ du noeud +						*/
/*--------------------------------------------------------------------------*/
#define PlusNode_DPlus(PlusNodePtr)\
((PlusNodePtr)->DPlus)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de fin du sommet M+ du noeud					*/
/*--------------------------------------------------------------------------*/
#define PlusNode_MPlusEndCoord(PlusNodePtr)\
((PlusNodePtr)->MPlusEndCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de fin du sommet I+ du noeud					*/
/*--------------------------------------------------------------------------*/
#define PlusNode_IPlusEndCoord(PlusNodePtr)\
((PlusNodePtr)->IPlusEndCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de fin du sommet D+ du noeud					*/
/*--------------------------------------------------------------------------*/
#define PlusNode_DPlusEndCoord(PlusNodePtr)\
((PlusNodePtr)->DPlusEndCoord)

/*--------------------------------------------------------------------------*/
/* Impression d'un noeud+					 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PlusNodePtr				| Noeud+							*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_PlusNode(TPlusNodePtr PlusNodePtr);

/*==========================================*/
/* Routines de manipulation des sous-noeuds */
/*==========================================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet M du sous-noeud						*/
/*--------------------------------------------------------------------------*/
#define SubNode_PutM(SubNodePtr, Score)\
{(SubNodePtr)->M = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet D du sous-noeud						*/
/*--------------------------------------------------------------------------*/
#define SubNode_PutD(SubNodePtr, Score)\
{(SubNodePtr)->D = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de fin du sommet M du sous-noeud				*/
/*--------------------------------------------------------------------------*/
#define SubNode_PutMEndCoord(SubNodePtr, TheCoord)\
{(SubNodePtr)->MEndCoord = (TheCoord);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de fin du sommet D du sous-noeud				*/
/*--------------------------------------------------------------------------*/
#define SubNode_PutDEndCoord(SubNodePtr, TheCoord)\
{(SubNodePtr)->DEndCoord = (TheCoord);}

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
TCoordPtr PlusNodeCoordPtr, TInsPosPtr InsPosPtr, TBoolean LastPlusNode);

/*--------------------------------------------------------------------------*/
/* Calcul des alignements prolonges par un sous-noeuds						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubNodePtr				| Sous-noeud V						*/
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
TMatchPosPtr MatchPosPtr, TAlignPtr AlignPtr, TMolIndex *FirstMolIndexPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet M du sous-noeud						*/
/*--------------------------------------------------------------------------*/
#define SubNode_M(SubNodePtr)\
((SubNodePtr)->M)

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet D du sous-noeud						*/
/*--------------------------------------------------------------------------*/
#define SubNode_D(SubNodePtr)\
((SubNodePtr)->D)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de fin du sommet M du sous-noeud				*/
/*--------------------------------------------------------------------------*/
#define SubNode_MEndCoord(SubNodePtr)\
((SubNodePtr)->MEndCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de fin du sommet D du sous-noeud				*/
/*--------------------------------------------------------------------------*/
#define SubNode_DEndCoord(SubNodePtr)\
((SubNodePtr)->DEndCoord)

/*--------------------------------------------------------------------------*/
/* Impression d'un sous-noeud				 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubNodePtr				| Sous-noeud						*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_SubNode(TSubNodePtr SubNodePtr);

/*============================================*/
/* Routines de manipulation des sous-noeuds + */
/*============================================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet M+ du noeud +							*/
/*--------------------------------------------------------------------------*/
#define SubPlusNode_PutMPlus(SubPlusNodePtr, Score)\
{(SubPlusNodePtr)->MPlus = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet D+ du noeud +							*/
/*--------------------------------------------------------------------------*/
#define SubPlusNode_PutDPlus(PlusNodePtr, Score)\
{(PlusNodePtr)->DPlus = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de depart du sommet M+ du sous-noeud +		*/
/*--------------------------------------------------------------------------*/
#define SubPlusNode_PutMPlusStartCoord(SubPlusNodePtr, TheCoord)\
{(SubPlusNodePtr)->MPlusStartCoord = (TheCoord);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de depart du sommet D+ du sous-noeud			*/
/*--------------------------------------------------------------------------*/
#define SubPlusNode_PutDPlusStartCoord(SubPlusNodePtr, TheCoord)\
{(SubPlusNodePtr)->DPlusStartCoord = (TheCoord);}

/*--------------------------------------------------------------------------*/
/* Calcul d'un sous-noeud +													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubPlusNodePtr			| Sous-noeud +						*/
/*			| NodePtr					| Noeud								*/
/*			| NodeCoordPtr				| Coordonnees du noeud				*/
/*			| InsPosPtr					| Position d'insertion				*/
/*			| FirstNode					| Indique s'il s'agit du 1er noeud	*/
/* Sortie:	| SubNode_Calc				| Sous-Noeud calcule				*/
/*			| SubNodePtr				| Idem								*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
TSubPlusNodePtr SubPlusNode_Calc(TSubPlusNodePtr SubPlusNodePtr, TNodePtr
NodePtr, TCoordPtr NodeCoordPtr, TInsPosPtr InsPosPtr, TBoolean FirstNode);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet M+ du sous-noeud +					*/
/*--------------------------------------------------------------------------*/
#define SubPlusNode_MPlus(SubPlusNodePtr)\
((SubPlusNodePtr)->MPlus)

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet D+ du sous-noeud +					*/
/*--------------------------------------------------------------------------*/
#define SubPlusNode_DPlus(SubPlusNodePtr)\
((SubPlusNodePtr)->DPlus)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de depart du sommet M+ du sous-noeud +		*/
/*--------------------------------------------------------------------------*/
#define SubPlusNode_MPlusStartCoord(SubPlusNodePtr)\
((SubPlusNodePtr)->MPlusStartCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de depart du sommet D+ du sous-noeud+		*/
/*--------------------------------------------------------------------------*/
#define SubPlusNode_DPlusStartCoord(SubPlusNodePtr)\
((SubPlusNodePtr)->DPlusStartCoord)

/*--------------------------------------------------------------------------*/
/* Impression d'un sous-noeud+				 								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubPlusNodePtr			| Sous-noeud+						*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_SubPlusNode(TSubPlusNodePtr SubPlusNodePtr);

/*===================================================*/
/* Manipulations des vecteurs de noeuds // au profil */
/*===================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodeNbr					| Nombre de noeuds etendus			*/
/* Sortie:	| I_NodeVect				| Vecteur de noeuds etendus			*/
/* Erreur:	| I_NodeVect=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TNodeVectPtr I_NodeVect(TPosIndex NodeNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodeVectPtr				| Vecteur de noeuds					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_NodeVect(TNodeVectPtr NodeVectPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant un noeud du tableau indexe de 0							*/
/*--------------------------------------------------------------------------*/
#define NodeVect_PutNodeNth(NodeVectPtr, Node, NodeIndex)\
{NodeVectPtr->NodeArray[NodeIndex] = (Node);}

/*--------------------------------------------------------------------------*/
/* Macro affectant un noeud du tableau indexe de 0							*/
/*--------------------------------------------------------------------------*/
#define NodeArray_PutNodeNth(NodeArray, Node, NodeIndex)\
{(NodeArray)[NodeIndex] = (Node);}

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
TNodeVectPtr OutNodeVectPtr, TCoordPtr StartCoordPtr, TCoordPtr EndCoordPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un noeud du vecteur	indexe de 0							*/
/*--------------------------------------------------------------------------*/
#define NodeVect_NodeNth(NodeVectPtr, NodeIndex)\
((NodeVectPtr)->NodeArray[NodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le tableau de noeuds									*/
/*--------------------------------------------------------------------------*/
#define NodeVect_Array(NodeVectPtr)\
((NodeVectPtr)->NodeArray)

/*--------------------------------------------------------------------------*/
/* Macro retournant un noeud du tableau indexe de 0							*/
/*--------------------------------------------------------------------------*/
#define NodeArray_NodeNth(NodeArray, NodeIndex)\
((NodeArray)[NodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de noeuds du vecteur							*/
/*--------------------------------------------------------------------------*/
#define NodeVect_NodeNbr(NodeVectPtr)\
((NodeVectPtr)->NodeNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NodeVectPtr				| Vecteur de noeuds					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_NodeVect(TNodeVectPtr NodeVectPtr);

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
TExtNodeVectPtr I_ExtNodeVect(TPosIndex ExtNodeNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de noeuds etendu								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodeVectPtr			| Vecteur de noeuds etendu			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_ExtNodeVect(TExtNodeVectPtr ExtNodeVectPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant un noeud etendu du tableau indexe de 0					*/
/*--------------------------------------------------------------------------*/
#define ExtNodeVect_PutExtNodeNth(ExtNodeVectPtr, ExtNode, ExtNodeIndex)\
{ExtNodeVectPtr->ExtNodeArray[ExtNodeIndex] = (ExtNode);}

/*--------------------------------------------------------------------------*/
/* Macro affectant un noeud etendu du tableau indexe de 0					*/
/*--------------------------------------------------------------------------*/
#define ExtNodeArray_PutExtNodeNth(ExtNodeArray, ExtNode, ExtNodeIndex)\
{(ExtNodeArray)[ExtNodeIndex] = (ExtNode);}

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
/*			| FirstMolIndex				| min(fp(V).j)						*/
/*			| ExtNodeVect_Calc			| Meilleur score rencontre			*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TScore ExtNodeVect_Calc(TExtNodeVectPtr InExtNodeVectPtr, TBoolean FirstVect,
TBoolean SecondVect, TBoolean LastVect, TSubPlusNodePtr SubPlusNodePtr11,
TSubPlusNodePtr SubPlusNodePtr12, TSubNodePtr SubNodePtr21, TMol Mol,
TMolIndex MolIndex, TPrfMatrixPtr PrfMatrixPtr, TPosIndex StartInsPos,
TExtNodeVectPtr OutExtNodeVectPtr, TAlignPtr AlignPtr, TMolIndex
*FirstMolIndexPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un noeud du vecteur	indexe de 0							*/
/*--------------------------------------------------------------------------*/
#define ExtNodeVect_ExtNodeNth(ExtNodeVectPtr, ExtNodeIndex)\
((ExtNodeVectPtr)->ExtNodeArray[ExtNodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le tableau de noeuds etendu								*/
/*--------------------------------------------------------------------------*/
#define ExtNodeVect_Array(ExtNodeVectPtr)\
((ExtNodeVectPtr)->ExtNodeArray)

/*--------------------------------------------------------------------------*/
/* Macro retournant un noeud etendu du tableau indexe de 0					*/
/*--------------------------------------------------------------------------*/
#define ExtNodeArray_ExtNodeNth(ExtNodeArray, ExtNodeIndex)\
((ExtNodeArray)[ExtNodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de noeuds etendu du vecteur					*/
/*--------------------------------------------------------------------------*/
#define ExtNodeVect_ExtNodeNbr(ExtNodeVectPtr)\
((ExtNodeVectPtr)->ExtNodeNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de noeuds etendus								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ExtNodeVectPtr			| Vecteur de noeuds etendus			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_ExtNodeVect(TExtNodeVectPtr ExtNodeVectPtr);

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
TSeqNodeVectPtr I_SeqNodeVect(TMolIndex NodeNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqNodeVectPtr			| Vecteur de noeuds					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SeqNodeVect(TSeqNodeVectPtr SeqNodeVectPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant un noeud du tableau indexe de 0							*/
/*--------------------------------------------------------------------------*/
#define SeqNodeArray_PutNodeNth(NodeArray, Node, NodeIndex)\
{(NodeArray)[NodeIndex] = (Node);}

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
BestEndCoordPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un noeud du vecteur	indexe de 0							*/
/*--------------------------------------------------------------------------*/
#define SeqNodeVect_NodeNth(NodeVectPtr, NodeIndex)\
((NodeVectPtr)->NodeArray[NodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le tableau de noeuds									*/
/*--------------------------------------------------------------------------*/
#define SeqNodeVect_Array(SeqNodeVectPtr)\
((SeqNodeVectPtr)->NodeArray)

/*--------------------------------------------------------------------------*/
/* Macro retournant un noeud du tableau	indexe de 0							*/
/*--------------------------------------------------------------------------*/
#define SeqNodeArray_NodeNth(NodeArray, NodeIndex)\
((NodeArray)[NodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de noeuds du vecteur							*/
/*--------------------------------------------------------------------------*/
#define SeqNodeVect_NodeNbr(NodeVectPtr)\
((NodeVectPtr)->NodeNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de noeuds										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqNodeVectPtr			| Vecteur de noeuds					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_SeqNodeVect(TSeqNodeVectPtr SeqNodeVectPtr);

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
TSeqPlusNodeVectPtr I_SeqPlusNodeVect(TMolIndex NodeNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de noeuds+										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqPlusNodeVectPtr		| Vecteur de noeuds+				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SeqPlusNodeVect(TSeqPlusNodeVectPtr SeqPlusNodeVectPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant un noeud+ du tableau indexe de 0							*/
/*--------------------------------------------------------------------------*/
#define SeqPlusNodeArray_PutPlusNodeNth(PlusNodeArray, PlusNode,\
PlusNodeIndex)\
{(PlusNodeArray)[PlusNodeIndex] = (PlusNode);}

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
BestEndCoordPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un noeud+ du vecteur indexe de 0						*/
/*--------------------------------------------------------------------------*/
#define SeqPlusNodeVect_PlusNodeNth(PlusNodeVectPtr, PlusNodeIndex)\
((PlusNodeVectPtr)->PlusNodeArray[PlusNodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le tableau de noeuds+									*/
/*--------------------------------------------------------------------------*/
#define SeqPlusNodeVect_Array(SeqPlusNodeVectPtr)\
((SeqPlusNodeVectPtr)->PlusNodeArray)

/*--------------------------------------------------------------------------*/
/* Macro retournant un noeud+ du tableau indexe de 0						*/
/*--------------------------------------------------------------------------*/
#define SeqPlusNodeArray_PlusNodeNth(PlusNodeArray, PlusNodeIndex)\
((PlusNodeArray)[PlusNodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de noeuds+ du vecteur							*/
/*--------------------------------------------------------------------------*/
#define SeqPlusNodeVect_PlusNodeNbr(PlusNodeVectPtr)\
((PlusNodeVectPtr)->PlusNodeNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de noeuds+										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqPlusNodeVectPtr		| Vecteur de noeuds+				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_SeqPlusNodeVect(TSeqPlusNodeVectPtr SeqPlusNodeVectPtr);

/*==========================================*/
/* Manipulation des vecteurs de sous-noeuds */
/*==========================================*/

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
TSubNodeVectPtr I_SubNodeVect(TMolIndex SubNodeNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de sous-noeuds									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubNodeVectPtr			| Vecteur de sous-noeuds			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SubNodeVect(TSubNodeVectPtr SubNodeVectPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant un sous-noeud du tableau indexe de 0						*/
/*--------------------------------------------------------------------------*/
#define SubNodeArray_PutSubNodeNth(SubNodeArray, SubNode, SubNodeIndex)\
{(SubNodeArray)[SubNodeIndex] = (SubNode);}

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
TSubNodeVectPtr SubNodeVectPtr, TPosIndex PosIndex, TInsPosPtr InsPosPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un sous-noeud du vecteur indexe de 0					*/
/*--------------------------------------------------------------------------*/
#define SubNodeVect_SubNodeNth(SubNodeVectPtr, SubNodeIndex)\
((SubNodeVectPtr)->SubNodeArray[SubNodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le tableau de sous-noeuds								*/
/*--------------------------------------------------------------------------*/
#define SubNodeVect_Array(SubNodeVectPtr)\
((SubNodeVectPtr)->SubNodeArray)

/*--------------------------------------------------------------------------*/
/* Macro retournant un sous-noeud du tableau indexe de 0					*/
/*--------------------------------------------------------------------------*/
#define SubNodeArray_SubNodeNth(SubNodeArray, SubNodeIndex)\
((SubNodeArray)[SubNodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de sous-noeuds du vecteur						*/
/*--------------------------------------------------------------------------*/
#define SubNodeVect_SubNodeNbr(SubNodeVectPtr)\
((SubNodeVectPtr)->SubNodeNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de sous-noeuds									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubNodeVectPtr			| Vecteur de sous-noeuds			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_SubNodeVect(TSubNodeVectPtr SubNodeVectPtr);

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
TSubPlusNodeVectPtr I_SubPlusNodeVect(TMolIndex SubPlusNodeNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de sous-noeuds +								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubPlusNodeVectPtr		| Vecteur de sous-noeuds +			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SubPlusNodeVect(TSubPlusNodeVectPtr SubPlusNodeVectPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant un sous-noeud + du tableau indexe de 0					*/
/*--------------------------------------------------------------------------*/
#define SubPlusNodeArray_PutSubPlusNodeNth(SubPlusNodeArray, SubPlusNode,\
SubPlusNodeIndex)\
{(SubPlusNodeArray)[SubPlusNodeIndex] = (SubPlusNode);}

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
InsPosPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un sous-noeud + du vecteur indexe de 0					*/
/*--------------------------------------------------------------------------*/
#define SubPlusNodeVect_SubPlusNodeNth(SubPlusNodeVectPtr, SubPlusNodeIndex)\
((SubPlusNodeVectPtr)->SubPlusNodeArray[SubPlusNodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le tableau de sous-noeuds +								*/
/*--------------------------------------------------------------------------*/
#define SubPlusNodeVect_Array(SubPlusNodeVectPtr)\
((SubPlusNodeVectPtr)->SubPlusNodeArray)

/*--------------------------------------------------------------------------*/
/* Macro retournant un sous-noeud + du tableau indexe de 0					*/
/*--------------------------------------------------------------------------*/
#define SubPlusNodeArray_SubPlusNodeNth(SubPlusNodeArray, SubPlusNodeIndex)\
((SubPlusNodeArray)[SubPlusNodeIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de sous-noeuds + du vecteur					*/
/*--------------------------------------------------------------------------*/
#define SubPlusNodeVect_SubPlusNodeNbr(SubPlusNodeVectPtr)\
((SubPlusNodeVectPtr)->SubPlusNodeNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de sous-noeuds +									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SubPlusNodeVectPtr		| Vecteur de sous-noeuds +			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_SubPlusNodeVect(TSubPlusNodeVectPtr SubPlusNodeVectPtr);

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
TAlignPtr I_Align();

/*--------------------------------------------------------------------------*/
/* Destruction d'un alignement												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlignPtr					| Alignement						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Align(TAlignPtr AlignPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant F(A)														*/
/*--------------------------------------------------------------------------*/
#define Align_PutStartCoord(AlignPtr, TheCoord)\
((AlignPtr)->StartCoord = (TheCoord))

/*--------------------------------------------------------------------------*/
/* Macro affectant L(A)														*/
/*--------------------------------------------------------------------------*/
#define Align_PutEndCoord(AlignPtr, TheCoord)\
((AlignPtr)->EndCoord =(TheCoord))

/*--------------------------------------------------------------------------*/
/* Macro affectant Fp(A)													*/
/*--------------------------------------------------------------------------*/
#define Align_PutInCoord(AlignPtr, TheCoord)\
((AlignPtr)->InCoord = (TheCoord))

/*--------------------------------------------------------------------------*/
/* Macro affectant Lp(A)													*/
/*--------------------------------------------------------------------------*/
#define Align_PutOutCoord(AlignPtr, TheCoord)\
((AlignPtr)->OutCoord =(TheCoord))

/*--------------------------------------------------------------------------*/
/* Macro affectant S(A)														*/
/*--------------------------------------------------------------------------*/
#define Align_PutScore(AlignPtr, TheCoord)\
((AlignPtr)->Score = (TheCoord))

/*--------------------------------------------------------------------------*/
/* Macro d'initialisation d'un alignement									*/
/*--------------------------------------------------------------------------*/
#define Align_Reset(AlignPtr)\
{\
	Coord_Reset(&((AlignPtr)->StartCoord));\
	Coord_Reset(&((AlignPtr)->EndCoord));\
	Coord_Reset(&((AlignPtr)->InCoord));\
	Coord_Reset(&((AlignPtr)->OutCoord));\
	Score_Reset((AlignPtr)->Score);\
}

/*--------------------------------------------------------------------------*/
/* Macro de copie d'un alignement											*/
/*--------------------------------------------------------------------------*/
#define Align_Copy(SourceAlignPtr, DestAlignPtr)\
memcpy(DestAlignPtr, SourceAlignPtr, sizeof(TAlign));

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant F(A)													*/
/*--------------------------------------------------------------------------*/
#define Align_StartCoord(AlignPtr)\
((AlignPtr)->StartCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant L(A)													*/
/*--------------------------------------------------------------------------*/
#define Align_EndCoord(AlignPtr)\
((AlignPtr)->EndCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant Fp(A)													*/
/*--------------------------------------------------------------------------*/
#define Align_InCoord(AlignPtr)\
((AlignPtr)->InCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant Lp(A)													*/
/*--------------------------------------------------------------------------*/
#define Align_OutCoord(AlignPtr)\
((AlignPtr)->OutCoord)

/*--------------------------------------------------------------------------*/
/* Macro retournant le score de l'alignement								*/
/*--------------------------------------------------------------------------*/
#define Align_Score(AlignPtr)\
((AlignPtr)->Score)

/*--------------------------------------------------------------------------*/
/* Macro de sortie de l'etendue d'un alignement								*/
/*--------------------------------------------------------------------------*/
#define Align_OutRange(OutputFile, AlignPtr)\
{\
Out_MolIndex(OutputFile, Coord_MolIndex(&Align_StartCoord(AlignPtr)) + 1);\
fprintf(OutputFile, " - ");\
Out_MolIndex(OutputFile, Coord_MolIndex(&Align_EndCoord(AlignPtr)));\
}

/*--------------------------------------------------------------------------*/
/* Macro de sortie de l'etendue d'un alignement complementaire				*/
/*--------------------------------------------------------------------------*/
#define Align_OutCplRange(OutputFile, AlignPtr, MolNbr)\
{\
Out_MolIndex(OutputFile,\
MolNbr - Coord_MolIndex(&Align_StartCoord(AlignPtr)));\
fprintf(OutputFile, " - ");\
Out_MolIndex(OutputFile,\
MolNbr - Coord_MolIndex(&Align_EndCoord(AlignPtr))) + 1;\
}


/*--------------------------------------------------------------------------*/
/* Impression d'un alignement												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlignPtr					| Alignement						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Align(TAlignPtr AlignPtr);


/*========================================*/
/* Manipulation des indices d'alignements */
/*========================================*/

/*-----------*/
/* Selecteur */
/*-----------*/

/*--------------------------------------------------------------------------*/
/* Macro de sortie d'un index d'alignement									*/
/*--------------------------------------------------------------------------*/
#define Out_AlignIndex(OutputFile, AlignIndex)\
{fprintf(OutputFile, "%3d", AlignIndex);}

/*===================================*/
/* Routines des listes d'alignements */
/*===================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'une liste d'alignements							*/
/*--------------------------------------------------------------------------*/
#define I_AlignList(MaxAlignNbr)\
((TAlignListPtr)I_List((TPtrIndex)(MaxAlignNbr)))

/*--------------------------------------------------------------------------*/
/* Destruction d'une liste d'alignements									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlignListPtr				| Liste d'alignements				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_AlignList(TAlignListPtr AlignListPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'un alignement											*/
/*--------------------------------------------------------------------------*/
#define AlignList_AddAlign(AlignListPtr, AlignPtr)\
List_AddPtr((TListPtr)(AlignListPtr), (void*)(AlignPtr))

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un alignement indexe a partir de 0 						*/
/*--------------------------------------------------------------------------*/
#define AlignList_AlignNth(AlignListPtr, AlignIndex)\
(TAlignPtr)List_PtrNth((TListPtr)(AlignListPtr), (TPtrIndex)AlignIndex)

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre d'alignements			 						*/
/*--------------------------------------------------------------------------*/
#define AlignList_AlignNbr(AlignListPtr)\
(TAlignIndex)List_PtrNbr((TListPtr)(AlignListPtr))

/*--------------------------------------------------------------------------*/
/* Macro indiquant si la liste est pleine			 						*/
/*--------------------------------------------------------------------------*/
#define AlignList_Full(AlignListPtr)\
List_Full((TListPtr)(AlignListPtr))

/*--------------------------------------------------------------------------*/
/* Impression d'une liste d'alignements										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlignListPtr				| Liste d'alignements				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_AlignList(TAlignListPtr AlignListPtr);

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
TAlignIndex MaxAlignNbr);

/*--------------------------------------------------------------------------*/
/* Destruction des donnees d'alignement sans la sequence ni le profil		*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfAlignPtr				| Donnees d'alignement				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PrfAlign(TPrfAlignPtr PrfAlignPtr);

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
TErrIndex *ErrIndexPtr);

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
TBoolean TestProt, TErrIndex *ErrIndexPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant les donnees de la sequence de molecules					*/
/*--------------------------------------------------------------------------*/
#define PrfAlign_SeqData(PrfAlignPtr)\
((PrfAlignPtr)->SeqDataPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant les donnees de profil									*/
/*--------------------------------------------------------------------------*/
#define PrfAlign_PrfData(PrfAlignPtr)\
((PrfAlignPtr)->PrfDataPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la liste des alignements								*/
/*--------------------------------------------------------------------------*/
#define PrfAlign_AlignList(PrfAlignPtr)\
((PrfAlignPtr)->AlignListPtr)

/*--------------------------------------------------------------------------*/
/* Impression des donnees d'alignement										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfAlignPtr				| Donnees d'alignement				*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_PrfAlign(TPrfAlignPtr PrfAlignPtr);

/*--------------------------------------------------------------------------*/
/* Existence d'un alignement non protege acceptable							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOff					| Valeur de coupure					*/
/*			| SubPlusNodePtr			| Sous-noeud						*/
/*			| SubNodePtr				| Sous-noeud+						*/
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
EndMatchPosIndex);

/*==========================================*/
/* Routine des noeuds avec trace du chemin	*/
/*==========================================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet M du noeud							*/
/*--------------------------------------------------------------------------*/
#define PathNode_PutM(PathNodePtr, Score)\
{(PathNodePtr)->M = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet I du noeud							*/
/*--------------------------------------------------------------------------*/
#define PathNode_PutI(PathNodePtr, Score)\
{(PathNodePtr)->I = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le score du sommet D du noeud							*/
/*--------------------------------------------------------------------------*/
#define PathNode_PutD(PathNodePtr, Score)\
{(PathNodePtr)->D = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le sommet suivant de M									*/
/*--------------------------------------------------------------------------*/
#define PathNode_PutMNext(PathNodePtr, TheSource)\
{(PathNodePtr)->MNext = (TheSource);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le sommet suivant de I									*/
/*--------------------------------------------------------------------------*/
#define PathNode_PutINext(PathNodePtr, TheSource)\
{(PathNodePtr)->INext = (TheSource);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le sommet suivant de D									*/
/*--------------------------------------------------------------------------*/
#define PathNode_PutDNext(PathNodePtr, TheSource)\
{(PathNodePtr)->DNext = (TheSource);}

/*--------------------------------------------------------------------------*/
/* Macro reinitialisant un noeud avec trace									*/
/*--------------------------------------------------------------------------*/
#define PathNode_Reset(PathNodePtr)\
{\
	PathNode_PutM(PathNodePtr, PD_INFINITE);\
	PathNode_PutI(PathNodePtr, PD_INFINITE);\
	PathNode_PutD(PathNodePtr, PD_INFINITE);\
	PathNode_PutMNext(PathNodePtr, PA_VTX_NOT_DEF);\
	PathNode_PutINext(PathNodePtr, PA_VTX_NOT_DEF);\
	PathNode_PutDNext(PathNodePtr, PA_VTX_NOT_DEF);\
}

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
TInsPosPtr InsPosPtr, TBoolean LastPathNode);

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
Mol, TMatchPosPtr MatchPosPtr, TInsPosPtr InsPosPtr);

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
TVertex *BNextPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet M du noeud							*/
/*--------------------------------------------------------------------------*/
#define PathNode_M(PathNodePtr)\
((PathNodePtr)->M)

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet I du noeud							*/
/*--------------------------------------------------------------------------*/
#define PathNode_I(PathNodePtr)\
((PathNodePtr)->I)

/*--------------------------------------------------------------------------*/
/* Macro retournant le score du sommet D du noeud							*/
/*--------------------------------------------------------------------------*/
#define PathNode_D(PathNodePtr)\
((PathNodePtr)->D)

/*--------------------------------------------------------------------------*/
/* Macro retournant le sommet suivant M										*/
/*--------------------------------------------------------------------------*/
#define PathNode_MNext(PathNodePtr)\
((PathNodePtr)->MNext)

/*--------------------------------------------------------------------------*/
/* Macro retournant le sommet suivant I										*/
/*--------------------------------------------------------------------------*/
#define PathNode_INext(PathNodePtr)\
((PathNodePtr)->INext)

/*--------------------------------------------------------------------------*/
/* Macro retournant le sommet suivant D										*/
/*--------------------------------------------------------------------------*/
#define PathNode_DNext(PathNodePtr)\
((PathNodePtr)->DNext)

/*--------------------------------------------------------------------------*/
/* Impression d'un noeud avec trace du chemin								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PathNodePtr				| Noeud+							*/
/* Sortie:	| -							| 									*/
/* Erreur:	| -							|									*/
/*--------------------------------------------------------------------------*/
void Print_PathNode(TPathNodePtr PathNodePtr);

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
StartCoordPtr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une matrice de chemin										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PathMatrixPtr				| Matrice de chemin					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PathMatrix(TPathMatrixPtr PathMatrixPtr);

/*--------------*/
/* Contructeurs */
/*--------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'affectation d'un noeud dans la matrice indicee de (0,0)			*/
/*--------------------------------------------------------------------------*/
#define PathMatrix_PutPathNode(PathMatrixPtr, TheRow, TheColumn, PathNodePtr)\
{(PathMatrixPtr)->Matrix[(TheRow)*(PathMatrixPtr)->ColumnNbr + (TheColumn)]\
= *(PathNodePtr);}

/*--------------------------------------------------------------------------*/
/* Macro d'affectation de s_g(B+) dans la matrice							*/
/*--------------------------------------------------------------------------*/
#define PathMatrix_PutScoreBPlus(PathMatrixPtr, TheScoreBPlus)\
{(PathMatrixPtr)->ScoreBPlus = (TheScoreBPlus);}

/*--------------------------------------------------------------------------*/
/* Macro d'affectation du sommet suivant B									*/
/*--------------------------------------------------------------------------*/
#define PathMatrix_PutBNext(PathMatrixPtr, TheBNext)\
((PathMatrixPtr)->BNext = (TheBNext))

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
TPrfMatrixPtr PrfMatrixPtr, TMolSeqPtr MolSeqPtr);

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
TPrfMatrixPtr PrfMatrixPtr, TMolSeqPtr MolSeqPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un noeud de la matrice indicee de (0,0)					*/
/*--------------------------------------------------------------------------*/
#define PathMatrix_PathNode(PathMatrixPtr, TheRow, TheColumn)\
(&((PathMatrixPtr)->Matrix[(TheRow)*(PathMatrixPtr)->ColumnNbr + (TheColumn)]))

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de lignes de la matrice						*/
/*--------------------------------------------------------------------------*/
#define PathMatrix_RowNbr(PathMatrixPtr)\
((PathMatrixPtr)->RowNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de colonnes de la matrice						*/
/*--------------------------------------------------------------------------*/
#define PathMatrix_ColumnNbr(PathMatrixPtr)\
((PathMatrixPtr)->ColumnNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de depart de la matrice						*/
/*--------------------------------------------------------------------------*/
#define PathMatrix_StartCoord(PathMatrixPtr)\
(&((PathMatrixPtr)->StartCoord))

/*--------------------------------------------------------------------------*/
/* Macro retournant s_g(B+) de la matrice									*/
/*--------------------------------------------------------------------------*/
#define PathMatrix_ScoreBPlus(PathMatrixPtr)\
((PathMatrixPtr)->ScoreBPlus)

/*--------------------------------------------------------------------------*/
/* Macro retournant le sommet suivant B										*/
/*--------------------------------------------------------------------------*/
#define PathMatrix_BNext(PathMatrixPtr)\
((PathMatrixPtr)->BNext)

/*--------------------------------------------------------------------------*/
/* Impression d'une matrice de chemin										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PathMatrixPtr				| Matrice de chemin					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_PathMatrix(TPathMatrixPtr PathMatrixPtr);

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
TCoordVectPtr I_CoordVect(TCoordIndex CoordMaxNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'un vecteur de coordonnees									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CoordVectPtr				| Vecteur de coord.					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_CoordVect(TCoordVectPtr CoordVectPtr);

/*--------------*/
/* Contructeurs */
/*--------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'une coordonnee dans le vecteur							*/
/*--------------------------------------------------------------------------*/
#define CoordVect_AddCoord(CoordVectPtr, CoordPtr)\
{(CoordVectPtr)->Array[(CoordVectPtr)->CoordNbr++] = *(CoordPtr);}

/*--------------------------------------------------------------------------*/
/* Macro affectant s_g(B+)													*/
/*--------------------------------------------------------------------------*/
#define CoordVect_PutScoreBPlus(CoordVectPtr, TheScoreBPlus)\
{(CoordVectPtr)->ScoreBPlus = (TheScoreBPlus);}

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
TPathMatrixPtr PathMatrixPtr, TErrIndex *ErrIndexPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant une coordonnee dans le vecteur indice a partir de 0		*/
/*--------------------------------------------------------------------------*/
#define CoordVect_CoordNth(CoordVectPtr, CoordIndex)\
(&((CoordVectPtr)->Array[CoordIndex]))

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de coord. dans le vecteur						*/
/*--------------------------------------------------------------------------*/
#define CoordVect_CoordNbr(CoordVectPtr)\
((CoordVectPtr)->CoordNbr)

/*--------------------------------------------------------------------------*/
/* Macro indiquant si le vecteur est plein									*/
/*--------------------------------------------------------------------------*/
#define CoordVect_Full(CoordVectPtr)\
((CoordVectPtr)->CoordNbr == (CoordVectPtr)->CoordMaxNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant s_g(B+)													*/
/*--------------------------------------------------------------------------*/
#define CoordVect_ScoreBPlus(CoordVectPtr)\
((CoordVectPtr)->ScoreBPlus)

/*--------------------------------------------------------------------------*/
/* Sortie d'un vecteur de coordonnees										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| OutPutFile				| Fichier de sortie					*/
/*			| CoordVectPtr				| Vecteur de coord.					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Out_CoordVect(FILE *OutPutFile, TCoordVectPtr CoordVectPtr);

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de coordonnees									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CoordVectPtr				| Vecteur de coord.					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_CoordVect(TCoordVectPtr CoordVectPtr);

/*==========================================*/
/* Manipulation des caracteres d'alignement */
/*==========================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'affichage d'un caractere											*/
/*--------------------------------------------------------------------------*/
#define Print_AliChar(AliChar)\
printf("%c", AliChar);

/*--------------------------------------------------------------------------*/
/* Macro de sortie d'un caractere											*/
/*--------------------------------------------------------------------------*/
#define Out_AliChar(OutPutFile, AliChar)\
fprintf(OutPutFile, "%c", AliChar);

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
TAliStrPtr I_AliStr(TAliCharIndex AliCharMaxNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une chaine d'alignement									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AliStrPtr					| Chaine d'alignement				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_AliStr(TAliStrPtr AliStrPtr);

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
TErrIndex *ErrIndexPtr);

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'un caractere dans une chaine								*/
/*--------------------------------------------------------------------------*/
#define AliStr_AddChar(AliStrPtr, PrfChar, SeqChar, LinkChar)\
{\
	(AliStrPtr)->PrfStr[(AliStrPtr)->AliCharNbr] = PrfChar;\
	(AliStrPtr)->SeqStr[(AliStrPtr)->AliCharNbr] = SeqChar;\
	(AliStrPtr)->LinkStr[(AliStrPtr)->AliCharNbr++] = LinkChar;\
}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de depart										*/
/*--------------------------------------------------------------------------*/
#define AliStr_PutStartCoord(AliStrPtr, StartCoordPtr)\
{(AliStrPtr)->StartCoord = *(StartCoordPtr);}

/*--------------------------------------------------------------------------*/
/* Macro affectant les coord. de fin										*/
/*--------------------------------------------------------------------------*/
#define AliStr_PutEndCoord(AliStrPtr, EndCoordPtr)\
{(AliStrPtr)->EndCoord = *(EndCoordPtr);}

/*--------------------------------------------------------------------------*/
/* Macro affectant s_g(B+)													*/
/*--------------------------------------------------------------------------*/
#define AliStr_PutScoreBPlus(AliStrPtr, TheScoreBPlus)\
{(AliStrPtr)->ScoreBPlus = (TheScoreBPlus);}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un caractere d'une chaine indexe a partir de 1			*/
/*--------------------------------------------------------------------------*/
#define AliCharStr_CharNth(AliCharStr, AliCharIndex)\
((AliCharStr)[(AliCharIndex) - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant un car. de la chaine de profil indexe a partir de 1		*/
/*--------------------------------------------------------------------------*/
#define AliStr_PrfCharNth(AliStrPtr, AliCharIndex)\
((AliStrPtr)->PrfStr[(AliCharIndex) - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant un car. de la chaine de seq. indexe a partir de 1		*/
/*--------------------------------------------------------------------------*/
#define AliStr_SeqCharNth(AliStrPtr, AliCharIndex)\
((AliStrPtr)->SeqStr[(AliCharIndex) - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant un car. de la chaine de liens indexe a partir de 1		*/
/*--------------------------------------------------------------------------*/
#define AliStr_LinkCharNth(AliStrPtr, AliCharIndex)\
((AliStrPtr)->LinkStr[(AliCharIndex) - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant la chaine de la sequence								*/
/*--------------------------------------------------------------------------*/
#define AliStr_SeqStr(AliStrPtr)\
((AliStrPtr)->SeqStr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la chaine de lien										*/
/*--------------------------------------------------------------------------*/
#define AliStr_LinkStr(AliStrPtr)\
((AliStrPtr)->LinkStr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la chaine de profil										*/
/*--------------------------------------------------------------------------*/
#define AliStr_PrfStr(AliStrPtr)\
((AliStrPtr)->PrfStr)

/*--------------------------------------------------------------------------*/
/* Macro indiquant si la chaine est pleine									*/
/*--------------------------------------------------------------------------*/
#define AliStr_Full(AliStrPtr)\
((AliStrPtr)->AliCharNbr == (AliStrPtr)->AliCharMaxNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de caractere dans la chaine					*/
/*--------------------------------------------------------------------------*/
#define AliStr_CharNbr(AliStrPtr)\
((AliStrPtr)->AliCharNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de depart										*/
/*--------------------------------------------------------------------------*/
#define AliStr_StartCoord(AliStrPtr)\
(&((AliStrPtr)->StartCoord))

/*--------------------------------------------------------------------------*/
/* Macro retournant les coord. de fin										*/
/*--------------------------------------------------------------------------*/
#define AliStr_EndCoord(AliStrPtr)\
(&((AliStrPtr)->EndCoord))

/*--------------------------------------------------------------------------*/
/* Macro retournant s_g(B+)													*/
/*--------------------------------------------------------------------------*/
#define AliStr_ScoreBPlus(AliStrPtr)\
(&((AliStrPtr)->ScoreBPlus))

/*--------------------------------------------------------------------------*/
/* Sortie d'une chaine d'alignement											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| OutPutFile				| Fichier de sortie					*/
/*			| AliStrPtr					| Chaine d'alignement				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Out_AliStr(FILE *OutPutFile, TAliStrPtr AliStrPtr);

#endif
