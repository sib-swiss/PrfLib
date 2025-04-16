/****************************************************************************/
/*																			*/
/*	But: Implementation des routines de manipulation des donnees de profil	*/
/*																			*/
/****************************************************************************/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "PrfData.h"

/*******************************/
/* IMPLEMENTATION DES ROUTINES */
/*******************************/

/*=============================*/
/* Manipulation des topologies */
/*=============================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une topologie												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Topo						| Topologie							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Topo(TTopo Topo)
{
	switch (Topo) {
		case PD_TOPO_LINEAR:
			printf("Linear");
			break;
		case PD_TOPO_CIRCULAR:
			printf("Circular");
			break;
	}
}

/*===========================================*/
/* Manipulation des specifications generales */
/*===========================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une specification generale								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| AlphPtr					| Alphabet							*/
/* Sortie:	| I_GenSpec					| Specification generale			*/
/* Erreur:	| I_GenSpec=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TGenSpecPtr I_GenSpec(TAlphPtr AlphPtr)
{
	TGenSpecPtr GenSpecPtr;
	
	GenSpecPtr = (TGenSpecPtr)malloc(sizeof(TGenSpec));
	if (!GenSpecPtr) {
		/* Erreur d'allocation */
		return NULL;
	}
	GenSpecPtr->AlphPtr = AlphPtr;
	GenSpecPtr->Topo = PD_TOPO_LINEAR;
	GenSpecPtr->PosNbr = 0;
	return GenSpecPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une specification generale									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| GenSpecPtr				| Specification generale			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_GenSpec(TGenSpecPtr GenSpecPtr)
{
	Free_Alph(GenSpecPtr->AlphPtr);
	free(GenSpecPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une specification generale									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| GenSpecPtr				| Specification generale			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_GenSpec(TGenSpecPtr GenSpecPtr)
{
	printf("Alphabet: ");
	Print_Alph(GenSpec_Alph(GenSpecPtr));
	printf("\n");
	printf("Topology: ");
	Print_Topo(GenSpec_Topo(GenSpecPtr));
	printf("\n");
	printf("Positions number: ");
	Print_PosIndex(GenSpec_PosNbr(GenSpecPtr));
	printf("\n");
}

/*==========================================*/
/* Manipulation des definitions d'exclusion */
/*==========================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une definition d'exclusion									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DisjointDef				| Definition d'exclusion			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_DisjointDef(TDisjointDef DisjointDef)
{
	switch (DisjointDef) {
		case PD_UNIQUE:
			printf("Unique");
			break;
		case PD_PROTECT:
			printf("Protect");
			break;
	}
}

/*==================================================*/
/* Manipulation des listes de parametres d'excusion */
/*==================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une liste de parametres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ParNbr					| Nombre de parametres				*/
/* Sortie:	| I_DisjointParList			| Liste de parametres				*/
/* Erreur:	| I_DisjointParList=NULL	| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TDisjointParListPtr I_DisjointParList(TDisjointParIndex ParNbr)
{
	TDisjointParListPtr DisjointParListPtr;
	
	DisjointParListPtr =
	(TDisjointParListPtr)malloc(sizeof(TDisjointParList));
	if (!DisjointParListPtr) {
		/* Erreur allocation */
		return NULL;
	}
	DisjointParListPtr->List = (TDisjointPar*)calloc(ParNbr,
	sizeof(TDisjointPar));
	if (!(DisjointParListPtr->List)) {
		/* Erreur allocation */
		free(DisjointParListPtr);
		return NULL;
	}
	DisjointParListPtr->ParNbr = ParNbr;
	return DisjointParListPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une liste de parametres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| TDisjointParListPtr		| Liste de parametres				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_DisjointParList(TDisjointParListPtr DisjointParListPtr)
{
	free(DisjointParListPtr->List);
	free(DisjointParListPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une liste de parametres										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DisjointParListPtr		| Liste de parametres				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_DisjointParList(TDisjointParListPtr DisjointParListPtr)
{
	TDisjointParIndex ParIndex;

	for (ParIndex = 1; ParIndex < DisjointParList_ParNbr(DisjointParListPtr)
	+ 1; ParIndex++) {
		Print_DisjointPar(DisjointParList_ParNth(DisjointParListPtr,
		ParIndex));
		printf("\n");
	}
}

/*=============================*/
/* Manipulation des exclusions */
/*=============================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une exclusion												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DisjointParListPtr		| Liste des parametres				*/
/* Sortie:	| I_Disjoint				| Exclusion							*/
/* Erreur:	| I_Disjoint=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TDisjointPtr I_Disjoint(TDisjointParListPtr DisjointParListPtr)
{
	TDisjointPtr DisjointPtr;
	
	DisjointPtr = (TDisjointPtr)malloc(sizeof(TDisjoint));
	if (!DisjointPtr) {
		/* Erreur d'allocation */
		return NULL;
	}
	DisjointPtr->ParListPtr = DisjointParListPtr;
	return DisjointPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une exclusion												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DisjointPtr				| Exclusion							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Disjoint(TDisjointPtr DisjointPtr)
{
	Free_DisjointParList(DisjointPtr->ParListPtr);
	free(DisjointPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une exclusion												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| DisjointPtr				| Exclusion							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Disjoint(TDisjointPtr DisjointPtr)
{
	printf("Definition: ");
	Print_DisjointDef(Disjoint_Def(DisjointPtr));
	printf("\n");
	printf("Parameters:\n");
	Print_DisjointParList(Disjoint_ParList(DisjointPtr));
}

/*==============================================*/
/* Manipulation des fonctions de normalisations */
/*==============================================*/

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une fonction de normalisation								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormFct					| Fonction de normalisation			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_NormFct(TNormFct NormFct)
{
	switch (NormFct) {
		case PD_NORM_LINEAR:
			printf("Linear\n");
			break;
		case PD_NORM_GRIB:
			printf("Gribskov\n");
			break;
	}
}

/*========================================================*/
/* Manipulation des listes de parametres de normalisation */
/*========================================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une liste de parametres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ParNbr					| Nombre de parametres				*/
/* Sortie:	| I_NormParList				| Liste de parametres				*/
/* Erreur:	| I_NormParList=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TNormParListPtr I_NormParList(TNormParIndex ParNbr)
{
	TNormParListPtr NormParListPtr;
	
	NormParListPtr =
	(TNormParListPtr)malloc(sizeof(TNormParList));
	if (!NormParListPtr) {
		/* Erreur allocation */
		return NULL;
	}
	NormParListPtr->List = (TNormPar*)calloc(ParNbr,
	sizeof(TNormPar));
	if (!(NormParListPtr->List)) {
		/* Erreur allocation */
		free(NormParListPtr);
		return NULL;
	}
	NormParListPtr->ParNbr = ParNbr;
	return NormParListPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une liste de parametres									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| TNormParListPtr			| Liste de parametres				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_NormParList(TNormParListPtr NormParListPtr)
{
	free(NormParListPtr->List);
	free(NormParListPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une liste de parametres										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormParListPtr			| Liste de parametres				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_NormParList(TNormParListPtr NormParListPtr)
{
	TNormParIndex ParIndex;

	for (ParIndex = 1; ParIndex < NormParList_ParNbr(NormParListPtr)
	+ 1; ParIndex++) {
		Print_NormPar(NormParList_ParNth(NormParListPtr,
		ParIndex));
		printf("\n");
	}
}

/*=================================*/
/* Manipulation des normalisations */
/*=================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une normalisation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormParListPtr			| Liste de parametres				*/
/*			| Text						| Texte								*/
/* Sortie:	| I_Norm					| Normalisation						*/
/* Erreur:	| I_Norm=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TNormPtr I_Norm(TNormParListPtr NormParListPtr, TText Text)
{
	TNormPtr NormPtr;
	
	NormPtr = (TNormPtr)malloc(sizeof(TNorm));
	if (!NormPtr) {
		/* Erreur d'allocation */
		return NULL;
	}
	NormPtr->ParListPtr = NormParListPtr;
	NormPtr->Text = Text;
	return NormPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une normalisation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormPtr					| Normalisation						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_Norm(TNormPtr NormPtr)
{
	Free_NormParList(NormPtr->ParListPtr);
	if (NormPtr->Text) Free_Text(NormPtr->Text);
	free(NormPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une normalisation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormPtr					| Normalisation						*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_Norm(TNormPtr NormPtr)
{
	printf("Function: ");
	Print_NormFct(Norm_Fct(NormPtr));
	printf("Priority: ");
	Print_NormPrty(Norm_Prty(NormPtr));
	
	printf("Parameters:\n");
	Print_NormParList(Norm_ParList(NormPtr));
	
	if (Norm_Text(NormPtr)) {
		printf("Description: ");
		Print_Text(Norm_Text(NormPtr));
		printf("\n");
	}
}

/*===========================================*/
/* Manipulation des listes de normalisations */
/*===========================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Desctruction d'une liste de normalisations								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormListPtr				| Liste de normalisations			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_NormList(TNormListPtr NormListPtr)
{
	TNormIndex NormIndex;
	
	for (NormIndex = 1; NormIndex <= NormList_NormNbr(NormListPtr);
	NormIndex++) {
		if (NormList_NormNth(NormListPtr, NormIndex))
			Free_Norm(NormList_NormNth(NormListPtr, NormIndex));
	}
	Free_List((TListPtr)NormListPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Verifie si les priorites sont toutes presentes							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormListPtr				| Liste des normalisations			*/
/* Sortie:	| NormList_PrtyComplete		| Etat des priorites				*/
/* Erreur:	| NormList_PrtyComplete		| = FALSE =>						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PD_MEM_ERR				| Allocation memoire				*/
/*			| PD_OUT_PRTY				| Priorite hors rangee				*/
/*			| PD_DBL_PRTY				| Priorite deja utilisee			*/
/*			| PD_PRTY_MISS				| Priorite manquante				*/
/*--------------------------------------------------------------------------*/
TBoolean NormList_PrtyComplete(TNormListPtr NormListPtr, TErrIndex *ErrIndexPtr)
{
	TBoolean *TestArray;
	TNormIndex NormIndex;
	
	TestArray = (TBoolean*)calloc(NormList_NormNbr(NormListPtr),
	sizeof(TBoolean));
	/* Le tableau est initialise a FALSE */
	if (!TestArray) {
		/* Erreur d'allocation */
		*ErrIndexPtr = PD_MEM_ERR;
		return FALSE;
	}
	/* Parcours des priorites */
	for (NormIndex = 1; NormIndex <= NormList_NormNbr(NormListPtr);
	NormIndex++) {
		if (Norm_Prty(NormList_NormNth(NormListPtr, NormIndex)) >
		NormList_NormNbr(NormListPtr)) {
			/* Une priorite est trop grande */
			free(TestArray);
			*ErrIndexPtr = PD_OUT_PRTY;
			return FALSE;
		}
		/* Verifie si la priorite existe deja */
		if (TestArray[Norm_Prty(NormList_NormNth(NormListPtr, NormIndex))
		- 1]) {
			/* Cette priorite existe deja */
			printf("Erreur\n");
			free(TestArray);
			*ErrIndexPtr = PD_DBL_PRTY;
			return FALSE;
		}
		TestArray[Norm_Prty(NormList_NormNth(NormListPtr, NormIndex))] = TRUE;
	}
	/* Controle qu'il ne manque aucune priorite */
	for (NormIndex = 1; NormIndex <= NormList_NormNbr(NormListPtr);
	NormIndex++) {
		if (!NormList_NormNth(NormListPtr, NormIndex)) {
			/* Il manque une priorite */
			free(TestArray);
			*ErrIndexPtr = PD_PRTY_MISS;
			return FALSE;
		}
	}
	free(TestArray);
	*ErrIndexPtr = PD_NO_ERROR;
	return TRUE;
}

/*--------------------------------------------------------------------------*/
/* Impression de la liste des normalisations								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NormListPtr				| Liste des normalisations			*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_NormList(TNormListPtr NormListPtr)
{
	TNormIndex NormIndex;
	
	for (NormIndex = 1; NormIndex < NormList_NormNbr(NormListPtr) + 1;
	NormIndex++) {
		if (NormList_NormNth(NormListPtr, NormIndex)) {
			printf("\n");
			printf("Norm mode: ");
			Print_NormIndex(NormIndex);
			printf("\n");
			Print_Norm(NormList_NormNth(NormListPtr, NormIndex));
		}
	}
}

/*=========================*/
/* Manipulation des scores */
/*=========================*/

/*---------------*/
/* Constructeurs */
/*---------------*/

/*--------------------------------------------------------------------------*/
/* Addition de scores														*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Score1					| 1er score							*/
/*			| Score2					| 2eme score						*/
/* Sortie:	| Score_Add					| Somme								*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
TScore Score_Add(TScore Score1, TScore Score2)
{
	return (((Score1 == PD_INFINITE)||(Score2 == PD_INFINITE)) ?
	PD_INFINITE : Score1 + Score2);
}

/*==============================================*/
/* Manipulation des listes de scores normalises */
/*==============================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une liste de scores normalises							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NScoreNbr					| Nombre de scores normalises		*/
/* Sortie:	| I_NScoreList				| Liste de scores normalises		*/
/* Erreur:	| I_NScoreList=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TNScoreListPtr I_NScoreList(TNScoreIndex NScoreNbr)
{
	TNScoreListPtr NScoreListPtr;
	
	NScoreListPtr = (TNScoreListPtr)malloc(sizeof(TNScoreList));
	if (!NScoreListPtr) {
		/* Erreur allocation */
		return NULL;
	}
	NScoreListPtr->List = (TNScore*)calloc(NScoreNbr, sizeof(TNScore));
	if (!(NScoreListPtr->List)) {
		/* Erreur allocation */
		free(NScoreListPtr);
		return NULL;
	}
	NScoreListPtr->NScoreNbr = NScoreNbr;
	return NScoreListPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une liste de scores normalises								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NScoreListPtr				| Liste de scores normalises		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_NScoreList(TNScoreListPtr NScoreListPtr)
{
	free(NScoreListPtr->List);
	free(NScoreListPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une liste de scores normalises								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| NScoreListPtr				| Liste de scores normalises		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_NScoreList(TNScoreListPtr NScoreListPtr)
{
	TNScoreIndex NScoreIndex;
	
	for (NScoreIndex = 0; NScoreIndex < NScoreList_NScoreNbr(NScoreListPtr);
	NScoreIndex++) {
		printf("Normalized score: ");
		Print_NScoreVal(NScoreList_Val(NScoreListPtr, NScoreIndex));
		printf("\n");
		printf("Normalization mode: ");
		Print_NormIndex(NScoreList_Mode(NScoreListPtr, NScoreIndex));
		printf("\n");
	}
}


/*=====================================*/
/* Manipulation des valeurs de coupure */
/*=====================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une valeur de coupure										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Text						| Texte								*/
/*			| NScoreListPtr				| Liste de scores normalises		*/
/* Sortie:	| I_CutOff					| Valeur de coupure					*/
/* Erreur:	| I_CutOff=NULL				| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TCutOffPtr I_CutOff(TText Text, TNScoreListPtr NScoreListPtr)
{
	TCutOffPtr CutOffPtr;
	
	CutOffPtr = (TCutOffPtr)malloc(sizeof(TCutOff));
	if (!CutOffPtr) {
		return NULL;
	}
	CutOffPtr->Text = Text;
	CutOffPtr->NScoreListPtr = NScoreListPtr;
	return CutOffPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une valeur de coupure										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOffPtr					| Valeur de coupure					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_CutOff(TCutOffPtr CutOffPtr)
{
	if (CutOffPtr->Text) Free_Text(CutOffPtr->Text);
	if (CutOffPtr->NScoreListPtr) Free_NScoreList(CutOffPtr->NScoreListPtr);
	free(CutOffPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une valeur de coupure										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOffPtr					| Valeur de coupure					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_CutOff(TCutOffPtr CutOffPtr)
{
	printf("Cut-Off level: ");
	Print_CutOffLevel(CutOff_Level(CutOffPtr));
	printf("\n");
	printf("Cut-Off score: ");
	Print_Score(CutOff_Score(CutOffPtr));
	printf("\n");
	if (CutOff_Text(CutOffPtr)) {
		printf("Description: ");
		Print_Text(CutOff_Text(CutOffPtr));
		printf("\n");
	}
	printf("Normalized scores:\n");
	if (CutOff_NScoreList(CutOffPtr)) {
		Print_NScoreList(CutOff_NScoreList(CutOffPtr));
	}
}

/*===============================================*/
/* Manipulation des listes de valeurs de coupure */
/*===============================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Desctruction d'une liste de valeurs de coupure							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOffListPtr				| Liste de valeurs de coupure		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_CutOffList(TCutOffListPtr CutOffListPtr)
{
	TCutOffIndex CutOffIndex;
	
	for (CutOffIndex = 0; CutOffIndex < CutOffList_CutOffNbr(CutOffListPtr);
	CutOffIndex++) {
		if (CutOffList_CutOffNth(CutOffListPtr, CutOffIndex))
			Free_CutOff(CutOffList_CutOffNth(CutOffListPtr, CutOffIndex));
	}
	Free_List((TListPtr)CutOffListPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Tri de la liste de valeurs de coupure									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOffListPtr				| Liste des valeurs de coupure		*/
/* Sortie:	| CutOffList_Sort			| Nouvelle liste					*/
/* Erreur:	| CutOffList_Sort=NULL		| =>								*/
/*			| ErrIndex					| Index d'erreur					*/
/*			| PD_MEM_ERR				| Erreur memoire					*/
/*			| PD_DBL_LEVEL				| Niveau de cut-off a double		*/
/*			| PD_LEVEL_MISS				| Niveau de cut-off manquant		*/
/*			| PD_ZERO_LEVEL_MISS		| Niveau zero manquant				*/
/*--------------------------------------------------------------------------*/
TCutOffListPtr CutOffList_Sort(TCutOffListPtr CutOffListPtr, TErrIndex
*ErrIndexPtr)
{
	TCutOffListPtr NewCutOffListPtr;
	TCutOffLevel LevelMin;
	TCutOffLevel LevelMax;
	TCutOffIndex CutOffIndex;
	TCutOffIndex NewCutOffIndex;
	TCutOffIndex CutOffNbr = CutOffList_CutOffNbr(CutOffListPtr);
	
	/* Determination du plus petit et plus grand niveau */
	LevelMax = LevelMin =
	CutOff_Level(CutOffList_CutOffNth(CutOffListPtr, 0));
	for (CutOffIndex = 1; CutOffIndex < CutOffNbr; CutOffIndex++) {
	
		if (CutOff_Level(CutOffList_CutOffNth(CutOffListPtr, CutOffIndex)) <
		LevelMin) {
			LevelMin = CutOff_Level(CutOffList_CutOffNth(CutOffListPtr,
			CutOffIndex));
		}
		if (CutOff_Level(CutOffList_CutOffNth(CutOffListPtr, CutOffIndex)) >
		LevelMax) {
			LevelMax = CutOff_Level(CutOffList_CutOffNth(CutOffListPtr,
			CutOffIndex));
		}
	}

	/* Allocation nouvelle liste */
	NewCutOffListPtr = I_CutOffList(LevelMax - LevelMin + 1);
	if (!NewCutOffListPtr) {
		/* Erreur allocation */
		*ErrIndexPtr = PD_MEM_ERR;
		return NULL;
	}

	/* Tri des valeurs de coupure */
	for (CutOffIndex = 0; CutOffIndex < CutOffNbr; CutOffIndex++) {
		NewCutOffIndex = CutOff_Level(CutOffList_CutOffNth(CutOffListPtr,
		CutOffIndex)) - LevelMin;
		if (CutOffList_CutOffNth(NewCutOffListPtr, NewCutOffIndex)) { 
			/* CutOff a double */
			Free_List((TListPtr)NewCutOffListPtr);
			*ErrIndexPtr = PD_DBL_LEVEL;
			return NULL;
		}
		/* Ajout dans la liste */
		CutOffList_AddCutOffNth(NewCutOffListPtr, CutOffList_CutOffNth(
		CutOffListPtr, CutOffIndex), NewCutOffIndex);
	}
	/* Teste si la liste est complete */
	if (!(List_Complete((TListPtr)NewCutOffListPtr))) {
		/* La liste n'est pas complete */
		Free_List((TListPtr)NewCutOffListPtr);
		*ErrIndexPtr = PD_LEVEL_MISS;
		return NULL;
	}

	/* Controle si le niveau zero existe */
	if ((CutOff_Level(CutOffList_CutOffNth(NewCutOffListPtr, 0)) > 0) ||
	(CutOff_Level(CutOffList_CutOffNth(NewCutOffListPtr,
	CutOffNbr - 1)) < 0)) {
		/* Pas de niveau zero */
		Free_List((TListPtr)NewCutOffListPtr);
		*ErrIndexPtr = PD_ZERO_LEVEL_MISS;
		return NULL;
	}

	Free_List((TListPtr)CutOffListPtr);
	*ErrIndexPtr = PD_NO_ERROR;
	return NewCutOffListPtr;
}

/*--------------------------------------------------------------------------*/
/* Impression de la liste des valeurs de coupure							*/
/*--------------------------------------------------------------------------*/
/* Entree:	| CutOffListPtr				| Liste des valeurs de coupure		*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_CutOffList(TCutOffListPtr CutOffListPtr)
{
	TCutOffIndex CutOffIndex;
	
	for (CutOffIndex = 0; CutOffIndex < CutOffList_CutOffNbr(CutOffListPtr);
	CutOffIndex++) {
		if (CutOffList_CutOffNth(CutOffListPtr, CutOffIndex)) {
			printf("\n");
			Print_CutOff(CutOffList_CutOffNth(CutOffListPtr, CutOffIndex));
		}
	}
}

/*=====================================*/
/* Manipulation des vecteurs de scores */
/*=====================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Clonage d'un vecteur de scores											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ScoreVect					| Vecteur de scores original		*/
/*			| AlphSize					| Taille de l'alphabet				*/
/* Sortie:	| Clone_ScoreVect			| Vecteur de scores					*/
/* Erreur:	| Clone_ScoreVect=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TScoreVect Clone_ScoreVect(TScoreVect ScoreVect, TAlphSize AlphSize)
{
	TScoreVect ScoreVectDest;
	
	ScoreVectDest = I_ScoreVect(AlphSize);
	if (!ScoreVectDest) {
		/* Erreur allocation */
		return NULL;
	}
	ScoreVectDest= (TScoreVect)memcpy(ScoreVectDest, ScoreVect,
	(AlphSize + 1)*sizeof(TScore));
	return ScoreVectDest;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'un vecteur de scores										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ScoreVect					| Vecteur de scores					*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_ScoreVect(TScoreVect ScoreVect, TAlphPtr AlphPtr)
{
	TAlphSize LetIndex;
	
	for (LetIndex = 1; LetIndex <= Alph_Size(AlphPtr); LetIndex++) {
		Print_Let(Alph_LetNth(AlphPtr, LetIndex));
		printf(": ");
		Print_Score(ScoreVect_ScoreNth(ScoreVect, LetIndex));
		printf("\n");
	}
	printf("Unknown letter: ");
	Print_Score(ScoreVect_ScoreNth(ScoreVect, 0));
	printf("\n");
}

/*====================================================*/
/* Routines de manipulation des positions d'insertion */
/*====================================================*/

/*--------------------------------------------------------------------------*/
/* Construction d'une position d'insertion									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ScoreVect					| Vecteur de scores					*/
/* Sortie:	| I_InsPos					| Position d'insertion				*/
/* Erreur:	| I_InsPos=NULL				| Erreur d'allocation				*/
/*--------------------------------------------------------------------------*/
TInsPosPtr I_InsPos(TScoreVect ScoreVect)
{
	TInsPosPtr InsPosPtr;
	
	InsPosPtr = (TInsPosPtr)malloc(sizeof(TInsPos));
	if (!InsPosPtr) {
		return NULL;
	}
	InsPosPtr->I = ScoreVect;
	return InsPosPtr;
}

/*--------------------------------------------------------------------------*/
/* Clonage d'une position d'insertion										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| InsPosPtr					| Position d'insertion originale	*/
/*			| AlphSize					| Taille de l'alphabet				*/
/* Sortie:	| Clone_InsPos				| Position d'insertion				*/
/* Erreur:	| Clone_InsPos=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TInsPosPtr Clone_InsPos(TInsPosPtr InsPosPtr, TAlphSize AlphSize)
{
	TInsPosPtr InsPosDestPtr;
	TScoreVect ScoreVectDest;
	
	/* Clonage du vecteur de scores */
	ScoreVectDest = Clone_ScoreVect(InsPosPtr->I, AlphSize);
	if (!ScoreVectDest) {
		/* Erreur d'allocation */
		return NULL;
	}
	/* Allocation d'une nouvelle position d'insertion */
	InsPosDestPtr = (TInsPosPtr)malloc(sizeof(TInsPos));
	if (!InsPosDestPtr){
		/* Erreur d'allocation */
		Free_ScoreVect(ScoreVectDest);
		return NULL;
	}
	/* Copie */
	InsPosDestPtr = (TInsPosPtr)memcpy(InsPosDestPtr, InsPosPtr,
	sizeof(TInsPos));
	InsPosDestPtr->I = ScoreVectDest;
	return InsPosDestPtr;

}

/*--------------------------------------------------------------------------*/
/* Destruction d'une position d'insertion									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| InsPosPtr					| Position d'insertion				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_InsPos(TInsPosPtr InsPosPtr)
{
	Free_ScoreVect(InsPosPtr->I);
	free(InsPosPtr);
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une position d'insertion									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| InsPosPtr					| Position d'insertion				*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_InsPos(TInsPosPtr InsPosPtr, TAlphPtr AlphPtr)
{
	printf("Significative symbol: ");
	Print_Symb(InsPos_Symb(InsPosPtr));
	printf("\n");
	printf("External initiation score: ");
	Print_Score(InsPos_B0(InsPosPtr)); printf("\n");
	printf("Internal initiation score: ");
	Print_Score(InsPos_B1(InsPosPtr)); printf("\n");
	printf("External termination score: ");
	Print_Score(InsPos_E0(InsPosPtr)); printf("\n");
	printf("Internal termination score: ");
	Print_Score(InsPos_E1(InsPosPtr)); printf("\n");
	printf("\n");
	printf("External State transition score from B to M: ");
	Print_Score(InsPos_BM(InsPosPtr)); printf("\n");
	printf("External State transition score from B to I: ");
	Print_Score(InsPos_BI(InsPosPtr)); printf("\n");
	printf("External State transition score from B to D: ");
	Print_Score(InsPos_BD(InsPosPtr)); printf("\n");
	printf("External State transition score from B to E: ");
	Print_Score(InsPos_BE(InsPosPtr)); printf("\n");
	printf("External State transition score from M to M: ");
	Print_Score(InsPos_MM(InsPosPtr)); printf("\n");
	printf("External State transition score from M to I: ");
	Print_Score(InsPos_MI(InsPosPtr)); printf("\n");
	printf("External State transition score from M to D: ");
	Print_Score(InsPos_MD(InsPosPtr)); printf("\n");
	printf("External State transition score from M to E: ");
	Print_Score(InsPos_ME(InsPosPtr)); printf("\n");
	printf("External State transition score from I to M: ");
	Print_Score(InsPos_IM(InsPosPtr)); printf("\n");
	printf("External State transition score from I to I: ");
	Print_Score(InsPos_II(InsPosPtr)); printf("\n");
	printf("External State transition score from I to D: ");
	Print_Score(InsPos_ID(InsPosPtr)); printf("\n");
	printf("External State transition score from I to E: ");
	Print_Score(InsPos_IE(InsPosPtr)); printf("\n");
	printf("External State transition score from D to M: ");
	Print_Score(InsPos_DM(InsPosPtr)); printf("\n");
	printf("External State transition score from D to I: ");
	Print_Score(InsPos_DI(InsPosPtr)); printf("\n");
	printf("External State transition score from D to D: ");
	Print_Score(InsPos_DD(InsPosPtr)); printf("\n");
	printf("External State transition score from D to E: ");
	Print_Score(InsPos_DE(InsPosPtr)); printf("\n\n");
	printf("Insert scores:\n");
	Print_ScoreVect(InsPos_I(InsPosPtr), AlphPtr);
}

/*==================================*/
/* Manipulation des positions match */
/*==================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une position match										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ScoreVect					| Score de vecteurs					*/
/* Sortie:	| I_MatchPos				| Position match					*/
/* Erreur:	| I_MatchPos=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TMatchPosPtr I_MatchPos(TScoreVect ScoreVect)
{
	TMatchPosPtr MatchPosPtr;
	
	MatchPosPtr = (TMatchPosPtr)malloc(sizeof(TMatchPos));
	if (!MatchPosPtr) {
		/* Erreur allocation */
		return NULL;
	}
	MatchPosPtr->M = ScoreVect;
	return MatchPosPtr;
}

/*--------------------------------------------------------------------------*/
/* Clonage d'une position match												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MatchPosPtr				| Position match original			*/
/*			| AlphSize					| Taille de l'alphabet				*/
/* Sortie:	| Clone_MatchPos			| Position match					*/
/* Erreur:	| Clone_MatchPos=NULL		| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TMatchPosPtr Clone_MatchPos(TMatchPosPtr MatchPosPtr, TAlphSize AlphSize)
{
	TMatchPosPtr MatchPosDestPtr;
	TScoreVect ScoreVectDest;
	
	/* Clonage du vecteur de score */
	ScoreVectDest = Clone_ScoreVect(MatchPosPtr->M, AlphSize);
	if (!ScoreVectDest) {
		/* Erreur allocation */
		return NULL;
	}
	/* Allocation d'une nouvelle position match */
	MatchPosDestPtr = (TMatchPosPtr)malloc(sizeof(TMatchPos));
	if (!MatchPosDestPtr) {
		/* Erreur allocation */
		return NULL;
	}
	/* Copie */
	MatchPosDestPtr = (TMatchPosPtr)memcpy(MatchPosDestPtr, MatchPosPtr,
	sizeof(TMatchPos));
	MatchPosDestPtr->M = ScoreVectDest;
	return MatchPosDestPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une position match											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MatchPosPtr				| Position match					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_MatchPos(TMatchPosPtr MatchPosPtr)
{
	Free_ScoreVect(MatchPosPtr->M);
	free(MatchPosPtr);
}

/*--------------------------------------------------------------------------*/
/* Impression d'une position match											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MatchPosPtr				| position match					*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_MatchPos(TMatchPosPtr MatchPosPtr, TAlphPtr AlphPtr)
{
	printf("Significative symbol: ");
	Print_Symb(MatchPos_Symb(MatchPosPtr));
	printf("\n");
	printf("Match scores:\n");
	Print_ScoreVect(MatchPos_M(MatchPosPtr), AlphPtr);
	printf("Deletion score: ");
	Print_Score(MatchPos_D(MatchPosPtr)); printf("\n");
}

/*=====================================*/
/* Manipulation des matrices de profil */
/*=====================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction d'une matrice de profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| MaxPosNbr					| Taille max. de la matr. de profil	*/
/* Sortie:	| I_PrfMatrix				| Matrice de profil					*/
/* Erreur:	| I_PrfMatrix=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TPrfMatrixPtr I_PrfMatrix(TPosIndex MaxPosNbr)
{
	TPrfMatrixPtr PrfMatrixPtr;
	
	PrfMatrixPtr = (TPrfMatrixPtr)malloc(sizeof(TPrfMatrix));
	if (!PrfMatrixPtr) {
		/* Erreur d'allocation */
		return NULL;
	}
	PrfMatrixPtr->InsPosList = (TInsPosPtr*)calloc(MaxPosNbr + 1,
	sizeof(TInsPosPtr));
	if (!(PrfMatrixPtr->InsPosList)) {
		/* Erreur d'allocation */
		free(PrfMatrixPtr);
		return NULL;
	}
	PrfMatrixPtr->MatchPosList = (TMatchPosPtr*)
	calloc(MaxPosNbr, sizeof(TMatchPosPtr));
	if (!(PrfMatrixPtr->MatchPosList)) {
		/* Erreur d'allocation */
		free(PrfMatrixPtr->InsPosList);
		free(PrfMatrixPtr);
		return NULL;
	}
	PrfMatrixPtr->MaxPosNbr = MaxPosNbr;
	PrfMatrixPtr->PosNbr = 0;
	PrfMatrixPtr->LastPos = FALSE;
	return PrfMatrixPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction d'une matrice de profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfMatrixPtr				| Matrice de profil					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PrfMatrix(TPrfMatrixPtr PrfMatrixPtr)
{
	TPosIndex PosIndex;
	
	for (PosIndex = 0; PosIndex < PrfMatrixPtr->PosNbr; PosIndex++) {
		Free_InsPos(PrfMatrixPtr->InsPosList[PosIndex]);
		Free_MatchPos(PrfMatrixPtr->MatchPosList[PosIndex]);
	}
	if (PrfMatrixPtr->LastPos)
		Free_InsPos(PrfMatrixPtr->InsPosList[PosIndex]);
	free(PrfMatrixPtr->InsPosList);
	free(PrfMatrixPtr->MatchPosList);
	free(PrfMatrixPtr);
}

/*--------------------------------------------------------------------------*/
/* Recalibration d'une matrice de profil									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfMatrixPtr				| Matrice de profil					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Resize_PrfMatrix(TPrfMatrixPtr PrfMatrixPtr)
{
	PrfMatrixPtr->InsPosList = (TInsPosPtr*)realloc(PrfMatrixPtr->InsPosList,
	(PrfMatrixPtr->PosNbr + 1)*sizeof(TInsPosPtr));
	PrfMatrixPtr->MatchPosList = (TMatchPosPtr*)realloc(
	PrfMatrixPtr->MatchPosList, PrfMatrixPtr->PosNbr*sizeof(TMatchPosPtr));
	PrfMatrixPtr->MaxPosNbr = PrfMatrixPtr->PosNbr;
}

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression d'une matrice de profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfMatrixPtr				| Matrice de profil					*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_PrfMatrix(TPrfMatrixPtr PrfMatrixPtr, TAlphPtr AlphPtr)
{
	/* Attention: la matrice de profil doit etre complete */
	TPosIndex PosIndex;

	printf("\n");
	printf("Position Nth0");
	printf(":\n\n");
	printf("Insert position:\n");
	Print_InsPos(PrfMatrix_InsPosNth(PrfMatrixPtr, 0), AlphPtr);
	
	for (PosIndex = 1; PosIndex < PrfMatrix_PosNbr(PrfMatrixPtr) + 1;
	PosIndex++) {
		printf("\n");
		printf("Position Nth");
		Print_PosIndex(PosIndex);
		printf(":\n\nMatch position:\n\n");
		Print_MatchPos(PrfMatrix_MatchPosNth(PrfMatrixPtr, PosIndex), AlphPtr);
		printf("\nInsert position:\n\n");
		Print_InsPos(PrfMatrix_InsPosNth(PrfMatrixPtr, PosIndex), AlphPtr);
	}
}

/*======================================*/
/* Manipulation des donnees de profils	*/
/*======================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction des donnees d'un profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| Id						| Identificateur du profil			*/
/*			| De						| Description du profil				*/
/*			| NbrAc						| Nombre AC							*/
/*			| GenSpecPtr				| Specification generales			*/
/*			| DisjointPtr				| Exclusion							*/
/*			| NormListPtr				| Liste de normalisations			*/
/*			| CutOffListPtr				| Liste de valeurs de coupure		*/
/*			| PrfMatrixPtr				| Matrice de profil					*/
/* Sortie:	| I_PrfData					| Donnees du profil					*/
/* Erreur:	| I_PrfData=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TPrfDataPtr I_PrfData(TId Id, TDe De, TNbrAc NbrAc, TGenSpecPtr GenSpecPtr,
TDisjointPtr DisjointPtr, TNormListPtr NormListPtr, TCutOffListPtr
CutOffListPtr, TPrfMatrixPtr PrfMatrixPtr)
{
	TPrfDataPtr PrfDataPtr;
	
	PrfDataPtr = (TPrfDataPtr)malloc(sizeof(TPrfData));
	if (!PrfDataPtr) {
		/* Erreur allocation */
		return NULL;
	}
	PrfDataPtr->Id = Id;
	PrfDataPtr->De = De;
	PrfDataPtr->NbrAc = NbrAc;
	PrfDataPtr->GenSpecPtr = GenSpecPtr;
	PrfDataPtr->DisjointPtr = DisjointPtr;
	PrfDataPtr->NormListPtr = NormListPtr;
	PrfDataPtr->CutOffListPtr = CutOffListPtr;
	PrfDataPtr->PrfMatrixPtr = PrfMatrixPtr;
	return PrfDataPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction des donnees d'un profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfDataPtr				| Donnees du profil					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PrfData(TPrfDataPtr PrfDataPtr)
{
	Free_Id(PrfDataPtr->Id);
	if (PrfDataPtr->De) Free_De(PrfDataPtr->De);
	Free_NbrAc(PrfDataPtr->NbrAc);
	Free_GenSpec(PrfDataPtr->GenSpecPtr);
	Free_Disjoint(PrfDataPtr->DisjointPtr);
	Free_NormList(PrfDataPtr->NormListPtr);
	Free_CutOffList(PrfDataPtr->CutOffListPtr);
	Free_PrfMatrix(PrfDataPtr->PrfMatrixPtr);
	free(PrfDataPtr);
}


