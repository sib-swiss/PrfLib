/****************************************************************************/
/*																			*/
/*	But: Implementation de la lecture d'un fichier de profils.				*/
/*																			*/
/****************************************************************************/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ReadSeqFile.h"

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
/* Saute a la prochaine ligne significative du fichier						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadSeqFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadSeqFile_NextSignLine	| Resultat de la recherche =		*/
/*			| RSF_END_OF_FILE			| Fin de fichier atteinte			*/
/*			| RSF_END_OF_SEQ			| Fin de sequence atteinte			*/
/*			| RSF_SQ_LINE				| Ligne SQ trouvee					*/
/*			| RSF_ID_LINE				| Ligne ID trouvee					*/
/* Erreur:	| -							| 									*/
/*--------------------------------------------------------------------------*/
TSearchResult ReadSeqFile_NextSignLine(TReadSeqFilePtr ReadSeqFilePtr)
{
	TSearchResult SearchResult;
	
	do {
		SearchResult = ReadSeqFile_NextLine(ReadSeqFilePtr);
		if (SearchResult == RSF_END_OF_FILE) {
			/* Fin de fichier atteinte */
			return RSF_END_OF_FILE;
		}
		if (!strncmp(ReadSeqFile_CurrentCharPtr(ReadSeqFilePtr), "//", 2)) {
			ReadSeqFile_NextChar(ReadSeqFilePtr);
			ReadSeqFile_NextChar(ReadSeqFilePtr);
			return RSF_END_OF_SEQ;
		}
		else if (!strncmp(ReadSeqFile_CurrentCharPtr(ReadSeqFilePtr), "SQ", 2)) {
			ReadSeqFile_NextChar(ReadSeqFilePtr);
			ReadSeqFile_NextChar(ReadSeqFilePtr);
			return RSF_SQ_LINE;
		}
		else if (!strncmp(ReadSeqFile_CurrentCharPtr(ReadSeqFilePtr), "ID", 2)) {
			ReadSeqFile_NextChar(ReadSeqFilePtr);
			ReadSeqFile_NextChar(ReadSeqFilePtr);
			return RSF_ID_LINE;
		}
		else if (!strncmp(ReadSeqFile_CurrentCharPtr(ReadSeqFilePtr), "DE", 2)) {
			ReadSeqFile_NextChar(ReadSeqFilePtr);
			ReadSeqFile_NextChar(ReadSeqFilePtr);
			return RSF_DE_LINE;
		}
	}
	while (TRUE);
}

/*--------------------------------------------------------------------------*/
/* Retourne l'ID de la sequence de la ligne ID courante						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadSeqFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadSeqFile_LineId		| ID de la sequence					*/
/* Erreur:	| ReadSeqFile_LineId		| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RSF_WRD_EXP_UEOL			| Mot attendu, fin de ligne inatt.	*/
/*			| RSF_WRD_EXP_UEOF			| Mot att., fin de fichier inatt.	*/
/*			| RSF_WRD_EXP				| Mot attendu						*/
/*			| RSF_MEM_ERR				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TWordPtr ReadSeqFile_LineId(TReadSeqFilePtr ReadSeqFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TWordPtr Id;


	/* On saute les blancs */
	SearchResult = ReadSeqFile_JumpBlanks(ReadSeqFilePtr);
	if (SearchResult == RSF_END_OF_LINE) {
		*ErrIndexPtr = RSF_WRD_EXP_UEOL;
		return NULL;
	}
	if (SearchResult == RSF_END_OF_FILE) {
		*ErrIndexPtr = RSF_WRD_EXP_UEOF;
		return NULL;
	}
	/* Un caractere a ete trouve */
	/* Lecture de l'ID */
	Id = ReadSeqFile_Word(ReadSeqFilePtr, ErrIndexPtr);
	if (!Id) {
		/* Une erreur de lecture de l'ID est survenue */
		return NULL;
	}
	*ErrIndexPtr = RSF_NO_ERROR;
	return Id;
}

