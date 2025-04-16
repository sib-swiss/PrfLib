/****************************************************************************/
/*																			*/
/*	But: Definition des types generaux.										*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TBoolean							| 	-								*/
/*--------------------------------------------------------------------------*/
/*	TCharStrSize						|	-								*/
/*--------------------------------------------------------------------------*/
/*	TChar								|	Print_Char						*/
/*--------------------------------------------------------------------------*/
/*	TCharStr							|	I_CharStr						*/
/*										|	Free_CharStr					*/
/*										|	nChar_To_CharStr				*/
/*										|	Str_To_CharStr					*/
/*										|	Print_CharStr					*/
/*--------------------------------------------------------------------------*/
/*	TText								|	Free_Text						*/
/*										|	Str_To_Text						*/
/*										|	Print_Text						*/
/*--------------------------------------------------------------------------*/
/*	TId									|	Free_Id							*/
/*										|	Str_To_Id						*/
/*										|	Print_Id						*/
/*										|	Out_SeqId						*/
/*										|	Out_PrfId						*/
/*--------------------------------------------------------------------------*/
/*	ListPtr								|	I_List							*/
/*										|	Free_List						*/
/*										|	Resize_List						*/
/*										|	List_AddPtr						*/
/*										|	List_AddIndexPtr				*/
/*										|	List_PtrNbr						*/
/*										|	List_MaxPtrNbr					*/
/*										|	List_PtrNth						*/
/*										|	List_Full						*/
/*										|	List_Complete					*/
/****************************************************************************/

#ifndef _GENERALTYPES_
#define _GENERALTYPES_

#include <stddef.h>
#include <stdio.h>

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*=======================*/
/* Constantes booleennes */
/*=======================*/

#define TRUE 	1
#define FALSE	0

/************************/
/* DEFINITION DES TYPES */
/************************/

/*===================*/
/* Type d'un booleen */
/*===================*/

typedef unsigned char TBoolean;

/*==============================================*/
/* Type de la taille d'une chaine de caracteres */
/*==============================================*/

typedef unsigned int TCharStrSize;

/*=====================*/
/* Type d'un caractere */
/*=====================*/

typedef char TChar;

/*=================================*/
/* Type d'une chaine de caracteres */
/*=================================*/

typedef TChar *TCharStr;

/*=================*/
/* Type d'un texte */
/*=================*/

typedef TCharStr TText;

/*==========================*/
/* Type d'un identificateur */
/*==========================*/

typedef TCharStr TId;

/*==================================*/
/* Type d'une chaine de description */
/*==================================*/

typedef TCharStr TDe;

/*===========================*/
/* Type d'un index d'element */
/*===========================*/

typedef unsigned int TPtrIndex;

/*=======================*/
/* Structure d'une liste */
/*=======================*/

typedef struct TList {
	void **PtrArray;		/* Liste d'elements			*/
	TPtrIndex PtrNbr;		/* Nombre d'elements		*/
	TPtrIndex MaxPtrNbr;	/* Nombre max. d'elements	*/
} TList;
typedef TList *TListPtr;

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

/*===========================*/
/* Manipulation des booleens */
/*===========================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un booleens											*/
/*--------------------------------------------------------------------------*/
#define Print_Boolean(Boolean)\
printf("%s", Boolean ? "TRUE" : "FALSE")

/*=============================*/
/* Manipulation des caracteres */
/*=============================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un caractere										*/
/*--------------------------------------------------------------------------*/
#define Print_Char(Char)\
printf("%c", Char)

/*========================================*/
/* Manipulation des chaines de caracteres */
/*========================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une chaine de caracteres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CharStrSize				| Taille de la chaine				*/
/* Sortie:	| I_CharStr					| Chaine							*/
/* Erreur:	| I_CharStr=NULL			| Erreur d'allocation				*/
/*--------------------------------------------------------------------------*/
TCharStr I_CharStr(TCharStrSize CharStrSize);

/*--------------------------------------------------------------------------*/
/* Destruction d'une chaine de caracteres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CharStr					| Chaine							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_CharStr(TCharStr CharStr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une chaine a partir de n caracteres						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CharStr					| Chaine							*/
/* Sortie:	| CharStr_ToUpper			| Chaine convertie					*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TCharStr CharStr_ToUpper(TCharStr CharStr);

/*--------------------------------------------------------------------------*/
/* Construction d'une chaine a partir de n caracteres						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| String					| Chaine							*/
/*			| CharNbr					| Nbr de car a prendre de la chaine	*/
/* Sortie:	| nChar_To_CharStr			| Chaine							*/
/* Erreur:	| nChar_To_CharStr=NULL		| Erreur d'allocation				*/
/*--------------------------------------------------------------------------*/
TCharStr nChar_To_CharStr(char *String, unsigned int CharNbr);

/*--------------------------------------------------------------------------*/
/* Construction d'une chaine a partir d'une chaine							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Str						| Chaine							*/
/* Sortie:	| Str_To_CharStr			| Chaine							*/
/* Erreur:	| Str_To_CharStr=NULL		| Erreur d'allocation				*/
/*--------------------------------------------------------------------------*/
TCharStr Str_To_CharStr(char *Str);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant la longueur d'une chaine								*/
/*--------------------------------------------------------------------------*/
#define CharStr_Length(CharStr)\
((TCharStrSize)strlen((char*)(CharStr)))

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'une chaine											*/
/*--------------------------------------------------------------------------*/
#define Print_CharStr(CharStr)\
printf("%s", CharStr)