/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Impression des donnees d'un profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfDataPtr				| Donnees du profil					*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Print_PrfData(TPrfDataPtr PrfDataPtr)
{
	printf("Profile ID: ");
	Print_Id(PrfData_Id(PrfDataPtr)); printf("\n");
	printf("Profile Description: ");
	if (PrfData_De(PrfDataPtr)) {
		Print_De(PrfData_De(PrfDataPtr));
	}
	printf("\n");
	printf("Prosite number: ");
	Print_NbrAc(PrfData_NbrAc(PrfDataPtr)); printf("\n");
	printf("\n");
	printf("General specifications:\n");
	Print_GenSpec(PrfData_GenSpec(PrfDataPtr));
	printf("\n");
	printf("Disjointness:\n");
	Print_Disjoint(PrfData_Disjoint(PrfDataPtr));
	printf("\n");
	printf("Norm modes:\n");
	Print_NormList(PrfData_NormList(PrfDataPtr));
	printf("\n");
	printf("Cut-off levels:\n");
	Print_CutOffList(PrfData_CutOffList(PrfDataPtr));
	printf("\n");
	printf("Profile matrix:\n");
	Print_PrfMatrix(PrfData_PrfMatrix(PrfDataPtr),
	GenSpec_Alph(PrfData_GenSpec(PrfDataPtr)));
}