/*--------------------------------------------------------------------------*/
/* Recherche le prochain ID d'une sequence dans le fichier					*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadSeqFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadSeqFile_NextId		| ID de la sequence					*/
/* Erreur:	| ReadSeqFile_NextId		| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RSF_ID_EXP_UEOF			| Lgne ID att., fin de fich. inatt.	*/
/*			| RSF_WRD_EXP_UEOL			| Mot attendu, fin de ligne inatt.	*/
/*			| RSF_WRD_EXP_UEOF			| Mot att., fin de fichier inatt.	*/
/*			| RSF_WRD_EXP				| Mot attendu						*/
/*			| RSF_MEM_ERR				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TWordPtr ReadSeqFile_NextId(TReadSeqFilePtr ReadSeqFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TWordPtr Id;
	
	do {
		/* Saut a la ligne ID */
		SearchResult = ReadSeqFile_NextSignLine(ReadSeqFilePtr);
		if (SearchResult == RSF_END_OF_FILE) {
			/* Fin de fichier rencontree */
			*ErrIndexPtr = RSF_ID_EXP_UEOF;
			return NULL;
		}
		if (SearchResult == RSF_ID_LINE) {
			/* Une ligne ID a ete rencontree */
			/* Extraction de l'ID */
			Id = ReadSeqFile_LineId(ReadSeqFilePtr, ErrIndexPtr);
			if (!Id) {
				/* Erreur dans la lecture de l'ID */
				/* Renvoi de l'erreur */
				return NULL;
			}
			/* Un ID de sequence a ete lu */
			*ErrIndexPtr = RSF_NO_ERROR;
			return Id;
		}
	}
	while (TRUE);
}

/*--------------------------------------------------------------------------*/
/* Retourne la description de la ligne DE courante							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadSeqFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadSeqFile_LineDe		| Description						*/
/* Erreur:	| ErrIndex				 	| Index d'erreur != RPF_NO_ERROR =	*/
/*			| RSF_DESC_EXP_UEOL			| Desc. att. fin de ligne inatt.	*/
/*			| RSF_DESC_EXP_UEOF			| Desc. att. fin de fichier inatt.	*/
/*			| RSF_MEM_ERR				| Erreur allocation					*/
/*--------------------------------------------------------------------------*/
TSentPtr ReadSeqFile_LineDe(TReadSeqFilePtr ReadSeqFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TSentPtr De;
	
	/* On saute les blancs */
	SearchResult = ReadSeqFile_JumpBlanks(ReadSeqFilePtr);
	if (SearchResult == RSF_END_OF_LINE) {
		/* Fin de ligne inattendue */
		*ErrIndexPtr = RSF_DE_EXP_UEOL;
		return NULL;
	}
	if (SearchResult == RSF_END_OF_FILE) {
		/* Fin de fichier inattendue */
		*ErrIndexPtr = RSF_DE_EXP_UEOF;
		return NULL;
	}
	/* Un caractere a ete trouve */
	/* Lecture de la description */
	De = ReadSeqFile_Sent(ReadSeqFilePtr, ErrIndexPtr);
	if (!De) {
		/* Une erreur de lecture de la description est survenue */
		/* Renvoi de l'erreur */
		return NULL;
	}
	/* Description lue */
	ReadSeqFile_NextChar(ReadSeqFilePtr);
	*ErrIndexPtr = RSF_NO_ERROR;
	return De;
}

