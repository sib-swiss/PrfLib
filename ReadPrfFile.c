/****************************************************************************/
/*																			*/
/*	But: Implementation de la lecture d'un fichier de profils.				*/
/*																			*/
/****************************************************************************/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "ReadPrfFile.h"

/*******************************/
/* IMPLEMENTATION DES ROUTINES */
/*******************************/

/*=====================================*/
/* Manipulation des donnees de lecture */
/*=====================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Saute a la prochaine ligne significative du fichier						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_NextSignLine	| Resultat de la recherche =		*/
/*			| RPF_END_OF_FILE			| Fin de fichier atteinte			*/
/*			| RPF_END_OF_PRF			| Fin de profil atteinte			*/
/*			| RPF_MA_LINE				| Ligne MA trouvee 					*/
/*			| RPF_ID_LINE				| Ligne ID trouvee 					*/
/*			| RPF_DE_LINE				| Ligne DE trouvee 					*/
/*			| RPF_AC_LINE				| Ligne AC trouvee 					*/
/* Erreur:	| -							| 									*/
/*--------------------------------------------------------------------------*/
TSearchResult ReadPrfFile_NextSignLine(TReadPrfFilePtr ReadPrfFilePtr)
{
	TSearchResult SearchResult;
	
	do {
		SearchResult = ReadPrfFile_NextLine(ReadPrfFilePtr);
		if (SearchResult == RPF_END_OF_FILE) {
			/* Fin de fichier atteinte */
			return RPF_END_OF_FILE;
		}
		if (!strncmp(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr), "//", 2)) {
			ReadPrfFile_NextChar(ReadPrfFilePtr);
			ReadPrfFile_NextChar(ReadPrfFilePtr);
			return RPF_END_OF_PRF;
		}
		else if (!strncmp(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr),
		"MA", 2)) {
			ReadPrfFile_NextChar(ReadPrfFilePtr);
			ReadPrfFile_NextChar(ReadPrfFilePtr);
			return RPF_MA_LINE;
		}
		else if (!strncmp(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr),
		"ID", 2)) {
			ReadPrfFile_NextChar(ReadPrfFilePtr);
			ReadPrfFile_NextChar(ReadPrfFilePtr);
			return RPF_ID_LINE;
		}
		else if (!strncmp(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr),
		"AC", 2)) {
			ReadPrfFile_NextChar(ReadPrfFilePtr);
			ReadPrfFile_NextChar(ReadPrfFilePtr);
			return RPF_AC_LINE;
		}
		else if (!strncmp(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr),
		"DE", 2)) {
			ReadPrfFile_NextChar(ReadPrfFilePtr);
			ReadPrfFile_NextChar(ReadPrfFilePtr);
			return RPF_DE_LINE;
		}
	}
	while (TRUE);
}

/*--------------------------------------------------------------------------*/
/* Retourne l'identificateur du profil de la ligne ID courante				*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_LineId		| Identificateur du profil			*/
/* Erreur:	| ReadPrfFile_LineId		| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RPF_MEM_ERR				| Allocation memoire				*/
/*			| RPF_WRD_EXP_UEOL			| Mot att. fin de ligne inatt.		*/
/*			| RPF_WRD_EXP_UEOF			| Mot att. fin de fichier inatt.	*/
/*			| RPF_WRD_EXP				| Mot attendu						*/
/*			| RPF_SEP_EXP_UEOL			| Sep. att. fin de ligne inatt.		*/
/*			| RPF_SEP_EXP_UEOF			| Sep. att. fin de fichier inatt.	*/
/*			| RPF_SEP_EXP				| Separateur attendu				*/
/*			| RPF_NO_PRF_ID				| Pas un ID de profil				*/
/*--------------------------------------------------------------------------*/
TWordPtr ReadPrfFile_LineId(TReadPrfFilePtr ReadPrfFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TWordPtr Id;
	TWordPtr IdKind;

		/* On saute les blancs */
		SearchResult = ReadPrfFile_JumpBlanks(ReadPrfFilePtr);
		if (SearchResult == RPF_END_OF_LINE) {
			*ErrIndexPtr = RPF_WRD_EXP_UEOL;
			return NULL;
		}
		if (SearchResult == RPF_END_OF_FILE) {
			*ErrIndexPtr = RPF_WRD_EXP_UEOF;
			return NULL;
		}
		/* Un caractere a ete trouve */
		/* Lecture de l'ID */
		Id = ReadPrfFile_Word(ReadPrfFilePtr, ErrIndexPtr);
		if (!Id) {
			/* Une erreur de lecture de l'ID est survenue */
			return NULL;
		}
		/* Un ID a ete lu */
		/* On saute les blancs */
		SearchResult = ReadPrfFile_JumpBlanks(ReadPrfFilePtr);
		if (SearchResult == RPF_END_OF_LINE) {
			/* Fin de ligne inattendue */
			Free_Word(Id);
			*ErrIndexPtr = RPF_SEP_EXP_UEOL;
			return NULL;
		}
		if (SearchResult == RPF_END_OF_FILE) {
			/* Fin de fichier inattendue */
			Free_Word(Id);
			*ErrIndexPtr = RPF_SEP_EXP_UEOF;
			return NULL;
		}
		if (*(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)) != ';') {
			/* Le ';' manque */
			Free_Word(Id);
			*ErrIndexPtr = RPF_SEP_EXP;
			return NULL;
		}
		/* Un ';' a ete trouve */
		ReadPrfFile_NextChar(ReadPrfFilePtr);
		/* On saute les blancs */
		SearchResult = ReadPrfFile_JumpBlanks(ReadPrfFilePtr);
		if (SearchResult == RPF_END_OF_LINE) {
			/* Fin de ligne inattendue */
			Free_Word(Id);
			*ErrIndexPtr = RPF_WRD_EXP_UEOL;
			return NULL;
		}
		if (SearchResult == RPF_END_OF_FILE) {
			/* Fin de ligne inattendue */
			Free_Word(Id);
			*ErrIndexPtr = RPF_WRD_EXP_UEOF;
			return NULL;
		}
		/* Un caractere a ete trouve */
		/* Lecture du type de l'ID */
		IdKind = ReadPrfFile_Word(ReadPrfFilePtr, ErrIndexPtr);
		if (!IdKind) {
			/* Une erreur de lecture du type est survenue */
			Free_Word(Id);
			return NULL;
		}
		/* Un type d'ID a ete trouve */
		if (strcmp(IdKind, "MATRIX")) {
			/* Ce n'est pas un ID de profil */
			Free_Word(Id);
			Free_Word(IdKind);
			*ErrIndexPtr = RPF_NO_PRF_ID;
			return NULL;
		}
		/* C'est un ID de profil */
		Free_Word(IdKind);
		SearchResult = ReadPrfFile_JumpBlanks(ReadPrfFilePtr);
		if (SearchResult == RPF_END_OF_LINE) {
			/* Fin de ligne inattendue */
			Free_Word(Id);
			*ErrIndexPtr = RPF_SEP_EXP_UEOL;
			return NULL;
		}
		if (SearchResult == RPF_END_OF_FILE) {
			/* Fin de ligne inattendue */
			Free_Word(Id);
			*ErrIndexPtr = RPF_SEP_EXP_UEOF;
			return NULL;
		}
		if (*(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)) != '.') {
			/* Le '.' manque */
			Free_Word(Id);
			*ErrIndexPtr = RPF_SEP_EXP;
			return NULL;
		}
		/* Le '.' a ete trouve */
		ReadPrfFile_NextChar(ReadPrfFilePtr);
		*ErrIndexPtr = RPF_NO_ERROR;
		return Id;
}

