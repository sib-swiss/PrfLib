/****************************************************************************/
/*																			*/
/*	But: Definition des donnees d'une sequence								*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TMol								| 	Print_Mol						*/
/*--------------------------------------------------------------------------*/
/*	TMolIndex							|	Print_MolIndex					*/
/*--------------------------------------------------------------------------*/
/*	TMolSeq								| 	I_MolSeq						*/
/*										|	Free_MolSeq						*/
/*										|	MolSeq_CplStrand				*/
/*										|	MolSeq_MolStr					*/
/*										|	MolStr_MolNth					*/
/*										|	MolSeq_MolNth					*/
/*										|	MolSeq_MolNbr					*/
/*										|	Print_MolSeq					*/
/*--------------------------------------------------------------------------*/
/*	TSeqData							|	I_SeqData						*/
/*										|	Free_SeqData					*/
/*										|	SeqData_NewAlph					*/
/*										|	SeqData_Id						*/
/*										|	SeqData_Alph					*/
/*										|	SeqData_MolSeq					*/
/*										|	Print_SeqData					*/
/****************************************************************************/

#ifndef _SEQDATA_
#define _SEQDATA_

#include <stddef.h>
#include "GeneralTypes.h"
#include "Alphabet.h"

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*===================*/
/* Index de molecule */
/*===================*/

#define SD_MOL_IDX_NOT_DEF UINT_MAX

/*==========*/
/* Molecule */
/*==========*/

#define SD_MOL_NOT_DEF 0

/**************************/
/* DEFINITION DES DONNEES */
/**************************/

/*=====================*/
/* Type d'une molecule */
/*=====================*/

typedef unsigned char TMol;

/*=============================*/
/* Type d'un index de molecule */
/*=============================*/

typedef unsigned int TMolIndex;

/*=======================================*/
/* Structure d'une sequence de molecules */
/*=======================================*/

typedef struct TMolSeq {
	TMol *MolStr;			/* Chaine				*/
	TMolIndex MolNbr;		/* Nombre de molecules	*/
} TMolSeq;
typedef TMolSeq *TMolSeqPtr;

/*======================================*/
/* Structure des donnees d'une sequence */
/*======================================*/

typedef struct TSeqData {
	TId Id;					/* ID de la sequence			*/
	TDe De;					/* Description de la sequence	*/
	TAlphPtr AlphPtr;		/* Alphabet						*/
	TMolSeqPtr MolSeqPtr;	/* Sequence de molecules		*/
} TSeqData;
typedef TSeqData *TSeqDataPtr;

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

/*============================*/
/* Manipulation des molecules */
/*============================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'une molecules										*/
/*--------------------------------------------------------------------------*/
#define Print_Mol(Mol, AlphPtr)\
printf("%c", Mol ? (char)Alph_LetNth(AlphPtr, (TAlphSize)Mol) : '-')

/*=====================================*/
/* Manipulation des index de molecules */
/*=====================================*/

/*============*/
/* Selecteurs */
/*============*/

/*--------------------------------------------------------------------------*/
/* Macro d'impression d'un index de molecule								*/
/*--------------------------------------------------------------------------*/
#define Print_MolIndex(MolIndex)\
{if (MolIndex == SD_MOL_IDX_NOT_DEF) printf("*"); else printf("%d", MolIndex);}

/*--------------------------------------------------------------------------*/
/* Macro de sortie d'un index de molecule									*/
/*--------------------------------------------------------------------------*/
#define Out_MolIndex(OutputFile, MolIndex)\
{if (MolIndex == SD_MOL_IDX_NOT_DEF) fprintf(OutputFile, "%6c", '*');\
else fprintf(OutputFile, "%6d", MolIndex);}

/*=========================================*/
/* Manipulation des sequences de molecules */
/*=========================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/
/*--------------------------------------------------------------------------*/
/* Construction d'une sequence de molecules									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MolNbr					| Nombre de molecules				*/
/* Sortie:	| I_MolSeq					| Sequence de molecules				*/
/* Erreur:	| I_MolSeq=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TMolSeqPtr I_MolSeq(TMolIndex MolNbr);
					
/*--------------------------------------------------------------------------*/
/* Destruction d'une chaine de molecules									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MolSeqPtr					| Sequence de molecules				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_MolSeq(TMolSeqPtr MolSeqPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Macro affectant une molecule de la chaine indexee a partir de 1			*/
/*--------------------------------------------------------------------------*/
#define MolStr_PutMolNth(MolStr, MolIndex, Mol)\
{(MolStr)[MolIndex - 1] = (Mol);}

