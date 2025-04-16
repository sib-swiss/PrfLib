/****************************************************************************/
/*																			*/
/*	But: Implementation de la lecture d'un fichier FASTA de sequences.		*/
/*																			*/
/****************************************************************************/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ReadFASTAFile.h"

/*******************************/
/* IMPLEMENTATION DES ROUTINES */
/*******************************/

/*=====================================*/
/* Manipulation des donnees de lecture */
/*=====================================*/

/*==============================*/
/* IMPLEMENTATION  DES ROUTINES */
/*==============================*/

/*=====================================*/
/* Manipulation des donnees de lecture */
/*=====================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Retourne l'ID de la sequence de la ligne ID courante						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFASTAFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadFASTAFile_LineId		| ID de la sequence					*/
/* Erreur:	| ReadFASTAFile_LineId		| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RFF_WRD_EXP				| Mot attendu						*/
/*			| RFF_MEM_ERR				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TWordPtr ReadFASTAFile_LineId(TReadFASTAFilePtr ReadFASTAFilePtr,
TErrIndex *ErrIndexPtr)
{
	TWordPtr Id;
	TChar *CharPtr;

	/* Recherche du 1er caractere non visible */
	CharPtr = ReadFASTAFile_CurrentCharPtr(ReadFASTAFilePtr);	
	while ((*CharPtr != RFF_EOL) && (*CharPtr != RFF_TAB) &&
	(*CharPtr != RFF_SPACE) && (*CharPtr != 0)) {
		++CharPtr;
	}
	/* Retour vers le dernier '|' ou sur le '>' */
	do {
		--CharPtr;
	}
	while ((CharPtr != ReadFASTAFile_CurrentCharPtr(ReadFASTAFilePtr))
	&& (*CharPtr != '|'));
	/* Caractere suivant */
	++CharPtr;
	ReadFASTAFile_CurrentCharPtr(ReadFASTAFilePtr) = CharPtr;
	/* Lecture de l'ID */
	Id = ReadFASTAFile_Word(ReadFASTAFilePtr, ErrIndexPtr);
	if (!Id) {
		/* Une erreur de lecture de l'ID est survenue */
		/* Retour de l'erreur */
		return NULL;
	}
	*ErrIndexPtr = RFF_NO_ERROR;
	return Id;
}

/*--------------------------------------------------------------------------*/
/* Recherche le prochain ID d'une sequence dans le fichier					*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFASTAFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadFASTAFile_NextId		| ID de la sequence					*/
/* Erreur:	| ReadFASTAFile_NextId		| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RFF_ID_EXP_UEOF			| Lgne ID att., fin de fich. inatt.	*/
/*			| RFF_WRD_EXP				| Mot attendu						*/
/*			| RFF_MEM_ERR				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TWordPtr ReadFASTAFile_NextId(TReadFASTAFilePtr ReadFASTAFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TWordPtr Id;


	/* Saut a la prochaine ligne ID */
	do {
		if (!strncmp(ReadFASTAFile_CurrentCharPtr(ReadFASTAFilePtr), ">", 1)) {
			/* Une ligne ID a ete rencontree */
			/* Extraction de l'ID */
			ReadFASTAFile_NextChar(ReadFASTAFilePtr);
			Id = ReadFASTAFile_LineId(ReadFASTAFilePtr, ErrIndexPtr);
			if (!Id) {
				/* Erreur dans la lecture de l'ID */
				/* Renvoi de l'erreur */
				return NULL;
			}
			/* Un ID de sequence a ete lu */
			*ErrIndexPtr = RFF_NO_ERROR;
			return Id;
		}
		SearchResult = ReadFASTAFile_NextLine(ReadFASTAFilePtr);
		if (SearchResult == RFF_END_OF_FILE) {
			/* Fin de fichier inattendue */
			*ErrIndexPtr = RFF_ID_EXP_UEOF;
			return NULL;
		}
	}
	while (TRUE);
}

/*--------------------------------------------------------------------------*/
/* Retourne la description depuis le caractere courant						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFASTAFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadFASTAFile_LineDe		| Description						*/
/* Erreur:	| ErrIndex				 	| Index d'erreur != RPF_NO_ERROR =	*/
/*			| RFF_MEM_ERR				| Erreur allocation					*/
/*--------------------------------------------------------------------------*/
TSentPtr ReadFASTAFile_LineDe(TReadFASTAFilePtr ReadFASTAFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSentPtr De;

	/* Lecture de la description */
	De = ReadFASTAFile_Sent(ReadFASTAFilePtr, ErrIndexPtr);
	if (!De) {
		/* Une erreur de lecture de la description est survenue */
		/* Renvoi de l'erreur */
		return NULL;
	}
	/* Description lue */
	ReadFASTAFile_NextChar(ReadFASTAFilePtr);
	return De;
}

