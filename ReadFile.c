/****************************************************************************/
/*																			*/
/*	But: Implementation de la lecture d'un fichier.							*/
/*																			*/
/****************************************************************************/

#ifdef _SUN_
#include <floatingpoint.h>
#endif
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "ReadFile.h"

/*******************************/
/* IMPLEMENTATION DES ROUTINES */
/*******************************/

/*=====================================*/
/* Manipulation des donnees de lecture */
/*=====================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Initialisation des donnees de lecture									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| FileName					| Nom du fichier					*/
/* Sortie:	| I_ReadFile				| Donnees de lecture				*/
/* Erreur:	| I_ReadFile				| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RF_MEM_ERR				| Allocation memoire				*/
/*			| RF_OPEN_ERR				| Erreur d'ouverture				*/
/*--------------------------------------------------------------------------*/
TReadFilePtr I_ReadFile(char *FileName, TErrIndex *ErrIndexPtr)
{
	TReadFilePtr ReadFilePtr;
	char *CharPtr;
	
	ReadFilePtr = (TReadFilePtr)malloc(sizeof(TReadFile));
	if (!ReadFilePtr) {
		*ErrIndexPtr = RF_MEM_ERR;
		return NULL;
	}
	ReadFilePtr->InputFile = fopen(FileName, "r");
	if (!(ReadFilePtr->InputFile)) {
		free(ReadFilePtr);
		*ErrIndexPtr = RF_OPEN_ERR;
		return NULL;
	}
	ReadFilePtr->CurrentLine[0] = 0; /* Chaine vide avant lecture */
	ReadFilePtr->CurrentCharPtr = ReadFilePtr->CurrentLine;
	CharPtr = strcpy(ReadFilePtr->FileName, FileName);
	ReadFilePtr->NthLine = 0;
	*ErrIndexPtr = RF_NO_ERROR;
	return ReadFilePtr;
}

/*--------------------------------------------------------------------------*/
/* Cloture de la lecture des donnees										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_ReadFile(TReadFilePtr ReadFilePtr)
{
	fclose(ReadFilePtr->InputFile);
	free(ReadFilePtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Saute les espaces et tabulations											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| ReadFile_JumpBlanks		| Resultat de la recherche =		*/
/*			| RF_END_OF_LINE			| Fin de ligne atteinte				*/
/*			| RF_END_OF_FILE			| Fin de fichier atteinte			*/
/*			| RF_CHAR_FND				| Caractere trouve					*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TSearchResult ReadFile_JumpBlanks(TReadFilePtr ReadFilePtr)
{
	while ((*(ReadFilePtr->CurrentCharPtr) == RF_SPACE) ||
	(*(ReadFilePtr->CurrentCharPtr) == RF_TAB)) {
		/* Une tabulation ou un espace a ete trouve */
		/* On saute au prochain caractere			*/
		ReadFile_NextChar(ReadFilePtr);
	}
	if (*(ReadFilePtr->CurrentCharPtr) == RF_EOL)
		/* Fin de ligne atteinte */
		return RF_END_OF_LINE;
	if (*(ReadFilePtr->CurrentCharPtr) == 0)
		/* Fin de fichier atteinte */
		return RF_END_OF_FILE;
	/* Un caractere a ete trouve */
	return RF_CHAR_FND;
}

/*--------------------------------------------------------------------------*/
/* Saute a la prochaine ligne												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| NextLine					| Resultat de la recherche =		*/
/*			| RF_END_OF_FILE			| Fin de fichier atteinte			*/
/*			| RF_LINE_FND				| Ligne trouvee						*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TSearchResult ReadFile_NextLine(TReadFilePtr ReadFilePtr)
{
	char* CharPtr;

	CharPtr = fgets(ReadFilePtr->CurrentLine, UCHAR_MAX,
	ReadFilePtr->InputFile);
	if (!CharPtr) {
		/* Fin de fichier atteinte */
		return RF_END_OF_FILE;
	}
	/* Ligne trouvee */
	ReadFilePtr->NthLine++;
	ReadFilePtr->CurrentCharPtr = ReadFilePtr->CurrentLine;
	if (*(ReadFilePtr->CurrentCharPtr) == RF_CR_PC) {
		ReadFile_NextChar(ReadFilePtr);
	}
	return RF_LINE_FND;
}

/*--------------------------------------------------------------------------*/
/* Lecture d'un nombre entier positif										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| ReadFile_GetPos			| Nombre entier positif				*/
/* Erreur:	| ErrIndex					| Index d'erreur != RF_NO_ERROR = 	*/
/*			| RF_POS_INT_EXP			| Nombre entier positif attendu		*/
/*--------------------------------------------------------------------------*/
TPos ReadFile_Pos(TReadFilePtr ReadFilePtr, TErrIndex *ErrIndexPtr)
{
	char *CharPtr;			/* Pointeur sur un caractere	*/
	long int Long;			/* Nombre lu					*/
	
	Long = (long)strtol(ReadFilePtr->CurrentCharPtr, &CharPtr, 10);
	if ((ReadFilePtr->CurrentCharPtr == CharPtr) || (Long < 0)) {
		*ErrIndexPtr = RF_POS_INT_EXP;
		return 0;
	}
	ReadFilePtr->CurrentCharPtr = CharPtr;
	*ErrIndexPtr = RF_NO_ERROR;
	return (TPos)Long;
}