/*--------------------------------------------------------------------------*/
/* Recherche la prochaine description dans le fichier						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadSeqFilePtr			| Donnees de lecture				*/
/* Sortie:	| SearchResult				| Resultat de la recherche			*/
/*			| ReadSeqFile_NextDe		| Description						*/
/* Erreur:	| ErrIndex					| Index d'erreur != RPF_NO_ERROR =	*/
/*			| RSF_DE_EXP_UEOF			| Ligne DE att, fin de fich. inatt.	*/
/*			| RSF_DE_EXP				| Ligne DE attendue					*/
/*			| RSF_DESC_EXP_UEOL			| Desc. att. fin de ligne inatt.	*/
/*			| RSF_DESC_EXP_UEOF			| Desc att. fin de fichier inatt.	*/
/*			| RPF_MEM_ERR				| Erreur allocation					*/
/*--------------------------------------------------------------------------*/
TSentPtr ReadSeqFile_NextDe(TReadSeqFilePtr ReadSeqFilePtr, TSearchResult
*SearchResultPtr, TErrIndex *ErrIndexPtr)
{
	TSentPtr DeTab[RSF_DE_NBR];
	TSentPtr De;
	TSentPtr SentCharPtr;
	TLineIndex DeIndex;
	TLineIndex Index;
	TSentSize DeLength;
	
	
	/* Saut a la 1ere ligne DE */
	*SearchResultPtr = ReadSeqFile_NextSignLine(ReadSeqFilePtr);
	if (*SearchResultPtr == RSF_END_OF_FILE) {
		/* Fin de fichier atteinte */
		*ErrIndexPtr = RSF_DE_EXP_UEOF;
		return NULL;
	}
	if (*SearchResultPtr != RSF_DE_LINE) {
		/* Ligne DE attendue */
		*ErrIndexPtr = RSF_DE_EXP;
		return NULL;
	}
	
	DeIndex = 0;
	do {
		/* Lecture de la ligne */
		DeTab[DeIndex++] = ReadSeqFile_LineDe(ReadSeqFilePtr, ErrIndexPtr);
		if (*ErrIndexPtr != RSF_NO_ERROR) {
			/* Une erreur est survenue */
			for (Index = 0; Index < DeIndex; Index++) {
				Free_Sent(DeTab[Index]);
			}
			return NULL;
		}

		/* Prochaine ligne DE */
		*SearchResultPtr = ReadSeqFile_NextSignLine(ReadSeqFilePtr);
		if (*SearchResultPtr != RSF_DE_LINE) {
			/* La ligne n'est pas une ligne DE */
			/* Sortie de la boucle */
			break;
		}
		/* Une ligne DE a ete trouvee */
		if (DeIndex == RSF_DE_NBR) {
			/* Trop de lignes de description */
			for (Index = 0; Index < DeIndex; Index++) {
				Free_Sent(DeTab[Index]);
			}
			*ErrIndexPtr = RSF_DE_LINE_OVF;
			return NULL;
		}
	}
	while (TRUE);
	
	/* Construction de la description totale */
	DeLength = 0;
	for (Index = 0; Index < DeIndex; Index++) {
		DeLength += Sent_Length(DeTab[Index]);
	}
	DeLength += DeIndex - 1; /* Prevoir les blancs */
	/* Allocation de la phrase */
	De = I_Sent(DeLength);
	if (!De) {
		/* Erreur d'allocation */
		for (Index = 0; Index < DeIndex; Index++) {
			Free_Sent(DeTab[Index]);
		}
		*ErrIndexPtr = RSF_MEM_ERR;
		return NULL;
	}
	/* Copie des descriptions */
	SentCharPtr = De;
	for (Index = 0; Index < DeIndex; Index++) {
		/* Copie avec Caractere NULL (utile pour le dernier) */
		strcpy((char*)SentCharPtr, (char*)DeTab[Index]);
		SentCharPtr += Sent_Length(DeTab[Index]);
		/* Copie d'un blanc */
		if (Index < DeIndex - 1) *(SentCharPtr++) = ' ';
		Free_Sent(DeTab[Index]);
	}
	*ErrIndexPtr = RSF_NO_ERROR;
	return De;
}

