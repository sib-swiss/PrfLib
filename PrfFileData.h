/****************************************************************************/
/*																			*/
/*	But: Definition des donnees d'un fichier de profil.						*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TValPtr								| 	I_Val							*/
/*										|	Free_Val						*/
/*										|	Print_Val						*/
/*										|	Val_Nbr							*/
/*										|	Val_Str							*/
/*										|	Val_Word						*/
/*										|	Val_Type						*/
/*--------------------------------------------------------------------------*/
/*	TValIndex							| 	-								*/
/*--------------------------------------------------------------------------*/
/*	TAssPtr								| 	I_Ass							*/
/*										|	Free_Ass						*/
/*										|	Ass_ResizeValList				*/
/*										|	Ass_AddVal						*/
/*										|	Ass_ValListFull					*/
/*										|	Ass_ValNth						*/
/*										|	Ass_ValNbr						*/
/*										|	Ass_Word						*/
/*										|	Print_Ass						*/
/*--------------------------------------------------------------------------*/
/*	TAssIndex							| 	-								*/
/*--------------------------------------------------------------------------*/
/*	TDescPtr							| 	I_Desc							*/
/*										|	Free_Desc						*/
/*										|	Desc_ResizeAssList				*/
/*										|	Desc_AddAss						*/
/*										|	Desc_AssListFull				*/
/*										|	Desc_AssNth						*/
/*										|	Desc_AssNbr						*/
/*										|	Desc_Keyword					*/
/*										|	Print_Desc						*/
/*--------------------------------------------------------------------------*/
/*	TDescIndex							| 	-								*/
/*--------------------------------------------------------------------------*/
/*	TPrfPtr								| 	I_Prf							*/
/*										|	Free_Prf						*/
/*										|	Prf_ResizeDescList				*/
/*										|	Prf_AddDesc						*/
/*										|	Prf_DescListFull				*/
/*										|	Prf_DescNth						*/
/*										|	Prf_DescNbr						*/
/*										|	Print_Prf						*/
/*--------------------------------------------------------------------------*/
/*	TPrfFileDataPtr						| 	I_PrfFileData					*/
/*										|	Free_PrfFileData				*/
/*										|	PrfFileData_Id					*/
/*										|	PrfFileData_De					*/
/*										|	PrfFileData_NbrAc				*/
/*										|	PrfFileData_Prf					*/
/*										|	Print_PrfFileData				*/
/****************************************************************************/

#ifndef _PRFFILEDATA_
#define _PRFFILEDATA_

#include <stddef.h>
#include <stdio.h>
#include "GeneralTypes.h"
#include "FileData.h"

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*==============================*/
/* Constantes de type de valeur */
/*==============================*/

#define PFD_A_NBR		1
#define PFD_A_STR		2
#define PFD_A_WORD		3
#define PFD_INFINITE	4

/************************/
/* DEFINITION DES TYPES */
/************************/

/*========================*/
/* Structure d'une valeur */
/*========================*/

typedef union TData {
	TNbr Nbr;
	TStrPtr StrPtr;
	TWordPtr WordPtr;
} TData;
typedef unsigned char TValType;
typedef struct TVal {	
	TData Data;
	TValType ValType;
} TVal;
typedef TVal *TValPtr;

/*=============================*/
/* Structure d'une assignation */
/*=============================*/

typedef unsigned int TValIndex;
typedef struct TAss {
	TWordPtr WordPtr;
	TValPtr *ValList;
	TValIndex MaxValNbr;
	TValIndex ValNbr;
} TAss;
typedef TAss *TAssPtr;

/*=============================*/
/* Structure d'une description */
/*=============================*/

typedef unsigned int TAssIndex;
typedef struct TDesc {
	TWordPtr KeywordPtr;
	TAssPtr *AssList;
	TAssIndex MaxAssNbr;
	TAssIndex AssNbr;
} TDesc;
typedef TDesc *TDescPtr;

/*=======================*/
/* Structure d'un profil */
/*=======================*/

typedef unsigned int TDescIndex;
typedef struct TPrf {
	TDescPtr *DescList;
	TDescIndex MaxDescNbr;
	TDescIndex DescNbr;
} TPrf;
typedef TPrf *TPrfPtr;

/*============================================*/
/* Structure des donnees de profil du fichier */
/*============================================*/

