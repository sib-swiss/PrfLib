/****************************************************************************/
/*																			*/
/*	But: Definition de la lecture d'un fichier de sequences.				*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TReadSeqFilePtr						| 	I_ReadSeqFile					*/
/*										|	Free_ReadSeqFile				*/
/*										|	ReadSeqFile_CurrentCharPtr		*/
/*										|	ReadSeqFile_CurrentLine			*/
/*										|	ReadSeqFile_FileName			*/
/*										|	ReadSeqFile_NthLine				*/
/*										|	ReadSeqFile_NextChar			*/
/*										|	ReadSeqFile_JumpBlanks			*/
/*										|	ReadSeqFile_NextLine			*/
/*										|	ReadSeqFile_Pos					*/
/*										|	ReadSeqFile_Nbr					*/
/*										|	ReadSeqFile_Word				*/
/*										|	ReadSeqFile_NextSignLine		*/
/*										|	ReadSeqFile_LineId				*/
/*										|	ReadSeqFile_NextId				*/
/*										|	ReadSeqFile_LineSeq				*/
/*										|	ReadSeqFile_NextSQ				*/
/*										|	ReadSeqFile_SeqFileData			*/
/****************************************************************************/

#ifndef _READSEQFILE_
#define _READSEQFILE_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ReadFile.h"
#include "SeqFileData.h"

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*====================*/
/* Numero des erreurs */
/*====================*/

#define RSF_NO_ERROR		RF_NO_ERROR
#define RSF_MEM_ERR			RF_MEM_ERR
#define RSF_OPEN_ERR		RF_OPEN_ERR
#define RSF_POS_INT_EXP		RF_POS_INT_EXP
#define RSF_NBR_EXP			RF_NBR_EXP
#define RSF_WRD_EXP			RF_WRD_EXP
#define RSF_STAP_EXP		RF_STAP_EXP
#define RSF_EDAP_EXP		RF_EDAP_EXP
#define RSF_WRD_EXP_UEOL	8
#define RSF_WRD_EXP_UEOF	9
#define RSF_POS_EXP_UEOL	10
#define RSF_POS_EXP_UEOF	11
#define RSF_BAD_LENGTH		12
#define RSF_ID_EXP_UEOF		13
#define RSF_SQ_EXP_UEOF		14
#define RSF_SQ_EXP			15
#define RSF_SEQ_EXP			16
#define RSF_DESC_EXP_UEOL	17
#define RSF_DESC_EXP_UEOF	18
#define RSF_DE_EXP_UEOL		19
#define RSF_DE_EXP_UEOF		20
#define RSF_DE_EXP			21
#define RSF_DE_LINE_OVF		22

/*=======================*/
/* Constantes de tailles */
/*=======================*/

#define RSF_DE_NBR			255

/*========================*/
/* Constantes syntaxiques */
/*========================*/

#define RSF_TAB		RF_TAB
#define RSF_SPACE	RF_SPACE
#define RSF_EOL		RF_EOL

/*==========================*/
/* Resultat d'une recherche	*/
/*==========================*/

#define RSF_ERROR			RF_ERROR
#define RSF_END_OF_FILE		RF_END_OF_FILE
#define RSF_CHAR_FND		RF_CHAR_FND
#define RSF_END_OF_LINE		RF_END_OF_LINE
#define RSF_LINE_FND		RF_LINE_FND
#define RSF_ID_LINE			5
#define RSF_SQ_LINE			6
#define RSF_END_OF_SEQ		7
#define RSF_DE_LINE			8

/**************************/
/* DEFINITION DES DONNEES */
/**************************/

/*===================================*/
/* Donnees de lecture d'une sequence */
/*===================================*/

typedef TReadFilePtr TReadSeqFilePtr;

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

/*=====================================*/
/* Manipulation des donnees de lecture */
/*=====================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Macro de construction des donnees de lecture d'une sequence 				*/
/*--------------------------------------------------------------------------*/
#define I_ReadSeqFile(FileName, ErrIndexPtr)\
(TReadSeqFilePtr)I_ReadFile(FileName, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Macro de destruction des donnees de lecture d'une sequence 				*/
/*--------------------------------------------------------------------------*/
#define Free_ReadSeqFile(ReadSeqFilePtr)\
Free_ReadFile((TReadFilePtr)ReadSeqFilePtr)

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le pointeur sur le caractere en lecture					*/
/*--------------------------------------------------------------------------*/
#define ReadSeqFile_CurrentCharPtr(ReadSeqFilePtr)\
ReadFile_CurrentCharPtr((TReadFilePtr)ReadSeqFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la ligne en lecture										*/
/*--------------------------------------------------------------------------*/
#define ReadSeqFile_CurrentLine(ReadSeqFilePtr)\
ReadFile_CurrentLine((TReadFilePtr)ReadSeqFilePtr)\

/*--------------------------------------------------------------------------*/
/* Macro retournant le fichier en lecture									*/
/*--------------------------------------------------------------------------*/
#define ReadSeqFile_FileName(ReadSeqFilePtr)\
ReadFile_FileName((TReadFilePtr)ReadSeqFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le numero de la ligne en cours de lecture				*/
/*--------------------------------------------------------------------------*/
#define ReadSeqFile_NthLine(ReadSeqFilePtr)\
ReadFile_NthLine((TReadFilePtr)ReadSeqFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro sautant au prochain caractere de la ligne							*/
/*--------------------------------------------------------------------------*/
#define ReadSeqFile_NextChar(ReadSeqFilePtr)\
ReadFile_NextChar((TReadFilePtr)ReadSeqFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro sautant les espaces et tabulations									*/
/*--------------------------------------------------------------------------*/
#define ReadSeqFile_JumpBlanks(ReadSeqFilePtr)\
ReadFile_JumpBlanks((TReadFilePtr)ReadSeqFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro sautant a la prochaine ligne										*/
/*--------------------------------------------------------------------------*/
#define ReadSeqFile_NextLine(ReadSeqFilePtr)\
ReadFile_NextLine((TReadFilePtr)ReadSeqFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro de lecture d'un nombre entier positif								*/
/*--------------------------------------------------------------------------*/
#define ReadSeqFile_Pos(ReadSeqFilePtr, ErrIndexPtr)\
ReadFile_Pos((TReadFilePtr)ReadSeqFilePtr, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Macro de lecture d'un nombre												*/
/*--------------------------------------------------------------------------*/
#define ReadSeqFile_Nbr(ReadSeqFilePtr, ErrIndexPtr)\
ReadFile_Nbr((TReadFilePtr)ReadSeqFilePtr, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Macro de lecture d'un mot												*/
/*--------------------------------------------------------------------------*/
#define ReadSeqFile_Word(ReadSeqFilePtr, ErrIndexPtr)\
ReadFile_Word((TReadFilePtr)ReadSeqFilePtr, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Macro de lecture d'une phrase											*/
/*--------------------------------------------------------------------------*/
#define ReadSeqFile_Sent(ReadSeqFilePtr, ErrIndexPtr)\
ReadFile_Sent((TReadFilePtr)ReadSeqFilePtr, ErrIndexPtr)

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
TSearchResult ReadSeqFile_NextSignLine(TReadSeqFilePtr ReadSeqFilePtr);

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
TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

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
*SearchResultPtr, TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

#endif