/*--------------------------------------------------------------------------*/
/* Lecture d'un nombre														*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| ReadFile_GetNbr			| Nombre							*/
/* Erreur:	| ErrIndex					| Index d'erreur != RF_NO_ERROR =	*/
/*			| RF_NBR_EXP				| Nombre attendu					*/
/*--------------------------------------------------------------------------*/
TNbr ReadFile_Nbr(TReadFilePtr ReadFilePtr, TErrIndex *ErrIndexPtr)
{
	char *CharPtr;			/* Pointeur sur un caractere	*/
	TNbr Nbr;				/* Nombre lu					*/

	Nbr = (TNbr)strtod(ReadFilePtr->CurrentCharPtr, &CharPtr);
	if (ReadFilePtr->CurrentCharPtr == CharPtr) {
		*ErrIndexPtr = RF_NBR_EXP;
		return 0.0;
	}
	ReadFilePtr->CurrentCharPtr = CharPtr;
	*ErrIndexPtr = RF_NO_ERROR;
	return Nbr;
}

/*--------------------------------------------------------------------------*/
/* Lecture d'un mot															*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| ReadFile_GetWord			| Mot								*/
/* Erreur:	| ReadFile_GetWord			| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RF_WRD_EXP				| Mot attendu						*/
/*			| RF_MEM_ERR				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TWordPtr ReadFile_Word(TReadFilePtr ReadFilePtr, TErrIndex *ErrIndexPtr)
{
	TWordPtr WordPtr;		/* Pointeur retourne	*/
	unsigned int EndWordOffset;	/* Taille du mot		*/
	
	if (!strchr(RF_START_WRD, *(ReadFilePtr->CurrentCharPtr))) {
		*ErrIndexPtr = RF_WRD_EXP;
		return NULL;
	}
	EndWordOffset = strspn(ReadFilePtr->CurrentCharPtr, RF_WRD_ALPH);
	WordPtr = Str_To_Word(ReadFilePtr->CurrentCharPtr, EndWordOffset);
	if (!WordPtr) {
		*ErrIndexPtr = RF_MEM_ERR;
		return NULL;
	}
	ReadFilePtr->CurrentCharPtr += EndWordOffset;
	*ErrIndexPtr = RF_NO_ERROR;
	return WordPtr;
}

/*--------------------------------------------------------------------------*/
/* Lecture d'une chaine														*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| ReadFile_Str				| Chaine							*/
/* Erreur:	| ReadFile_Str				| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RF_STAP_EXP				| "'" de debut attendu				*/
/*			| RF_EDAP_EXP				| "'" de fin attendu				*/
/*			| RF_MEM_ERR				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TStrPtr ReadFile_Str(TReadFilePtr ReadFilePtr, TErrIndex *ErrIndexPtr)
{
	TStrPtr StrPtr;			/* Pointeur retourne			*/
	TStrSize StrSize;		/* Taille de la chaine			*/
	char *CharPtr;			/* Pointeur sur un caractere	*/
	
	if (*(ReadFile_CurrentCharPtr(ReadFilePtr)) != RF_APOS) {
		*ErrIndexPtr = RF_STAP_EXP;
		return NULL;
	}
	ReadFile_NextChar(ReadFilePtr);
	CharPtr = strchr(ReadFile_CurrentCharPtr(ReadFilePtr), RF_APOS);
	if (!CharPtr) {
		*ErrIndexPtr = RF_EDAP_EXP;
		return NULL;
	}
	StrSize = (TStrSize)(CharPtr - ReadFile_CurrentCharPtr(ReadFilePtr));
	StrPtr = Str_To_Str(ReadFile_CurrentCharPtr(ReadFilePtr), StrSize);
	if (!StrPtr)	{
		*ErrIndexPtr = RF_MEM_ERR;
		return NULL;
	}
	ReadFile_CurrentCharPtr(ReadFilePtr) = ++CharPtr;
	*ErrIndexPtr = RF_NO_ERROR;
	return StrPtr;
}

/*--------------------------------------------------------------------------*/
/* Lecture d'une phrase														*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| ReadFile_Str				| Phrase							*/
/* Erreur:	| ReadFile_Str				| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RF_MEM_ERR				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSentPtr ReadFile_Sent(TReadFilePtr ReadFilePtr, TErrIndex *ErrIndexPtr)
{
	TSentPtr SentPtr;		/* Pointeur retourne			*/
	TSentSize SentSize;		/* Taille de la phrase			*/
	char *CharPtr;			/* Pointeur sur un caractere	*/
	
	/* Recherche du 1er caractere non affichable */
	CharPtr = ReadFile_CurrentCharPtr(ReadFilePtr);
	while ((*CharPtr != RF_EOL) && (*CharPtr != 0)) {
		CharPtr++;
	}
	
	SentSize = (TSentSize)(CharPtr - ReadFile_CurrentCharPtr(ReadFilePtr));
	SentPtr = Str_To_Sent(ReadFile_CurrentCharPtr(ReadFilePtr), SentSize);
	if (!SentPtr)	{
		*ErrIndexPtr = RF_MEM_ERR;
		return NULL;
	}
	ReadFile_CurrentCharPtr(ReadFilePtr) = CharPtr + SentSize;
	*ErrIndexPtr = RF_NO_ERROR;
	/* La chaine peut avoir une longueur nulle */
	return SentPtr;
}
