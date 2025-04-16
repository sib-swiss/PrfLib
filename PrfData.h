/****************************************************************************/
/*																			*/
/*	But: Definition des donnees d'une matrice de profil.					*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TNbrAc								| 	Free_NbrAc						*/
/*										|	Str_To_NbrAc					*/
/*										|	Print_NbrAc						*/
/*										|	Out_NbrAc						*/
/*--------------------------------------------------------------------------*/
/*	TTopo								|	Print_Topo						*/
/*--------------------------------------------------------------------------*/
/*	TGenSpecPtr							|	I_GenSpec						*/
/*										|	Free_GenSpec					*/
/*										|	GenSpec_Alph					*/
/*										|	GenSpec_Topo					*/
/*										|	Print_GenSpec					*/
/*--------------------------------------------------------------------------*/
/*	TDisjointDef						|	Print_DisjointDef				*/
/*--------------------------------------------------------------------------*/
/*	TDisjointPar						|	Print_DisjointPar				*/
/*--------------------------------------------------------------------------*/
/*	TDisjointParIndex					|	-								*/
/*--------------------------------------------------------------------------*/
/*	TDisjointPtr						|	I_Disjoint						*/
/*										|	Free_Disjoint					*/
/*										|	Disjoint_Def					*/
/*										|	Disjoint_ParList				*/
/*										|	Print_Disjoint					*/
/*--------------------------------------------------------------------------*/
/*	TNormFct							|	Print_NormFct					*/
/*--------------------------------------------------------------------------*/
/*	TNormPrty							|	Print_NormPrty					*/
/*--------------------------------------------------------------------------*/
/*	TNormPar							|	Print_NormPar					*/
/*--------------------------------------------------------------------------*/
/*	TNormParIndex						|	-								*/
/*--------------------------------------------------------------------------*/
/*	TNormPtr							|	I_Norm							*/
/*										|	Free_Norm						*/
/*										|	Norm_Fct						*/
/*										|	Norm_Prty						*/
/*										|	Norm_ParNth						*/
/*										|	ParNbr							*/
/*										|	Norm_Text						*/
/*										|	Print_Norm						*/
/*--------------------------------------------------------------------------*/
/*	TNormIndex							|	Print_NormIndex					*/
/*--------------------------------------------------------------------------*/
/*	TNormListPtr						|	I_NormList						*/
/*										|	Free_NormList					*/
/*										|	Resize_NormList					*/
/*										|	NormList_AddNorm				*/
/*										|	NormList_NormNth				*/
/*										|	NormList_NormNbr				*/
/*										|	NormList_MaxNormNbr				*/
/*										|	NormList_Complete				*/
/*										|	NormList_PrtyComplete			*/
/*										|	Print_NormList					*/
/*--------------------------------------------------------------------------*/
/*	TScore								|	Score_Plus						*/
/*										|	Score_Add						*/
/*										|	Score_Reset						*/
/*										|	Print_Score						*/
/*										|	Out_Score						*/
/*--------------------------------------------------------------------------*/
/*	TNScore								|	Print_NScore					*/
/*--------------------------------------------------------------------------*/
/*	TNScoreIndex						|	-								*/
/*--------------------------------------------------------------------------*/
/*	TCutOffLevel						|	Print_CutOffLevel				*/
/*--------------------------------------------------------------------------*/
/*	TCutOffPtr							|	I_CutOff						*/
/*										|	Free_CutOff						*/
/*										|	CutOff_PutLevel					*/
/*										|	CutOff_PutScore					*/
/*										|	CutOff_Score					*/
/*										|	CutOff_Level					*/
/*										|	CutOff_Text						*/
/*										|	CutOff_NScoreNth				*/
/*										|	CutOff_ModeNth					*/
/*										|	CutOff_NScoreNbr				*/
/*										|	Print_CutOff					*/
/*--------------------------------------------------------------------------*/
/*	TCutOffIndex						|	Print_CutOffIndex				*/
/*										|	Out_CutOffIndex					*/
/*--------------------------------------------------------------------------*/
/*	TCutOffListPtr						|	I_CutOffList					*/
/*										|	Free_CutOffList					*/
/*										|	Resize_CutOffList				*/
/*										|	CutOffList_AddCutOff			*/
/*										|	CutOffList_CutOffNth			*/
/*										|	CutOffList_CutOffNbr			*/
/*										|	CutOffList_MaxCutOffNbr			*/
/*										|	CutOffList_Test					*/
/*										|	Print_CutOffList				*/
/*--------------------------------------------------------------------------*/
/*	TSymb								|	Print_Symb						*/
/*--------------------------------------------------------------------------*/
/*	TInsPosPtr							|	I_InsPos						*/
/*										|	Clone_InsPos					*/
/*										|	Free_InsPos						*/
/*										|	InsPos_Symb						*/
/*										|	InsPos_B0						*/
/*										|	InsPos_B1						*/
/*										|	InsPos_E0						*/
/*										|	InsPos_E1						*/
/*										|	InsPos_BM						*/
/*										|	InsPos_BI						*/
/*										|	InsPos_BD						*/
/*										|	InsPos_BE						*/
/*										|	InsPos_MM						*/
/*										|	InsPos_MI						*/
/*										|	InsPos_MD						*/
/*										|	InsPos_ME						*/
/*										|	InsPos_IM						*/
/*										|	InsPos_II						*/
/*										|	InsPos_ID						*/
/*										|	InsPos_IE						*/
/*										|	InsPos_DM						*/
/*										|	InsPos_DI						*/
/*										|	InsPos_DD						*/
/*										|	InsPos_DE						*/
/*										|	InsPos_I						*/
/*										|	InsPos_I0						*/
/*										|	InsPos_IV						*/
/*										|	Print_InsPos					*/
/*--------------------------------------------------------------------------*/
/*	TMatchPosPtr						|	I_MatchPos						*/
/*										|	Clone_MatchPos					*/
/*										|	Free_MatchPos					*/
/*										|	MatchPos_Symb					*/
/*										|	MatchPos_M						*/
/*										|	MatchPos_M0						*/
/*										|	MatchPos_MV						*/
/*										|	MatchPos_D						*/
/*										|	Print_MatchPos					*/
/*--------------------------------------------------------------------------*/
/*	TPosIndex							|	Print_PosIndex					*/
/*--------------------------------------------------------------------------*/
/*	TPrfMatrixPtr						|	I_PrfMatrix						*/
/*										|	Free_PrfMatrix					*/
/*										|	Resize_PrfMatrix				*/
/*										|	PrfMatrix_AddPos				*/
/*										|	PrfMatrix_AddLastPos			*/
/*										|	PrfMatrix_InsPosList			*/
/*										|	InsPosList_PosNth				*/
/*										|	PrfMatrix_MatchPosList			*/
/*										|	MatchPosList_PosNth				*/
/*										|	PrfMatrix_InsPosNth				*/
/*										|	PrfMatrix_MatchPosNth			*/
/*										|	PrfMatrix_PosNbr				*/
/*										|	PrfMatrix_LastPos				*/
/*										|	PrfMatrix_Full					*/
/*										|	Print_PrfMatrix					*/
/*--------------------------------------------------------------------------*/
/*	TPrfDataPtr							|	I_PrfData						*/
/*										|	Free_PrfData					*/
/*										|	PrfData_Id						*/
/*										|	PrfData_De						*/
/*										|	PrfData_NbrAc					*/
/*										|	PrfData_GenSpec					*/
/*										|	PrfData_Disjoint				*/
/*										|	PrfData_NormList				*/
/*										|	PrfData_CutOffList				*/
/*										|	PrfData_PrfMatrix				*/
/*										|	Print_PrfData					*/
/****************************************************************************/

