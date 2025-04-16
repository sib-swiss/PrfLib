/****************************************************************************/
/*																			*/
/*	But: Implementation des routines de manipulation d'un alphabet			*/
/*																			*/
/****************************************************************************/

#include <string.h>
#include "Alphabet.h"

/*******************************/
/* IMPLEMENTATION DES ROUTINES */
/*******************************/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Position d'une lettre dans l'alphabet a partir de 1						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlphPtr					| Alphabet							*/
/*			| Let						| Lettre							*/
/* Sortie:	| Alph_LetPos				| Position de la lettre				*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TAlphSize Alph_LetPos(TAlphPtr AlphPtr, TLet Let)
{
	char *LetPosPtr = strchr(AlphPtr, Let);
	
	return (LetPosPtr ? LetPosPtr - AlphPtr + 1 : 0);
}