/*--------------------------------------------------------------------------*/
/* Recherche le prochain identificateur d'un profile dans le fichier		*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/*			| IdStr						| Chaine de l'identificateur		*/
/* Sortie:	| ReadPrfFile_NextId		| ID du profil						*/
/* Erreur:	| ReadPrfFile_NextId		| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RPF_MEM_ERR				| Allocation memoire				*/
/*			| RPF_WRD_EXP_UEOL			| Mot att. fin de ligne inatt.		*/
/*			| RPF_WRD_EXP_UEOF			| Mot att. fin de fichier inatt.	*/
/*			| RPF_WRD_EXP				| Mot attendu						*/
/*			| RPF_SEP_EXP_UEOL			| Sep. att. fin de ligne inatt.		*/
/*			| RPF_SEP_EXP_UEOF			| Sep. att. fin de fichier inatt.	*/
/*			| RPF_SEP_EXP				| Separateur attendu				*/
/*			| RPF_ID_EXP_UEOF			| Ligne ID att., fin de fich. inat.	*/
/*--------------------------------------------------------------------------*/
TWordPtr ReadPrfFile_NextId(TReadPrfFilePtr ReadPrfFilePtr, char *IdStr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TWordPtr Id;
	
	do {
		/* Saut a la ligne ID */
		SearchResult = ReadPrfFile_NextSignLine(ReadPrfFilePtr);
		if (SearchResult == RPF_END_OF_FILE) {
			/* Fin de fichier rencontree */
			*ErrIndexPtr = RPF_ID_EXP_UEOF;
			return NULL;
		}
		if (SearchResult == RPF_ID_LINE) {
			/* Une ligne ID a ete rencontree */
			/* Extraction de l'ID */
			Id = ReadPrfFile_LineId(ReadPrfFilePtr, ErrIndexPtr);
			if (!Id) {
				/* Erreur dans la lecture de l'ID */
				if (*ErrIndexPtr != RPF_NO_PRF_ID) {
					/* Erreur autre qu'un probleme de type d'ID */
					return NULL;
				}
			}
			/* Un ID de profil a ete lu */
			if (IdStr == NULL) {
				/* Aucun identificateur n'a ete specifie */
				*ErrIndexPtr = RPF_NO_ERROR;
				return Id;
			}
			/* Un identificateur a ete specifie */
			if (!strcmp(IdStr, (char*)Id)) {
				/* C'est le bon identificateur */
				*ErrIndexPtr = RPF_NO_ERROR;
				return Id;
			}
			/* On continue la recherche */
			Free_Id(Id);
		}
	}
	while (TRUE);
}

/*--------------------------------------------------------------------------*/
/* Retourne la description de la ligne DE courante							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_LineDe		| Description						*/
/* Erreur:	| ErrIndex				 	| Index d'erreur != RPF_NO_ERROR =	*/
/*			| RPF_DESC_EXP_UEOL			| Desc. att. fin de ligne inatt.	*/
/*			| RPF_DESC_EXP_UEOF			| Desc. att. fin de fichier inatt.	*/
/*			| RPF_PT_EXP				| "." attendu						*/
/*			| RPF_MEM_ERR				| Erreur allocation					*/
/*--------------------------------------------------------------------------*/
TSentPtr ReadPrfFile_LineDe(TReadPrfFilePtr ReadPrfFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TSentPtr De;

	/* On saute les blancs */
	SearchResult = ReadPrfFile_JumpBlanks(ReadPrfFilePtr);
	if (SearchResult == RPF_END_OF_LINE) {
		/* Fin de ligne inattendue */
		*ErrIndexPtr = RPF_DE_EXP_UEOL;
		return NULL;
	}
	if (SearchResult == RPF_END_OF_FILE) {
		/* Fin de fichier inattendue */
		*ErrIndexPtr = RPF_DE_EXP_UEOF;
		return NULL;
	}
	/* Un caractere a ete trouve */
	/* Lecture de la description */
	De = ReadPrfFile_Sent(ReadPrfFilePtr, ErrIndexPtr);
	if (!De) {
		/* Une erreur de lecture de la description est survenue */
		/* Renvoi de l'erreur */
		return NULL;
	}
	/* Description lue */
	ReadPrfFile_NextChar(ReadPrfFilePtr);
	return De;
}