#ifndef _PRFDATA_
#define _PRFDATA_

#include <stddef.h>
#include "error.h"
#include "GeneralTypes.h"
#include "Alphabet.h"
#include <limits.h>

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*=========*/
/* Erreurs */
/*=========*/

#define PD_NO_ERROR			0	/* Pas d'erreur					*/
#define PD_MEM_ERR			1	/* Allocation memoire			*/
#define PD_OUT_PRTY			2	/* Priorite hors rangee			*/
#define PD_DBL_PRTY			3	/* Priorite deja existante		*/
#define PD_PRTY_MISS		4	/* Priorite manquante			*/
#define PD_DBL_LEVEL		5	/* Niveau de coupure a double	*/
#define PD_LEVEL_MISS		6	/* Niveau de coupure manquant	*/
#define PD_ZERO_LEVEL_MISS	7	/* Niveau zero manquant			*/

/*===================*/
/* Index de position */
/*===================*/

#define PD_POS_IDX_NOT_DEF UINT_MAX

/*============*/
/* Topologies */
/*============*/

#define PD_TOPO_LINEAR		1
#define PD_TOPO_CIRCULAR	2

/*============*/
/* Exclusions */
/*============*/

#define PD_UNIQUE	1
#define PD_PROTECT	2

/*================*/
/* Normalisations */
/*================*/

#define PD_NORM_LINEAR	1
#define PD_NORM_GRIB	2

/*========*/
/* Scores */
/*========*/

#define PD_INFINITE	SHRT_MIN

/************************/
/* DEFINITION DES TYPES */
/************************/

/*==========================*/
/* Type d'un nombre Prosite */
/*==========================*/

typedef TCharStr TNbrAc;

/*======================*/
/* Type d'une topologie */
/*======================*/

typedef unsigned char TTopo;

/*=============================*/
/* Type d'un index de position */
/*=============================*/

typedef unsigned int TPosIndex;

/*========================================*/
/* Structure des specifications generales */
/*========================================*/

typedef struct TGenSpec {
	TAlphPtr AlphPtr;	/* Alphabet						*/
	TTopo Topo;			/* Topologie					*/
	TPosIndex PosNbr;	/* Nombre de positions match	*/
} TGenSpec;
typedef TGenSpec *TGenSpecPtr;

/*===================================*/
/* Type d'une definition d'exclusion */
/*===================================*/

typedef unsigned char TDisjointDef;

/*=================================*/
/* Type d'un parametre d'exclusion */
/*=================================*/

typedef unsigned int TDisjointPar;

/*==========================================*/
/* Type d'un index de parametre d'exclusion */
/*==========================================*/

typedef unsigned int TDisjointParIndex;

/*=================================================*/
/* Structure d'une liste de parametres d'exclusion */
/*=================================================*/

typedef struct TDisjointParList {
	TDisjointPar *List;			/* Liste 				*/
	TDisjointParIndex ParNbr;	/* Nombre de parametres	*/
} TDisjointParList;
typedef TDisjointParList *TDisjointParListPtr;

/*==========================*/
/* Structure d'un exclusion */
/*==========================*/

typedef struct TDisjoint {
	TDisjointDef Def;				/* Definition			*/
	TDisjointParListPtr ParListPtr;	/* Liste des parametres	*/
} TDisjoint;
typedef TDisjoint *TDisjointPtr;

/*======================================*/
/* Type d'une fonction de normalisation */
/*======================================*/

typedef unsigned char TNormFct;

/*=====================================*/
/* Type d'un priorite de normalisation */
/*=====================================*/

typedef unsigned char TNormPrty;

/*======================================*/
/* Type d'un parametre de normalisation */
/*======================================*/

typedef double TNormPar;

/*===============================================*/
/* Type d'un index de parametre de normalisation */
/*===============================================*/

typedef unsigned int TNormParIndex;

/*======================================================*/
/* Structure d'une liste de parametres de normalisation */
/*======================================================*/

typedef struct TNormParList {
	TNormPar *List;			/* Liste 				*/
	TNormParIndex ParNbr;	/* Nombre de parametres	*/
} TNormParList;
typedef TNormParList *TNormParListPtr;

/*===============================*/
/* Structure d'une normalisation */
/*===============================*/
 
typedef struct TNorm {
	TNormFct Fct;				/* Fonction de normalisation	*/
	TNormPrty Prty;				/* Priorite de la normalisation	*/
	TNormParListPtr ParListPtr;	/* Parametres de normalisation	*/
	TText Text;					/* Texte 						*/
} TNorm;
typedef TNorm *TNormPtr;

/*==================================*/
/* Type d'un index de normalisation */
/*==================================*/

typedef TPtrIndex TNormIndex;

/*====================================*/
/* Type d'une liste de normalisations */
/*====================================*/

typedef TListPtr TNormListPtr;

/*=================*/
/* Type d'un score */
/*=================*/

typedef short TScore;

/*========================================*/
/* Type de la valeur d'un score normalise */
/*========================================*/

typedef double TNScoreVal;

/*================================*/
/* Structure d'un score normalise */
/*================================*/

typedef struct TNScore {
	TNScoreVal Val;		/* Valeur	*/
	TNormIndex Mode;	/* Mode		*/
} TNScore;

/*====================================*/
/* Type d'un index de score normalise */
/*====================================*/

typedef unsigned int TNScoreIndex;

/*============================================*/
/* Structure d'une liste de scores normalises */
/*============================================*/

typedef struct TNScoreList {
	TNScore *List;			/* Liste de scores	*/
	TNScoreIndex NScoreNbr;	/* Nombre de scores	*/
} TNScoreList;
typedef TNScoreList *TNScoreListPtr;

/*=======================================*/
/* Type d'un niveau de valeur de coupure */
/*=======================================*/

typedef int TCutOffLevel;

/*===================================*/
/* Structure d'une valeur de coupure */
/*===================================*/
 
typedef struct TCutOff {
	TCutOffLevel Level;				/* Niveau de la valeur de coupure	*/
	TScore Score;					/* Score de la valeur de coupure	*/
	TText Text;						/* Texte							*/
	TNScoreListPtr NScoreListPtr;	/* Liste de scoree normalises		*/
} TCutOff;
typedef TCutOff *TCutOffPtr;

/*======================================*/
/* Type d'un index de valeur de coupure */
/*======================================*/

typedef TPtrIndex TCutOffIndex;

/*========================================*/
/* Type d'une liste de valeurs de coupure */
/*========================================*/

typedef TListPtr TCutOffListPtr;

/*==================*/
/* Type d'un symbol */
/*==================*/

typedef char TSymb;

/*=============================*/
/* Type d'un vecteur de scores */
/*=============================*/

typedef TScore *TScoreVect;

/*======================================*/
/* Structure d'une position d'insertion */
/*======================================*/