typedef struct TPrfFileData {
	TWordPtr Id;
	TSentPtr De;
	TWordPtr NbrAc;
	TPrfPtr PrfPtr;
} TPrfFileData;
typedef TPrfFileData *TPrfFileDataPtr;

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

/*==========================*/
/* Manipulation des valeurs */
/*==========================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une valeur												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| -							| -									*/
/* Sortie:	| I_Val						| Valeur							*/
/* Erreur:	| I_Val=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TValPtr I_Val();

/*--------------------------------------------------------------------------*/
/* Destruction d'une valeur													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ValPtr					| Valeur							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Val(TValPtr ValPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une valeur													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ValPtr					| Valeur							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Val(TValPtr ValPtr);

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre d'une valeur 									*/
/*--------------------------------------------------------------------------*/
#define Val_Nbr(ValPtr)\
((ValPtr)->Data.Nbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la chaine d'une valeur									*/
/*--------------------------------------------------------------------------*/
#define Val_Str(ValPtr)\
((ValPtr)->Data.StrPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le mot d'une valeur									 	*/
/*--------------------------------------------------------------------------*/
#define Val_Word(ValPtr)\
((ValPtr)->Data.WordPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le type d'une valeur 									*/
/*--------------------------------------------------------------------------*/
#define Val_Type(ValPtr)\
((ValPtr)->ValType)

/*===============================*/
/* Manipulation des assignations */
/*===============================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une assignation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MaxValNbr					| Taille de la liste des valeurs	*/
/*			| WordPtr					| Nom de la variable				*/
/* Sortie:	| I_Ass						| Assignation						*/
/* Erreur:	| I_Ass=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TAssPtr I_Ass(TValIndex MaxValNbr, TWordPtr WordPtr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une assignation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AssPtr					| Assignation						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Ass(TAssPtr AssPtr);

/*--------------------------------------------------------------------------*/
/* Recalibration de la liste de valeurs										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AssPtr					| Assignation						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Ass_ResizeValList(TAssPtr AssPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'une valeur a la liste des valeurs						*/
/*--------------------------------------------------------------------------*/
#define Ass_AddVal(AssPtr, ValPtr) \
(AssPtr)->ValList[((AssPtr)->ValNbr)++] = (ValPtr)

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro indiquant si la liste des valeurs est pleine						*/
/*--------------------------------------------------------------------------*/
#define Ass_ValListFull(AssPtr)\
((AssPtr)->MaxValNbr == (AssPtr)->ValNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la valeur No ValIndex a partir de 0						*/
/*--------------------------------------------------------------------------*/
#define Ass_ValNth(AssPtr, ValIndex)\
((AssPtr)->ValList[(ValIndex)])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de valeurs									*/
/*--------------------------------------------------------------------------*/
#define Ass_ValNbr(AssPtr)\
((AssPtr)->ValNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le mot d'une assignation								*/
/*--------------------------------------------------------------------------*/
#define Ass_Word(AssPtr)\
((AssPtr)->WordPtr)

/*--------------------------------------------------------------------------*/
/* Impression d'une assignation												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AssPtr					| Assignation						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Ass(TAssPtr AssPtr);

/*===============================*/
/* Manipulation des descriptions */
/*===============================*/
	
/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une description											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MaxAssNbr					| Taille de la liste des ass.		*/
/*			| KeyWordPtr				| Mot-cle							*/
/* Sortie:	| I_Desc					| Description						*/
/* Erreur:	| I_Desc=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TDescPtr I_Desc(TAssIndex MaxAssNbr, TWordPtr KeyWordPtr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une description											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DescPtr					| Description						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Desc(TDescPtr DescPtr);

/*--------------------------------------------------------------------------*/
/* Recalibration de la liste des assignations								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DescPtr					| Description						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Desc_ResizeAssList(TDescPtr DescPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'une assignation a la liste des assignations				*/
/*--------------------------------------------------------------------------*/
#define Desc_AddAss(DescPtr, AssPtr)\
(DescPtr)->AssList[((DescPtr)->AssNbr)++] = (AssPtr)

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro indiquant si la liste des assignations est pleine					*/
/*--------------------------------------------------------------------------*/
#define Desc_AssListFull(DescPtr) \
((DescPtr)->MaxAssNbr == (DescPtr)->AssNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant l'assignation No AssIndex a partir de 0					*/
/*--------------------------------------------------------------------------*/
#define Desc_AssNth(DescPtr, AssIndex)\
((DescPtr)->AssList[(AssIndex)])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre d'assignations								*/
/*--------------------------------------------------------------------------*/
#define Desc_AssNbr(DescPtr)\
((DescPtr)->AssNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le mot-cle d'une description							*/
/*--------------------------------------------------------------------------*/
#define Desc_Keyword(DescPtr)\
((DescPtr)->KeywordPtr)

/*--------------------------------------------------------------------------*/
/* Impression d'une description												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DescPtr					| Description						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Desc(TDescPtr DescPtr);

/*==========================*/
/* Manipulation des profils */
/*==========================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/
	
/*--------------------------------------------------------------------------*/
/* Construction d'un profil													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MaxDescNbr				| Taille de la liste des descr.		*/
/* Sortie:	| I_Prf						| Profil							*/
/* Erreur:	| I_Prf=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TPrfPtr I_Prf(TDescIndex MaxDescNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'un profil													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfPtr					| Profil							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Prf(TPrfPtr PrfPtr);

/*--------------------------------------------------------------------------*/
/* Recalibration de la liste des descriptions								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfPtr					| Profil							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Prf_ResizeDescList(TPrfPtr PrfPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'une description a la liste des descriptions				*/
/*--------------------------------------------------------------------------*/
#define Prf_AddDesc(PrfPtr, DescPtr)\
(PrfPtr)->DescList[((PrfPtr)->DescNbr)++] = (DescPtr)

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro indiquant si la liste des descriptions est pleine					*/
/*--------------------------------------------------------------------------*/
#define Prf_DescListFull(PrfPtr)\
((PrfPtr)->MaxDescNbr == (PrfPtr)->DescNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la description No DescIndex a partir de 0				*/
/*--------------------------------------------------------------------------*/
#define Prf_DescNth(PrfPtr, DescIndex)\
((PrfPtr)->DescList[(DescIndex)])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de descriptions								*/
/*--------------------------------------------------------------------------*/
#define Prf_DescNbr(PrfPtr)\
((PrfPtr)->DescNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'un profil													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfPtr					| Profil							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Prf(TPrfPtr PrfPtr);

/*===============================================*/
/* Manipulation des donnees du fichier de profil */
/*===============================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction des donnees du fichier de profil							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Id						| Identificateur du profil			*/
/*			| De						| Description du profil				*/
/*			| NbrAc						| Nombre Prosite du profil			*/
/*			| PrfPtr					| Profil							*/
/* Sortie:	| I_PrfFileData				| Donnees du fichier de profil		*/
/* Erreur:	| I_PrfFileData=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TPrfFileDataPtr I_PrfFileData(TWordPtr Id, TSentPtr De, TWordPtr NbrAc,
TPrfPtr PrfPtr);

/*--------------------------------------------------------------------------*/
/* Destruction des donnees du fichier de profil								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfFileDataPtr			| Donnees du fichier de profil		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PrfFileData(TPrfFileDataPtr PrfFileDataPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant l'identificateur des donnees du profil					*/
/*--------------------------------------------------------------------------*/
#define PrfFileData_Id(PrfFileDataPtr)\
((PrfFileDataPtr)->Id)

/*--------------------------------------------------------------------------*/
/* Macro retournant la description des donnees du profil					*/
/*--------------------------------------------------------------------------*/
#define PrfFileData_De(PrfFileDataPtr)\
((PrfFileDataPtr)->De)

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre AC du profil									*/
/*--------------------------------------------------------------------------*/
#define PrfFileData_NbrAc(PrfFileDataPtr)\
((PrfFileDataPtr)->NbrAc)

/*--------------------------------------------------------------------------*/
/* Macro retournant le profil des donnees du profil							*/
/*--------------------------------------------------------------------------*/
#define PrfFileData_Prf(PrfFileDataPtr)\
((PrfFileDataPtr)->PrfPtr)

/*--------------------------------------------------------------------------*/
/* Impression des donnees du fichier de profil								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfFileDataPtr			| Donnees du fichier de profil		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_PrfFileData(TPrfFileDataPtr PrfFileDataPtr);

#endif