/*--------------------------------------------------------------------------*/
/* Recherche la prochaine description dans le fichier						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_NextDe		| Description						*/
/* Erreur:	| ErrIndex					| Index d'erreur != RPF_NO_ERROR =	*/
/*			| RPF_DE_EXP_UEOF			| Ligne DE att, fin de fich. inatt.	*/
/*			| RPF_DE_EXP				| Ligne DE attendue					*/
/*			| RPF_DESC_EXP_UEOL			| Desc. att. fin de ligne inatt.	*/
/*			| RPF_DESC_EXP_UEOF			| Desc att. fin de fichier inatt.	*/
/*			| RPF_PT_EXP				| Mot attendu						*/
/*			| RPF_MEM_ERR				| Erreur allocation					*/
/*--------------------------------------------------------------------------*/
TSentPtr ReadPrfFile_NextDe(TReadPrfFilePtr ReadPrfFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TSentPtr De;
	
	/* Lecture de la ligne */
	SearchResult = ReadPrfFile_NextSignLine(ReadPrfFilePtr);
	if (SearchResult == RPF_END_OF_FILE) {
		/* Fin de fichier atteinte */
		*ErrIndexPtr = RPF_DE_EXP_UEOF;
		return NULL;
	}
	if (SearchResult != RPF_DE_LINE) {
		/* La ligne n'est pas une ligne DE */
		*ErrIndexPtr = RPF_DE_EXP;
		return NULL;
	}
	/* La ligne DE est trouvee */
	De = ReadPrfFile_LineDe(ReadPrfFilePtr, ErrIndexPtr);
	if (*ErrIndexPtr != RPF_NO_ERROR) {
		/* Une erreur est survenue */
		/* Renvoi de l'erreur */
		return NULL;
	}
	/* Une description a ete trouvee */
	return De;
}

/*--------------------------------------------------------------------------*/
/* Retourne nombre Prosite de la ligne courante								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_LineNbrAc		| nombre AC							*/
/* Erreur:	| ErrIndex				 	| Index d'erreur != RPF_NO_ERROR =	*/
/*			| RPF_PS_EXP_UEOL			| PS att. fin de ligne inatt.		*/
/*			| RPF_PS_EXP_UEOF			| PS att. fin de fichier inatt.		*/
/*			| RPF_MEM_ERR				| Erreur allocation					*/
/*			| RPF_PT_EXP_UEOL			| Separ. att. fin de ligne inatt.	*/
/*			| RPF_SEP_EXP_UEOF			| Separ. att. fin de fichier inatt.	*/
/*			| RPF_SEP_EXP				| Separateur attendu				*/
/*--------------------------------------------------------------------------*/
TWordPtr ReadPrfFile_LineNbrAc(TReadPrfFilePtr ReadPrfFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TWordPtr NbrAc;

	/* On saute les blancs */
	SearchResult = ReadPrfFile_JumpBlanks(ReadPrfFilePtr);
	if (SearchResult == RPF_END_OF_LINE) {
		/* Fin de ligne inattendue */
		*ErrIndexPtr = RPF_PS_EXP_UEOL;
		return NULL;
	}
	if (SearchResult == RPF_END_OF_FILE) {
		/* Fin de fichier inattendue */
		*ErrIndexPtr = RPF_PS_EXP_UEOF;
		return NULL;
	}
	/* Un caractere a ete trouve */
	/* Lecture du nombre AC */
	NbrAc = ReadPrfFile_Word(ReadPrfFilePtr, ErrIndexPtr);
	if (!NbrAc) {
		/* Une erreur de lecture du nombre AC est survenue */
		return NULL;
	}
	/* Le nombre AC a ete lu */
	/* On saute les blancs */
	SearchResult = ReadPrfFile_JumpBlanks(ReadPrfFilePtr);
	if (SearchResult == RPF_END_OF_LINE) {
		/* Fin de ligne inattendue */
		Free_Word(NbrAc);
		*ErrIndexPtr = RPF_SEP_EXP_UEOL;
		return NULL;
	}
	if (SearchResult == RPF_END_OF_FILE) {
		/* Fin de fichier inattendue */
		Free_Word(NbrAc);
		*ErrIndexPtr = RPF_SEP_EXP_UEOF;
		return NULL;
	}
	if (*(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)) != ';') {
		/* Le ';' manque */
		Free_Word(NbrAc);
		*ErrIndexPtr = RPF_SEP_EXP;
		return NULL;
	}
	/* ';' trouve */
	ReadPrfFile_NextChar(ReadPrfFilePtr);
	return NbrAc;
}

/*--------------------------------------------------------------------------*/
/* Recherche le prochain nombre Prosite dans le fichier						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_NextNbrAc		| Nombre AC							*/
/* Erreur:	| ErrIndex					| Index d'erreur != RPF_NO_ERROR =	*/
/*			| RPF_AC_EXP_UEOF			| Ligne AC att, fin de fich. inatt.	*/
/*			| RPF_AC_EXP				| Ligne AC attendue					*/
/*			| RPF_PS_EXP_UEOL			| PS att. fin de ligne inatt.		*/
/*			| RPF_PS_EXP_UEOF			| PS att. fin de fichier inatt.		*/
/*			| RPF_WRD_EXP				| Mot attendu						*/
/*			| RPF_MEM_ERR				| Erreur allocation					*/
/*			| RPF_SEP_EXP_UEOL			| Separ. att. fin de ligne inatt.	*/
/*			| RPF_SEP_EXP_UEOF			| Separ. att. fin de fichier inatt.	*/
/*			| RPF_SEP_EXP				| Separateur attendu				*/
/*--------------------------------------------------------------------------*/
TWordPtr ReadPrfFile_NextNbrAc(TReadPrfFilePtr ReadPrfFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	TWordPtr NbrAc;
	
	/* Lecture de la ligne */
	SearchResult = ReadPrfFile_NextSignLine(ReadPrfFilePtr);
	if (SearchResult == RPF_END_OF_FILE) {
		/* Fin de fichier atteinte */
		*ErrIndexPtr = RPF_AC_EXP_UEOF;
		return NULL;
	}
	if (SearchResult != RPF_AC_LINE) {
		/* La ligne n'est pas une ligne AC */
		*ErrIndexPtr = RPF_AC_EXP;
		return NULL;
	}
	/* La ligne AC est trouvee */
	NbrAc = ReadPrfFile_LineNbrAc(ReadPrfFilePtr, ErrIndexPtr);
	if (*ErrIndexPtr != RPF_NO_ERROR) {
		/* Une erreur est survenue */
		/* Renvoi de l'erreur */
		return NULL;
	}
	/* Un nombre AC a ete trouve */
	return NbrAc;
}

