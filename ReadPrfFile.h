/****************************************************************************/
/*																			*/
/*	But: Definition de la lecture d'un fichier de profils.					*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TReadPrfFilePtr						| 	I_ReadPrfFile					*/
/*										|	Free_ReadPrfFile				*/
/*										|	ReadPrfFile_CurrentCharPtr		*/
/*										|	ReadPrfFile_CurrentLine			*/
/*										|	ReadPrfFile_FileName			*/
/*										|	ReadPrfFile_NthLine				*/
/*										|	ReadPrfFile_NextChar			*/
/*										|	ReadPrfFile_JumpBlanks			*/
/*										|	ReadPrfFile_NextLine			*/
/*										|	ReadPrfFile_Pos					*/
/*										|	ReadPrfFile_Nbr					*/
/*										|	ReadPrfFile_Word				*/
/*										|	ReadPrfFile_Str					*/
/*										|	ReadPrfFile_NextSignLine		*/
/*										|	ReadPrfFile_LineId				*/
/*										|	ReadPrfFile_NextId				*/
/*										|	ReadPrfFile_LineDe				*/
/*										|	ReadPrfFile_NextDe				*/
/*										|	ReadPrfFile_LineNbrAc			*/
/*										|	ReadPrfFile_NextNbrAc			*/
/*										|	ReadPrfFile_NextMA				*/
/*										|	ReadPrfFile_JumpSpaces			*/
/*										|	ReadPrfFile_Keyword				*/
/*										|	ReadPrfFile_Val					*/
/*										|	ReadPrfFile_Ass					*/
/*										|	ReadPrfFile_Desc				*/
/*										|	ReadPrfFile_Prf					*/
/*										|	ReadPrfFile_PrfFileData			*/
/****************************************************************************/

#ifndef _READPRFFILE_
#define _READPRFFILE_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "ReadFile.h"
#include "PrfFileData.h"

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*====================*/
/* Numero des erreurs */
/*====================*/

#define RPF_NO_ERROR		RF_NO_ERROR
#define RPF_MEM_ERR			RF_MEM_ERR
#define RPF_OPEN_ERR		RF_OPEN_ERR
#define RPF_POS_INT_EXP		RF_POS_INT_EXP
#define RPF_NBR_EXP			RF_NBR_EXP
#define RPF_WRD_EXP			RF_WRD_EXP
#define RPF_STAP_EXP		RF_STAP_EXP
#define RPF_EDAP_EXP		RF_EDAP_EXP
#define RPF_SLSH_EXP		8
#define RPF_DBLPT_EXP		9
#define RPF_EQU_EXP_UEOF	10
#define RPF_EQU_EXP_UEOP	11
#define RPF_EQU_EXP			12
#define RPF_VAL_EXP_UEOF	13
#define RPF_VAL_EXP_UEOP	14
#define RPF_VAL_EXP			15
#define RPF_SEP_EXP_UEOF	16
#define RPF_SEP_EXP_UEOP	17
#define RPF_SEP_EXP			18
#define RPF_VAL_NBR_OVF		19
#define RPF_ASS_NBR_OVF		20
#define RPF_DESC_NBR_OVF	21
#define RPF_EMPTY_PRF		22
#define RPF_NO_PRF_ID		23
#define RPF_WRD_EXP_UEOL	24
#define RPF_WRD_EXP_UEOF	25
#define RPF_SEP_EXP_UEOL	26
#define RPF_PS_EXP_UEOL		27
#define RPF_PS_EXP_UEOF		28
#define RPF_ID_EXP_UEOF		29
#define RPF_AC_EXP_UEOF		30
#define RPF_AC_EXP			31
#define RPF_MA_EXP			32
#define RPF_MA_EXP_UEOP		33
#define RPF_MA_EXP_UEOF		34
#define RPF_DESC_EXP_UEOL	35
#define RPF_DESC_EXP_UEOF	36
#define RPF_DE_EXP_UEOL		37
#define RPF_DE_EXP_UEOF		38
#define RPF_DE_EXP			39


