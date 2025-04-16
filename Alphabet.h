/****************************************************************************/
/*																			*/
/*	But: Definition des donnees d'un alphabet			.					*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TAlphSize							| 	-								*/
/*--------------------------------------------------------------------------*/
/*	TLet								|	Print_Let						*/
/*--------------------------------------------------------------------------*/
/*	TAlph								| 	I_Alph							*/
/*										|	Free_Alph						*/
/*										|	Clone_Alph						*/
/*										|	Str_To_Alph						*/
/*										|	Alph_LetPos						*/
/*										|	Print_Alph						*/
/*										|	Alph_LetNth						*/
/*										|	Alph_Size						*/
/****************************************************************************/

#ifndef _ALPHABET_
#define _ALPHABET_

#include <string.h>
#include <stddef.h>
#include "GeneralTypes.h"

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*==============================*/
/* Chaines standards d'alphabet */
/*==============================*/

#define AL_STD_PROT	"ACDEFGHIKLMNPQRSTVWY"
#define AL_STD_ADN	"ACGT"

/**************************/
/* DEFINITION DES DONNEES */
/**************************/

/*=================================*/
/* Type de la taille d'un alphabet */
/*=================================*/

typedef TCharStrSize TAlphSize;

/*===================*/
/* Type d'une lettre */
/*===================*/

typedef char TLet;

/*====================*/
/* Type d'un alphabet */
/*====================*/

typedef TCharStr TAlphPtr;

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

/*==========================*/
/* Manipulation des lettres */
/*==========================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'une lettre											*/
/*--------------------------------------------------------------------------*/
#define Print_Let(Let)\
Print_Char((TChar)Let)

/*============================*/
/* Manipulation des alphabets */
/*============================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'un alphabet										*/
/*--------------------------------------------------------------------------*/
#define I_Alph(AlphSize)\
((TAlphPtr)(ICharStr((TCharStrSize)AlphSize)))

/*--------------------------------------------------------------------------*/
/* Macro de destruction d'un alphabet										*/
/*--------------------------------------------------------------------------*/
#define Free_Alph(AlphPtr)\
Free_CharStr((TCharStr)AlphPtr)

/*--------------------------------------------------------------------------*/
/* Macro de clonage d'un alphabet											*/
/*--------------------------------------------------------------------------*/
#define Clone_Alph(AlphPtr)\
((TAlphPtr)(Str_To_CharStr((char*)AlphPtr)))

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction d'un alphabet a partir d'une chaine				*/
/*--------------------------------------------------------------------------*/
#define Str_To_Alph(Str)\
((TAlphPtr)(Str_To_CharStr(Str)))

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Position d'une lettre dans l'alphabet a partir de 1						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlphPtr					| Alphabet							*/
/*			| Let						| Lettre							*/
/* Sortie:	| Alph_LetPos				| Position de la lettre				*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TAlphSize Alph_LetPos(TAlphPtr AlphPtr, TLet Let);

/*--------------------------------------------------------------------------*/
/* Macro d'impression de l'alphabet											*/
/*--------------------------------------------------------------------------*/
#define Print_Alph(AlphPtr)\
Print_CharStr((TCharStr)AlphPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la lettre No LetterIndex a partir de 1					*/
/*--------------------------------------------------------------------------*/
#define Alph_LetNth(AlphPtr, LetIndex)\
((AlphPtr)[(LetIndex) - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant la taille de l'alphabet									*/
/*--------------------------------------------------------------------------*/
#define Alph_Size(AlphPtr)\
((TAlphSize)strlen(AlphPtr))

#endif