/*--------------------------------------------------------------------------*/
/* Saute a la prochaine ligne MA du fichier									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| SearchNextMA=				| Resultat de la recherche			*/
/*			| RPF_END_OF_FILE			| Fin de fichier atteinte			*/
/*			| RPF_END_OF_PRF			| Fin de profil atteinte			*/
/*			| RPF_MA_LINE				| Ligne MA trouvee 					*/
/* Erreur:	| ReadPrfFile_NextMA		| = RPF_ERROR =>					*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RPF_MA_EXP				| Ligne MA attendue					*/
/*--------------------------------------------------------------------------*/
TSearchResult ReadPrfFile_NextMA(TReadPrfFilePtr ReadPrfFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;

	SearchResult = ReadPrfFile_NextSignLine(ReadPrfFilePtr);
	if ((SearchResult == RPF_END_OF_FILE) || (SearchResult == RPF_END_OF_PRF)) {
		/* Fin du fichier ou du profil atteinte */
		*ErrIndexPtr = RPF_NO_ERROR;
		return SearchResult;
	}
	if (SearchResult != RPF_MA_LINE) {
		/* Ligne illegale */
		*ErrIndexPtr = RPF_MA_EXP;
		return RPF_ERROR;
	}
	*ErrIndexPtr = RPF_NO_ERROR;
	return RPF_MA_LINE;
}

/*--------------------------------------------------------------------------*/
/* Saute les espaces et les lignes non significatives dans le lignes MA		*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| JumpSpaces=				| Resultat de la recherche			*/
/*			| RPF_END_OF_FILE			| Fin de fichier atteinte			*/
/*			| RPF_END_OF_PRF			| Fin de profil atteinte			*/
/*			| RPF_CHAR_FND				| Un caractere a ete trouvee 		*/
/* Erreur:	| ReadPrfFile_JumpSpaces	| = RPF_ERROR =>					*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RPF_MA_EXP				| Ligne MA attendue					*/
/*--------------------------------------------------------------------------*/
TSearchResult ReadPrfFile_JumpSpaces(TReadPrfFilePtr ReadPrfFilePtr,
TErrIndex *ErrIndexPtr)
{
	TSearchResult SearchResult;
	
	do {
		SearchResult = ReadPrfFile_JumpBlanks(ReadPrfFilePtr);
		if (SearchResult == RPF_CHAR_FND) {
			/* Un caractere a ete trouve */
			*ErrIndexPtr = RPF_NO_ERROR;
			return RPF_CHAR_FND;
		}
		if (SearchResult == RPF_END_OF_FILE) {
			/* Fin de fichier atteinte */
			*ErrIndexPtr = RPF_NO_ERROR;
			return RPF_END_OF_FILE;
		}
		if (SearchResult == RPF_END_OF_LINE) {
			/* Fin de ligne atteinte */
			/* Saut a la prochaine ligne MA */
			SearchResult = ReadPrfFile_NextMA(ReadPrfFilePtr, ErrIndexPtr);
			if (SearchResult == RPF_ERROR) {
				/* Une erreur est survenue */
				/* Renvoi de l'erreur */
				return RPF_ERROR;
			}
			if ((SearchResult == RPF_END_OF_FILE) ||
			(SearchResult == RPF_END_OF_PRF)) {
				/* Fin de fichier ou de profil atteinte */
				/* Renvoi du resultat */
				*ErrIndexPtr = RPF_NO_ERROR;
				return SearchResult;
			}
			/* Une ligne MA a ete trouvee */
		}
	}
	while (TRUE);
}

/*--------------------------------------------------------------------------*/
/* Lecture d'un mot-cle														*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_Keyword		| Mot-cle							*/
/* Erreur:	| ReadPrfFile_Keyword		| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RPF_SLSH_EXP				| '/' attendu						*/
/*			| RPF_WRD_EXP				| Mot attendu						*/
/*			| RPF_MEM_ERR				| Allocation memoire				*/
/*			| RPF_DBLPT_EXP				| ':' attendu						*/
/*--------------------------------------------------------------------------*/
TWordPtr ReadPrfFile_Keyword(TReadPrfFilePtr ReadPrfFilePtr,
TErrIndex *ErrIndexPtr)
{
	TWordPtr KeywordPtr;
	
	if (*(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)) != '/') {
		/* Le '/' manque */
		*ErrIndexPtr = RPF_SLSH_EXP;
		return NULL;
	}
	ReadPrfFile_NextChar(ReadPrfFilePtr);
	KeywordPtr = ReadPrfFile_Word(ReadPrfFilePtr, ErrIndexPtr);
	if (!KeywordPtr) {
		/* Erreur de lecture */
		return NULL;
	}
	if (*(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)) != ':') {
		/* Le ':' manque */
		Free_Word(KeywordPtr);
		*ErrIndexPtr = RPF_DBLPT_EXP;
		return NULL;
	}
	ReadPrfFile_NextChar(ReadPrfFilePtr);
	*ErrIndexPtr = RPF_NO_ERROR;
	return KeywordPtr;
}

