/****************************************************************************/
/*																			*/
/*	But: implementation des routines d'extraction des donnees d'une seq.	*/
/*																			*/
/****************************************************************************/

#include <stdlib.h>
#include <ctype.h>
#include "SeqExtr.h"

/*=======================================*/
/* Extraction des donnees d'une sequence */
/*=======================================*/

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
TSeqExtrPtr I_SeqExtr(TSeqFileDataPtr SeqFileDataPtr, TAlphPtr AlphPtr)
{
	TSeqExtrPtr SeqExtrPtr;
	
	SeqExtrPtr = (TSeqExtrPtr)malloc(sizeof(TSeqExtr));
	if (!SeqExtrPtr) {
		/* Erreur d'allocation */
		return NULL;
	}
	SeqExtrPtr->SeqFileDataPtr = SeqFileDataPtr;
	SeqExtrPtr->AlphPtr = AlphPtr;
	return SeqExtrPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction des donnees d'extractions									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqExtr					| Donnees d'extraction				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SeqExtr(TSeqExtrPtr SeqExtrPtr)
{
	free(SeqExtrPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Extraction de l'identificateur de la sequence							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| SeqExtr_Id				| Identificateur de la sequence		*/
/* Erreur:	| SeqExtr_Id=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TId SeqExtr_Id(TSeqExtrPtr SeqExtrPtr)
{
	TId Id;
	
	Id = Str_To_Id((char*)SeqFileData_Id(SeqExtr_SeqFileData(SeqExtrPtr)));
	if (!Id) {
		/* Erreur d'allocation */
		return NULL;
	}
	return Id;
}

/*--------------------------------------------------------------------------*/
/* Extraction de la description de la sequence								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| SeqExtr_De				| Description de la sequence		*/
/* Erreur:	| SeqExtr_De=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TDe SeqExtr_De(TSeqExtrPtr SeqExtrPtr)
{
	TDe De;
	
	De = Str_To_De((char*)SeqFileData_De(SeqExtr_SeqFileData(SeqExtrPtr)));
	if (!De) {
		/* Erreur d'allocation */
		return NULL;
	}
	return De;
}

/*--------------------------------------------------------------------------*/
/* Extraction de la sequence de molecules									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| SeqExtr_MolSeq			| Sequence de molecules				*/
/* Erreur:	| SeqExtr_MolSeq=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TMolSeqPtr SeqExtr_MolSeq(TSeqExtrPtr SeqExtrPtr)
{
	TMolSeqPtr MolSeqPtr;
	TSeqPtr SeqPtr;
	TSeqCharIndex CharIndex;
	TSeqFileDataPtr SeqFileDataPtr;
	
	SeqFileDataPtr = SeqExtr_SeqFileData(SeqExtrPtr);
	SeqPtr = SeqFileData_Seq(SeqFileDataPtr);
	MolSeqPtr = I_MolSeq(Seq_CharNbr(SeqPtr));
	if (!MolSeqPtr) {
		/* Erreur d'allocation */
		return NULL;
	}
	for (CharIndex = 1; CharIndex <= Seq_CharNbr(SeqPtr); CharIndex++) {
		MolSeq_MolNth(MolSeqPtr, (TMolIndex)CharIndex) =
		Alph_LetPos(SeqExtr_Alph(SeqExtrPtr),
		(TLet)(toupper(Seq_CharNth(SeqPtr, CharIndex))));
	}
	return MolSeqPtr;
}

/*--------------------------------------------------------------------------*/
/* Extraction des donnees de la sequence									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| SeqExtr_SeqData			| Donnees de la sequence			*/
/* Erreur:	| SeqExtr_SeqData=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSeqDataPtr SeqExtr_SeqData(TSeqExtrPtr SeqExtrPtr)
{
	TId Id;
	TDe De;
	TAlphPtr SeqAlphPtr;
	TMolSeqPtr MolSeqPtr;
	TSeqDataPtr SeqDataPtr;
	TSeqFileDataPtr SeqFileDataPtr;
	
	SeqFileDataPtr = SeqExtr_SeqFileData(SeqExtrPtr);
	
	/* Extraction de l'ID */
	Id = SeqExtr_Id(SeqExtrPtr);
	if (!Id) {
		/* Erreur d'allocation */
		return NULL;
	}
	/* Extraction de la description */
	if (SeqFileData_De(SeqExtr_SeqFileData(SeqExtrPtr))) {
		De = SeqExtr_De(SeqExtrPtr);
		if (!De) {
			/* Erreur d'allocation */
			Free_Id(Id);
			return NULL;
		}
	}
	else {
		De = NULL;
	}
	/* Extraction de l'alphabet */
	SeqAlphPtr = Str_To_Alph((char*)SeqExtr_Alph(SeqExtrPtr));
	if (!SeqAlphPtr) {
		/* Erreur d'allocation */
		Free_Id(Id);
		Free_Id(De);
		return NULL;
	}
	/* Extraction de la sequence */
	MolSeqPtr = SeqExtr_MolSeq(SeqExtrPtr);
	if (!MolSeqPtr) {
		/* Erreur d'allocation */
		Free_Id(Id);
		Free_Id(De);
		Free_Alph(SeqAlphPtr);
		return NULL;
	}
	/* Construction des donnees de la sequence */
	SeqDataPtr = I_SeqData(Id, De, SeqAlphPtr, MolSeqPtr);
	if (!SeqDataPtr) {
		/* Erreur d'allocation */
		Free_Id(Id);
		Free_Id(De);
		Free_Alph(SeqAlphPtr);
		Free_MolSeq(MolSeqPtr);
		return NULL;
	}
	return SeqDataPtr;
}