/*--------------------------------------------------------------------------*/
/* Lecture d'une sequence de la ligne courante								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFASTAFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadFASTAFile_LineSeq		| Sequence							*/
/* Erreurs:	| ReadFASTAFile_LineSeq		| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RFF_MEM_ERR				| Allocation memoire				*/
/*			| RFF_SEQ_LENGTH_OVF		| Longueurs trop grande				*/
/*--------------------------------------------------------------------------*/
TSeqPtr ReadFASTAFile_LineSeq(TReadFASTAFilePtr ReadFASTAFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TSeqCharIndex CurrentSeqLength;
	unsigned int CharIndex;
	unsigned int LineLength;
	TBoolean Over;
	TSeqPtr SeqPtr;
	
	/* la longueur de la sequence a ete lue */
	SeqPtr = I_Seq((TSeqCharIndex)RFF_MAX_SEQ_LENGTH);
	if (!SeqPtr) {
		/* Une erreur d'allocation est survenue */
		*ErrIndexPtr = RFF_MEM_ERR;
		return NULL;
	}
	CurrentSeqLength = 1;
	Over = FALSE;
	while (!Over) {
		/* Lecture des caracteres de la ligne */
		LineLength = strlen(ReadFASTAFile_CurrentCharPtr(ReadFASTAFilePtr));
		for (CharIndex = 0; CharIndex < LineLength; CharIndex++) {
			if (isalpha(*ReadFASTAFile_CurrentCharPtr(ReadFASTAFilePtr))) {
				/* Un caractere a ete trouve */
				if ((TPos)CurrentSeqLength > RFF_MAX_SEQ_LENGTH) {
					/* Longueur trop grande */
					Free_Seq(SeqPtr);
					*ErrIndexPtr = RFF_SEQ_LENGTH_OVF;
					return NULL;
				}
				Seq_CharNth(SeqPtr, CurrentSeqLength) =
				(TChar)*ReadFASTAFile_CurrentCharPtr(ReadFASTAFilePtr);
				CurrentSeqLength++;
			}
			ReadFASTAFile_NextChar(ReadFASTAFilePtr);
		}
		SearchResult = ReadFASTAFile_NextLine(ReadFASTAFilePtr);
		if (SearchResult == RFF_END_OF_FILE) {
			/* Fin de fichier atteinte */
			Over = TRUE;
		}
		if (!strncmp(ReadFASTAFile_CurrentCharPtr(ReadFASTAFilePtr), ">", 1)) {
			/* Fin de la sequence atteinte */
			Over = TRUE;
		}
	}
	/* Sequence lue */
	/* Reajustage de la taille de la sequence */
	Seq_ResizeTo(SeqPtr, --CurrentSeqLength);
	*ErrIndexPtr = RFF_NO_ERROR;
	return SeqPtr;
}

/*--------------------------------------------------------------------------*/
/* Lecture des donnees du fichier de sequences								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFASTAFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadFASTAFile_SeqFileData	| donnees du fichier de sequence	*/
/* Erreurs:	| ReadFASTAFile_SeqFileData	| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RFF_ID_EXP_UEOF			| Lgne ID att., fin de fich. inatt.	*/
/*			| RFF_WRD_EXP				| Mot attendu						*/
/*			| RFF_MEM_ERR				| Allocation memoire				*/
/*			| RFF_SQ_EXP_UEOF			| Seq. att., fin de fich. inatt.	*/
/*			| RFF_SEQ_LENGTH_OVF		| Longueurs trop grande				*/
/*--------------------------------------------------------------------------*/
TSeqFileDataPtr ReadFASTAFile_SeqFileData(TReadFASTAFilePtr
ReadFASTAFilePtr, TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TWordPtr Id;
	TSentPtr De;
	TSeqPtr SeqPtr;
	TSeqFileDataPtr SeqFileDataPtr;
	
	/* Lecture de l'identificateur */
	Id = ReadFASTAFile_NextId(ReadFASTAFilePtr, ErrIndexPtr);
	if (!Id) {
		/* Une erreur est survenue */
		/* Renvoie l'erreur */
		return NULL;
	}
	/* Saut des blancs */
	SearchResult = ReadFASTAFile_JumpBlanks(ReadFASTAFilePtr);
	if (SearchResult == RFF_CHAR_FND) {
		/* Un caractere a ete trouve -> lecture description */
		De = ReadFASTAFile_LineDe(ReadFASTAFilePtr, ErrIndexPtr);
		if (*ErrIndexPtr != RFF_NO_ERROR) {
			/* Une erreur est survenue */
			Free_Word(Id);
			return NULL;
		}
	}
	else {
		/* Desciption nulle */
		De = NULL;
	}
	/* Saut d'une ligne */
	SearchResult = ReadFASTAFile_NextLine(ReadFASTAFilePtr);
	if (SearchResult == RFF_END_OF_FILE) {
		/* Fin de fichier atteinte */
		Free_Word(Id);
		if (De) Free_Sent(De);
		*ErrIndexPtr = RFF_SQ_EXP_UEOF;
		return NULL;
	}
	/* Lecture de la sequence */
	SeqPtr = ReadFASTAFile_LineSeq(ReadFASTAFilePtr, ErrIndexPtr);
	if (!SeqPtr) {
		/* La lecture de la sequence a echoue */
		Free_Word(Id);
		if (De) Free_Sent(De);
		return NULL;
	}
	/* Construction des donnees de profil du fichier */
	SeqFileDataPtr = I_SeqFileData(Id, De, SeqPtr);
	if (!SeqFileDataPtr) {
		/* L'initialisation a echoue */
		Free_Word(Id);
		if (De) Free_Sent(De);
		Free_Seq(SeqPtr);
		*ErrIndexPtr = RFF_MEM_ERR;
		return NULL;
	}
	*ErrIndexPtr = RFF_NO_ERROR;
	return SeqFileDataPtr;
}