/*========================*/
/* Constantes syntaxiques */
/*========================*/

#define RPF_START_WRD 		RF_START_WRD
#define RPF_START_NBR		RF_START_NBR
#define RPF_APOS			RF_APOS
#define RPF_MAX_VALUES		UCHAR_MAX	/* Nbr max de val. par ass.		*/
#define RPF_MAX_ASSIGN		UCHAR_MAX	/* Nbr max d'ass. par desc.		*/
#define RPF_MAX_DESCR		4*UCHAR_MAX	/* Nbr max de desc. par profil	*/

/*==========================*/
/* Resultat d'une recherche	*/
/*==========================*/

#define RPF_ERROR			RF_ERROR
#define RPF_END_OF_FILE		RF_END_OF_FILE
#define RPF_CHAR_FND		RF_CHAR_FND
#define RPF_END_OF_LINE		RF_END_OF_LINE
#define RPF_LINE_FND		RF_LINE_FND
#define RPF_END_OF_PRF		5
#define RPF_ID_LINE			6
#define RPF_AC_LINE			7
#define RPF_DE_LINE			8
#define RPF_MA_LINE			9

/**************************/
/* DEFINITION DES DONNEES */
/**************************/

/*================================*/
/* Donnees de lecture d'un profil */
/*================================*/

typedef TReadFilePtr TReadPrfFilePtr;

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

