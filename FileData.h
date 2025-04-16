/****************************************************************************/
/*																			*/
/*	But: Definition des donnees d'un fichier.								*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TPos								| 	-								*/
/*--------------------------------------------------------------------------*/
/*	TNbr								|	-								*/
/*--------------------------------------------------------------------------*/
/*	TWordSize							| 	-								*/
/*--------------------------------------------------------------------------*/
/*	TWordPtr							| 	IWord							*/
/*										|	Free_Word						*/
/*										|	Word_ToUpper					*/
/*										|	Str_To_Word						*/
/*										|	Word_CharNth					*/
/*										|	Print_Word						*/
/*										|	Print_FmtWord					*/
/*--------------------------------------------------------------------------*/
/*	TStrSize							| 	-								*/
/*--------------------------------------------------------------------------*/
/*	TStrPtr								| 	I_Str							*/
/*										|	Free_Str						*/
/*										|	Str_To_Str						*/
/*										|	Str_CharNth						*/
/*--------------------------------------------------------------------------*/
/*	TSentPtr							| 	I_Sent							*/
/*										|	Free_Sent						*/
/*										|	Str_To_Sent						*/
/*										|	Sent_CharNth					*/
/****************************************************************************/

#ifndef _FILEDATA_
#define _FILEDATA_

#include <stddef.h>
#include "GeneralTypes.h"

/************************/
/* DEFINITION DES TYPES */
/************************/

/*======================================================*/
/* Structure d'un nombre et d'un nombre entier positif	*/
/*======================================================*/

typedef unsigned long int TPos;
typedef double TNbr;

/*=====================*/
/* Structure d'un mot  */
/*=====================*/

typedef TCharStrSize TWordSize;
typedef TCharStr TWordPtr;

/*========================*/
/* Structure d'une chaine */
/*========================*/

typedef TCharStrSize TStrSize;
typedef TCharStr TStrPtr;

/*========================*/
/* Structure d'une phrase */
/*========================*/

typedef TCharStrSize TSentSize;
typedef TCharStr TSentPtr;

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

/*=======================*/
/* Manipulation des mots */
/*=======================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'initialisation d'un mot											*/
/*--------------------------------------------------------------------------*/
#define IWord(WordSize)\
((TWordPtr)(ICharStr(WordSize)))

/*--------------------------------------------------------------------------*/
/* Macro de destruction d'un mot											*/
/*--------------------------------------------------------------------------*/
#define Free_Word(WordPtr)\
Free_CharStr((TCharStr)WordPtr)

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro de conversion d'un mot en majuscules								*/
/*--------------------------------------------------------------------------*/
#define Word_ToUpper(WordPtr)\
((TWordPtr)(CharStr_ToUpper((TCharStr)WordPtr)))

/*--------------------------------------------------------------------------*/
/* Macro d'initialisation d'un mot a partir de n caracteres					*/
/*--------------------------------------------------------------------------*/
#define Str_To_Word(Str, CharNbr)\
((TWordPtr)(nChar_To_CharStr(Str, CharNbr)))

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant un caractere d'un mot indexe a partir de 1				*/
/*--------------------------------------------------------------------------*/
#define Word_CharNth(Word, CharIndex)\
(Word[(CharIndex) - 1])

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un mot												*/
/*--------------------------------------------------------------------------*/
#define Print_Word(WordPtr)\
Print_CharStr((TCharStr)WordPtr)

/*--------------------------------------------------------------------------*/
/* Sortie d'un mot															*/
/*--------------------------------------------------------------------------*/
#define Out_Word(OutPutFile, WordPtr)\
fprintf(OutPutFile, "%-21s", (char*)WordPtr)

/*==========================*/
/* Manipulation des chaines */
/*==========================*/
	
/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'une chaine										*/
/*--------------------------------------------------------------------------*/
#define I_Str(StrSize)\
((TStrPtr)(I_CharStr((TCharStrSize)StrSize)))

/*--------------------------------------------------------------------------*/
/* Macro de destruction d'une chaine										*/
/*--------------------------------------------------------------------------*/
#define Free_Str(StrPtr)\
Free_CharStr((TCharStr)StrPtr)

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'une chaine a partir d'une chaine					*/
/*--------------------------------------------------------------------------*/
#define Str_To_Str(StrPtr, CharNbr)\
((TStrPtr)(nChar_To_CharStr(StrPtr, CharNbr)))

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'une chaine											*/
/*--------------------------------------------------------------------------*/
#define Print_Str(StrPtr)\
Print_CharStr((TCharStr)StrPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant un caractere d'une chaine indexe a partir de 0			*/
/*--------------------------------------------------------------------------*/
#define Str_CharNth(StrPtr, CharIndex)\
((StrPtr)[CharIndex])

/*==========================*/
/* Manipulation des phrases */
/*==========================*/
	
/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'une phrase										*/
/*--------------------------------------------------------------------------*/
#define I_Sent(SentSize)\
((TSentPtr)(I_CharStr((TCharStrSize)SentSize)))

/*--------------------------------------------------------------------------*/
/* Macro de destruction d'une phrase										*/
/*--------------------------------------------------------------------------*/
#define Free_Sent(SentPtr)\
Free_CharStr((TCharStr)SentPtr)

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'une phrase a partir d'une chaine					*/
/*--------------------------------------------------------------------------*/
#define Str_To_Sent(StrPtr, CharNbr)\
((TSentPtr)(nChar_To_CharStr(StrPtr, CharNbr)))

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant la longueur d'une phrase								*/
/*--------------------------------------------------------------------------*/
#define Sent_Length(SentPtr)\
((TSentSize)CharStr_Length((TCharStr)SentPtr))

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'une phrase											*/
/*--------------------------------------------------------------------------*/
#define Print_Sent(SentPtr)\
Print_CharStr((TCharStr)SentPtr)

/*--------------------------------------------------------------------------*/
/* Macro de sortie d'une phrase												*/
/*--------------------------------------------------------------------------*/
#define Out_Sent20(OutPutFile, SentPtr)\
{fprintf(OutPutFile, "%-20.20s",SentPtr);}

/*--------------------------------------------------------------------------*/
/* Macro retournant un caractere d'une phrase indexe a partir de 0			*/
/*--------------------------------------------------------------------------*/
#define Sent_CharNth(SentPtr, CharIndex)\
((SentPtr)[CharIndex])

#endif
