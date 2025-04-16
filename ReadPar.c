/****************************************************************************/
/*																			*/
/*	But: Implementation de la lecture des parametres d'un programme			*/
/*																			*/
/****************************************************************************/

#include "ReadPar.h"
#include <ctype.h>
#include <string.h>

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
char ProgPar(int argc, char *argv[], char **ParStrPtr, TErrIndex *ErrIndexPtr)
{
	static unsigned int ParNth = 1;	/* Numero du parametre en cours */
	char TheParChar;				/* Caractere du parametre		*/
	
	/* Verification de l'existence d'un parametre */
	if (ParNth == argc) {
		/* Plus de parametres */
		*ErrIndexPtr = RP_PAR_EXP;
		return 0;
	}
	
	/* Lecture du type de parametre s'il existe */
	if ((strlen(argv[ParNth]) == 2) && (argv[ParNth][0] == '-') &&
	(isalpha(argv[ParNth][1]))) {
		/* Lecture du type de parametre */
		TheParChar = argv[ParNth][1];
		/* Parametre suivant */
		ParNth++;
	}
	else {
		TheParChar = ' ';
	}

	/* Verification de l'existence d'un parametre */
	if (ParNth == argc) {
		/* Plus de parametres */
		*ParStrPtr = NULL;
		*ErrIndexPtr = RP_NO_ERROR;
		return TheParChar;
	}
	/* Lecture de la chaine */
	if (!((strlen(argv[ParNth]) == 2) && (argv[ParNth][0] == '-') &&
	(isalpha(argv[ParNth][1])))) {
		*ParStrPtr = argv[ParNth];
		/* Parametre suivant */
		ParNth++;
	}
	else {
		*ParStrPtr = NULL;
	}
	*ErrIndexPtr = RP_NO_ERROR;
	return TheParChar;
}
