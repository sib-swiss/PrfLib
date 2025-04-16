/****************************************************************************/
/*																			*/
/*	But: Definition des donnees d'un fichier de sequences.					*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TSeqCharIndex						|	-								*/
/*--------------------------------------------------------------------------*/
/*	TSeqChar							|	Print_SeqChar					*/
/*--------------------------------------------------------------------------*/
/*	TSeqPtr								|	I_Seq							*/
/*										|	Seq_ResizeTo					*/
/*										|	Free_Seq						*/
/*										|	Print_Seq						*/
/*--------------------------------------------------------------------------*/
/*	TSeqFileDataPtr						|	I_SeqFileData					*/
/*										|	Free_SeqFileData				*/
/*										|	Print_SeqFileData				*/
/*										|	SeqFileData_Id					*/
/*										|	SeqFileData_De					*/
/*										|	SeqFileData_Seq					*/
/****************************************************************************/

#ifndef _SEQFILEDATA_
#define _SEQFILEDATA_

#include <stddef.h>
#include <stdio.h>
#include "GeneralTypes.h"
#include "FileData.h"

/**************************/
/* DEFINITION DES DONNEES */
/**************************/

/*==========================================*/
/* Type d'un index de caractere de sequence */
/*==========================================*/

typedef unsigned int TSeqCharIndex;

/*=================================*/
/* Type d'un caractere de sequence */
/*=================================*/

typedef char TSeqChar;

/*==========================*/
/* Structure d'une sequence */
/*==========================*/

typedef struct TSeq {
	TSeqChar *Str;
	TSeqCharIndex CharNbr;
} TSeq;
typedef TSeq *TSeqPtr;

/*==============================================*/
/* Structure des donnees de sequence du fichier */
/*==============================================*/

typedef struct TSeqFileData {
	TWordPtr Id;
	TSentPtr De;
	TSeqPtr SeqPtr;
} TSeqFileData;
typedef TSeqFileData *TSeqFileDataPtr;


/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

/*==========================================*/
/* Manipulation des caracteres de sequences */
/*==========================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Affichage d'un caractere de sequence										*/
/*--------------------------------------------------------------------------*/
#define Print_SeqChar(SeqChar)\
{printf("%c", SeqChar);}

/*============================*/
/* Manipulation des sequences */
/*============================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/
	
/*--------------------------------------------------------------------------*/
/* Construction d'une sequence												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CharNbr					| Nombre de caracteres de la seq.	*/
/* Sortie:	| I_Seq						| Sequence							*/
/* Erreur:	| I_Seq=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSeqPtr I_Seq(TSeqCharIndex CharNbr);

/*--------------------------------------------------------------------------*/
/* Destruction d'une sequence												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqPtr					| Sequence							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Seq(TSeqPtr SeqPtr);

/*--------------------------------------------------------------------------*/
/* Redimensionnement d'une sequence											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqPtr					| Sequence							*/
/*			| NewCharNbr				| Nouvelle taille					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Seq_ResizeTo(TSeqPtr SeqPtr,TSeqCharIndex NewCharNbr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une sequence												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqPtr					| Sequence							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Seq(TSeqPtr SeqPtr);

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de caracteres de la sequence					*/
/*--------------------------------------------------------------------------*/
#define Seq_CharNbr(SeqPtr)\
((SeqPtr)->CharNbr)

/*--------------------------------------------------------------------------*/
/* Macro retournant un caractere indexe a partir de 1						*/
/*--------------------------------------------------------------------------*/
#define Seq_CharNth(SeqPtr, CharIndex)\
((SeqPtr)->Str[CharIndex - 1])

/*=================================================*/
/* Manipulation des donnees du fichier de sequence */
/*=================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction des donnees du fichier de sequence							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Id						| Identificateur de la sequence		*/
/*			| De						| Description de la sequence		*/
/*			| SeqPtr					| Sequence							*/
/* Sortie:	| I_SeqFileData				| Donnees du fichier de sequence	*/
/* Erreur:	| I_SeqFileData=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSeqFileDataPtr I_SeqFileData(TWordPtr Id, TSentPtr De, TSeqPtr SeqPtr);

/*--------------------------------------------------------------------------*/
/* Destruction des donnees du fichier de sequence							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqFileDataPtr			| Donnees du fichier de sequence	*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SeqFileData(TSeqFileDataPtr SeqFileDataPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression des donnees du fichier de sequence							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqFileDataPtr			| Donnees du fichier de sequence	*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_SeqFileData(TSeqFileDataPtr SeqFileDataPtr);

/*--------------------------------------------------------------------------*/
/* Retourne l'identificateur des donnees de la sequence						*/
/*--------------------------------------------------------------------------*/
#define SeqFileData_Id(SeqFileDataPtr)\
((SeqFileDataPtr)->Id)

/*--------------------------------------------------------------------------*/
/* Retourne la description des donnees de la sequence						*/
/*--------------------------------------------------------------------------*/
#define SeqFileData_De(SeqFileDataPtr)\
((SeqFileDataPtr)->De)

/*--------------------------------------------------------------------------*/
/* Retourne la sequence des donnees de la sequence							*/
/*--------------------------------------------------------------------------*/
#define SeqFileData_Seq(SeqFileDataPtr)\
((SeqFileDataPtr)->SeqPtr)

#endif
