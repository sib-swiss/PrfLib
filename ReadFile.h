/****************************************************************************/
/*																			*/
/*	But: Definition de la lecture des fichiers.								*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TSearchResult						| 	-								*/
/*--------------------------------------------------------------------------*/
/*	TLineIndex							| 	-								*/
/*--------------------------------------------------------------------------*/
/*	TReadFilePtr						| 	I_ReadFile						*/
/*										|	Free_ReadFile					*/
/*										|	ReadFile_CurrentCharPtr			*/
/*										|	ReadFile_CurrentLine			*/
/*										|	ReadFile_FileName				*/
/*										|	ReadFile_NthLine				*/
/*										|	ReadFile_NextChar				*/
/*										|	ReadFile_JumpBlanks				*/
/*										|	ReadFile_NextLine				*/
/*										|	ReadFile_Pos					*/
/*										|	ReadFile_Nbr					*/
/*										|	ReadFile_Word					*/
/*										|	ReadFile_Str					*/
/*										|	ReadFile_Sent					*/
/****************************************************************************/

#ifndef _READFILE_
#define _READFILE_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "error.h"
#include "FileData.h"

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*====================*/
/* Numero des erreurs */
/*====================*/

#define RF_NO_ERROR		0
#define RF_MEM_ERR		1
#define RF_OPEN_ERR		2
#define RF_POS_INT_EXP	3
#define RF_NBR_EXP		4
#define RF_WRD_EXP		5
#define RF_STAP_EXP		6
#define RF_EDAP_EXP		7

/*========================*/
/* Constantes syntaxiques */
/*========================*/

#define RF_APOS			'\''
#define RF_PT			'.'

/*==========================*/
/* Resultat d'une recherche	*/
/*==========================*/

#define RF_ERROR		0
#define RF_END_OF_FILE	1
#define RF_CHAR_FND		2
#define RF_END_OF_LINE	3
#define RF_LINE_FND		4

/*==========*/
/* Tailles	*/
/*==========*/

#define RF_MAX_LINE_SIZE	UCHAR_MAX	/* Taille des lignes du fichier	*/
#define RF_FILENAME_SIZE	UCHAR_MAX	/* Taille du nom du fichier		*/

/*========================*/
/* Constantes syntaxiques */
/*========================*/

#define RF_TAB			'\t'		/* Tabulation						*/
#define RF_SPACE		' '			/* Espace							*/
#define RF_EOL			'\n'		/* Fin de ligne						*/
#define RF_CR_PC		10			/* Retour de chariot pour format PC	*/
#define RF_WRD_ALPH		"ABCDEFGHIJKLMNOPQRSTUVWXYZ\
abcdefghijklmnopqrstuvwxyz_1234567890"
#define RF_START_WRD 	"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"
#define RF_START_NBR	"1234567890+-"

/**************************/
/* DEFINITION DES DONNEES */
/**************************/

/*==========================================*/
/* Definition du resultat d'une recherche	*/
/*==========================================*/

typedef char TSearchResult;

/*==============================================*/
/*Structure des donnees de lecture d'un fichier	*/
/*==============================================*/

typedef unsigned int TLineIndex;
typedef struct TReadFile {
	char *CurrentCharPtr;				/* Pointeur sur le caractere courant	*/
	char CurrentLine[RF_MAX_LINE_SIZE];	/* Ligne courante						*/
	FILE *InputFile;					/* Fichier d'entree						*/
	char FileName[RF_FILENAME_SIZE];	/* Nom du fichier d'entree				*/
	TLineIndex NthLine;					/* No de ligne en cours de lecture		*/
} TReadFile;
typedef TReadFile *TReadFilePtr;

/*=========================*/
/* DEFINITION DES ROUTINES */
/*=========================*/

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
/*			| RF_OPEN_ERR				| Fichier non trouve				*/
/*--------------------------------------------------------------------------*/
TReadFilePtr I_ReadFile(char *FileName, TErrIndex *ErrIndexPtr);

/*--------------------------------------------------------------------------*/
/* Cloture de la lecture des donnees										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_ReadFile(TReadFilePtr ReadFilePtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le pointeur sur le caractere en lecture					*/
/*--------------------------------------------------------------------------*/
#define ReadFile_CurrentCharPtr(ReadFilePtr)\
((ReadFilePtr)->CurrentCharPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la ligne en lecture										*/
/*--------------------------------------------------------------------------*/
#define ReadFile_CurrentLine(ReadFilePtr)\
((ReadFilePtr)->CurrentLine)

/*--------------------------------------------------------------------------*/
/* Macro retournant le fichier en lecture									*/
/*--------------------------------------------------------------------------*/
#define ReadFile_FileName(ReadFilePtr)\
((ReadFilePtr)->FileName)

/*--------------------------------------------------------------------------*/
/* Macro retournant le numero de la ligne en cours de lecture				*/
/*--------------------------------------------------------------------------*/
#define ReadFile_NthLine(ReadFilePtr)\
((ReadFilePtr)->NthLine)

/*--------------------------------------------------------------------------*/
/* Macro sautant au prochain caractere de la ligne							*/
/*--------------------------------------------------------------------------*/
#define ReadFile_NextChar(ReadFilePtr)\
((ReadFilePtr)->CurrentCharPtr)++

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
TSearchResult ReadFile_JumpBlanks(TReadFilePtr ReadFilePtr);

/*--------------------------------------------------------------------------*/
/* Saute a la prochaine ligne												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| NextLine					| Resultat de la recherche =		*/
/*			| RF_END_OF_FILE			| Fin de fichier atteinte			*/
/*			| RF_LINE_FND				| Ligne trouvee						*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TSearchResult ReadFile_NextLine(TReadFilePtr ReadFilePtr);

/*--------------------------------------------------------------------------*/
/* Lecture d'un nombre entier positif										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| ReadFile_GetPos			| Nombre entier positif				*/
/* Erreur:	| ErrIndex					| Index d'erreur != RF_NO_ERROR = 	*/
/*			| RF_POS_INT_EXP			| Nombre entier positif attendu		*/
/*--------------------------------------------------------------------------*/
TPos ReadFile_Pos(TReadFilePtr ReadFilePtr, TErrIndex *ErrIndexPtr);

/*--------------------------------------------------------------------------*/
/* Lecture d'un nombre														*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| ReadFile_GetNbr			| Nombre							*/
/* Erreur:	| ErrIndex					| Index d'erreur != RF_NO_ERROR =	*/
/*			| RF_NBR_EXP				| Nombre attendu					*/
/*--------------------------------------------------------------------------*/
TNbr ReadFile_Nbr(TReadFilePtr ReadFilePtr, TErrIndex *ErrIndexPtr);

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
TWordPtr ReadFile_Word(TReadFilePtr ReadFilePtr, TErrIndex *ErrIndexPtr);

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
TStrPtr ReadFile_Str(TReadFilePtr ReadFilePtr, TErrIndex *ErrIndexPtr);

/*--------------------------------------------------------------------------*/
/* Lecture d'une phrase														*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFilePtr				| Donnees de lecture				*/
/* Sortie:	| ReadFile_Str				| Phrase							*/
/* Erreur:	| ReadFile_Str				| = NULL =>  						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RF_PT_EXP					| "." attendu						*/
/*			| RF_MEM_ERR				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TSentPtr ReadFile_Sent(TReadFilePtr ReadFilePtr, TErrIndex *ErrIndexPtr);

#endif