/*--------------------------------------------------------------------------*/
/* Lecture d'une valeur														*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_Val			| Valeur							*/
/* Erreur:	| ReadPrfFile_Val			| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RPF_MEM_ERR				| Allocation memoire				*/
/*			| RPF_EDAP_EXP				| "'" de fin de chaine attendu		*/
/*			| RPF_VAL_EXP				| Valeur attendue					*/
/*--------------------------------------------------------------------------*/
TValPtr ReadPrfFile_Val(TReadPrfFilePtr ReadPrfFilePtr, TErrIndex *ErrIndexPtr)
{
	TValPtr ValPtr;	/* Pointeur retourne		*/

	ValPtr = I_Val();
	if (!ValPtr) {
		*ErrIndexPtr = RPF_MEM_ERR;
		return NULL;
	}
	if (*(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)) == '*') {
		ReadPrfFile_NextChar(ReadPrfFilePtr);
		Val_Type(ValPtr) = PFD_INFINITE;
		Val_Nbr(ValPtr) = 0.0;
		return ValPtr;
	}
	if (*(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)) == RPF_APOS) {
		/* C'est une chaine */
		Val_Str(ValPtr) = ReadPrfFile_Str(ReadPrfFilePtr, ErrIndexPtr);
		if (!Val_Str(ValPtr)) {
			/* Une erreur est survenue */
			/* Renvoi de l'erreur */
			Free_Val(ValPtr);
			return NULL;
		}
		Val_Type(ValPtr) = PFD_A_STR;
		*ErrIndexPtr = RPF_NO_ERROR;
		return ValPtr;
	}
	if (strchr(RPF_START_NBR, *(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)))) {
		/* C'est un nombre */
		Val_Nbr(ValPtr) = ReadPrfFile_Nbr(ReadPrfFilePtr, ErrIndexPtr);
		if (*ErrIndexPtr != RPF_NO_ERROR) {
			/* Pour la forme: n'arrive jamais */
			/* Une erreur est survenue */
			/* Renvoi de l'erreur */
			Free_Val(ValPtr);
			return NULL;
		}
		Val_Type(ValPtr) = PFD_A_NBR;
		*ErrIndexPtr = RPF_NO_ERROR;
		return ValPtr;
	}
	if (strchr(RPF_START_WRD, *(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)))) {
		/* C'est un mot */
		Val_Word(ValPtr) = ReadPrfFile_Word(ReadPrfFilePtr,
		ErrIndexPtr);
		if (!Val_Word(ValPtr)) {
			/* Une erreur est survenue */
			/* Renvoi de l'erreur */
			Free_Val(ValPtr);
			return NULL;
		}
		Val_Type(ValPtr) = PFD_A_WORD;
		*ErrIndexPtr = RPF_NO_ERROR;
		return ValPtr;
	}
	/* erreur */
	*ErrIndexPtr = RPF_VAL_EXP;
	Free_Val(ValPtr);
	return NULL;
}

/*--------------------------------------------------------------------------*/
/* Lecture d'une assignation												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_Ass			| Assignation						*/
/* Erreur:	| ReadPrfFile_Ass			| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RPF_MEM_ERR				| Allocation memoire				*/
/*			| RPF_WRD_EXP				| Mot attendu						*/
/*			| RPF_MA_EXP				| Ligne MA attendue					*/
/*			| RPF_EQU_EXP_UEOF			| '=' attendu, fin de fich. inatt.	*/
/*			| RPF_EQU_EXP_UEOP			| '=' attendu, fin de prof. inatt.	*/
/*			| RPF_EQU_EXP				| '=' attendu						*/
/*			| RPF_VAL_NBR_OVF			| trop de valeurs					*/
/*			| RPF_VAL_EXP_UEOF			| valeur att., fin de fich. inatt.	*/
/*			| RPF_VAL_EXP_UEOP			| valeur att., fin de prof. inatt.	*/
/*			| RPF_EDAP_EXP				| "'" de fin de chaine attendu		*/
/*			| RPF_VAL_EXP				| Valeur attendue					*/
/*			| RPF_SEP_EXP_UEOF			| sep. att., fin de fich. inatt.	*/
/*			| RPF_SEP_EXP_UEOP			| sep. att., fin de prof. inatt.	*/
/*			| RPF_SEP_EXP				| sep. attendu						*/
/*--------------------------------------------------------------------------*/
TAssPtr ReadPrfFile_Ass(TReadPrfFilePtr ReadPrfFilePtr, TErrIndex *ErrIndexPtr)
{
	TAssPtr AssPtr;					/* Pointeur retourne			*/
	TWordPtr WordPtr;				/* Mot de l'assignation			*/
	TBoolean Over;					/* Flag de terminaison			*/
	TSearchResult SearchResult;		/* Resultat d'un saut d'espace	*/
	TValPtr ValPtr;					/* Valeur lue					*/
	
	WordPtr = ReadPrfFile_Word(ReadPrfFilePtr, ErrIndexPtr);
	if (!WordPtr) {
		/* Une erreur est survenue */
		/* Renvoi de l'erreur */
		return NULL;
	}
	AssPtr = I_Ass(RPF_MAX_VALUES, WordPtr);
	if (!AssPtr) {
		Free_Word(WordPtr);
		*ErrIndexPtr = RPF_MEM_ERR;
		return NULL;
	}
	SearchResult = ReadPrfFile_JumpSpaces(ReadPrfFilePtr, ErrIndexPtr);
	if (SearchResult == RPF_ERROR) {
		/* Une erreur est survenue */
		/* Renvoi de l'erreur */
		Free_Ass(AssPtr);
		return NULL;
	}
	if (SearchResult == RPF_END_OF_FILE) {
		/* Fin de fichier inattendue */
		Free_Ass(AssPtr);
		*ErrIndexPtr = RPF_EQU_EXP_UEOF;
		return NULL;
	}
	if (SearchResult == RPF_END_OF_PRF) {
		/* Fin de profil inattendue */
		Free_Ass(AssPtr);
		*ErrIndexPtr = RPF_EQU_EXP_UEOP;
		return NULL;
	}
	if (*(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)) != '=') {
		/* '=' attendu */
		Free_Ass(AssPtr);
		*ErrIndexPtr = RPF_EQU_EXP;
		return NULL;
	}
	ReadPrfFile_NextChar(ReadPrfFilePtr);
	Over = FALSE;
	do {
		if (Ass_ValListFull(AssPtr)) {
			/* Trop de valeurs dans la liste */
			Free_Ass(AssPtr);
			*ErrIndexPtr = RPF_VAL_NBR_OVF;
			return NULL;
		}
		SearchResult = ReadPrfFile_JumpSpaces(ReadPrfFilePtr, ErrIndexPtr);
		if (SearchResult == RPF_ERROR) {
			/* Une erreur est survenue */
			/* Renvoi de l'erreur */
			Free_Ass(AssPtr);
			return NULL;
		}
		if (SearchResult == RPF_END_OF_FILE) {
			/* Fin de fichier inattendue */
			Free_Ass(AssPtr);
			*ErrIndexPtr = RPF_VAL_EXP_UEOF;
			return NULL;
		}
		if (SearchResult == RPF_END_OF_PRF) {
			/* Fin de profil inattendue */
			Free_Ass(AssPtr);
			*ErrIndexPtr = RPF_VAL_EXP_UEOP;
			return NULL;
		}
		/* Lecture du nombre */
		ValPtr = ReadPrfFile_Val(ReadPrfFilePtr, ErrIndexPtr);
		if (!ValPtr) {
			/* Une erreur est survenue */
			/* Renvoi de l'erreur */
			Free_Ass(AssPtr);
			return NULL;
		}
		/* Ajout de la valeur dans la liste */
		Ass_AddVal(AssPtr, ValPtr);
		SearchResult = ReadPrfFile_JumpSpaces(ReadPrfFilePtr, ErrIndexPtr);
		if (SearchResult == RPF_ERROR) {
			/* Une erreur est survenue */
			/* Renvoi de l'erreur */
			Free_Ass(AssPtr);
			return NULL;
		}
		if (SearchResult == RPF_END_OF_FILE) {
			/* Fin de fichier inattendue */
			Free_Ass(AssPtr);
			*ErrIndexPtr = RPF_SEP_EXP_UEOF;
			return NULL;
		}
		if (SearchResult == RPF_END_OF_PRF) {
			/* Fin de profil inattendue */
			Free_Ass(AssPtr);
			*ErrIndexPtr = RPF_SEP_EXP_UEOP;
			return NULL;
		}
		if (*(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)) == ';') Over = TRUE;
		else if (*(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)) != ',') {
			/* Separateur attendu */
			Free_Ass(AssPtr);
			*ErrIndexPtr = RPF_SEP_EXP;
			return NULL;
		}
		ReadPrfFile_NextChar(ReadPrfFilePtr);
	}
	while (!Over);
	/* Ass_ResizeValList(AssPtr); */
	*ErrIndexPtr = RPF_NO_ERROR;
	return AssPtr;
}