typedef struct TInsPos {
	TSymb Symb;
	TScore B0;
	TScore B1;
	TScore E0;
	TScore E1;
	TScore BM;
	TScore BI;
	TScore BD;
	TScore BE;
	TScore MM;
	TScore MI;
	TScore MD;
	TScore ME;
	TScore IM;
	TScore II;
	TScore ID;
	TScore IE;
	TScore DM;
	TScore DI;
	TScore DD;
	TScore DE;
	TScoreVect I;
} TInsPos;
typedef TInsPos *TInsPosPtr;

/*================================*/
/* Structure d'une position match */
/*================================*/

typedef struct TMatchPos {
	TSymb Symb;
	TScoreVect M;
	TScore D;
} TMatchPos;
typedef TMatchPos *TMatchPosPtr;

/*===================================*/
/* Structure d'une matrice de profil */
/*===================================*/

typedef struct TPrfMatrix {
	TInsPosPtr *InsPosList;		/* Positions d'insertion		*/
	TMatchPosPtr *MatchPosList;	/* Positions match				*/
	TPosIndex PosNbr;			/* Taille de la matrice			*/
	TPosIndex MaxPosNbr;		/* Taille maximum de la matrice	*/
	TBoolean LastPos;			/* Flg de pres. de la drn. pos.	*/
} TPrfMatrix;
typedef TPrfMatrix *TPrfMatrixPtr;

/*===================================*/
/* Structure des donnees d'un profil */
/*===================================*/

typedef struct TPrfData {
	TId Id;							/* ID du profil					*/
	TDe De;							/* Description du profil		*/
	TNbrAc NbrAc;					/* Nombre prosite du profil		*/
	TGenSpecPtr GenSpecPtr;			/* Specifications generales		*/
	TDisjointPtr DisjointPtr;		/* Definition de l'exclusion	*/
	TNormListPtr NormListPtr;		/* Liste de normalisations		*/
	TCutOffListPtr CutOffListPtr;	/* Liste des valeurs de coupure	*/
	TPrfMatrixPtr PrfMatrixPtr;		/* Matrice de positions 		*/
} TPrfData;
typedef TPrfData *TPrfDataPtr;

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

/*==================================*/
/* Manipulation des nombres Prosite */
/*==================================*/

/*--------------------------------------------------------------------------*/
/* Macro de destruction d'un nombre AC										*/
/*--------------------------------------------------------------------------*/
#define Free_NbrAc(NbrAc)\
Free_CharStr((TCharStr)NbrAc)

/*--------------------------------------------------------------------------*/
/* Macro de construction d'un nombre AC										*/
/*--------------------------------------------------------------------------*/
#define Str_To_NbrAc(Str)\
((TNbrAc)(Str_To_CharStr(Str)))

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un nombre Prosite									*/
/*--------------------------------------------------------------------------*/
#define Print_NbrAc(NbrAc)\
printf("%-7s", (char*)NbrAc)

/*--------------------------------------------------------------------------*/
/* Macro d'envoi d'un nombre Prosite										*/
/*--------------------------------------------------------------------------*/
#define Out_NbrAc(OutputFile, NbrAc)\
fprintf(OutputFile,"%-7s", (char*)NbrAc)