/*=================================================*/
/* Manipulation des donnees de lecture d'un profil */
/*=================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction des donnees de lecture d'un profil 				*/
/*--------------------------------------------------------------------------*/
#define I_ReadPrfFile(FileName, ErrIndexPtr)\
(TReadPrfFilePtr)I_ReadFile(FileName, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Macro de destruction des donnees de lecture d'un profil 					*/
/*--------------------------------------------------------------------------*/
#define Free_ReadPrfFile(ReadPrfFilePtr)\
Free_ReadFile((TReadFilePtr)ReadPrfFilePtr)

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le pointeur sur le caractere en lecture					*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_CurrentCharPtr(ReadPrfFilePtr)\
ReadFile_CurrentCharPtr((TReadFilePtr)ReadPrfFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la ligne en lecture										*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_CurrentLine(ReadPrfFilePtr)\
ReadFile_CurrentLine((TReadFilePtr)ReadPrfFilePtr)\

/*--------------------------------------------------------------------------*/
/* Macro retournant le fichier en lecture									*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_FileName(ReadPrfFilePtr)\
ReadFile_FileName((TReadFilePtr)ReadPrfFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le numero de la ligne en cours de lecture				*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_NthLine(ReadPrfFilePtr)\
ReadFile_NthLine((TReadFilePtr)ReadPrfFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro sautant au prochain caractere de la ligne							*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_NextChar(ReadPrfFilePtr)\
ReadFile_NextChar((TReadFilePtr)ReadPrfFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro sautant les espaces et tabulations									*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_JumpBlanks(ReadPrfFilePtr)\
ReadFile_JumpBlanks((TReadFilePtr)ReadPrfFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro sautant a la prochaine ligne										*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_NextLine(ReadPrfFilePtr)\
ReadFile_NextLine((TReadFilePtr)ReadPrfFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro de lecture d'un nombre entier positif								*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_Pos(ReadPrfFilePtr, ErrIndexPtr)\
ReadFile_Pos((TReadFilePtr)ReadPrfFilePtr, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Macro de lecture d'un nombre												*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_Nbr(ReadPrfFilePtr, ErrIndexPtr)\
ReadFile_Nbr((TReadFilePtr)ReadPrfFilePtr, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Macro de lecture d'un mot												*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_Word(ReadPrfFilePtr, ErrIndexPtr)\
ReadFile_Word((TReadFilePtr)ReadPrfFilePtr, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Macro de lecture d'une phrase											*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_Sent(ReadPrfFilePtr, ErrIndexPtr)\
ReadFile_Sent((TReadFilePtr)ReadPrfFilePtr, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Macro de lecture d'une chaine											*/
/*--------------------------------------------------------------------------*/
#define ReadPrfFile_Str(ReadPrfFilePtr, ErrIndexPtr)\
ReadFile_Str((TReadFilePtr)ReadPrfFilePtr, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Saute a la prochaine ligne significative du fichier						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_NextSignLine	| Resultat de la recherche =		*/
/*			| RPF_END_OF_FILE			| Fin de fichier atteinte			*/
/*			| RPF_END_OF_PRF			| Fin de profil atteinte			*/
/*			| RPF_MA_LINE				| Ligne MA trouvee 					*/
/*			| RPF_ID_LINE				| Ligne ID trouvee 					*/
/*			| RPF_AC_LINE				| Ligne AC trouvee 					*/
/* Erreur:	| -							| 									*/
/*--------------------------------------------------------------------------*/
TSearchResult ReadPrfFile_NextSignLine(TReadPrfFilePtr ReadPrfFilePtr);

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
TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

/*--------------------------------------------------------------------------*/
/* Recherche la prochaine description dans le fichier						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_NextDe		| Description						*/
/* Erreur:	| ErrIndex					| Index d'erreur != RPF_NO_ERROR =	*/
/*			| RPF_DE_EXP_UEOF			| Ligne AC att, fin de fich. inatt.	*/
/*			| RPF_DE_EXP				| Ligne AC attendue					*/
/*			| RPF_DESC_EXP_UEOL			| PS att. fin de ligne inatt.		*/
/*			| RPF_DESC_EXP_UEOF			| PS att. fin de fichier inatt.		*/
/*			| RPF_PT_EXP				| Mot attendu						*/
/*			| RPF_MEM_ERR				| Erreur allocation					*/
/*--------------------------------------------------------------------------*/
TSentPtr ReadPrfFile_NextDe(TReadPrfFilePtr ReadPrfFilePtr,
TErrIndex *ErrIndexPtr);

/*--------------------------------------------------------------------------*/
/* Retourne nombre Prosite de la ligne courante								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadPrfFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadPrfFile_LineNbrAc		| nombre AC							*/
/* Erreur:	| ErrIndex				 	| Index d'erreur != RPF_NO_ERROR =	*/
/*			| RPF_PS_EXP_UEOL			| PS att. fin de ligne inatt.		*/
/*			| RPF_PS_EXP_UEOF			| PS att. fin de fichier inatt.		*/
/*			| RPF_WRD_EXP				| Mot attendu						*/
/*			| RPF_MEM_ERR				| Erreur allocation					*/
/*			| RPF_SEP_EXP_UEOL			| Separ. att. fin de ligne inatt.	*/
/*			| RPF_SEP_EXP_UEOF			| Separ. att. fin de fichier inatt.	*/
/*			| RPF_SEP_EXP				| Separateur attendu				*/
/*--------------------------------------------------------------------------*/
TWordPtr ReadPrfFile_LineNbrAc(TReadPrfFilePtr ReadPrfFilePtr,
TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

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
TValPtr ReadPrfFile_Val(TReadPrfFilePtr ReadPrfFilePtr, TErrIndex *ErrIndexPtr);

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
TAssPtr ReadPrfFile_Ass(TReadPrfFilePtr ReadPrfFilePtr, TErrIndex *ErrIndexPtr);

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
TSearchResult *SearchResultPtr, TErrIndex *ErrIndexPtr);

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
TPrfPtr ReadPrfFile_Prf(TReadPrfFilePtr ReadPrfFilePtr, TErrIndex *ErrIndexPtr);

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
char *IdStr, TErrIndex *ErrIndexPtr);

#endif
