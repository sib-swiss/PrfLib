/****************************************************************************/
/*																			*/
/*	But:  Implementation des types generaux.								*/
/*																			*/
/****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "GeneralTypes.h"

/*******************************/
/* IMPLEMENTATION DES ROUTINES */
/*******************************/

/*========================================*/
/* Manipulation des chaines de caracteres */
/*========================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une chaine de caracteres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CharStrSize				| Taille de la chaine				*/
/* Sortie:	| I_CharStr					| Chaine							*/
/* Erreur:	| I_CharStr=NULL			| Erreur d'allocation				*/
/*--------------------------------------------------------------------------*/
TCharStr I_CharStr(TCharStrSize CharStrSize)
{
	TCharStr CharStr;
	
	CharStr = (TChar*)calloc(CharStrSize + 1, sizeof(TChar));
	if (!CharStr) {
		return NULL;
	}
	return CharStr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une chaine de caracteres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CharStr					| Chaine							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_CharStr(TCharStr CharStr)
{
	free(CharStr);
}

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une chaine a partir de n caracteres						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CharStr					| Chaine							*/
/* Sortie:	| CharStr_ToUpper			| Chaine convertie					*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TCharStr CharStr_ToUpper(TCharStr CharStr)
{
	unsigned int CharIndex;
	
	/* Conversion en majuscules */
	for (CharIndex = 0; CharIndex < CharStr_Length(CharStr); CharIndex++) {
		CharStr[CharIndex] = toupper(CharStr[CharIndex]);
	}
	return CharStr;

}

/*--------------------------------------------------------------------------*/
/* Construction d'un mot a partir de n caracteres							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Str						| Chaine							*/
/*			| CharNbr					| Nbr de car a prendre de la chaine	*/
/* Sortie:	| nChar_To_CharStr			| Chaine							*/
/* Erreur:	| nChar_To_CharStr=NULL		| Erreur d'allocation				*/
/*--------------------------------------------------------------------------*/
TCharStr nChar_To_CharStr(char *Str, unsigned int CharNbr)
{
	TCharStr CharStr;
	
	CharStr = I_CharStr((TCharStrSize)CharNbr);
	if (!CharStr) {
		return NULL;
	}
	CharStr = (TCharStr)strncpy((char*)CharStr, Str, (size_t)CharNbr);
	CharStr[CharNbr] = 0;
	return CharStr;
}

/*--------------------------------------------------------------------------*/
/* Construction d'un mot a partir d'une chaine								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Str						| Chaine							*/
/* Sortie:	| Str_To_CharStr			| Chaine							*/
/* Erreur:	| Str_To_CharStr=NULL		| Erreur d'allocation				*/
/*--------------------------------------------------------------------------*/
TCharStr Str_To_CharStr(char *Str)
{
	TCharStr CharStr;
	
	CharStr = I_CharStr((TCharStrSize)strlen(Str));
	if (!CharStr) {
		return NULL;
	}
	CharStr = (TCharStr)strcpy((char*)CharStr, Str);
	return CharStr;
}

/*=========================*/
/* Manipulation des listes */
/*=========================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une liste													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MaxPtrNbr					| Nombre maximum d'elements			*/
/* Sortie:	| I_List					| Liste								*/
/* Erreur:	| I_List=NULL				| Erreur d'allocation				*/
/*--------------------------------------------------------------------------*/
TListPtr I_List(TPtrIndex MaxPtrNbr)
{
	TListPtr ListPtr;
	
	ListPtr = (TListPtr)malloc(sizeof(TList));
	if (!ListPtr) {
		/* Erreur d'allocation */
		return NULL;
	}
	ListPtr->PtrArray = (void*)calloc(MaxPtrNbr, sizeof(void*));
	if (!(ListPtr->PtrArray)) {
		/* Erreur d'allocation */
		free(ListPtr);
		return NULL;
	}
	ListPtr->PtrNbr = 0;
	ListPtr->MaxPtrNbr = MaxPtrNbr;
	return ListPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une liste sans ses element									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ListPtr					| Liste								*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_List(TListPtr ListPtr)
{
	free(ListPtr->PtrArray);
	free(ListPtr);
}

/*--------------------------------------------------------------------------*/
/* Recalibration d'une liste												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ListPtr					| Liste								*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Resize_List(TListPtr ListPtr)
{
	ListPtr->PtrArray = (void*)realloc(ListPtr->PtrArray, (ListPtr->PtrNbr)*
	sizeof(void*));
	ListPtr->MaxPtrNbr = ListPtr->PtrNbr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Routine indiquant si la liste est complete								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ListPtr					| Liste								*/
/* Sortie:	| List_Complete				| Etat de la liste					*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TBoolean List_Complete(TListPtr ListPtr)
{
	TPtrIndex PtrIndex;
	
	for (PtrIndex = 0; PtrIndex < List_PtrNbr(ListPtr); PtrIndex++) {
		if (List_PtrNth(ListPtr, PtrIndex) == NULL) return FALSE;
	}
	return TRUE;
}