/*--------------------------------------------------------------------------*/
/* Lecture d'une description												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_Desc			| Description						*/
/*			| SearchResult =			| Resultat de la recherche			*/
/*			| RPF_END_OF_FILE			| Fin du fichier atteinte			*/
/*			| RPF_END_OF_PRF			| Fin du profil atteinte			*/
/*			| RPF_CHAR_FND				| Un caractere suit la description	*/
/* Erreurs:	| ReadPrfFile_Desc			| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur = 					*/
/*			| RPF_MEM_ERR				| Allocation memoire				*/
/*			| RPF_SLSH_EXP				| '/' attendu						*/
/*			| RPF_WRD_EXP				| Mot attendu						*/
/*			| RPF_DBLPT_EXP				| ':' attendu						*/
/*			| RPF_MA_EXP				| Ligne MA attendue					*/
/*			| RPF_ASS_NBR_OVF			| trop d'assignations				*/
/*			| RPF_EQU_EXP_UEOF			| '=' attendu, fin de fich. inatt.	*/
/*			| RPF_EQU_EXP_UEOP			| '=' attendu, fin de prof. inatt.	*/
/*			| RPF_EQU_EXP				| '=' attendu						*/
/*			| RPF_VAL_NBR_OVF			| trop de valeurs					*/
/*			| RPF_VAL_EXP_UEOF			| valeur att., fin de fich. inatt.	*/
/*			| RPF_VAL_EXP_UEOP			| valeur att., fin de prof. inatt.	*/
/*			| RPF_EDAP_EXP				| "'" de fin de chaine attendu		*/
/*			| RPF_VAL_EXP				| Valeur attendue					*/
/*			| RPF_SEP_EXP_UEOF			| sep. att., fin de fich. inatt.	*/
/*			| RPF_SEP_EXP_UEOP			| sep. att., fin de prof. inatt.	*/
/*			| RPF_SEP_EXP				| sep. attendu						*/
/*--------------------------------------------------------------------------*/
TDescPtr ReadPrfFile_Desc(TReadPrfFilePtr ReadPrfFilePtr,
TSearchResult *SearchResultPtr, TErrIndex *ErrIndexPtr)
{
	TDescPtr DescPtr;				/* Pointeur retourne			*/
	TWordPtr KeywordPtr;			/* Mot-cle de la description	*/
	TBoolean Over;					/* Flag de terminaison			*/
	TSearchResult SearchResult;		/* Resultat d'un saut d'espace	*/
	TAssPtr AssPtr;					/* Assignation lue				*/

	/* Lecture du mot-cle */
	KeywordPtr = ReadPrfFile_Keyword(ReadPrfFilePtr, ErrIndexPtr);
	if (!KeywordPtr) {
		/* Une erreur est survenue */
		/* Renvoi de l'erreur */
		return NULL;
	}
	DescPtr =I_Desc(RPF_MAX_ASSIGN, KeywordPtr);
	if (!DescPtr) {
		Free_Word(KeywordPtr);
		*ErrIndexPtr = RPF_MEM_ERR;
		return NULL;
	}
	Over = FALSE;
	do {
		SearchResult = ReadPrfFile_JumpSpaces(ReadPrfFilePtr, ErrIndexPtr);
		if (SearchResult == RPF_ERROR) {
			/* Une erreur est survenue */
			/* Renvoi de l'erreur */
			Free_Desc(DescPtr);
			return NULL;
		}
		if (SearchResult == RPF_END_OF_FILE) {
			/* Fin de fichier atteinte */
			*SearchResultPtr = RPF_END_OF_FILE;
			Over = TRUE;
		} else if (SearchResult == RPF_END_OF_PRF) {
			/* Fin de profil atteinte */
			*SearchResultPtr = RPF_END_OF_PRF;
			Over = TRUE;
		} else if (!strchr(RPF_START_WRD,
		*(ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)))) {
			/* Plus de nouvelle assignation */
			*SearchResultPtr = RPF_CHAR_FND;
			Over = TRUE;
		}
		if (!Over) {
			if (Desc_AssListFull(DescPtr)) {
				/* Trop d'assignations dans la liste */
				Free_Desc(DescPtr);
				*ErrIndexPtr = RPF_ASS_NBR_OVF;
				return NULL;
			}
			AssPtr = ReadPrfFile_Ass(ReadPrfFilePtr, ErrIndexPtr);
			if (!AssPtr) {
				/* Une erreur est survenue */
				/* Renvoi de l'erreur */
				Free_Desc(DescPtr);
				return NULL;
			}
			/* Ajout de l'assignation dans la liste */
			Desc_AddAss(DescPtr, AssPtr);
		}
	}
	while (!Over);
	/* Desc_ResizeAssList(DescPtr); */
	*ErrIndexPtr = RPF_NO_ERROR;
	return DescPtr;
}

