/****************************************************************************/
/*																			*/
/*	But: Definition des routines de manipulation d'un profil				*/
/*																			*/
/****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "PrfFileData.h"

/*******************************/
/* IMPLEMENTATION DES ROUTINES */
/*******************************/

/*==========================*/
/* Manipulation des valeurs */
/*==========================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une valeur												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| -							| -									*/
/* Sortie:	| I_Val						| Valeur							*/
/* Erreur:	| I_Val=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TValPtr I_Val()
{
	TValPtr ValPtr;
	
	ValPtr = (TValPtr)malloc(sizeof(TVal));
	if (!ValPtr) {
		return NULL;
	}
	ValPtr->ValType = PFD_INFINITE;
	ValPtr->Data.Nbr = 0.0;
	return ValPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une valeur													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ValPtr					| Valeur							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Val(TValPtr ValPtr)
{
	switch (Val_Type(ValPtr)) {
		case PFD_A_STR:
			Free_Str(Val_Str(ValPtr));
			break;
		case PFD_A_NBR:
			break;
		case PFD_A_WORD:
			Free_Word(Val_Word(ValPtr));
			break;
		case PFD_INFINITE:
			break;
	}
	free(ValPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une valeur													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ValPtr					| Valeur							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Val(TValPtr ValPtr)
{
	switch (Val_Type(ValPtr)) {
		case PFD_A_STR:
			printf("String: %s\n", Val_Str(ValPtr));
			break;
		case PFD_A_NBR:
			printf("Number: %e\n", Val_Nbr(ValPtr));
			break;
		case PFD_A_WORD:
			printf("Word: %s\n", Val_Word(ValPtr));
			break;
		case PFD_INFINITE:
			printf("Number: Infinite value\n");
			break;
	}
}

/*===============================*/
/* Manipulation des assignations */
/*===============================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une assignation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MaxValNbr					| Taille de la liste des valeurs	*/
/*			| WordPtr					| Nom de la variable				*/
/* Sortie:	| I_Ass						| Assignation						*/
/* Erreur:	| I_Ass=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TAssPtr I_Ass(TValIndex MaxValNbr, TWordPtr WordPtr)
{
	TAssPtr AssPtr;
	
	AssPtr = (TAssPtr)malloc(sizeof(TAss));
	if (!AssPtr) {
		return NULL;
	}
	AssPtr->ValList = (TValPtr*)calloc(MaxValNbr, sizeof(TValPtr));
	if (!AssPtr->ValList) {
		free(AssPtr);
		return NULL;
	}
	AssPtr->MaxValNbr = MaxValNbr;
	AssPtr->WordPtr = WordPtr;
	AssPtr->ValNbr = 0;
	return AssPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une assignation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AssPtr					| Assignation						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Ass(TAssPtr AssPtr)
{
	TValIndex ValIndex;
	
	Free_Word(Ass_Word(AssPtr));
	for (ValIndex = 0; ValIndex < Ass_ValNbr(AssPtr); ValIndex++)
		Free_Val(Ass_ValNth(AssPtr, ValIndex));
	free(AssPtr->ValList);
	free(AssPtr);
}

/*--------------------------------------------------------------------------*/
/* Recalibration de la liste des valeurs									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AssPtr					| Assignation						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Ass_ResizeValList(TAssPtr AssPtr)
{
	AssPtr->ValList = (TValPtr*)realloc(AssPtr->ValList,
	AssPtr->ValNbr*sizeof(TValPtr));
	AssPtr->MaxValNbr = AssPtr->ValNbr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une assignation												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AssPtr					| Assignation						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Ass(TAssPtr AssPtr)
{
	TValIndex ValIndex;
	
	printf("Variable name: %s\n", Ass_Word(AssPtr));
	printf("Vals:\n");
	for (ValIndex = 0; ValIndex < Ass_ValNbr(AssPtr); ValIndex++)
		Print_Val(Ass_ValNth(AssPtr, ValIndex));
}

/*===============================*/
/* Manipulation des descriptions */
/*===============================*/
	