/*--------------------------------------------------------------------------*/
/* Lecture d'une sequence de la ligne courante								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadSeqFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadSeqFile_LineSeq		| Sequence							*/
/* Erreurs:	| ReadSeqFile_LineSeq		| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RSF_WRD_EXP_UEOL			| Mot att. fin de ligne inatt.		*/
/*			| RSF_WRD_EXP_UEOF			| Mot att. fin de fichier inatt.	*/
/*			| RSF_WRD_EXP				| Mot attendu						*/
/*			| RSF_MEM_ERR				| Allocation memoire				*/
/*			| RSF_POS_EXP_UEOL			| Ent. pos. att. fin de li. inatt.	*/
/*			| RSF_POS_EXP_UEOF			| Ent. pos. att. fin de fi. inatt.	*/
/*			| RSF_POS_INT_EXP			| Entier positif attendu			*/
/*			| RSF_BAD_LENGTH			| Longueurs incompatibles			*/
/*--------------------------------------------------------------------------*/
TSeqPtr ReadSeqFile_LineSeq(TReadSeqFilePtr ReadSeqFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TPos SeqLength;
	TSeqCharIndex CurrentSeqLength;
	unsigned int CharIndex;
	unsigned int LineLength;
	TBoolean Over;
	TSeqPtr SeqPtr;
	TWordPtr SeqWord;
	
	/* On saute les blancs */
	SearchResult = ReadSeqFile_JumpBlanks(ReadSeqFilePtr);
	if (SearchResult == RSF_END_OF_LINE) {
		*ErrIndexPtr = RSF_WRD_EXP_UEOL;
		return NULL;
	}
	if (SearchResult == RSF_END_OF_FILE) {
		*ErrIndexPtr = RSF_WRD_EXP_UEOF;
		return NULL;
	}
	/* Un caractere est rencontre */
	/* Lecture du mot SEQUENCE */
	SeqWord = ReadSeqFile_Word(ReadSeqFilePtr, ErrIndexPtr);
	if (!SeqWord) {
		/* Une erreur de lecture est survenue */
		/* Renvoi de l'erreur */
		return NULL;
	}
	/* Conversion du mot en majuscule */
	SeqWord = Word_ToUpper(SeqWord);
	if (strcmp(SeqWord, "SEQUENCE")) {
		/* Le mot n'est pas SEQUENCE */
		*ErrIndexPtr = RSF_SEQ_EXP;
		Free_Word(SeqWord);
		return NULL;
	}
	/* Le mot SEQUENCE est trouve */
	Free_Word(SeqWord);
	/* On saute les blancs */
	SearchResult = ReadSeqFile_JumpBlanks(ReadSeqFilePtr);
	if (SearchResult == RSF_END_OF_LINE) {
		*ErrIndexPtr = RSF_POS_EXP_UEOL;
		return NULL;
	}
	if (SearchResult == RSF_END_OF_FILE) {
		*ErrIndexPtr = RSF_POS_EXP_UEOF;
		return NULL;
	}
	/* Un caractere a ete trouve */
	/* Lecture du nombre de mol. */
	SeqLength = ReadSeqFile_Pos(ReadSeqFilePtr, ErrIndexPtr);
	if (*ErrIndexPtr!=RSF_NO_ERROR) {
		/* Une erreur de lecture est survenue */
		/* Renvoi de l'erreur */
		return NULL;
	}
	/* la longueur de la sequence a ete lue */
	SeqPtr = I_Seq((TSeqCharIndex)SeqLength);
	if (!SeqPtr) {
		/* Une erreur d'allocation est survenue */
		*ErrIndexPtr = RSF_MEM_ERR;
		return NULL;
	}
	CurrentSeqLength = 1;
	Over = FALSE;
	while (!Over) {
		SearchResult = ReadSeqFile_NextLine(ReadSeqFilePtr);
		if (SearchResult == RSF_END_OF_FILE) {
			/* Fin de fichier atteinte */
			Over = TRUE;
		}
		if (!strncmp(ReadSeqFile_CurrentCharPtr(ReadSeqFilePtr), "//", 2)) {
			/* Fin de la sequence atteinte */
			Over = TRUE;
		}
		if (!Over) {
			/* Lecture des caracteres de la ligne */
			LineLength = strlen(ReadSeqFile_CurrentCharPtr(ReadSeqFilePtr));
			for (CharIndex = 0; CharIndex < LineLength; CharIndex++) {
				if (isalpha(*ReadSeqFile_CurrentCharPtr(ReadSeqFilePtr))) {
					/* Un caractere a ete trouve */
					if ((TPos)CurrentSeqLength > SeqLength) {
						/* Incompatibilite entre longueur lue et donnee */
						/* Longueur trop grande */
						Free_Seq(SeqPtr);
						*ErrIndexPtr = RSF_BAD_LENGTH;
						return NULL;
					}
					Seq_CharNth(SeqPtr, CurrentSeqLength) =
					(TChar)*ReadSeqFile_CurrentCharPtr(ReadSeqFilePtr);
					CurrentSeqLength++;
				}
				ReadSeqFile_NextChar(ReadSeqFilePtr);
			}
		}
	}
	/* Verification de la longueur */
	if ((TPos)CurrentSeqLength <= SeqLength) {
		/* Longueur trop petite */
		Free_Seq(SeqPtr);
		*ErrIndexPtr = RSF_BAD_LENGTH;
		return NULL;
	}
	/* Sequence lue */
	*ErrIndexPtr = RSF_NO_ERROR;
	return SeqPtr;
}