/*--------------------------------------------------------------------------*/
/* Lecture d'un profil														*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_Prf			| Profil							*/
/* Erreurs:	| ReadPrfFile_Prf			| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RPF_MEM_ERR				| Allocation memoire				*/
/*			| RPF_MA_EXP				| Ligne MA attendue					*/
/*			| RPF_MA_EXP_UEOF			| Ligne MA att., fin de fich. inat.	*/
/*			| RPF_MA_EXP_UEOP			| Ligne MA att., fin de prof. inat.	*/
/*			| RPF_EMPTY_PRF				| profil vide						*/
/*			| RPF_DESC_NBR_OVF			| trop de descriptions				*/
/*			| RPF_SLSH_EXP				| '/' attendu						*/
/*			| RPF_WRD_EXP				| Mot attendu						*/
/*			| RPF_DBLPT_EXP				| ':' attendu						*/
/*			| RPF_ASS_NBR_OVF			| trop d'assignations				*/
/*			| RPF_EQU_EXP_UEOF			| '=' attendu, fin de fich. inatt.	*/
/*			| RPF_EQU_EXP_UEOP			| '=' attendu, fin de prof. inatt.	*/
/*			| RPF_EQU_EXP				| '=' attendu						*/
/*			| RPF_VAL_NBR_OVF			| trop de valeurs					*/
/*			| RPF_VAL_EXP_UEOF			| valeur att., fin de fich. inatt.	*/
/*			| RPF_VAL_EXP_UEOP			| valeur att., fin de prof. inatt.	*/
/*			| RPF_EDAP_EXP				| "'" de fin de chaine attendu		*/
/*			| RPF_VAL_EXP				| Valeur attendue					*/
/*			| RPF_SEP_EXP_UEOF			| sep. att., fin de fich. inatt.	*/
/*			| RPF_SEP_EXP_UEOP			| sep. att., fin de prof. inatt.	*/
/*			| RPF_SEP_EXP				| sep. attendu						*/
/*--------------------------------------------------------------------------*/
TPrfPtr ReadPrfFile_Prf(TReadPrfFilePtr ReadPrfFilePtr, TErrIndex *ErrIndexPtr)
{
	TPrfPtr PrfPtr;					/* Pointeur retourne			*/
	TBoolean Over;					/* Flag de terminaison			*/
	TSearchResult SearchResult;		/* Resultat d'un saut d'espace	*/
	TDescPtr DescPtr;				/* Description lue				*/

	PrfPtr =I_Prf(RPF_MAX_DESCR);
	if (!PrfPtr) {
		*ErrIndexPtr = RPF_MEM_ERR;
		return NULL;
	}
	/* Recherche de la premiere ligne MA */
	SearchResult = ReadPrfFile_NextMA(ReadPrfFilePtr, ErrIndexPtr);
	if (SearchResult == RPF_ERROR) {
		/* Une erreur est survenue */
		/* Renvoi de l'erreur */
		Free_Prf(PrfPtr);
		return NULL;
	}
	if (SearchResult == RPF_END_OF_FILE) {
		/* Fin de fichier inattendue */
		Free_Prf(PrfPtr);
		*ErrIndexPtr = RPF_MA_EXP_UEOF;
		return NULL;
	}
	if (SearchResult == RPF_END_OF_PRF) {
		/* Fin de profil inattendue */
		Free_Prf(PrfPtr);
		*ErrIndexPtr = RPF_MA_EXP_UEOP;
		return NULL;
	}
	/* Une ligne MA a ete trouvee */
	/* Saute jusqu'au premier caractere significatif */
	SearchResult = ReadPrfFile_JumpSpaces(ReadPrfFilePtr, ErrIndexPtr);
	if (SearchResult == RPF_ERROR) {
		/* Une erreur est survenue */
		Free_Prf(PrfPtr);
		return NULL;
	}
	if (SearchResult != RPF_CHAR_FND) {
		/* Fin du fichier ou du profil atteinte */
		/* Profil vide */
		Free_Prf(PrfPtr);
		*ErrIndexPtr = RPF_EMPTY_PRF;
		return NULL;
	}
	Over = FALSE;
	do {
		if (Prf_DescListFull(PrfPtr)) {
			/* Trop de description dans la liste */
			Free_Prf(PrfPtr);
			*ErrIndexPtr = RPF_DESC_NBR_OVF;
			return NULL;
		}
		DescPtr = ReadPrfFile_Desc(ReadPrfFilePtr, &SearchResult, ErrIndexPtr);
		if (!DescPtr) {
			/* Une erreur est survenue */
			/* Renvoi de l'erreur */
			Free_Prf(PrfPtr);
			return NULL;
		}
		/* Ajout de la description dans la liste */
		Prf_AddDesc(PrfPtr, DescPtr);
		if (SearchResult != RPF_CHAR_FND) {
			Over = TRUE;
		}
	}
	while (!Over);
	/* Prf_ResizeDescList(PrfPtr); */
	return PrfPtr;
}

