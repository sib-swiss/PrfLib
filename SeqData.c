/********************************************************************************/
/*																				*/
/*	But: Implementation des routines de manipulation des donnees de profil		*/
/*																				*/
/********************************************************************************/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "SeqData.h"

/*******************************/
/* IMPLEMENTATION DES ROUTINES */
/*******************************/

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
TMolSeqPtr I_MolSeq(TMolIndex MolNbr)
{
	TMolSeqPtr MolSeqPtr;
	
	MolSeqPtr = (TMolSeqPtr)malloc(sizeof(TMolSeq));
	if (!MolSeqPtr) {
		return NULL;
	}
	MolSeqPtr->MolStr = (TMol*)calloc(MolNbr, sizeof(TMol));
	if (!(MolSeqPtr->MolStr)) {
		free(MolSeqPtr);
		return NULL;
	}
	MolSeqPtr->MolNbr = MolNbr;
	return MolSeqPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une chaine de molecules									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MolSeqPtr					| Sequence de molecules				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_MolSeq(TMolSeqPtr MolSeqPtr)
{
	free(MolSeqPtr->MolStr);
	free(MolSeqPtr);
}

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Conversion d'une sequence ADN dans son complement						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MolSeqPtr					| Sequence de molecules				*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| MolSeq_CplStrand			| Sequence convertie				*/
/* Erreur:	| MolSeq_CplStrand=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TMolSeqPtr MolSeq_CplStrand(TMolSeqPtr MolSeqPtr, TAlphPtr AlphPtr)
{
	TMolIndex MolIndex;		/* Index de molecule				*/
	TMolIndex MidMolIndex;	/* index milieu sequence			*/
	TMol *MolStr;			/* Chaine de molecule				*/
	TAlphSize AlphSize;		/* Taille de l'alphabet				*/
	TMol Mol1, Mol2;		/* Molecules temporaires			*/
	
	
	MolStr = MolSeq_MolStr(MolSeqPtr);
	MidMolIndex = MolSeq_MolNbr(MolSeqPtr)/2;
	AlphSize = Alph_Size(AlphPtr);

	for (MolIndex = 1; MolIndex <= MidMolIndex; MolIndex++) {
		Mol1 = MolStr_MolNth(MolStr, MolIndex);
		if (Mol1) Mol1 = AlphSize - Mol1 + 1;
		Mol2 = MolStr_MolNth(MolStr, MolSeq_MolNbr(MolSeqPtr) - MolIndex + 1);
		if (Mol2) Mol2 = AlphSize - Mol2 + 1;
		MolStr_PutMolNth(MolStr, MolIndex, Mol2);
		MolStr_PutMolNth(MolStr, MolSeq_MolNbr(MolSeqPtr) - MolIndex + 1,
		Mol1);
	}
	if (MidMolIndex*2 < MolSeq_MolNbr(MolSeqPtr)) {
		Mol1 = MolStr_MolNth(MolStr, MolIndex);
		if (Mol1) {
			Mol1 = AlphSize - Mol1 + 1;
			MolStr_PutMolNth(MolStr, MolIndex, Mol1);
		}
	}
	return MolSeqPtr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une sequence de molecules									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MolSeqPtr					| Sequence de molecules				*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_MolSeq(TMolSeqPtr MolSeqPtr, TAlphPtr AlphPtr)
{
	TBoolean Over = FALSE;
	TMolIndex MolIndex = 1;
	TMolIndex MolIndex2;
	TMolIndex BlocIndex;
	
	while (!Over) {
		printf("%s", "     ");
		for (BlocIndex = 1; BlocIndex <= 6; BlocIndex++) {
			for (MolIndex2 = 1; MolIndex2 <= 10; MolIndex2++) {
				if (MolIndex <= MolSeq_MolNbr(MolSeqPtr)) {
					Print_Mol(MolSeq_MolNth(MolSeqPtr, MolIndex), AlphPtr);
					MolIndex++;
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
TSeqDataPtr I_SeqData(TId Id, TDe De, TAlphPtr AlphPtr, TMolSeqPtr MolSeqPtr)
{
	TSeqDataPtr SeqDataPtr;
	
	SeqDataPtr = (TSeqDataPtr)malloc(sizeof(TSeqData));
	if (!SeqDataPtr) {
		return NULL;
	}
	SeqDataPtr->Id = Id;
	SeqDataPtr->De = De;
	SeqDataPtr->AlphPtr = AlphPtr;
	SeqDataPtr->MolSeqPtr = MolSeqPtr;
	return SeqDataPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction des donnees d'une sequence									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqDataPtr				| Donnees de la sequence			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_SeqData(TSeqDataPtr SeqDataPtr)
{
	Free_Id(SeqDataPtr->Id);
	if (SeqDataPtr->De) Free_De(SeqDataPtr->De);
	Free_Alph(SeqDataPtr->AlphPtr);
	Free_MolSeq(SeqDataPtr->MolSeqPtr);
	free(SeqDataPtr);
}


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
TAlphPtr SeqData_NewAlph(TSeqDataPtr SeqDataPtr, TAlphPtr NewAlphPtr)
{
	TMol* MolStr;			/* La chaine de la sequence				*/
	TMolIndex MolNbr;		/* Le nombre de molecule				*/
	TMolIndex MolIndex;		/* Index de molelule					*/
	TAlphPtr AlphPtr;		/* Alphabet de la sequence				*/
	TAlphPtr TheNewAlphPtr;	/* Nouvel alphabet de la sequence		*/
	TAlphSize LetIndex;		/* Index des lettres dans l'alphabet	*/
	TMol *Table;			/* Table de conversion de molecules		*/
	
	MolStr = MolSeq_MolStr(SeqData_MolSeq(SeqDataPtr));
	MolNbr = MolSeq_MolNbr(SeqData_MolSeq(SeqDataPtr));
	AlphPtr = SeqData_Alph(SeqDataPtr);
	/* Allocation de la table */
	Table = (TMol*)calloc((size_t)Alph_Size(AlphPtr) + 1, sizeof(TMol));
	if (!Table) {
		/* Erreur d'allocation */
		return NULL;
	}
	/* Construction de la table */
	Table[0] = (TMol)0;
	for (LetIndex = 1; LetIndex <= Alph_Size(AlphPtr); LetIndex++) {
		Table[(size_t)LetIndex] = Alph_LetPos(NewAlphPtr,
		Alph_LetNth(AlphPtr, LetIndex));
	}
	for (MolIndex = 1; MolIndex <= MolNbr; MolIndex++) {
		MolStr_MolNth(MolStr, MolIndex) =
		Table[(size_t)MolStr_MolNth(MolStr, MolIndex)];
	}
	/* Destruction de la table */
	free(Table);
	/* Changement d'alphabet */
	/* Creation du nouvel alphabet */
	TheNewAlphPtr = Clone_Alph(NewAlphPtr);
	if (!TheNewAlphPtr) {
		/* Erreur d'allocation */
		return NULL;
	}	
	/* Destruction de l'ancien alphabet */
	Free_Alph(AlphPtr);
	/* Insertion du nouvel alphabet dans la sequence */
	SeqData_Alph(SeqDataPtr) = TheNewAlphPtr;
	return AlphPtr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression des donnees d'une sequence									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| SeqDataPtr				| Donnees de la sequence			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_SeqData(TSeqDataPtr SeqDataPtr)
{
	printf("Sequence ID: ");
	Print_Id(SeqData_Id(SeqDataPtr)); printf("\n");
	printf("Sequence description: ");
	if (SeqData_De(SeqDataPtr)) Print_De(SeqData_De(SeqDataPtr));
	printf("\n");
	Print_MolSeq(SeqData_MolSeq(SeqDataPtr), SeqData_Alph(SeqDataPtr));
}


