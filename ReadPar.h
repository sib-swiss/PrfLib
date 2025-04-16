/****************************************************************************/
/*																			*/
/*	But: lecture des parametres d'un programme								*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	-									| 	ProgPar							*/
/****************************************************************************/

#ifndef _READPAR_
#define _READPAR_

#include "error.h"
#include <stddef.h>

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*====================*/
/* Numero des erreurs */
/*====================*/

#define RP_NO_ERROR		0	/* Pas d'erreur					*/
#define RP_PAR_EXP		1	/* Parametre attendu			*/

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

/*--------------------------------------------------------------------------*/
/* Lecture du prochain parametre											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| argc						| Nombre de parametres				*/
/*			| argv						| Parametres						*/
/* Sortie:	| ParStrPtr					| Ptr. sur chaine du parametre		*/
/*			| ProgPar					| Type de parametre de lu			*/
/* Erreur:	| ProgPar=NULL				| Erreur de lecture =>				*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| RP_PAR_EXP				| Parametre attendu					*/
/*--------------------------------------------------------------------------*/
char ProgPar(int argc, char *argv[], char **ParStrPtr, TErrIndex *ErrIndexPtr);

#endif