/*--------------------------------------------------------------------------*/
/* Lecture des donnees du fichier de sequences								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadSeqFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadSeqFile_SeqFileData	| donnees du fichier de sequence	*/
/* Erreurs:	| ReadSeqFile_SeqFileData	| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RSF_ID_EXP_UEOF			| Lgne ID att., fin de fich. inatt.	*/
/*			| RSF_WRD_EXP_UEOL			| Mot attendu, fin de ligne inatt.	*/
/*			| RSF_WRD_EXP_UEOF			| Mot att., fin de fichier inatt.	*/
/*			| RSF_WRD_EXP				| Mot attendu						*/
/*			| RSF_MEM_ERR				| Allocation memoire				*/
/*			| RSF_DE_EXP_UEOF			| Ligne DE att, fin de fich. inatt.	*/
/*			| RSF_DE_EXP				| Ligne DE attendue					*/
/*			| RSF_DESC_EXP_UEOL			| Desc. att. fin de ligne inatt.	*/
/*			| RSF_DESC_EXP_UEOF			| Desc att. fin de fichier inatt.	*/
/*			| RSF_SQ_EXP_UEOF			| Lgne SQ att., fin de fich. inatt.	*/
/*			| RSF_SQ_EXP				| Ligne SQ attendue					*/
/*			| RSF_POS_EXP_UEOL			| Ent. pos. att. fin de li. inatt.	*/
/*			| RSF_POS_EXP_UEOF			| Ent. pos. att. fin de fi. inatt.	*/
/*			| RSF_POS_INT_EXP			| Entier positif attendu			*/
/*			| RSF_BAD_LENGTH			| Longueurs incompatibles			*/
/*--------------------------------------------------------------------------*/
TSeqFileDataPtr ReadSeqFile_SeqFileData(TReadSeqFilePtr ReadSeqFilePtr,
TErrIndex *ErrIndexPtr)
{
	TWordPtr Id;
	TSentPtr De;
	TSeqPtr SeqPtr;
	TSeqFileDataPtr SeqFileDataPtr;
	TSearchResult SearchResult;
	
	/* Lecture de l'identificateur */
	Id = ReadSeqFile_NextId(ReadSeqFilePtr, ErrIndexPtr);
	if (!Id) {
		/* Une erreur est survenue */
		/* Renvoie l'erreur */
		return NULL;
	}
	/* Lecture de la description */
	De = ReadSeqFile_NextDe(ReadSeqFilePtr, &SearchResult, ErrIndexPtr);
	if (*ErrIndexPtr != RSF_NO_ERROR) {
		/* Une erreur est survenue */
		/* Renvoie la meme erreur */
		Free_Word(Id);
		return NULL;
	}
	/* Lecture de la sequence */
	if (SearchResult == RSF_END_OF_FILE) {
		/* Fin du fichier inattendue */
		Free_Word(Id);
		Free_Sent(De);
		*ErrIndexPtr = RSF_SQ_EXP_UEOF;
		return NULL;
	}
	if (SearchResult != RSF_SQ_LINE) {
		/* Ligne illegale */
		Free_Word(Id);
		Free_Sent(De);
		*ErrIndexPtr = RSF_SQ_EXP;
		return NULL;
	}
	SeqPtr = ReadSeqFile_LineSeq(ReadSeqFilePtr, ErrIndexPtr);
	if (!SeqPtr) {
		/* La lecture de la sequence a echoue */
		Free_Word(Id);
		Free_Sent(De);
		return NULL;
	}
	/* Construction des donnees de profil du fichier */
	SeqFileDataPtr = I_SeqFileData(Id, De, SeqPtr);
	if (!SeqFileDataPtr) {
		/* L'initialisation a echoue */
		Free_Word(Id);
		Free_Sent(De);
		Free_Seq(SeqPtr);
		return NULL;
	}
	*ErrIndexPtr = RSF_NO_ERROR;
	return SeqFileDataPtr;
}