/*--------------------------------------------------------------------------*/
/* Lecture des donnees du fichier de profils								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/*			| IdStr						| Chaine de l'identificateur		*/
/* Sortie:	| ReadPrfFile_PrfFileData	| donnees du fichier de profil		*/
/* Erreurs:	| ReadPrfFile_PrfFileData	| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RPF_MEM_ERR				| Allocation memoire				*/
/*			| RPF_WRD_EXP_UEOL			| Mot att. fin de ligne inatt.		*/
/*			| RPF_WRD_EXP_UEOF			| Mot att. fin de fichier inatt.	*/
/*			| RPF_WRD_EXP				| Mot attendu						*/
/*			| RPF_SEP_EXP_UEOL			| Sep. att. fin de ligne inatt.		*/
/*			| RPF_SEP_EXP_UEOF			| Sep. att. fin de fichier inatt.	*/
/*			| RPF_SEP_EXP				| Separateur attendu				*/
/*			| RPF_ID_EXP_UEOF			| Ligne ID att., fin de fich. inat.	*/
/*			| RPF_AC_EXP_UEOF			| Ligne AC att, fin de fich. inatt.	*/
/*			| RPF_AC_EXP				| Ligne AC attendue					*/
/*			| RPF_PS_EXP_UEOL			| PS att. fin de ligne inatt.		*/
/*			| RPF_PS_EXP_UEOF			| PS att. fin de fichier inatt.		*/
/*			| RPF_NBR_EXP				| Nombre attendu					*/
/*			| RPF_MA_EXP				| Ligne MA attendue					*/
/*			| RPF_MA_EXP_UEOF			| Ligne MA att., fin de fich. inat.	*/
/*			| RPF_MA_EXP_UEOP			| Ligne MA att., fin de prof. inat.	*/
/*			| RPF_EMPTY_PRF				| profil vide						*/
/*			| RPF_DESC_NBR_OVF			| trop de descriptions				*/
/*			| RPF_SLSH_EXP				| '/' attendu						*/
/*			| RPF_WRD_EXP				| Mot attendu						*/
/*			| RPF_DBLPT_EXP				| ':' attendu						*/
/*			| RPF_ASS_NBR_OVF			| trop d'assignations				*/
/*			| RPF_EQU_EXP_UEOF			| '=' attendu, fin de fich. inatt.	*/
/*			| RPF_EQU_EXP_UEOP			| '=' attendu, fin de prof. inatt.	*/
/*			| RPF_EQU_EXP				| '=' attendu						*/
/*			| RPF_VAL_NBR_OVF			| trop de valeurs					*/
/*			| RPF_VAL_EXP_UEOF			| valeur att., fin de fich. inatt.	*/
/*			| RPF_VAL_EXP_UEOP			| valeur att., fin de prof. inatt.	*/
/*			| RPF_EDAP_EXP				| "'" de fin de chaine attendu		*/
/*			| RPF_VAL_EXP				| Valeur attendue					*/
/*			| RPF_SEP_EXP_UEOP			| sep. att., fin de prof. inatt.	*/
/*--------------------------------------------------------------------------*/
TPrfFileDataPtr ReadPrfFile_PrfFileData(TReadPrfFilePtr ReadPrfFilePtr,
char *IdStr, TErrIndex *ErrIndexPtr)
{
	TWordPtr Id;
	TSentPtr De;
	TWordPtr NbrAc;
	TPrfPtr PrfPtr;
	TPrfFileDataPtr PrfFileDataPtr;
	
	/* Lecture de l'identificateur */
	Id = ReadPrfFile_NextId(ReadPrfFilePtr, IdStr, ErrIndexPtr);
	if (!Id) {
		/* Une erreur est survenue */
		/* Renvoie l'erreur */
		return NULL;
	}
	/* Lecture du nombre AC */
	NbrAc = ReadPrfFile_NextNbrAc(ReadPrfFilePtr, ErrIndexPtr);
	if (*ErrIndexPtr != RPF_NO_ERROR) {
		/* Une erreur est survenue */
		/* Renvoie la meme erreur */
		Free_Word(Id);
		return NULL;
	}
	/* Lecture de la description */
	De = ReadPrfFile_NextDe(ReadPrfFilePtr, ErrIndexPtr);
	if (*ErrIndexPtr != RPF_NO_ERROR) {
		/* Une erreur est survenue */
		/* Renvoie la meme erreur */
		Free_Word(Id);
		Free_Word(NbrAc);
		return NULL;
	}
	/* Lecture du profil */
	PrfPtr = ReadPrfFile_Prf(ReadPrfFilePtr, ErrIndexPtr);
	if (!PrfPtr) {
		/* La lecture du profile a echoue */
		Free_Word(Id);
		Free_Word(NbrAc);
		Free_Word(De);
		return NULL;
	}
	/* Construction des donnees de profil du fichier */
	PrfFileDataPtr = I_PrfFileData(Id, De, NbrAc, PrfPtr);
	if (!PrfFileDataPtr) {
		/* L'initialisation a echoue */
		Free_Word(Id);
		Free_Word(NbrAc);
		Free_Word(De);
		Free_Prf(PrfPtr);
		*ErrIndexPtr = RPF_MEM_ERR;
		return NULL;
	}
	return PrfFileDataPtr;
}