/*--------------------------------------------------------------------------*/
/* Conversion d'une sequence ADN dans son complement						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MolSeqPtr					| Sequence de molecules				*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| MolSeq_CplStrand			| Sequence convertie				*/
/* Erreur:	| MolSeq_CplStrand=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TMolSeqPtr MolSeq_CplStrand(TMolSeqPtr MolSeqPtr, TAlphPtr AlphPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant la chaine de molecule									*/
/*--------------------------------------------------------------------------*/
#define MolSeq_MolStr(MolSeqPtr)\
((MolSeqPtr)->MolStr)

/*--------------------------------------------------------------------------*/
/* Macro retournant une molecule de la chaine indexee a partir de 1			*/
/*--------------------------------------------------------------------------*/
#define MolStr_MolNth(MolStr, MolIndex)\
((MolStr)[MolIndex - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant une molecule indexee a partir de 1						*/
/*--------------------------------------------------------------------------*/
#define MolSeq_MolNth(MolSeqPtr, MolIndex)\
((MolSeqPtr)->MolStr[MolIndex - 1])

/*--------------------------------------------------------------------------*/
/* Macro retournant le nombre de molecules									*/
/*--------------------------------------------------------------------------*/
#define MolSeq_MolNbr(MolSeqPtr)\
((MolSeqPtr)->MolNbr)

/*--------------------------------------------------------------------------*/
/* Impression d'une sequence de molecules									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MolSeqPtr					| Sequence de molecules				*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_MolSeq(TMolSeqPtr MolSeqPtr, TAlphPtr AlphPtr);

/*=======================================*/
/* Manipulation des donnees de sequences */
/*=======================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction des donnees d'une sequence									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Id						| Identificateur de la sequence		*/
/*			| De						| Description de la sequence		*/
/*			| AlphPtr					| Alphabet							*/
/*			| MolSeqPtr					| Sequence de molecules				*/
/* Sortie:	| I_SeqData					| Donnees du profil					*/
/* Erreur:	| I_SeqData=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSeqDataPtr I_SeqData(TId Id, TDe De, TAlphPtr AlphPtr, TMolSeqPtr MolSeqPtr);

/*--------------------------------------------------------------------------*/
/* Destruction des donnees d'une sequence									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqDataPtr				| Donnees de la sequence			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SeqData(TSeqDataPtr SeqDataPtr);

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Changement de l'alphabet d'une sequence									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqDataPtr				| Donnees de la sequence			*/
/*			| NewAlphPtr				| Nouvel alphabet					*/
/* Sortie:	| SeqData_NewAlphabet		| Nouvel alphabet					*/
/* Erreur:	| SeqData_NewAlphabet=NULL	| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TAlphPtr SeqData_NewAlph(TSeqDataPtr SeqDataPtr, TAlphPtr NewAlphPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant l'identificateur de la sequence							*/
/*--------------------------------------------------------------------------*/
#define SeqData_Id(SeqDataPtr)\
((SeqDataPtr)->Id)

/*--------------------------------------------------------------------------*/
/* Macro retournant la description de la sequence							*/
/*--------------------------------------------------------------------------*/
#define SeqData_De(SeqDataPtr)\
((SeqDataPtr)->De)

/*--------------------------------------------------------------------------*/
/* Macro retournant l'alphabet												*/
/*--------------------------------------------------------------------------*/
#define SeqData_Alph(SeqDataPtr)\
((SeqDataPtr)->AlphPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la sequence de molecules								*/
/*--------------------------------------------------------------------------*/
#define SeqData_MolSeq(SeqDataPtr)\
((SeqDataPtr)->MolSeqPtr)

/*--------------------------------------------------------------------------*/
/* Impression des donnees d'une sequence									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqDataPtr				| Donnees de la sequence			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_SeqData(TSeqDataPtr SeqDataPtr);

#endif
