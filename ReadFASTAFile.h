/****************************************************************************/
/*																			*/
/*	But: Definition de la lecture d'un fichier FASTA de sequences.			*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TReadFASTAFilePtr					| 	I_ReadFASTAFile					*/
/*										|	Free_ReadFASTAFile				*/
/*										|	ReadFASTAFile_CurrentCharPtr	*/
/*										|	ReadFASTAFile_CurrentLine		*/
/*										|	ReadFASTAFile_FileName			*/
/*										|	ReadFASTAFile_NthLine			*/
/*										|	ReadFASTAFile_NextChar			*/
/*										|	ReadFASTAFile_JumpBlanks		*/
/*										|	ReadFASTAFile_NextLine			*/
/*										|	ReadFASTAFile_Pos				*/
/*										|	ReadFASTAFile_Nbr				*/
/*										|	ReadFASTAFile_Word				*/
/*										|	ReadFASTAFile_NextSignLine		*/
/*										|	ReadFASTAFile_LineId			*/
/*										|	ReadFASTAFile_NextId			*/
/*										|	ReadFASTAFile_LineSeq			*/
/*										|	ReadFASTAFile_NextSQ			*/
/*										|	ReadFASTAFile_SeqFileData		*/
/****************************************************************************/

#ifndef _READFASTAFILE_
#define _READFASTAFILE_

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

#define RFF_NO_ERROR		RF_NO_ERROR
#define RFF_MEM_ERR			RF_MEM_ERR
#define RFF_OPEN_ERR		RF_OPEN_ERR
#define RFF_POS_INT_EXP		RF_POS_INT_EXP
#define RFF_NBR_EXP			RF_NBR_EXP
#define RFF_WRD_EXP			RF_WRD_EXP
#define RFF_STAP_EXP		RF_STAP_EXP
#define RFF_EDAP_EXP		RF_EDAP_EXP
#define RFF_SEQ_LENGTH_OVF	8
#define RFF_ID_EXP_UEOF		9
#define RFF_SQ_EXP_UEOF		10

/*========================*/
/* Constantes syntaxiques */
/*========================*/

#define RFF_TAB		RF_TAB
#define RFF_SPACE	RF_SPACE
#define RFF_EOL		RF_EOL

/*==========================*/
/* Resultat d'une recherche	*/
/*==========================*/

#define RFF_ERROR			RF_ERROR
#define RFF_END_OF_FILE		RF_END_OF_FILE
#define RFF_CHAR_FND		RF_CHAR_FND
#define RFF_END_OF_LINE		RF_END_OF_LINE
#define RFF_LINE_FND		RF_LINE_FND

/*=====================*/
/* Constante de taille */
/*=====================*/

#define RFF_MAX_SEQ_LENGTH	3000

/**************************/
/* DEFINITION DES DONNEES */
/**************************/

/*===================================*/
/* Donnees de lecture d'une sequence */
/*===================================*/

typedef TReadFilePtr TReadFASTAFilePtr;

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
#define I_ReadFASTAFile(FileName, ErrIndexPtr)\
(TReadFASTAFilePtr)I_ReadFile(FileName, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Macro de destruction des donnees de lecture d'une sequence 				*/
/*--------------------------------------------------------------------------*/
#define Free_ReadFASTAFile(ReadFASTAFilePtr)\
Free_ReadFile((TReadFilePtr)ReadFASTAFilePtr)

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le pointeur sur le caractere en lecture					*/
/*--------------------------------------------------------------------------*/
#define ReadFASTAFile_CurrentCharPtr(ReadFASTAFilePtr)\
ReadFile_CurrentCharPtr((TReadFilePtr)ReadFASTAFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la ligne en lecture										*/
/*--------------------------------------------------------------------------*/
#define ReadFASTAFile_CurrentLine(ReadFASTAFilePtr)\
ReadFile_CurrentLine((TReadFilePtr)ReadFASTAFilePtr)\

/*--------------------------------------------------------------------------*/
/* Macro retournant le fichier en lecture									*/
/*--------------------------------------------------------------------------*/
#define ReadFASTAFile_FileName(ReadFASTAFilePtr)\
ReadFile_FileName((TReadFilePtr)ReadFASTAFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le numero de la ligne en cours de lecture				*/
/*--------------------------------------------------------------------------*/
#define ReadFASTAFile_NthLine(ReadFASTAFilePtr)\
ReadFile_NthLine((TReadFilePtr)ReadFASTAFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro sautant au prochain caractere de la ligne							*/
/*--------------------------------------------------------------------------*/
#define ReadFASTAFile_NextChar(ReadFASTAFilePtr)\
ReadFile_NextChar((TReadFilePtr)ReadFASTAFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro sautant les espaces et tabulations									*/
/*--------------------------------------------------------------------------*/
#define ReadFASTAFile_JumpBlanks(ReadFASTAFilePtr)\
ReadFile_JumpBlanks((TReadFilePtr)ReadFASTAFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro sautant a la prochaine ligne										*/
/*--------------------------------------------------------------------------*/
#define ReadFASTAFile_NextLine(ReadFASTAFilePtr)\
ReadFile_NextLine((TReadFilePtr)ReadFASTAFilePtr)

/*--------------------------------------------------------------------------*/
/* Macro de lecture d'un mot												*/
/*--------------------------------------------------------------------------*/
#define ReadFASTAFile_Word(ReadFASTAFilePtr, ErrIndexPtr)\
ReadFile_Word((TReadFilePtr)ReadFASTAFilePtr, ErrIndexPtr)

/*--------------------------------------------------------------------------*/
/* Macro de lecture d'une phrase											*/
/*--------------------------------------------------------------------------*/
#define ReadFASTAFile_Sent(ReadFASTAFilePtr, ErrIndexPtr)\
ReadFile_Sent((TReadFilePtr)ReadFASTAFilePtr, ErrIndexPtr)

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
TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

/*--------------------------------------------------------------------------*/
/* Retourne la description depuis le caractere courant						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ReadFASTAFilePtr			| Donnees de lecture				*/
/* Sortie:	| ReadFASTAFile_LineDe		| Description						*/
/* Erreur:	| ErrIndex				 	| Index d'erreur != RPF_NO_ERROR =	*/
/*			| RFF_MEM_ERR				| Erreur allocation					*/
/*--------------------------------------------------------------------------*/
TSentPtr ReadFASTAFile_LineDe(TReadFASTAFilePtr ReadFASTAFilePtr,
TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

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
ReadFASTAFilePtr, TErrIndex *ErrIndexPtr);

#endif
