/****************************************************************************/
/*																			*/
/*	But: definition des routines d'extraction des donnees d'une sequence.	*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TSeqExtrPtr							| 	I_SeqExtr						*/
/*										|	Free_SeqExtr					*/
/*										|	SeqExtr_SeqFileData				*/
/*										|	SeqExtr_Alph					*/
/*										|	SeqExtr_Id						*/
/*										|	SeqExtr_De						*/
/*										|	SeqExtr_MolSeq					*/
/*										|	SeqExtr_SeqData					*/
/****************************************************************************/

#ifndef _SEQEXTR_
#define _SEQEXTR_

#include "SeqData.h"
#include "SeqFileData.h"

/**************************/
/* DEFINITION DES DONNEES */
/**************************/

/*====================================*/
/* Structure des donnees d'extraction */
/*====================================*/

typedef struct TSeqExtr {
	TSeqFileDataPtr SeqFileDataPtr;
	TAlphPtr AlphPtr;
} TSeqExtr;
typedef TSeqExtr *TSeqExtrPtr;

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

/*=====================================*/
/* Donnees d'extraction d'une sequence */
/*=====================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction des donnees d'extractions									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqFileDataPtr			| Donnees du fichier de sequence	*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| I_SeqExtr					| Donnees d'extraction				*/
/* Erreur:	| I_SeqExtr=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSeqExtrPtr I_SeqExtr(TSeqFileDataPtr SeqFileDataPtr, TAlphPtr AlphPtr);

/*--------------------------------------------------------------------------*/
/* Destruction des donnees d'extractions									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqExtr					| Donnees d'extraction				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SeqExtr(TSeqExtrPtr SeqExtrPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant les donnees du fichier des donnees d'extractions		*/
/*--------------------------------------------------------------------------*/
#define SeqExtr_SeqFileData(SeqExtrPtr)\
((SeqExtrPtr)->SeqFileDataPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant l'alphabet des donnees d'extractions					*/
/*--------------------------------------------------------------------------*/
#define SeqExtr_Alph(SeqExtrPtr)\
((SeqExtrPtr)->AlphPtr)

/*--------------------------------------------------------------------------*/
/* Extraction de l'identificateur de la sequence							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| SeqExtr_Id				| Identificateur de la sequence		*/
/* Erreur:	| SeqExtr_Id=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TId SeqExtr_Id(TSeqExtrPtr SeqExtrPtr);

/*--------------------------------------------------------------------------*/
/* Extraction de la description de la sequence								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| SeqExtr_De				| Description de la sequence		*/
/* Erreur:	| SeqExtr_De=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TDe SeqExtr_De(TSeqExtrPtr SeqExtrPtr);

/*--------------------------------------------------------------------------*/
/* Extraction de la sequence de molecules									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| SeqExtr_MolSeq			| Sequence de molecules				*/
/* Erreur:	| SeqExtr_MolSeq=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TMolSeqPtr SeqExtr_MolSeq(TSeqExtrPtr SeqExtrPtr);

/*--------------------------------------------------------------------------*/
/* Extraction des donnees de la sequence									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| SeqExtr_SeqData			| Donnees de la sequence			*/
/* Erreur:	| SeqExtr_SeqData=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSeqDataPtr SeqExtr_SeqData(TSeqExtrPtr SeqExtrPtr);

#endif