/*=========================*/
/* Manipulation des textes */
/*=========================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de destruction d'un texte											*/
/*--------------------------------------------------------------------------*/
#define Free_Text(Text)\
Free_CharStr((TCharStr)Text)

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'un texte											*/
/*--------------------------------------------------------------------------*/
#define Str_To_Text(Str)\
((TText)(Str_To_CharStr(Str)))

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un texte											*/
/*--------------------------------------------------------------------------*/
#define Print_Text(Text)\
Print_CharStr((TCharStr)Text)

/*==================================*/
/* Manipulation des identificateurs */
/*==================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de destruction d'un identificateur									*/
/*--------------------------------------------------------------------------*/
#define Free_Id(Id)\
Free_CharStr((TCharStr)Id)

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'un identificateur a partir d'une chaine			*/
/*--------------------------------------------------------------------------*/
#define Str_To_Id(Str)\
((TId)(Str_To_CharStr(Str)))

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un identificateur									*/
/*--------------------------------------------------------------------------*/
#define Print_Id(Id)\
printf("%s", (char*)Id)

/*--------------------------------------------------------------------------*/
/* Macro d'envoi d'un identificateur de sequence							*/
/*--------------------------------------------------------------------------*/
#define Out_SeqId(OutputFile, Id)\
fprintf(OutputFile, "%-13.13s", (char*)Id)

/*--------------------------------------------------------------------------*/
/* Macro d'envoi d'un identificateur de profil								*/
/*--------------------------------------------------------------------------*/
#define Out_PrfId(OutputFile, Id)\
fprintf(OutputFile, "%-21.21s", (char*)Id)

/*=========================================*/
/* Manipulation des chaines de description */
/*=========================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de destruction d'une description									*/
/*--------------------------------------------------------------------------*/
#define Free_De(De)\
Free_CharStr((TCharStr)De)

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'une description a partir d'une chaine			*/
/*--------------------------------------------------------------------------*/
#define Str_To_De(Str)\
((TDe)(Str_To_CharStr(Str)))

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macros d'impression d'une description                                    */
/*--------------------------------------------------------------------------*/
#define Print_De(De)\
{printf("%s", De);}

/*--------------------------------------------------------------------------*/
/* Macros d'envoi d'une description											*/
/*--------------------------------------------------------------------------*/
#define Out_De20(OutputFile, De)\
{fprintf(OutputFile, "%-20.20s", (char*)De);}
#define Out_De21(OutputFile, De)\
{fprintf(OutputFile, "%-21.21s", (char*)De);}
#define Out_De34(OutputFile, De)\
{fprintf(OutputFile, "%-34.34s", (char*)De);}
#define Out_De26(OutputFile, De)\
{fprintf(OutputFile, "%-26.26s", (char*)De);}
#define Out_De45(OutputFile, De)\
{fprintf(OutputFile, "%-45.45s", (char*)De);}
#define Out_De53(OutputFile, De)\
{fprintf(OutputFile, "%-53.53s", (char*)De);}

/*=========================*/
/* Manipulation des listes */
/*=========================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une liste													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MaxPtrNbr					| Nombre maximum d'elements			*/
/* Sortie:	| I_List					| Liste								*/
/* Erreur:	| I_List=NULL				| Erreur d'allocation				*/
/*--------------------------------------------------------------------------*/
TListPtr I_List(TPtrIndex MaxPtrNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une liste sans ses element									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ListPtr					| Liste								*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_List(TListPtr ListPtr);

/*--------------------------------------------------------------------------*/
/* Recalibration d'une liste												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ListPtr					| Liste								*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Resize_List(TListPtr ListPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'un element dans la liste									*/
/*--------------------------------------------------------------------------*/
#define List_AddPtr(ListPtr, Ptr)\
(ListPtr)->PtrArray[((ListPtr)->PtrNbr)++] = (Ptr)

/*--------------------------------------------------------------------------*/
/* Macro d'ajout d'un element indexe a partir de 0 dans la liste			*/
/*--------------------------------------------------------------------------*/
#define List_AddIndexPtr(ListPtr, Ptr, PtrIndex)\
{(ListPtr)->PtrArray[PtrIndex] = (Ptr);\
if (((PtrIndex) + 1) > (ListPtr)->PtrNbr) (ListPtr)->PtrNbr = (PtrIndex) + 1;}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre d'elements de la liste 						*/
/*--------------------------------------------------------------------------*/
#define List_PtrNbr(ListPtr)\
((ListPtr)->PtrNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre maximum d'elements de la liste 				*/
/*--------------------------------------------------------------------------*/
#define List_MaxPtrNbr(ListPtr)\
((ListPtr)->MaxPtrNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant un pointeur indexe a partir de 0 						*/
/*--------------------------------------------------------------------------*/
#define List_PtrNth(ListPtr, PtrIndex)\
((ListPtr)->PtrArray[PtrIndex])

/*--------------------------------------------------------------------------*/
/* Macro indiquant si la liste est pleine			 						*/
/*--------------------------------------------------------------------------*/
#define List_Full(ListPtr)\
((ListPtr)->PtrNbr == (ListPtr)->MaxPtrNbr)

/*--------------------------------------------------------------------------*/
/* Routine indiquant si la liste est complete								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ListPtr					| Liste								*/
/* Sortie:	| List_Complete				| Etat de la liste					*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TBoolean List_Complete(TListPtr ListPtr);

#endif