/*=============================*/
/* Manipulation des topologies */
/*=============================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une topologie												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Topo						| Topologie							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Topo(TTopo Topo);

/*===========================================*/
/* Manipulation des specifications generales */
/*===========================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une specification generale								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlphPtr					| Alphabet							*/
/* Sortie:	| I_GenSpec					| Specification generale			*/
/* Erreur:	| I_GenSpec=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TGenSpecPtr I_GenSpec(TAlphPtr AlphPtr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une specification generale									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| GenSpecPtr				| Specification generale			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_GenSpec(TGenSpecPtr GenSpecPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant la topologie												*/
/*--------------------------------------------------------------------------*/
#define GenSpec_PutTopo(GenSpecPtr, MyTopo)\
{(GenSpecPtr)->Topo = (MyTopo);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le nombre de positions match du profil					*/
/*--------------------------------------------------------------------------*/
#define GenSpec_PutPosNbr(GenSpecPtr, MyPosNbr)\
{(GenSpecPtr)->PosNbr = MyPosNbr;}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant l'alphabet												*/
/*--------------------------------------------------------------------------*/
#define GenSpec_Alph(GenSpecPtr)\
((GenSpecPtr)->AlphPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la topologie											*/
/*--------------------------------------------------------------------------*/
#define GenSpec_Topo(GenSpecPtr)\
((GenSpecPtr)->Topo)

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de positions match du profil					*/
/*--------------------------------------------------------------------------*/
#define GenSpec_PosNbr(GenSpecPtr)\
((GenSpecPtr)->PosNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'une specification generale									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| GenSpecPtr				| Specification generale			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_GenSpec(TGenSpecPtr GenSpecPtr);

/*==========================================*/
/* Manipulation des definitions d'exclusion */
/*==========================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une definition d'exclusion									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DisjointDef				| Definition d'exclusion			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_DisjointDef(TDisjointDef DisjointDef);

/*=========================================*/
/* Manipulation des parametres d'exclusion */
/*=========================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un parametre d'exclusion							*/
/*--------------------------------------------------------------------------*/
#define Print_DisjointPar(DisjointPar)\
printf("%d", DisjointPar)

/*==================================================*/
/* Manipulation des listes de parametres d'excusion */
/*==================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une liste de parametres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ParNbr					| Nombre de parametres				*/
/* Sortie:	| I_DisjointParList			| Liste de parametres				*/
/* Erreur:	| I_DisjointParList=NULL	| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TDisjointParListPtr I_DisjointParList(TDisjointParIndex ParNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une liste de parametres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DisjointParListPtr		| Liste de parametres				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_DisjointParList(TDisjointParListPtr DisjointParListPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'un parametre	indexe a partir de 1						*/
/*--------------------------------------------------------------------------*/
#define DisjointParList_AddPar(DisjointParListPtr, Par, ParIndex)\
{(DisjointParListPtr)->List[ParIndex - 1] = Par;}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un parametre indexe a partir de 1						*/
/*--------------------------------------------------------------------------*/
#define DisjointParList_ParNth(DisjointParListPtr, ParIndex)\
((DisjointParListPtr)->List[ParIndex - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de parametres									*/
/*--------------------------------------------------------------------------*/
#define DisjointParList_ParNbr(DisjointParListPtr)\
((DisjointParListPtr)->ParNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'une liste de parametres										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DisjointParListPtr		| Liste de parametres				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_DisjointParList(TDisjointParListPtr DisjointParListPtr);

/*=============================*/
/* Manipulation des exclusions */
/*=============================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une exclusion												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DisjointParListPtr		| Liste des parametres				*/
/* Sortie:	| I_Disjoint				| Exclusion							*/
/* Erreur:	| I_Disjoint=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TDisjointPtr I_Disjoint(TDisjointParListPtr DisjointParListPtr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une exclusion												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DisjointPtr				| Exclusion							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Disjoint(TDisjointPtr DisjointPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant la definition											*/
/*--------------------------------------------------------------------------*/
#define Disjoint_PutDef(DisjointPtr, MyDef)\
{(DisjointPtr)->Def = MyDef;}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant la definition											*/
/*--------------------------------------------------------------------------*/
#define Disjoint_Def(DisjointPtr)\
((DisjointPtr)->Def)

/*--------------------------------------------------------------------------*/
/* Macro retournant la liste des parametres									*/
/*--------------------------------------------------------------------------*/
#define Disjoint_ParList(DisjointPtr)\
((DisjointPtr)->ParListPtr)

/*--------------------------------------------------------------------------*/
/* Impression d'une exclusion												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DisjointPtr				| Exclusion							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Disjoint(TDisjointPtr DisjointPtr);

/*==============================================*/
/* Manipulation des fonctions de normalisations */
/*==============================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une fonction de normalisation								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormFct					| Fonction de normalisation			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_NormFct(TNormFct NormFct);

/*=============================================*/
/* Manipulation des priorites de normalisation */
/*=============================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'une priorite de normalisation						*/
/*--------------------------------------------------------------------------*/
#define Print_NormPrty(NormPrty)\
printf("%d\n", NormPrty)

/*==============================================*/
/* Manipulation des parametres de normalisation */
/*==============================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un parametre de normalisation						*/
/*--------------------------------------------------------------------------*/
#define Print_NormPar(NormPar)\
printf("%f", NormPar)

/*========================================================*/
/* Manipulation des listes de parametres de normalisation */
/*========================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une liste de parametres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ParNbr					| Nombre de parametres				*/
/* Sortie:	| I_NormParList				| Liste de parametres				*/
/* Erreur:	| I_NormParList=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TNormParListPtr I_NormParList(TNormParIndex ParNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une liste de parametres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormParListPtr			| Liste de parametres				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_NormParList(TNormParListPtr NormParListPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'un parametre	indexe a partir de 1						*/
/*--------------------------------------------------------------------------*/
#define NormParList_AddPar(NormParListPtr, Par, ParIndex)\
{(NormParListPtr)->List[(ParIndex) - 1] = Par;}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un parametre indexe a partir de 1						*/
/*--------------------------------------------------------------------------*/
#define NormParList_ParNth(NormParListPtr, ParIndex)\
((NormParListPtr)->List[(ParIndex) - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de parametres									*/
/*--------------------------------------------------------------------------*/
#define NormParList_ParNbr(NormParListPtr)\
((NormParListPtr)->ParNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'une liste de parametres										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormParListPtr			| Liste de parametres				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_NormParList(TNormParListPtr NormParListPtr);

/*=================================*/
/* Manipulation des normalisations */
/*=================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une normalisation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormParListPtr			| Liste de parametres				*/
/*			| Text						| Texte								*/
/* Sortie:	| I_Norm					| Normalisation						*/
/* Erreur:	| I_Norm=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TNormPtr I_Norm(TNormParListPtr NormParListPtr, TText Text);

/*--------------------------------------------------------------------------*/
/* Destruction d'une normalisation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormPtr					| Normalisation						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Norm(TNormPtr NormPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant la fonction	de normalisation							*/
/*--------------------------------------------------------------------------*/
#define Norm_PutFct(NormPtr, MyFct)\
{(NormPtr)->Fct = MyFct;}

/*--------------------------------------------------------------------------*/
/* Macro affectant la priorite	de la normalisation							*/
/*--------------------------------------------------------------------------*/
#define Norm_PutPrty(NormPtr, MyPrty)\
{(NormPtr)->Prty = MyPrty;}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant la fonction	de normalisation							*/
/*--------------------------------------------------------------------------*/
#define Norm_Fct(NormPtr)\
((NormPtr)->Fct)

/*--------------------------------------------------------------------------*/
/* Macro retournant la priorite	de la normalisation							*/
/*--------------------------------------------------------------------------*/
#define Norm_Prty(NormPtr)\
((NormPtr)->Prty)

/*--------------------------------------------------------------------------*/
/* Macro retournant la liste des parametres									*/
/*--------------------------------------------------------------------------*/
#define Norm_ParList(NormPtr)\
((NormPtr)->ParListPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le texte de la normalisation							*/
/*--------------------------------------------------------------------------*/
#define Norm_Text(NormPtr)\
((NormPtr)->Text)

/*--------------------------------------------------------------------------*/
/* Impression d'une normalisation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormPtr					| Normalisation						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Norm(TNormPtr NormPtr);

/*=========================================*/
/* Manipulation des index de normalisation */
/*=========================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un index de normalisation							*/
/*--------------------------------------------------------------------------*/
#define Print_NormIndex(NormIndex)\
printf("%d", NormIndex)

/*===========================================*/
/* Manipulation des listes de normalisations */
/*===========================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'une liste de normalisations						*/
/*--------------------------------------------------------------------------*/
#define I_NormList(MaxNormNbr)\
((TNormListPtr)I_List((TPtrIndex)(MaxNormNbr)))

/*--------------------------------------------------------------------------*/
/* Desctruction d'une liste de normalisations								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormListPtr				| Liste de normalisations			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_NormList(TNormListPtr NormListPtr);

/*--------------------------------------------------------------------------*/
/* Macro de recalibration d'une liste de normalisations						*/
/*--------------------------------------------------------------------------*/
#define Resize_NormList(NormListPtr)\
Resize_List((TListPtr)(NormListPtr))

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'une normalisation indexee a partir de 1					*/
/*--------------------------------------------------------------------------*/
#define NormList_AddNorm(NormListPtr, NormPtr, NormIndex)\
List_AddIndexPtr((TListPtr)(NormListPtr), (void*)(NormPtr),\
(TPtrIndex)(NormIndex) - 1)

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant une normalisation indexee a partir de 1					*/
/*--------------------------------------------------------------------------*/
#define NormList_NormNth(NormListPtr, NormIndex)\
(TNormPtr)List_PtrNth((TListPtr)(NormListPtr),\
(TPtrIndex)(NormIndex) - 1)

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de normalisations								*/
/*--------------------------------------------------------------------------*/
#define NormList_NormNbr(NormListPtr)\
(TNormIndex)List_PtrNbr((TListPtr)(NormListPtr))

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de normalisations maximum						*/
/*--------------------------------------------------------------------------*/
#define NormList_MaxNormNbr(NormListPtr)\
(TNormIndex)List_MaxPtrNbr((TListPtr)(NormListPtr))

/*--------------------------------------------------------------------------*/
/* Macro indiquant si la liste de normalisations est complete				*/
/*--------------------------------------------------------------------------*/
#define NormList_Complete(NormListPtr)\
List_Complete((TListPtr)(NormListPtr))

/*--------------------------------------------------------------------------*/
/* Verifie si les priorites sont toutes presentes							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormListPtr				| Liste des normalisations			*/
/* Sortie:	| NormList_PrtyComplete		| Etat des priorites				*/
/* Erreur:	| NormList_PrtyComplete		| = FALSE =>						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PD_MEM_ERR				| Allocation memoire				*/
/*			| PD_OUT_PRTY				| Priorite hors rangee				*/
/*			| PD_DBL_PRTY				| Priorite deja utilisee			*/
/*			| PD_PRTY_MISS				| Priorite manquante				*/
/*--------------------------------------------------------------------------*/
TBoolean NormList_PrtyComplete(TNormListPtr NormListPtr, TErrIndex *ErrIndexPtr);

/*--------------------------------------------------------------------------*/
/* Impression de la liste des normalisations								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormListPtr				| Liste des normalisations			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_NormList(TNormListPtr NormListPtr);

/*=========================*/
/* Manipulation des scores */
/*=========================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'addition de scores												*/
/*--------------------------------------------------------------------------*/
#define Score_Plus(Score1, Score2)\
(((Score1 == PD_INFINITE)||(Score2 == PD_INFINITE)) ?\
PD_INFINITE : Score1 + Score2)

/*--------------------------------------------------------------------------*/
/* Addition de scores														*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Score1					| 1er score							*/
/*			| Score2					| 2eme score						*/
/* Sortie:	| Score_Add					| Somme								*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TScore Score_Add(TScore Score1, TScore Score2);

/*--------------------------------------------------------------------------*/
/* Macro d'initialisation d'un score										*/
/*--------------------------------------------------------------------------*/
#define Score_Reset(TheScore)\
(TheScore) = PD_INFINITE;

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un score											*/
/*--------------------------------------------------------------------------*/
#define Print_Score(Score)\
{if (Score == PD_INFINITE) printf("%c", '*'); else printf("%d", Score);}

/*--------------------------------------------------------------------------*/
/* Macro d'envoi d'un score													*/
/*--------------------------------------------------------------------------*/
#define Out_Score(OutputFile, Score)\
{if (Score == PD_INFINITE) fprintf(OutputFile, "%6c", '*');\
else fprintf(OutputFile, "%6d", Score);}

/*--------------------------------------------------------------------------*/
/* Macro 2 d'envoi d'un score												*/
/*--------------------------------------------------------------------------*/
#define Out2_Score(OutputFile, Score)\
{if (Score == PD_INFINITE) fprintf(OutputFile, "%-6c", '*');\
else fprintf(OutputFile, "%-6d", Score);}

/*===============================================*/
/* Manipulation des valeurs de scores normalises */
/*===============================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'une valeur											*/
/*--------------------------------------------------------------------------*/
#define Print_NScoreVal(NScoreVal)\
printf("%f", NScoreVal)

/*==============================================*/
/* Manipulation des listes de scores normalises */
/*==============================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une liste de scores normalises							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NScoreNbr					| Nombre de scores normalises		*/
/* Sortie:	| I_NScoreList				| Liste de scores normalises		*/
/* Erreur:	| I_NScoreList=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TNScoreListPtr I_NScoreList(TNScoreIndex NScoreNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une liste de scores normalises								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NScoreListPtr				| Liste de scores normalises		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_NScoreList(TNScoreListPtr NScoreListPtr);

/*--------------*/
/* Constructeur */
/*--------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'une valeur d'un score normalise indexe a partir de 0		*/
/*--------------------------------------------------------------------------*/
#define NScoreList_AddVal(NScoreListPtr, MyVal, NScoreIndex)\
{(NScoreListPtr)->List[NScoreIndex].Val = (MyVal);}

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'un mode d'un score normalise indexe a partir de 0		*/
/*--------------------------------------------------------------------------*/
#define NScoreList_AddMode(NScoreListPtr, MyMode, NScoreIndex)\
{(NScoreListPtr)->List[NScoreIndex].Mode = (MyMode);}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant une valeur d'un score normalise indexe a partir de 0	*/
/*--------------------------------------------------------------------------*/
#define NScoreList_Val(NScoreListPtr, NScoreIndex)\
((NScoreListPtr)->List[NScoreIndex].Val)

/*--------------------------------------------------------------------------*/
/* Macro retournant un mode d'un score normalise indexe a partir de 0		*/
/*--------------------------------------------------------------------------*/
#define NScoreList_Mode(NScoreListPtr, NScoreIndex)\
((NScoreListPtr)->List[NScoreIndex].Mode)

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de scores normalises							*/
/*--------------------------------------------------------------------------*/
#define NScoreList_NScoreNbr(NScoreListPtr)\
((NScoreListPtr)->NScoreNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'une liste de scores normalises								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NScoreListPtr				| Liste de scores normalises		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_NScoreList(TNScoreListPtr NScoreListPtr);

/*===============================================*/
/* Manipulation des niveaux de valeur de coupure */
/*===============================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro imprimant un niveau de valeur de coupure							*/
/*--------------------------------------------------------------------------*/
#define Print_CutOffLevel(CutOffLevel)\
{printf("%d", CutOffLevel);}

/*=====================================*/
/* Manipulation des valeurs de coupure */
/*=====================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une valeur de coupure										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Text						| Texte								*/
/*			| NScoreListPtr				| Liste scores normalises			*/
/* Sortie:	| I_CutOff					| Valeur de coupure					*/
/* Erreur:	| I_CutOff=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TCutOffPtr I_CutOff(TText Text, TNScoreListPtr NScoreListPtr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une valeur de coupure										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOffPtr					| Valeur de coupure					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_CutOff(TCutOffPtr CutOffPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant le niveau de la valeur de coupure							*/
/*--------------------------------------------------------------------------*/
#define CutOff_PutLevel(CutOffPtr, MyLevel)\
{(CutOffPtr)->Level = (MyLevel);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le score de la valeur de coupure							*/
/*--------------------------------------------------------------------------*/
#define CutOff_PutScore(CutOffPtr, MyScore)\
{(CutOffPtr)->Score = (MyScore);}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le nievau de la valeur de coupure						*/
/*--------------------------------------------------------------------------*/
#define CutOff_Level(CutOffPtr)\
((CutOffPtr)->Level)

/*--------------------------------------------------------------------------*/
/* Macro retournant le score de la valeur de coupure						*/
/*--------------------------------------------------------------------------*/
#define CutOff_Score(CutOffPtr)\
((CutOffPtr)->Score)

/*--------------------------------------------------------------------------*/
/* Macro retournant le texte de la valeur de coupure						*/
/*--------------------------------------------------------------------------*/
#define CutOff_Text(CutOffPtr)\
((CutOffPtr)->Text)

/*--------------------------------------------------------------------------*/
/* Macro retournant la liste des scores normalises							*/
/*--------------------------------------------------------------------------*/
#define CutOff_NScoreList(CutOffPtr)\
((CutOffPtr)->NScoreListPtr)

/*--------------------------------------------------------------------------*/
/* Impression d'une valeur de coupure										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOffPtr					| Valeur de coupure					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_CutOff(TCutOffPtr CutOffPtr);

/*==============================================*/
/* Manipulation des index de valeurs de coupure */
/*==============================================*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un index de valeur de coupure						*/
/*--------------------------------------------------------------------------*/
#define Print_CutOffIndex(CutOffIndex)\
printf("%6d", CutOffIndex)

/*--------------------------------------------------------------------------*/
/* Macro d'envoi d'un index de valeur de coupure							*/
/*--------------------------------------------------------------------------*/
#define Out_CutOffIndex(OutputFile, CutOffIndex)\
fprintf(OutputFile,"%6d", CutOffIndex)

/*===============================================*/
/* Manipulation des listes de valeurs de coupure */
/*===============================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'une liste de valeurs de coupure					*/
/*--------------------------------------------------------------------------*/
#define I_CutOffList(MaxCutOffNbr)\
((TCutOffListPtr)I_List((TPtrIndex)(MaxCutOffNbr)))

/*--------------------------------------------------------------------------*/
/* Desctruction d'une liste de valeurs de coupure							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOffListPtr				| Liste de valeurs de coupure		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_CutOffList(TCutOffListPtr CutOffListPtr);

/*--------------------------------------------------------------------------*/
/* Macro de recalibration d'une liste de valeurs de coupure					*/
/*--------------------------------------------------------------------------*/
#define Resize_CutOffList(CutOffListPtr)\
Resize_List((TListPtr)(CutOffListPtr))

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'une valeur de coupure									*/
/*--------------------------------------------------------------------------*/
#define CutOffList_AddCutOff(CutOffListPtr, CutOffPtr)\
List_AddPtr((TListPtr)(CutOffListPtr), (void*)(CutOffPtr))

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'une valeur de coupure indexee a partir de 0				*/
/*--------------------------------------------------------------------------*/
#define CutOffList_AddCutOffNth(CutOffListPtr, CutOffPtr, CutOffIndex)\
List_AddIndexPtr((TListPtr)(CutOffListPtr), (void*)(CutOffPtr), (TPtrIndex)\
CutOffIndex)

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant une valeur de coupure indexee a partir de 0				*/
/*--------------------------------------------------------------------------*/
#define CutOffList_CutOffNth(CutOffListPtr, CutOffIndex)\
(TCutOffPtr)List_PtrNth((TListPtr)(CutOffListPtr), (TPtrIndex)(CutOffIndex))

/*--------------------------------------------------------------------------*/
/* Macro retournant une valeur de coupure indexee a partir de son niv.		*/
/*--------------------------------------------------------------------------*/
#define CutOffList_CutOffLevelNth(CutOffListPtr, CutOffLevel)\
CutOffList_CutOffNth(CutOffListPtr, CutOffLevel - CutOff_Level(\
CutOffList_CutOffNth(CutOffListPtr, 0)))


/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de valeurs de coupure							*/
/*--------------------------------------------------------------------------*/
#define CutOffList_CutOffNbr(CutOffListPtr)\
(TCutOffIndex)List_PtrNbr((TListPtr)(CutOffListPtr))

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de valeurs de coupure maximum					*/
/*--------------------------------------------------------------------------*/
#define CutOffList_MaxCutOffNbr(CutOffListPtr)\
(TCutOffIndex)List_MaxPtrNbr((TListPtr)(CutOffListPtr))

/*--------------------------------------------------------------------------*/
/* Macro indiquant si la liste des valeurs est pleine 						*/
/*--------------------------------------------------------------------------*/
#define CutOffList_Full(CutOffListPtr)\
List_Full((TListPtr)CutOffListPtr)

/*--------------------------------------------------------------------------*/
/* Tri de la liste de valeurs de coupure									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOffListPtr				| Liste des valeurs de coupure		*/
/* Sortie:	| CutOffList_Sort			| Nouvelle liste					*/
/* Erreur:	| ErrIndex					| Index d'erreur					*/
/*			| PD_MEM_ERR				| Erreur memoire					*/
/*			| PD_DBL_LEVEL				| Niveau de cut-off a double		*/
/*			| PD_LEVEL_MISS				| Niveau de cut-off manquant		*/
/*			| PD_ZERO_LEVEL_MISS		| Niveau zero manquant				*/
/*--------------------------------------------------------------------------*/
TCutOffListPtr CutOffList_Sort(TCutOffListPtr CutOffListPtr, TErrIndex
*ErrIndexPtr);

/*--------------------------------------------------------------------------*/
/* Impression de la liste des valeurs de coupure							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOffListPtr				| Liste des valeurs de coupure		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_CutOffList(TCutOffListPtr CutOffListPtr);

/*===========================*/
/* Manipulation des symboles */
/*===========================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un symbole											*/
/*--------------------------------------------------------------------------*/
#define Print_Symb(Symb)\
printf("%c\n", Symb)

/*=====================================*/
/* Manipulation des vecteurs de scores */
/*=====================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'un vecteur de scores								*/
/*--------------------------------------------------------------------------*/
#define  I_ScoreVect(AlphSize)\
((TScoreVect)calloc((AlphSize) + 1, sizeof(TScore)))

/*--------------------------------------------------------------------------*/
/* Clonage d'un vecteur de scores											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ScoreVect					| Vecteur de scores original		*/
/*			| AlphSize					| Taille de l'alphabet				*/
/* Sortie:	| Clone_ScoreVect			| Vecteur de scores					*/
/* Erreur:	| Clone_ScoreVect=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TScoreVect Clone_ScoreVect(TScoreVect ScoreVect, TAlphSize AlphSize);

/*--------------------------------------------------------------------------*/
/* Macro de destruction d'un vecteur de scores								*/
/*--------------------------------------------------------------------------*/
#define Free_ScoreVect(ScoreVect)\
{free(ScoreVect);}

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'affectation d'un score correspondant a une lettre				*/
/*--------------------------------------------------------------------------*/
#define ScoreVect_PutScore(ScoreVect, Score, Let)\
{(ScoreVect)[Let] = Score;}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un score correspondant a une lettre						*/
/*--------------------------------------------------------------------------*/
#define ScoreVect_ScoreNth(ScoreVect, Let)\
((ScoreVect)[Let])

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de scores										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ScoreVect					| Vecteur de scores					*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_ScoreVect(TScoreVect ScoreVect, TAlphPtr AlphPtr);

/*========================================*/
/* Manipulation des positions d'insertion */
/*========================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une position d'insertion									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ScoreVect					| Vecteur de scores					*/
/* Sortie:	| I_InsPos					| Position d'insertion				*/
/* Erreur:	| I_InsPos=NULL				| Erreur d'allocation				*/
/*--------------------------------------------------------------------------*/
TInsPosPtr I_InsPos(TScoreVect ScoreVect);

/*--------------------------------------------------------------------------*/
/* Clonage d'une position d'insertion										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| InsPosPtr					| Position d'insertion originale	*/
/*			| AlphSize					| Taille de l'alphabet				*/
/* Sortie:	| Clone_InsPos				| Position d'insertion				*/
/* Erreur:	| Clone_InsPos=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TInsPosPtr Clone_InsPos(TInsPosPtr InsPosPtr, TAlphSize AlphSize);

/*--------------------------------------------------------------------------*/
/* Destruction d'une position d'insertion									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_InsPos(TInsPosPtr InsPosPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant le symbole de la position			 					*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutSymb(InsPosPtr, MySymb)\
{(InsPosPtr)->Symb = (MySymb);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids d'initiation externe							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutB0(InsPosPtr, Score)\
{(InsPosPtr)->B0 = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids d'initiation interne							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutB1(InsPosPtr, Score)\
{(InsPosPtr)->B1 = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de terminaison externe							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutE0(InsPosPtr, Score)\
{(InsPosPtr)->E0 = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de terminaison interne							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutE1(InsPosPtr, Score)\
{(InsPosPtr)->E1 = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de B a M							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutBM(InsPosPtr, Score)\
{(InsPosPtr)->BM = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de B a I							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutBI(InsPosPtr, Score)\
{(InsPosPtr)->BI = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de B a D							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutBD(InsPosPtr, Score)\
{(InsPosPtr)->BD = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de B a E							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutBE(InsPosPtr, Score)\
{(InsPosPtr)->BE = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de M a M							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutMM(InsPosPtr, Score)\
{(InsPosPtr)->MM = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de M a I							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutMI(InsPosPtr, Score)\
{(InsPosPtr)->MI = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de M a D							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutMD(InsPosPtr, Score)\
{(InsPosPtr)->MD = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de M a E							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutME(InsPosPtr, Score)\
{(InsPosPtr)->ME = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de I a M							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutIM(InsPosPtr, Score)\
{(InsPosPtr)->IM = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de I a I							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutII(InsPosPtr, Score)\
{(InsPosPtr)->II = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de I a D							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutID(InsPosPtr, Score)\
{(InsPosPtr)->ID = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de I a E							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutIE(InsPosPtr, Score)\
{(InsPosPtr)->IE = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de D a M							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutDM(InsPosPtr, Score)\
{(InsPosPtr)->DM = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de D a I							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutDI(InsPosPtr, Score)\
{(InsPosPtr)->DI = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de D a D							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutDD(InsPosPtr, Score)\
{(InsPosPtr)->DD = (Score);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids de transition de D a E							*/
/*--------------------------------------------------------------------------*/
#define InsPos_PutDE(InsPosPtr, Score)\
{(InsPosPtr)->DE = (Score);}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le symbol de la position			 					*/
/*--------------------------------------------------------------------------*/
#define InsPos_Symb(InsPosPtr)\
((InsPosPtr)->Symb)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids d'initiation externe							*/
/*--------------------------------------------------------------------------*/
#define InsPos_B0(InsPosPtr)\
((InsPosPtr)->B0)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids d'initiation interne							*/
/*--------------------------------------------------------------------------*/
#define InsPos_B1(InsPosPtr)\
((InsPosPtr)->B1)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de terminaison externe							*/
/*--------------------------------------------------------------------------*/
#define InsPos_E0(InsPosPtr)\
((InsPosPtr)->E0)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de terminaison interne							*/
/*--------------------------------------------------------------------------*/
#define InsPos_E1(InsPosPtr)\
((InsPosPtr)->E1)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de B a M							*/
/*--------------------------------------------------------------------------*/
#define InsPos_BM(InsPosPtr)\
((InsPosPtr)->BM)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de B a I							*/
/*--------------------------------------------------------------------------*/
#define InsPos_BI(InsPosPtr)\
((InsPosPtr)->BI)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de B a D							*/
/*--------------------------------------------------------------------------*/
#define InsPos_BD(InsPosPtr)\
((InsPosPtr)->BD)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de B a E							*/
/*--------------------------------------------------------------------------*/
#define InsPos_BE(InsPosPtr)\
((InsPosPtr)->BE)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de M a M							*/
/*--------------------------------------------------------------------------*/
#define InsPos_MM(InsPosPtr)\
((InsPosPtr)->MM)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de M a I							*/
/*--------------------------------------------------------------------------*/
#define InsPos_MI(InsPosPtr)\
((InsPosPtr)->MI)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de M a D							*/
/*--------------------------------------------------------------------------*/
#define InsPos_MD(InsPosPtr)\
((InsPosPtr)->MD)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de M a E							*/
/*--------------------------------------------------------------------------*/
#define InsPos_ME(InsPosPtr)\
((InsPosPtr)->ME)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de I a M							*/
/*--------------------------------------------------------------------------*/
#define InsPos_IM(InsPosPtr)\
((InsPosPtr)->IM)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de I a I							*/
/*--------------------------------------------------------------------------*/
#define InsPos_II(InsPosPtr)\
((InsPosPtr)->II)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de I a D							*/
/*--------------------------------------------------------------------------*/
#define InsPos_ID(InsPosPtr)\
((InsPosPtr)->ID)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de I a E							*/
/*--------------------------------------------------------------------------*/
#define InsPos_IE(InsPosPtr)\
((InsPosPtr)->IE)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de D a M							*/
/*--------------------------------------------------------------------------*/
#define InsPos_DM(InsPosPtr)\
((InsPosPtr)->DM)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de D a I							*/
/*--------------------------------------------------------------------------*/
#define InsPos_DI(InsPosPtr)\
((InsPosPtr)->DI)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de D a D							*/
/*--------------------------------------------------------------------------*/
#define InsPos_DD(InsPosPtr)\
((InsPosPtr)->DD)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids de transition de D a E							*/
/*--------------------------------------------------------------------------*/
#define InsPos_DE(InsPosPtr)\
((InsPosPtr)->DE)

/*--------------------------------------------------------------------------*/
/* Macro retournant le vecteur des poids d'insertion						*/
/*--------------------------------------------------------------------------*/
#define InsPos_I(InsPosPtr)\
((InsPosPtr)->I)

/*--------------------------------------------------------------------------*/
/* Impression d'une position d'insertion									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| InsPosPtr					| Position d'insertion				*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_InsPos(TInsPosPtr InsPosPtr, TAlphPtr AlphPtr);

/*==================================*/
/* Manipulation des positions match */
/*==================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une position match										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ScoreVect					| Vecteur de scores					*/
/* Sortie:	| I_MatchPos				| Position match					*/
/* Erreur:	| I_MatchPos=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TMatchPosPtr I_MatchPos(TScoreVect ScoreVect);

/*--------------------------------------------------------------------------*/
/* Clonage d'une position match												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MatchPosPtr				| Position match original			*/
/*			| AlphSize					| Taille de l'alphabet				*/
/* Sortie:	| Clone_MatchPos			| Position match					*/
/* Erreur:	| Clone_MatchPos=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TMatchPosPtr Clone_MatchPos(TMatchPosPtr MatchPosPtr, TAlphSize AlphSize);

/*--------------------------------------------------------------------------*/
/* Destruction d'une position match											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MatchPosPtr				| Position match					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_MatchPos(TMatchPosPtr MatchPosPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant le symbol de la position					 				*/
/*--------------------------------------------------------------------------*/
#define MatchPos_PutSymb(MatchPosPtr, MySymb)\
{(MatchPosPtr)->Symb = (MySymb);}

/*--------------------------------------------------------------------------*/
/* Macro affectant le poids d'une deletion 									*/
/*--------------------------------------------------------------------------*/
#define MatchPos_PutD(MatchPosPtr, Score)\
{(MatchPosPtr)->D = (Score);}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le symbol de la position					 			*/
/*--------------------------------------------------------------------------*/
#define MatchPos_Symb(MatchPosPtr)\
((MatchPosPtr)->Symb)

/*--------------------------------------------------------------------------*/
/* Macro retournant le vecteur des poids de match							*/
/*--------------------------------------------------------------------------*/
#define MatchPos_M(MatchPosPtr)\
((MatchPosPtr)->M)

/*--------------------------------------------------------------------------*/
/* Macro retournant le poids d'une deletion 								*/
/*--------------------------------------------------------------------------*/
#define MatchPos_D(MatchPosPtr)\
((MatchPosPtr)->D)

/*--------------------------------------------------------------------------*/
/* Impression d'une position match											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MatchPosPtr				| position match					*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_MatchPos(TMatchPosPtr MatchPosPtr, TAlphPtr AlphPtr);

/*====================================*/
/* Manipulation des index de position */
/*====================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un index de position								*/
/*--------------------------------------------------------------------------*/
#define Print_PosIndex(PosIndex)\
{if (PosIndex == PD_POS_IDX_NOT_DEF) printf("*"); else printf("%d", PosIndex);}

/*--------------------------------------------------------------------------*/
/* Macro de sortie d'un index de position									*/
/*--------------------------------------------------------------------------*/
#define Out_PosIndex(OutputFile, PosIndex)\
{if (PosIndex == PD_POS_IDX_NOT_DEF) fprintf(OutputFile, "%6c", '*');\
else fprintf(OutputFile, "%6d", PosIndex);}

/*=====================================*/
/* Manipulation des matrices de profil */
/*=====================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une matrice de profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MaxPosNbr					| Taille max. de la matr. de profil	*/
/* Sortie:	| I_PrfMatrix				| Matrice de profil					*/
/* Erreur:	| I_PrfMatrix=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TPrfMatrixPtr I_PrfMatrix(TPosIndex MaxPosNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une matrice de profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfMatrixPtr				| Matrice de profil					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PrfMatrix(TPrfMatrixPtr PrfMatrixPtr);

/*--------------------------------------------------------------------------*/
/* Recalibration d'une matrice de profil									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfMatrixPtr				| Matrice de profil					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Resize_PrfMatrix(TPrfMatrixPtr PrfMatrixPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'une position												*/
/*--------------------------------------------------------------------------*/
#define PrfMatrix_AddPos(PrfMatrixPtr, InsPosPtr, MatchPosPtr)\
{(PrfMatrixPtr)->InsPosList[(PrfMatrixPtr)->PosNbr] = (InsPosPtr);\
(PrfMatrixPtr)->MatchPosList[((PrfMatrixPtr)->PosNbr)++] = (MatchPosPtr);}

/*--------------------------------------------------------------------------*/
/* Macro d'ajout de la derniere position d'insertion						*/
/*--------------------------------------------------------------------------*/
#define PrfMatrix_AddLastPos(PrfMatrixPtr, InsPosPtr)\
{(PrfMatrixPtr)->InsPosList[(PrfMatrixPtr)->PosNbr]\
= (InsPosPtr); (PrfMatrixPtr)->LastPos = TRUE;}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant la liste des positions d'insertion						*/
/*--------------------------------------------------------------------------*/
#define PrfMatrix_InsPosList(PrfMatrixPtr)\
((PrfMatrixPtr)->InsPosList)

/*--------------------------------------------------------------------------*/
/* Macro retournant une pos. d'insertion de la liste indexee a partir de 0	*/
/*--------------------------------------------------------------------------*/
#define InsPosList_PosNth(InsPosList, PosIndex)\
((InsPosList)[PosIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant la liste des positions match							*/
/*--------------------------------------------------------------------------*/
#define PrfMatrix_MatchPosList(PrfMatrixPtr)\
((PrfMatrixPtr)->MatchPosList)

/*--------------------------------------------------------------------------*/
/* Macro retournant une position match de la liste indexee a partir de 1	*/
/*--------------------------------------------------------------------------*/
#define MatchPosList_PosNth(MatchPosList, PosIndex)\
((MatchPosList)[PosIndex - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant une position d'insertion indexee a partir de 0			*/
/*--------------------------------------------------------------------------*/
#define PrfMatrix_InsPosNth(PrfMatrixPtr, PosIndex)\
((PrfMatrixPtr)->InsPosList[PosIndex])

/*--------------------------------------------------------------------------*/
/* Macro retournant une position match indexee a partir de 1				*/
/*--------------------------------------------------------------------------*/
#define PrfMatrix_MatchPosNth(PrfMatrixPtr, PosIndex)\
((PrfMatrixPtr)->MatchPosList[PosIndex - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de positions									*/
/*--------------------------------------------------------------------------*/
#define PrfMatrix_PosNbr(PrfMatrixPtr)\
((PrfMatrixPtr)->PosNbr)

/*--------------------------------------------------------------------------*/
/* Macro indiquant si la derniere position est occupee						*/
/*--------------------------------------------------------------------------*/
#define PrfMatrix_LastPos(PrfMatrixPtr)\
((PrfMatrixPtr)->LastPos)

/*--------------------------------------------------------------------------*/
/* Macro indiquant si la matrice est pleine									*/
/*--------------------------------------------------------------------------*/
#define PrfMatrix_Full(PrfMatrixPtr)\
((PrfMatrixPtr)->PosNbr == (PrfMatrixPtr)->MaxPosNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'une matrice de profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfMatrixPtr				| Matrice de profil					*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_PrfMatrix(TPrfMatrixPtr PrfMatrixPtr, TAlphPtr AlphPtr);

/*======================================*/
/* Manipulation des donnees de profils	*/
/*======================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction des donnees d'un profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Id						| Identificateur du profil			*/
/*			| De						| Description du profil				*/
/*			| NbrAc						| Nombre AC							*/
/*			| GenSpecPtr				| Specification generales			*/
/*			| DisjointPtr				| Exclusion							*/
/*			| NormListPtr				| Liste de normalisations			*/
/*			| CutOffListPtr				| Liste de valeurs de coupure		*/
/*			| PrfMatrixPtr				| Matrice de profil					*/
/* Sortie:	| I_PrfData					| Donnees du profil					*/
/* Erreur:	| I_PrfData=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TPrfDataPtr I_PrfData(TId Id, TDe De, TNbrAc NbrAc, TGenSpecPtr GenSpecPtr,
TDisjointPtr DisjointPtr, TNormListPtr NormListPtr, TCutOffListPtr
CutOffListPtr, TPrfMatrixPtr PrfMatrixPtr);

/*--------------------------------------------------------------------------*/
/* Destruction des donnees d'un profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfDataPtr				| Donnees du profil					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PrfData(TPrfDataPtr PrfDataPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant l'ID du profil											*/
/*--------------------------------------------------------------------------*/
#define PrfData_Id(PrfDataPtr)\
((PrfDataPtr)->Id)

/*--------------------------------------------------------------------------*/
/* Macro retournant la description du profil								*/
/*--------------------------------------------------------------------------*/
#define PrfData_De(PrfDataPtr)\
((PrfDataPtr)->De)

/*--------------------------------------------------------------------------*/
/* Macro retournant le numero Prosite										*/
/*--------------------------------------------------------------------------*/
#define PrfData_NbrAc(PrfDataPtr)\
((PrfDataPtr)->NbrAc)

/*--------------------------------------------------------------------------*/
/* Macro retournant les specifications generales							*/
/*--------------------------------------------------------------------------*/
#define PrfData_GenSpec(PrfDataPtr)\
((PrfDataPtr)->GenSpecPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant l'exclusion												*/
/*--------------------------------------------------------------------------*/
#define PrfData_Disjoint(PrfDataPtr)\
((PrfDataPtr)->DisjointPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la liste des normalisations								*/
/*--------------------------------------------------------------------------*/
#define PrfData_NormList(PrfDataPtr)\
((PrfDataPtr)->NormListPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la liste des la valeurs de coupure						*/
/*--------------------------------------------------------------------------*/
#define PrfData_CutOffList(PrfDataPtr)\
((PrfDataPtr)->CutOffListPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la matrice de profil									*/
/*--------------------------------------------------------------------------*/
#define PrfData_PrfMatrix(PrfDataPtr)\
((PrfDataPtr)->PrfMatrixPtr)

/*--------------------------------------------------------------------------*/
/* Impression des donnees d'un profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfDataPtr				| Donnees du profil					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_PrfData(TPrfDataPtr PrfDataPtr);

#endif
