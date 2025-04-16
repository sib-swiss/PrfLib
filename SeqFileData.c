/****************************************************************************/
/*																			*/
/*	But: Definition des routines de manipulation d'un profil				*/
/*																			*/
/****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "SeqFileData.h"

/*******************************/
/* IMPLEMENTATION DES ROUTINES */
/*******************************/

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
/* Sortie:	| I_Seq						| Seq							*/
/* Erreur:	| I_Seq=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSeqPtr I_Seq(TSeqCharIndex CharNbr)
{
	TSeqPtr SeqPtr;
	
	SeqPtr = (TSeqPtr)malloc(sizeof(TSeq));
	if (!SeqPtr) {
		/* Allocation memoire */
		return NULL;
	}
	SeqPtr->Str = (TChar*)calloc(CharNbr, sizeof(TChar));
	if (!(SeqPtr->Str)) {
		/* Allocation memoire */
		free(SeqPtr);
		return NULL;
	}
	SeqPtr->CharNbr = CharNbr;
	return SeqPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une sequence												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqPtr					| Sequence							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Seq(TSeqPtr SeqPtr)
{
	free(SeqPtr->Str);
	free(SeqPtr);
}

/*--------------------------------------------------------------------------*/
/* Redimensionnement d'une sequence											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqPtr					| Sequence							*/
/*			| NewCharNbr				| Nouvelle taille					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Seq_ResizeTo(TSeqPtr SeqPtr,TSeqCharIndex NewCharNbr)
{
	SeqPtr->Str = (TChar*)realloc(SeqPtr->Str, NewCharNbr*sizeof(TChar));
	SeqPtr->CharNbr = NewCharNbr;
}

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
void Print_Seq(TSeqPtr SeqPtr)
{
	TBoolean Over = FALSE;
	TSeqCharIndex CharIndex = 1;
	TSeqCharIndex CharIndex2;
	TSeqCharIndex BlocIndex;
	
	while (!Over) {
		printf("%s", "     ");
		for (BlocIndex = 1; BlocIndex <= 6; BlocIndex++) {
			for (CharIndex2 = 1; CharIndex2 <= 10; CharIndex2++) {
				if (CharIndex <= Seq_CharNbr(SeqPtr)) {
					Print_SeqChar(Seq_CharNth(SeqPtr, CharIndex));
					CharIndex++;
				} else {
					Over = TRUE;
					break;
				}
			}
			if (Over) break;
			printf("%c", ' ');
		}
		printf("\n");
	}
}

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
TSeqFileDataPtr I_SeqFileData(TWordPtr Id, TSentPtr De, TSeqPtr SeqPtr)
{
	TSeqFileDataPtr SeqFileDataPtr;
	
	SeqFileDataPtr = (TSeqFileDataPtr)malloc(sizeof(TSeqFileData));
	if (!SeqFileDataPtr) {
		/* Allocation memoire */
		return NULL;
	}
	SeqFileDataPtr->Id = Id;
	SeqFileDataPtr->De = De;
	SeqFileDataPtr->SeqPtr = SeqPtr;
	return SeqFileDataPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction des donnees du fichier de sequence							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqFileDataPtr			| Donnees du fichier de sequence	*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SeqFileData(TSeqFileDataPtr SeqFileDataPtr)
{
	Free_Word(SeqFileDataPtr->Id);
	if (SeqFileDataPtr->De) Free_Sent(SeqFileDataPtr->De);
	Free_Seq(SeqFileDataPtr->SeqPtr);
	free(SeqFileDataPtr);
}

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
void Print_SeqFileData(TSeqFileDataPtr SeqFileDataPtr)
{
	printf("Sequence ID: ");
	Print_Word(SeqFileData_Id(SeqFileDataPtr));
	printf("\n");
	printf("Sequence description: ");
	Print_Sent(SeqFileData_De(SeqFileDataPtr));
	printf("\n");
	Print_Seq(SeqFileData_Seq(SeqFileDataPtr));
}