/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une description											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MaxAssNbr					| Taille de la liste des ass.		*/
/*			| KeyWordPtr				| Mot-cle							*/
/* Sortie:	| I_Desc					| Description						*/
/* Erreur:	| I_Desc=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TDescPtr I_Desc(TAssIndex MaxAssNbr, TWordPtr KeyWordPtr)
{
	TDescPtr DescPtr;
	
	DescPtr = (TDescPtr)malloc(sizeof(TDesc));
	if (!DescPtr) {
		return NULL;
	}
	DescPtr->AssList = (TAssPtr*)calloc(MaxAssNbr, sizeof(TAssPtr));
	if (!DescPtr->AssList) {
		free(DescPtr);
		return NULL;
	}
	DescPtr->MaxAssNbr = MaxAssNbr;
	DescPtr->KeywordPtr = KeyWordPtr;
	DescPtr->AssNbr = 0;
	return DescPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une description											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DescPtr					| Description						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Desc(TDescPtr DescPtr)
{
	TAssIndex AssIndex;
	
	Free_Word(Desc_Keyword(DescPtr));
	for (AssIndex = 0; AssIndex < Desc_AssNbr(DescPtr); AssIndex++)
		Free_Ass(Desc_AssNth(DescPtr, AssIndex));
	free(DescPtr->AssList);
	free(DescPtr);
}

/*--------------------------------------------------------------------------*/
/* Recalibration de la liste des assignations								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DescPtr					| Description						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Desc_ResizeAssList(TDescPtr DescPtr)
{
	DescPtr->AssList = (TAssPtr*)realloc(DescPtr->AssList,
	DescPtr->AssNbr*sizeof(TAssPtr));
	DescPtr->MaxAssNbr = DescPtr->AssNbr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une description												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DescPtr					| Description						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Desc(TDescPtr DescPtr)
{
	TAssIndex AssIndex;

	printf("Desc name: %s\n", Desc_Keyword(DescPtr));
	printf("Assignations:\n");
	for (AssIndex = 0; AssIndex < Desc_AssNbr(DescPtr); AssIndex++)
		Print_Ass(Desc_AssNth(DescPtr, AssIndex));
}

/*==========================*/
/* Manipulation des profils */
/*==========================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'un profil													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MaxDescNbr				| Taille de la liste des descr.		*/
/* Sortie:	| I_Prf						| Profil							*/
/* Erreur:	| I_Prf=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TPrfPtr I_Prf(TDescIndex MaxDescNbr)
{
	TPrfPtr PrfPtr;
	
	PrfPtr = (TPrfPtr)malloc(sizeof(TPrf));
	if (!PrfPtr) {
		return NULL;
	}
	PrfPtr->DescList = (TDescPtr*)calloc(MaxDescNbr, sizeof(TDescPtr));
	if (!PrfPtr->DescList) {
		free(PrfPtr);
		return NULL;
	}
	PrfPtr->MaxDescNbr = MaxDescNbr;
	PrfPtr->DescNbr = 0;
	return PrfPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'un profil													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfPtr					| Profil							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Prf(TPrfPtr PrfPtr)
{
	TDescIndex DescIndex;

	for (DescIndex = 0; DescIndex < Prf_DescNbr(PrfPtr); DescIndex++)
		Free_Desc(Prf_DescNth(PrfPtr, DescIndex));
	free(PrfPtr->DescList);
	free(PrfPtr);
}

/*--------------------------------------------------------------------------*/
/* Recalibration de la liste des descriptions								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfPtr					| Profil							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Prf_ResizeDescList(TPrfPtr PrfPtr)
{
	PrfPtr->DescList = (TDescPtr*)realloc(PrfPtr->DescList,
	PrfPtr->DescNbr*sizeof(TDescPtr));
	PrfPtr->MaxDescNbr = PrfPtr->DescNbr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un profil													*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfPtr					| Profil							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Prf(TPrfPtr PrfPtr)
{
	TDescIndex DescIndex;

	printf("Profile definition\n");
	printf("Descriptions:\n");
	for (DescIndex = 0; DescIndex < Prf_DescNbr(PrfPtr); DescIndex++)
		Print_Desc(Prf_DescNth(PrfPtr, DescIndex));
}

/*===============================================*/
/* Manipulation des donnees du fichier de profil */
/*===============================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction des donnees du fichier de profil							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Id						| Identificateur du profil			*/
/*			| De						| Description du profil				*/
/*			| NbrAc						| Nombre Prosite du profil			*/
/*			| PrfPtr					| Profil							*/
/* Sortie:	| I_PrfFileData				| Donnees du fichier de profil		*/
/* Erreur:	| I_PrfFileData=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TPrfFileDataPtr I_PrfFileData(TWordPtr Id, TSentPtr De, TWordPtr NbrAc,
TPrfPtr PrfPtr)
{
	TPrfFileDataPtr PrfFileDataPtr;
	
	PrfFileDataPtr = (TPrfFileDataPtr)malloc(sizeof(TPrfFileData));
	if (!PrfFileDataPtr) return NULL;
	PrfFileDataPtr->Id = Id;
	PrfFileDataPtr->De = De;
	PrfFileDataPtr->NbrAc = NbrAc;
	PrfFileDataPtr->PrfPtr = PrfPtr;
	return PrfFileDataPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction des donnees du fichier de profil								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfFileDataPtr			| Donnees du fichier de profil		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PrfFileData(TPrfFileDataPtr PrfFileDataPtr)
{
	Free_Word(PrfFileDataPtr->Id);
	Free_Sent(PrfFileDataPtr->De);
	Free_Word(PrfFileDataPtr->NbrAc);
	Free_Prf(PrfFileDataPtr->PrfPtr);
	free(PrfFileDataPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression des donnees du fichier de profil								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfFileDataPtr			| Donnees du fichier de profil		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_PrfFileData(TPrfFileDataPtr PrfFileDataPtr)
{
	printf("Profile ID:");
	Print_Word(PrfFileData_Id(PrfFileDataPtr));
	printf("\n");
	printf("Profile description:");
	Print_Sent(PrfFileData_De(PrfFileDataPtr));
	printf("\n");
	printf("Prosite number: %d\n", PrfFileData_NbrAc(PrfFileDataPtr));
	Print_Prf(PrfFileData_Prf(PrfFileDataPtr));
}
