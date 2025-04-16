/****************************************************************************/
/*																			*/
/*	But: implementation des routines d'extraction des donnees d'un profil	*/
/*																			*/
/****************************************************************************/

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "PrfExtr.h"

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*============*/
/* Dimensions */
/*============*/

#define PE_MAX_NORM_NBR 	UCHAR_MAX
#define PE_MAX_CUTOFF_NBR	UCHAR_MAX
#define PE_MAX_POS_NBR		4*UCHAR_MAX

/*=========*/
/* Chaines */
/*=========*/

#define PE_GEN_SPEC_STR		"GENERAL_SPEC"
#define PE_ALPH_STR			"ALPHABET"
#define PE_LENGTH_STR		"LENGTH"
#define PE_TOPO_STR			"TOPOLOGY"
#define PE_LINEAR_STR		"LINEAR"
#define PE_CIRCULAR_STR		"CIRCULAR"
#define PE_DISJ_STR			"DISJOINT"
#define PE_DEF_STR			"DEFINITION"
#define PE_UNIQUE_STR		"UNIQUE"
#define PE_PROT_STR			"PROTECT"
#define PE_NORM_STR			"NORMALIZATION"
#define PE_FCT_STR			"FUNCTION"
#define PE_GRIB_STR			"GLE_ZSCORE"
#define PE_MODE_STR			"MODE"
#define PE_TEXT_STR			"TEXT"
#define PE_PRTY_STR			"PRIORITY"
#define PE_CUTOFF_STR		"CUT_OFF"
#define PE_SCORE_STR		"SCORE"
#define PE_LEVEL_STR		"LEVEL"
#define PE_N_SCORE_STR		"N_SCORE"
#define PE_SYMB_STR			"SY"
#define PE_B0_STR			"B0"
#define PE_B1_STR			"B1"
#define PE_E0_STR			"E0"
#define PE_E1_STR			"E1"
#define PE_BM_STR			"BM"
#define PE_BI_STR			"BI"
#define PE_BD_STR			"BD"
#define PE_BE_STR			"BE"
#define PE_MM_STR			"MM"
#define PE_MI_STR			"MI"
#define PE_MD_STR			"MD"
#define PE_ME_STR			"ME"
#define PE_IM_STR			"IM"
#define PE_II_STR			"II"
#define PE_ID_STR			"ID"
#define PE_IE_STR			"IE"
#define PE_DM_STR			"DM"
#define PE_DI_STR			"DI"
#define PE_DD_STR			"DD"
#define PE_DE_STR			"DE"
#define PE_I_STR			"I"
#define PE_I0_STR			"I0"
#define PE_M_STR			"M"
#define PE_M0_STR			"M0"
#define PE_D_STR			"D"
#define PE_SYMB_I_STR		"SY_I"
#define PE_SYMB_M_STR		"SY_M"
#define PE_DFT_STR			"DEFAULT"

/*====================*/
/* Constantes d'etats */
/*====================*/

#define PE_WAIT_I	0
#define PE_WAIT_M	1

/*******************************/
/* IMPLEMENTATION DES ROUTINES */
/*******************************/

/*==================================*/
/* Extraction des donnees du profil */
/*==================================*/

/*-----------------*/
/* Gestion memoire */
/*-----------------*/

/*--------------------------------------------------------------------------*/
/* Construction des donnees d'extractions d'un profil						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfFileDataPtr			| Donnees du profil					*/
/* Sortie:	| I_PrfExtr					| Donnees d'extraction				*/
/* Erreur:	| I_PrfExtr=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TPrfExtrPtr I_PrfExtr(TPrfFileDataPtr PrfFileDataPtr)
{
	TPrfExtrPtr PrfExtrPtr;
	
	PrfExtrPtr = (TPrfExtrPtr)malloc(sizeof(TPrfExtr));
	if (!PrfExtrPtr) {
		/* Erreur d'allocation */
		return NULL;
	}
	PrfExtrPtr->PrfFileDataPtr = PrfFileDataPtr;
	PrfExtrPtr->PrfPtr = PrfFileData_Prf(PrfFileDataPtr);
	if (Prf_DescNbr(PrfFileData_Prf(PrfFileDataPtr)) > 0) {
		/* Il existe au moins une description dans le profil */
		PrfExtrPtr->CurrentDescPtr =
		Prf_DescNth(PrfFileData_Prf(PrfFileDataPtr), 0);
		PrfExtrPtr->DescNth = 1;
		if (Desc_AssNbr(PrfExtrPtr->CurrentDescPtr) > 0) {
			/* Il existe au moins une assignation dans la description */
			PrfExtrPtr->CurrentAssPtr =
			Desc_AssNth(PrfExtrPtr->CurrentDescPtr, 0);
			PrfExtrPtr->AssNth = 1;
			/* Recherche de la valeur */
			PrfExtrPtr->CurrentValPtr =
			Ass_ValNth(PrfExtrPtr->CurrentAssPtr, 0);
			PrfExtrPtr->ValNth = 1;
		}
		else {
			PrfExtrPtr->CurrentAssPtr = NULL;
			PrfExtrPtr->CurrentValPtr = NULL;
			PrfExtrPtr->AssNth = 0;
			PrfExtrPtr->ValNth = 0;
		}
	}
	else {
		PrfExtrPtr->CurrentDescPtr = NULL;
		PrfExtrPtr->CurrentAssPtr = NULL;
		PrfExtrPtr->CurrentValPtr = NULL;
		PrfExtrPtr->DescNth = 0;
		PrfExtrPtr->AssNth = 0;
		PrfExtrPtr->ValNth = 0;
	}
	return PrfExtrPtr;
}

/*--------------------------------------------------------------------------*/
/* Destruction des donnees d'extractions d'un profil						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PrfExtr(TPrfExtrPtr PrfExtrPtr)
{
	free(PrfExtrPtr);
}


/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Extraction de l'identificateur du profil									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_Id				| Identificateur					*/
/* Erreur:	| PrfExtr_Id=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TId PrfExtr_Id(TPrfExtrPtr PrfExtrPtr)
{
	TId Id;
	
	Id = Str_To_Id((char*)PrfFileData_Id(PrfExtr_PrfFileData(PrfExtrPtr)));
	if (!Id) {
		/* Erreur allocation */
		return NULL;
	}
	return Id;
}

/*--------------------------------------------------------------------------*/
/* Extraction de la descritption du profil									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_De				| Description						*/
/* Erreur:	| PrfExtr_De=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TId PrfExtr_De(TPrfExtrPtr PrfExtrPtr)
{
	TDe De;
	
	De = Str_To_De((char*)PrfFileData_De(PrfExtr_PrfFileData(PrfExtrPtr)));
	if (!De) {
		/* Erreur allocation */
		return NULL;
	}
	return De;
}

/*--------------------------------------------------------------------------*/
/* Extraction du nombre Prosite du profil									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_NbrAc				| Nombre Prosite					*/
/* Erreur:	| PrfExtr_NbrAc=NULL		| Erreur allocation					*/
/*--------------------------------------------------------------------------*/
TNbrAc PrfExtr_NbrAc(TPrfExtrPtr PrfExtrPtr)
{
	TNbrAc NbrAc;
	
	NbrAc = Str_To_NbrAc((char*)PrfFileData_NbrAc(PrfExtr_PrfFileData
	(PrfExtrPtr)));
	if (!NbrAc) {
		/* Erreur allocation */
		return NULL;
	}
	return NbrAc;
}

/*--------------------------------------------------------------------------*/
/* Saute a la prochaine description	du profil								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_NextDesc			| Description						*/
/* Erreur:	| PrfExtr_NextDesc=NULL		| Plus de descriptions				*/
/*--------------------------------------------------------------------------*/
TDescPtr PrfExtr_NextDesc(TPrfExtrPtr PrfExtrPtr)
{
	/* Mise a jour de la description courante */
	if (!(PrfExtr_DescNth(PrfExtrPtr) <
	Prf_DescNbr(PrfExtr_Prf(PrfExtrPtr)))) {
		/* On est au bout de la liste des descriptions */
		PrfExtr_CurrentDesc(PrfExtrPtr) = NULL;
		PrfExtr_CurrentAss(PrfExtrPtr) = NULL;
		PrfExtr_CurrentVal(PrfExtrPtr) = NULL;
		PrfExtr_DescNth(PrfExtrPtr) = 0;
		PrfExtr_AssNth(PrfExtrPtr) = 0;
		PrfExtr_ValNth(PrfExtrPtr) = 0;
		return NULL;
	}
	PrfExtr_CurrentDesc(PrfExtrPtr) =
	Prf_DescNth(PrfExtr_Prf(PrfExtrPtr), PrfExtr_DescNth(PrfExtrPtr));
	PrfExtr_DescNth(PrfExtrPtr)++;
	/* Mise a jour de l'assignation courante */
	if (Desc_AssNbr(PrfExtr_CurrentDesc(PrfExtrPtr)) > 0) {
		/* Il existe au moins une assignation dans la description */
		PrfExtr_CurrentAss(PrfExtrPtr) =
		Desc_AssNth(PrfExtr_CurrentDesc(PrfExtrPtr), 0);
		PrfExtr_AssNth(PrfExtrPtr) = 1;
		/* Mise a jour de la valeur courante */
		/* Recherche de la valeur */
		PrfExtr_CurrentVal(PrfExtrPtr) =
		Ass_ValNth(PrfExtr_CurrentAss(PrfExtrPtr), 0);
		PrfExtr_ValNth(PrfExtrPtr) = 1;
	}
	else {
		/* Pas d'assignation */
		PrfExtr_CurrentAss(PrfExtrPtr) = NULL;
		PrfExtr_CurrentVal(PrfExtrPtr) = NULL;
		PrfExtr_AssNth(PrfExtrPtr) = 0;
		PrfExtr_ValNth(PrfExtrPtr) = 0;
	}
	return PrfExtr_CurrentDesc(PrfExtrPtr);
}

/*--------------------------------------------------------------------------*/
/* Saute a la prochaine assignation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_NextAss			| Assignation						*/
/* Erreur:	| PrfExtr_NextAss=NULL		| Plus d'assignations				*/
/*--------------------------------------------------------------------------*/
TAssPtr PrfExtr_NextAss(TPrfExtrPtr PrfExtrPtr)
{
	/* Mise a jour de l'assignation courante */
	if (!(PrfExtr_AssNth(PrfExtrPtr) <
	Desc_AssNbr(PrfExtr_CurrentDesc(PrfExtrPtr)))) {
		/* On est au bout de la liste des assignations */
		PrfExtr_CurrentAss(PrfExtrPtr) = NULL;
		PrfExtr_CurrentVal(PrfExtrPtr) = NULL;
		PrfExtr_AssNth(PrfExtrPtr) = 0;
		PrfExtr_ValNth(PrfExtrPtr) = 0;
		return NULL;
	}
	PrfExtr_CurrentAss(PrfExtrPtr) =
	Desc_AssNth(PrfExtr_CurrentDesc(PrfExtrPtr), PrfExtr_AssNth(PrfExtrPtr));
	PrfExtr_AssNth(PrfExtrPtr)++;
	/* Mise a jour de la valeur courante */
	PrfExtr_CurrentVal(PrfExtrPtr) =
	Ass_ValNth(PrfExtr_CurrentAss(PrfExtrPtr), 0);
	PrfExtr_ValNth(PrfExtrPtr) = 1;
	return PrfExtr_CurrentAss(PrfExtrPtr);
}

/*--------------------------------------------------------------------------*/
/* Saute a la prochaine valeur												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_NextVal			| Valeur							*/
/* Erreur:	| PrfExtr_NextVal=NULL		| Plus de valeurs					*/
/*--------------------------------------------------------------------------*/
TValPtr PrfExtr_NextVal(TPrfExtrPtr PrfExtrPtr)
{
	/* Mise a jour de la valeur courante */
	if (!(PrfExtr_ValNth(PrfExtrPtr) <
	Ass_ValNbr(PrfExtr_CurrentAss(PrfExtrPtr)))) {
		/* On est au bout de la liste des assignations */
		PrfExtr_CurrentVal(PrfExtrPtr) = NULL;
		PrfExtr_ValNth(PrfExtrPtr) = 0;
		return NULL;
	}
	PrfExtr_CurrentVal(PrfExtrPtr) =
	Ass_ValNth(PrfExtr_CurrentAss(PrfExtrPtr), PrfExtr_ValNth(PrfExtrPtr));
	PrfExtr_ValNth(PrfExtrPtr)++;
	return PrfExtr_CurrentVal(PrfExtrPtr);
}

/*--------------------------------------------------------------------------*/
/* Extraction des specifications generales de la description courante		*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_GenSpec			| Specifications generales			*/
/* Erreur:	| PrfExtr_GenSpec			| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PE_GEN_SPEC_EXP			| Specifications generales att.		*/
/*			| PE_DBL_ALPH				| Alphabet deja defini				*/
/*			| PE_STR_EXP				| Chaine attendue					*/
/*			| PE_MEM_ERR				| Allocation memoire				*/
/*			| PE_ILL_VAL				| Valeur illegale					*/
/*			| PE_DBL_LENGTH				| Longueur deja declaree			*/
/*			| PE_CARD_EXP				| Entier positif attendu			*/
/*			| PE_DBL_TOPO				| Topologie deja declaree			*/
/*			| PE_WORD_EXP				| Mot attendu						*/
/*			| PE_ILL_WORD				| Mot illegale						*/
/*			| PE_ILL_ASS				| Assignation illegale				*/
/*			| PE_ALPH_EXP				| Alphabet attendu					*/
/*--------------------------------------------------------------------------*/
TGenSpecPtr PrfExtr_GenSpec(TPrfExtrPtr PrfExtrPtr, TErrIndex *ErrIndexPtr)
{
	TGenSpecPtr GenSpecPtr;
	TAlphPtr AlphPtr;
	TTopo Topo;
	TPosIndex PosNbr;
	TBoolean TopoRead = FALSE;
	TBoolean PosNbrRead = FALSE;
	TAssPtr AssPtr;
	TValPtr ValPtr;
	TWordPtr WordPtr;
	TWordPtr AssWordPtr;
	
	/* Recherche de la description */
	if (!PrfExtr_CurrentDesc(PrfExtrPtr)) {
		/* Il n'y a pas de premiere description */
		*ErrIndexPtr = PE_GEN_SPEC_EXP;
		return NULL;
	}
	/* Controle du mot-cle */
	if (strcmp(PE_GEN_SPEC_STR,
	Desc_Keyword(PrfExtr_CurrentDesc(PrfExtrPtr)))) {
		/* Le mot cle n'est la specification generale */
		*ErrIndexPtr = PE_GEN_SPEC_EXP;
		return NULL;
	}
	/* Initialisation des valeurs par defaut */
	AlphPtr = NULL;
	Topo = PD_TOPO_LINEAR;
	PosNbr = 0;
	/* Recherche de la premiere assignation */
	AssPtr = PrfExtr_CurrentAss(PrfExtrPtr);
	while (AssPtr) {
		AssWordPtr = Ass_Word(AssPtr);
		/* Controle du mot */
		if (!strcmp(PE_ALPH_STR, AssWordPtr)) {
			/* Lecture de l'alphabet */
			if (AlphPtr) {
				/* Alphabet deja lu */
				Free_Alph(AlphPtr);
				*ErrIndexPtr = PE_DBL_ALPH;
				return NULL;
			}
			/* Controle du type de valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_STR) {
				/* La valeur n'est pas une chaine */
				*ErrIndexPtr = PE_STR_EXP;
				return NULL;
			}
			/* Conversion de la chaine */
			AlphPtr = Str_To_Alph((char*)Val_Str
			(PrfExtr_CurrentVal(PrfExtrPtr)));
			if (!AlphPtr) {
				/* Erreur memoire */
				*ErrIndexPtr = PE_MEM_ERR;
				return NULL;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il existe une valeur de trop */
				Free_Alph(AlphPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
		}
		else if (!strcmp(PE_LENGTH_STR, AssWordPtr)) {
			/* Lecture de la longueur */
			if (PosNbrRead) {
				/* Longueur deja lue */
				if (AlphPtr) Free_Alph(AlphPtr);
				*ErrIndexPtr = PE_DBL_LENGTH;
				return NULL;
			}
			/* Controle du type de la valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr))!=PFD_A_NBR) {
				/* La valeur n'est pas un nombre */
				if (AlphPtr) Free_Alph(AlphPtr);
				*ErrIndexPtr = PE_CARD_EXP;
				return NULL;
			}
			/* Lecture de la longueur */
			PosNbr = (TPosIndex)Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr));
			/* Controle de la longueur lue */
			if (((TNbr)PosNbr != Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr))) ||
			(PosNbr <= 0)) {
				/* La longueur n'est pas un entier strictement positif */
				if (AlphPtr) Free_Alph(AlphPtr);
				*ErrIndexPtr = PE_CARD_EXP;
				return NULL;
			}
			/* Prochaine valeur */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				if (AlphPtr) Free_Alph(AlphPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
			/* Longueur lue */
			PosNbrRead = TRUE;

		}
		else if (!strcmp(PE_TOPO_STR, AssWordPtr)) {
			/* Lecture de la topologie */
			if (TopoRead) {
				/* Topologie deja lue */
				if (AlphPtr) Free_Alph(AlphPtr);
				*ErrIndexPtr = PE_DBL_TOPO;
				return NULL;
			}
			/* Controle du type de la valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr))!=PFD_A_WORD) {
				/* Ce n'est pas un mot */
				if (AlphPtr) Free_Alph(AlphPtr);
				*ErrIndexPtr = PE_WORD_EXP;
				return NULL;
			}
			/* Lecture du mot */
			WordPtr = Val_Word(PrfExtr_CurrentVal(PrfExtrPtr));
			if (!strcmp(WordPtr, PE_LINEAR_STR)) {
				/* Le mot est LINEAR */
				/* Pas de changement de valeur */
			}
			else if (!strcmp(WordPtr, PE_CIRCULAR_STR)){
				/* Le mot est CIRCULAR */
				Topo = PD_TOPO_CIRCULAR;
			} else {
				/* Mot inconnu */
				if (AlphPtr) Free_Alph(AlphPtr);
				*ErrIndexPtr = PE_ILL_WORD;
				return NULL;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				if (AlphPtr) Free_Alph(AlphPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
			/* Topologie lue */
			TopoRead = TRUE;
		}
		else {
			/* Assignation illegale */
			if (AlphPtr) Free_Alph(AlphPtr);
			*ErrIndexPtr = PE_ILL_ASS;
			return NULL;
		}
		AssPtr = PrfExtr_NextAss(PrfExtrPtr);
	}
	/* Controle des parametres obligatoires */
	if (!AlphPtr) {
		*ErrIndexPtr = PE_ALPH_EXP;
		return NULL;
	}
	/* Construction des specifications generales */
	GenSpecPtr = I_GenSpec(AlphPtr);
	if (!GenSpecPtr) {
		/* Erreur d'allocation */
		Free_Alph(AlphPtr);
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	GenSpec_PutTopo(GenSpecPtr, Topo);
	if (PosNbrRead) GenSpec_PutPosNbr(GenSpecPtr, PosNbr)
	else GenSpec_PutPosNbr(GenSpecPtr, 0);
	*ErrIndexPtr = PE_NO_ERROR;
	return GenSpecPtr;
	/* Attention, on est toujours dans le meme description */
}

/*--------------------------------------------------------------------------*/
/* Extraction de l'exclusion de la description courante						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_Disjoint			| Exclusion							*/
/* Erreur:	| PrfExtr_Disjoint			| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PE_DISJ_EXP				| Exclusion attendue				*/
/*			| PE_DBL_DEF				| Definition deja declaree			*/
/*			| PE_WORD_EXP				| Mot attendu						*/
/*			| PE_ILL_WORD				| Mot illegal						*/
/*			| PE_ILL_VAL				| Valeur illegal					*/
/*			| PE_MEM_ERR				| Erreur d'allocation				*/
/*			| PE_PAR_EXP				| Parametre attendu					*/
/*			| PE_CARD_EXP				| Cardinal attendu					*/
/*			| PE_ILL_ASS				| Assignation illegale				*/
/*			| PE_DEF_EXP				| Definition attendue				*/
/*--------------------------------------------------------------------------*/
TDisjointPtr PrfExtr_Disjoint(TPrfExtrPtr PrfExtrPtr, TErrIndex *ErrIndexPtr)
{
	TDisjointDef Def;
	TDisjointPar Par;
	TDisjointParIndex ParNbr;
	TDisjointParIndex ParIndex;
	TDisjointParListPtr ParListPtr;
	TDisjointPtr DisjointPtr;
	TValPtr ValPtr;
	TAssPtr AssPtr;
	TWordPtr AssWordPtr;
	TWordPtr WordPtr;
	char *CharPtr;
	
	
	/* Recherche de la description */
	if (!PrfExtr_CurrentDesc(PrfExtrPtr)) {
		/* Il n'y a pas de premiere description */
		*ErrIndexPtr = PE_DISJ_EXP;
		return NULL;
	}
	/* Controle du mot-cle */
	if (strcmp(PE_DISJ_STR,
	Desc_Keyword(PrfExtr_CurrentDesc(PrfExtrPtr)))) {
		/* Le mot cle n'est pas l'exclusion */
		*ErrIndexPtr = PE_DISJ_EXP;
		return NULL;
	}
	/* Valeurs par defaut */
	ParListPtr = NULL;
	AssPtr = PrfExtr_CurrentAss(PrfExtrPtr);
	while (AssPtr) {
		AssWordPtr = Ass_Word(AssPtr);
		/* Controle du mot */
		if (!strcmp(PE_DEF_STR, AssWordPtr)) {
			/* Le mot est celui de la definition */
			if (ParListPtr) {
				/* La definition et les parametres ont deja ete lu */
				Free_DisjointParList(ParListPtr);
				*ErrIndexPtr = PE_DBL_DEF;
				return NULL;
			}
			/* Controle du type de valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_WORD) {
				/* La valeur n'est pas un mot */
				*ErrIndexPtr = PE_WORD_EXP;
				return NULL;
			}
			/* Lecture de la definition de l'exclusion */
			if (!strcmp(PE_UNIQUE_STR,
			Val_Word(PrfExtr_CurrentVal(PrfExtrPtr)))) {
				/* Le mot est UNIQUE */
				Def = PD_UNIQUE;
				ParNbr = 0;
			} else if (!strcmp(PE_PROT_STR,
			Val_Word(PrfExtr_CurrentVal(PrfExtrPtr)))) {
				/* Le mot est PROTECT */
				Def = PD_PROTECT;
				ParNbr = 2;
			} else {
				/* Le mot est inconnu */
				*ErrIndexPtr = PE_ILL_WORD;
				return NULL;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il existe une valeur de trop */
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
			/* Lecture des parametres de l'exclusion */
			/* Construction de la liste de parametres */
			ParListPtr = I_DisjointParList(ParNbr);
			if (!ParListPtr) {
				/* Erreur d'allocation */
				*ErrIndexPtr = PE_MEM_ERR;
				return NULL;
			}
			for (ParIndex = 1; ParIndex <= ParNbr; ParIndex++) {
				/* Assignation suivante */
				AssPtr = PrfExtr_NextAss(PrfExtrPtr);
				if (!AssPtr) {
					/* Plus d'assignations */
					Free_DisjointParList(ParListPtr);
					*ErrIndexPtr = PE_PAR_EXP;
					return NULL;
				}
				/* Controle du mot */
				WordPtr = Ass_Word(PrfExtr_CurrentAss(PrfExtrPtr));
				if (Word_CharNth(WordPtr, 1) != 'N') {
					/* Le mot n'est pas Ni */
					Free_DisjointParList(ParListPtr);
					*ErrIndexPtr = PE_PAR_EXP;
					return NULL;
				}
				if (strtol(&Word_CharNth(WordPtr, 2), &CharPtr, 10) !=
				(long int)ParIndex) {
					/* Le mot n'est pas Ni */
					Free_DisjointParList(ParListPtr);
					*ErrIndexPtr = PE_PAR_EXP;
					return NULL;
				}
				if (*CharPtr != 0) {
					/* Le mot n'est pas Ni */
					Free_DisjointParList(ParListPtr);
					*ErrIndexPtr = PE_PAR_EXP;
					return NULL;
				}
				/* Lecture de la valeur */
				/* Controle du type de la valeur */
				if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_NBR) {
					/* La valeur n'est pas un nombre */
					Free_DisjointParList(ParListPtr);
					*ErrIndexPtr = PE_CARD_EXP;
					return NULL;
				}
				/* Lecture du nombre */
				Par = (TDisjointPar)Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr));
				if ((Par < 1) || ((TNbr)Par !=
				Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr)))) {
					/* Le parametre n'est pas un cardinal */
					Free_DisjointParList(ParListPtr);
					*ErrIndexPtr = PE_CARD_EXP;
					return NULL;
				}
				DisjointParList_AddPar(ParListPtr, Par, ParIndex);
				/* Valeur suivante */
				ValPtr = PrfExtr_NextVal(PrfExtrPtr);
				if (ValPtr) {
					/* Il y a une valeur de trop */
					Free_DisjointParList(ParListPtr);
					*ErrIndexPtr = PE_ILL_VAL;
					return NULL;
				}
			}
		}
		else {
			/* Assignation illegale */
			if (ParListPtr) Free_DisjointParList(ParListPtr);
			*ErrIndexPtr = PE_ILL_ASS;
			return NULL;
		}
		AssPtr = PrfExtr_NextAss(PrfExtrPtr);
	}
	/* Controle des parametres obligatoires */
	if (!ParListPtr) {
		/* Definition et parametres non lus */
		*ErrIndexPtr = PE_DEF_EXP;
		return NULL;
	}
	/* Construction de l'exclusion */
	DisjointPtr = I_Disjoint(ParListPtr);
	if (!DisjointPtr) {
		/* Erreur d'allocation */
		Free_DisjointParList(ParListPtr);
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	Disjoint_PutDef(DisjointPtr, Def);
	*ErrIndexPtr = PE_NO_ERROR;
	return DisjointPtr;
	/* Attention, on est toujours dans le meme description */
}

/*--------------------------------------------------------------------------*/
/* Extraction de la normalisation de la description courante				*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_Norm				| Normalisation						*/
/*			| ModePres					| Presence du mode					*/
/*			| ModePres					| = TRUE =>							*/
/*			| Mode						| Mode de la normalisation			*/
/*			| PrtyPres					| Presence de la priorite			*/
/* Erreur:	| PrfExtr_Norm				| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PE_NORM_EXP				| Normalisation attendue			*/
/*			| PE_DBL_FCT				| Fonction deja declaree			*/
/*			| PE_WORD_EXP				| Mot attendu						*/
/*			| PE_ILL_WORD				| Mot illegal						*/
/*			| PE_ILL_VAL				| Valeur illegale					*/
/*			| PE_MEM_ERR				| Erreur allocation memoire			*/
/*			| PE_PAR_EXP				| Parametre attendu					*/
/*			| PE_NBR_EXP				| Nombre attendu					*/
/*			| PE_DBL_MODE				| Mode deja defini					*/
/*			| PE_CARD_EXP				| Cardinal attendu					*/
/*			| PE_DBL_PRTY2				| Priorite deja declaree			*/
/*			| PE_DBL_TEXT				| Texte deja declare				*/
/*			| PE_STR_EXP				| Chaine attendue					*/
/*			| PE_ILL_ASS				| Assignation illegale				*/
/*			| PE_FCT_EXP				| Fonction de norm. attendue		*/
/*--------------------------------------------------------------------------*/
TNormPtr PrfExtr_Norm(TPrfExtrPtr PrfExtrPtr, TNormIndex *ModePtr,
TBoolean *ModePresPtr, TBoolean *PrtyPresPtr, TErrIndex *ErrIndexPtr)
{
	TNormFct Fct;
	TNormParIndex ParNbr;
	TNormParIndex ParIndex;
	TNormParListPtr ParListPtr;
	TNormPrty Prty;
	TText Text;
	TNormPtr NormPtr;
	TValPtr ValPtr;
	TAssPtr AssPtr;
	TWordPtr WordPtr;
	TWordPtr AssWordPtr;
	char *CharPtr;
	
	/* Recherche de la description */
	if (!PrfExtr_CurrentDesc(PrfExtrPtr)) {
		/* Il n'y a pas de premiere description */
		*ErrIndexPtr = PE_NORM_EXP;
		return NULL;
	}
	/* Controle du mot-cle */
	if (strcmp(PE_NORM_STR, Desc_Keyword(PrfExtr_CurrentDesc(PrfExtrPtr)))) {
		/* Le mot cle n'est pas l'exclusion */
		*ErrIndexPtr = PE_NORM_EXP;
		return NULL;
	}
	/* Initialisation de flags */
	*ModePresPtr = FALSE;
	*PrtyPresPtr = FALSE;
	/* Valeurs par defaut */
	Text = NULL;
	ParListPtr = NULL;
	/* Recherche de l'assignation */
	AssPtr = PrfExtr_CurrentAss(PrfExtrPtr);
	while (AssPtr) {
		AssWordPtr = Ass_Word(AssPtr);
		/* Controle du mot */
		if (!strcmp(PE_FCT_STR, Ass_Word(AssPtr))) {
			/* Le mot est celui de la fonction */
			if (ParListPtr) {
				/* Fonction deja lue */
				Free_NormParList(ParListPtr);
				if (Text) Free_Text(Text);
				*ErrIndexPtr = PE_DBL_FCT;
				return NULL;
			}
			/* Controle du type de valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_WORD) {
				/* La valeur n'est pas un mot */
				if (Text) Free_Text(Text);
				*ErrIndexPtr = PE_WORD_EXP;
				return NULL;
			}
			/* Lecture de la fonction de normalisation */
			if (!strcmp(PE_LINEAR_STR,
			Val_Word(PrfExtr_CurrentVal(PrfExtrPtr)))) {
				/* Le mot est LINEAR */
				Fct = PD_NORM_LINEAR;
				ParNbr = 2;
			}
			else if (!strcmp(PE_GRIB_STR,
			Val_Word(PrfExtr_CurrentVal(PrfExtrPtr)))) {
				/* Le mot est GRIBSKOV */
				Fct = PD_NORM_GRIB;
				ParNbr = 5;
			}
			else {
				/* Le mot est inconnu */
				if (Text) Free_Text(Text);
				*ErrIndexPtr = PE_ILL_WORD;
				return NULL;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il existe une valeur de trop */
				if (Text) Free_Text(Text);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
			/* Lecture des parametres de l'exclusion */
			ParListPtr = I_NormParList(ParNbr);
			if (!ParListPtr) {
				/* Erreur allocation */
				if (Text) Free_Text(Text);
				*ErrIndexPtr = PE_MEM_ERR;
				return NULL;
			}
			for (ParIndex = 1; ParIndex <= ParNbr; ParIndex++) {
				/* Assignation suivante */
				AssPtr = PrfExtr_NextAss(PrfExtrPtr);
				if (!AssPtr) {
					/* Plus d'assignations */
					if (Text) Free_Text(Text);
					Free_NormParList(ParListPtr);
					*ErrIndexPtr = PE_PAR_EXP;
					return NULL;
				}
				/* Controle du mot */
				WordPtr = Ass_Word(PrfExtr_CurrentAss(PrfExtrPtr));
				if (Word_CharNth(WordPtr, 1) != 'R') {
					/* Le mot n'est pas Ri */
					if (Text) Free_Text(Text);
					Free_NormParList(ParListPtr);
					*ErrIndexPtr = PE_PAR_EXP;
					return NULL;
				}
				if (strtol(&Word_CharNth(WordPtr, 2), &CharPtr, 10) !=
				(long int)ParIndex) {
					/* Le mot n'est pas Ri */
					if (Text) Free_Text(Text);
					Free_NormParList(ParListPtr);
					*ErrIndexPtr = PE_PAR_EXP;
					return NULL;
				}
				if (*CharPtr != 0) {
					/* Le mot n'est pas Ni */
					if (Text) Free_Text(Text);
					Free_NormParList(ParListPtr);
					*ErrIndexPtr = PE_PAR_EXP;
					return NULL;
				}
				/* Lecture de la valeur */
				/* Controle du type de la valeur */
				if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_NBR) {
					/* La valeur n'est pas un nombre */
					if (Text) Free_Text(Text);
					Free_NormParList(ParListPtr);
					*ErrIndexPtr = PE_NBR_EXP;
					return NULL;
				}
				/* Lecture du nombre */
				NormParList_AddPar(ParListPtr,
				(TNormPar)Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr)), ParIndex);
				/* Valeur suivante */
				ValPtr = PrfExtr_NextVal(PrfExtrPtr);
				if (ValPtr) {
					/* Il y a une valeur de trop */
					if (Text) Free_Text(Text);
					Free_NormParList(ParListPtr);
					*ErrIndexPtr = PE_ILL_VAL;
					return NULL;
				}
			}
		}
		else if (!strcmp(PE_MODE_STR, AssWordPtr)) {
			/* Il s'agit d'un mode */
			if (*ModePresPtr) {
				/* Mode deja lu */
				if (Text) Free_Text(Text);
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_DBL_MODE;
				return NULL;
			}
			/* Controle du type de la valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_NBR) {
				/* La valeur n'est pas un cardinal */
				if (Text) Free_Text(Text);
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_CARD_EXP;
				return NULL;
			}
			*ModePtr = (TNormIndex)Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr));
			if ((*ModePtr < 1) ||
			((TNbr)(*ModePtr) != Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr)))) {
				/* Le nombre n'est pas un cardinal */
				if (Text) Free_Text(Text);
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_CARD_EXP;
				return NULL;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				if (Text) Free_Text(Text);
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
			/* Mode lue */
			*ModePresPtr = TRUE;
		}
		else if (!strcmp(PE_PRTY_STR, AssWordPtr)) {
			/* Il s'agit d'une priorite */
			if (*PrtyPresPtr) {
				/* Priorite deja lue */
				if (Text) Free_Text(Text);
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_DBL_PRTY2;
				return NULL;
			}
			/* Controle du type de la valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_NBR) {
			/* La valeur n'est pas un entier positif */
				if (Text) Free_Text(Text);
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_CARD_EXP;
				return NULL;
			}
			Prty = (TNormPrty)Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr));
			if ((Prty < 1) ||
			((TNbr)Prty != Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr)))) {
				/* Le nombre n'est pas un cardinal */
				if (Text) Free_Text(Text);
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_CARD_EXP;
				return NULL;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				if (Text) Free_Text(Text);
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
			/* priorite lue */
			*PrtyPresPtr = TRUE;
		}
		else if (!strcmp(PE_TEXT_STR, AssWordPtr)) {
			/* Il s'agit d'un texte */
			if (Text) {
				/* Texte deja lu */
				Free_Text(Text);
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_DBL_TEXT;
				return NULL;
			}
			/* Controle de la valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_STR) {
				/* Ce n'est pas une chaine */
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_STR_EXP;
				return NULL;
			}
			/* C'est une chaine */
			Text = Str_To_Text((char*)Val_Str(PrfExtr_CurrentVal(PrfExtrPtr)));
			if (!Text) {
				/* Erreur d'allocation */
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_MEM_ERR;
				return NULL;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				Free_Text(Text);
				if (ParListPtr) Free_NormParList(ParListPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
		}
		else {
			/* Assignation illegale */
			if (Text) Free_Text(Text);
			if (ParListPtr) Free_NormParList(ParListPtr);
			*ErrIndexPtr = PE_ILL_ASS;
			return NULL;
		}
		AssPtr = PrfExtr_NextAss(PrfExtrPtr);
	}
	/* Controle des parametres obligatoires */
	if (!ParListPtr) {
		/* Fonction et parametres non lus */
		if (Text) Free_Text(Text);
		*ErrIndexPtr = PE_FCT_EXP;
		return NULL;
	}
	/* Construction de la normalisation */
	NormPtr = I_Norm(ParListPtr, Text);
	if (!NormPtr) {
		/* Erreur d'allocation */
		if (Text) Free_Text(Text);
		Free_NormParList(ParListPtr);
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	Norm_PutFct(NormPtr, Fct);
	if (*PrtyPresPtr) Norm_PutPrty(NormPtr, Prty);
	*ErrIndexPtr = PE_NO_ERROR;
	return NormPtr;
	/* Attention, on est toujours dans le meme description */
}

/*--------------------------------------------------------------------------*/
/* Extraction de la liste des normalisations a partir de la desc. courante	*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_NormList			| Liste de normalisations			*/
/* Erreur:	| PrfExtr_NormList			| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PE_MEM_ERR				| Erreur allocation memoire			*/
/*			| PE_DBL_FCT				| Fonction deja declaree			*/
/*			| PE_WORD_EXP				| Mot attendu						*/
/*			| PE_ILL_WORD				| Mot illegal						*/
/*			| PE_ILL_VAL				| Valeur illegale					*/
/*			| PE_PAR_EXP				| Parametre attendu					*/
/*			| PE_NBR_EXP				| Nombre attendu					*/
/*			| PE_DBL_MODE				| Mode deja defini					*/
/*			| PE_CARD_EXP				| Cardinal attendu					*/
/*			| PE_DBL_PRTY2				| Priorite deja declaree			*/
/*			| PE_DBL_TEXT				| Texte deja declare				*/
/*			| PE_STR_EXP				| Chaine attendue					*/
/*			| PE_ILL_ASS				| Assignation illegale				*/
/*			| PE_FCT_EXP				| Fonction de norm. attendue		*/
/*			| PE_NORM_MODE_ILL			| Mode de normalisation illegal		*/
/*			| PE_NORM_PRTY_ILL			| Priorite de normalisation ill.	*/
/*			| PE_DBL_NORM_MODE			| Mode de normalisation a double	*/
/*			| PE_NORM_MODE_OVF			| Trop de modes de normalisation	*/
/*			| PE_NORM_MODE_MISS			| Il manque un mode de norm.		*/
/*			| PE_OUT_PRTY				| Priorite hors rangee				*/
/*			| PE_DBL_PRTY				| Priorite deja utilisee			*/
/*			| PE_NORM_MISS_PRTY			| Priorite manquante				*/
/*--------------------------------------------------------------------------*/
TNormListPtr PrfExtr_NormList(TPrfExtrPtr PrfExtrPtr, TErrIndex *ErrIndexPtr)
{
	/* Verification des modes et des priorites */
	TBoolean ModePres;
	TBoolean PrtyPres;
	TNormIndex Mode;
	TNormPrty Prty;
	TBoolean NormModePres;
	TBoolean NormPrtyPres;
	TNormPtr NormPtr;
	TNormListPtr NormListPtr;
	TBoolean Over;
	TBoolean PrtyComplete;
	TBoolean ModeComplete;
	
	Over = FALSE;
	NormListPtr = I_NormList(PE_MAX_NORM_NBR);
	if (!NormListPtr) {
		/* Erreur d'allocation */
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	/* Lecture de la premiere normalisation */
	NormPtr = PrfExtr_Norm(PrfExtrPtr, &Mode, &NormModePres,
	&NormPrtyPres, ErrIndexPtr);
	if (!NormPtr) {
		/* Erreur dans la lecture */
		if (*ErrIndexPtr == PE_NORM_EXP) {
			/* Ce n'est pas une normalisation -> fin */
			*ErrIndexPtr = PE_NO_ERROR;
			return NormListPtr;
		}
		else {
			/* C'est une autre erreur */
			/* Renvoi de l'erreur */
			Free_NormList(NormListPtr);
			return NULL;
		}
	}
	/* Verification des presences des modes et des priorites */
	if (NormModePres) {
		/* Le mode de la normalisation est present */
		ModePres = TRUE;
	}
	else {
		/* Initialisation du mode */
		ModePres = FALSE;
		Mode = 1;
	}
	if (NormPrtyPres) {
		/* La priorite de la normalisation est presente */
		PrtyPres = TRUE;
	}
	else {
		PrtyPres = FALSE;
		/* Initialisation de la priorite */
		Prty = 1;
	}
	/* Ajout de la normalisation */
	NormList_AddNorm(NormListPtr, NormPtr, Mode);
	PrfExtr_NextDesc(PrfExtrPtr);
	while (!Over) {
		/* Lecture de la normalisation */
		NormPtr = PrfExtr_Norm(PrfExtrPtr, &Mode, &NormModePres,
		&NormPrtyPres, ErrIndexPtr);
		if (!NormPtr) {
			/* Erreur dans la lecture */
			if (*ErrIndexPtr == PE_NORM_EXP) {
				/* Ce n'est pas une normalisation -> fin */
				Over = TRUE;
			}
			else {
				/* C'est une autre erreur */
				/* Renvoi de l'erreur */
				Free_NormList(NormListPtr);
				return NULL;
			}
		}
		if (!Over) {
			/* Lecture effectuee */
			/* Test de la coherence des presences */
			if (NormModePres != ModePres) {
				/* Incoherence des mode */
				Free_Norm(NormPtr);
				Free_NormList(NormListPtr);
				*ErrIndexPtr = PE_NORM_MODE_ILL;
				return NULL;
			}
			if (NormPrtyPres != PrtyPres) {
				/* Incoherence des priorites */
				Free_Norm(NormPtr);
				Free_NormList(NormListPtr);
				*ErrIndexPtr = PE_NORM_PRTY_ILL;
				return NULL;
			}
			/* Traitement du mode */
			if (!ModePres) {
				/* Incrementation du mode */
				Mode++;
			}
			else if (NormList_NormNth(NormListPtr, Mode)) {
				/* Verification de la non pre-existence du mode */
				/* Ce mode existe deja */
				Free_NormList(NormListPtr);
				Free_Norm(NormPtr);
				*ErrIndexPtr = PE_DBL_NORM_MODE;
				return NULL;
			}
			/* Test de la grandeur du mode */
			if (Mode > NormList_MaxNormNbr(NormListPtr)) {
				/* Le No de mode est trop grand */
				Free_NormList(NormListPtr);
				Free_Norm(NormPtr);
				*ErrIndexPtr = PE_NORM_MODE_OVF;
				return NULL;
			}
			/* Traitement de la priorite */
			if (!PrtyPres) {
				/* Incrementation de la priorite */
				Prty++;
				Norm_Prty(NormPtr) = Prty;
			}
			NormList_AddNorm(NormListPtr, NormPtr, Mode);
			PrfExtr_NextDesc(PrfExtrPtr);
		}
	}
	/* Test des mode */
	if (ModePres) {
		ModeComplete = NormList_Complete(NormListPtr);
		if (!ModeComplete) {
			/* Il manque des modes */
			Free_NormList(NormListPtr);
			*ErrIndexPtr = PE_NORM_MODE_MISS;
			return NULL;
		}
	}
	/* Test des priorites */
	if (PrtyPres) {
		PrtyComplete = NormList_PrtyComplete(NormListPtr, ErrIndexPtr);
		if (!PrtyComplete) {
			/* Une erreur dans le teste des priorites est survenue */
			/* Renvoi de l'erreur */
			Free_NormList(NormListPtr);
			return NULL;
		}
	}
	*ErrIndexPtr = PE_NO_ERROR;
	/*Resize_NormList(NormListPtr);*/
	return NormListPtr;
}

/*--------------------------------------------------------------------------*/
/* Extraction de la valeur de coupure de la description courante			*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_CutOff			| Liste de normalisation			*/
/* Erreur:	| PrfExtr_CutOff			| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PE_CUTOFF_EXP				| Valeur de coupure manquante		*/
/*			| PE_DBL_SCORE				| Score deja declare				*/
/*			| PE_INT_EXP				| Entier attendu					*/
/*			| PE_ILL_VAL				| Valeur illegale					*/
/*			| PE_DBL_LEVEL2				| Niveau deja declare				*/
/*			| PE_DBL_NSCORE				| Scores norm. deja declares		*/
/*			| PE_MEM_ERR				| Erreur allocation memoire			*/
/*			| PE_NSCORE_MODE_EXP		| Mode du score norm. attendu		*/
/*			| PE_NSCORE_NBR_INC			| Nombre de scores incorrect		*/
/*			| PE_CARD_EXP				| Cardinal attendu					*/
/*			| PE_DBL_TEXT				| Texte deja declare				*/
/*			| PE_STR_EXP				| Chaine attendue					*/
/*			| PE_ILL_ASS				| Assignation illegale				*/
/*			| PE_SCORE_EXP				| Score attendu						*/
/*--------------------------------------------------------------------------*/
TCutOffPtr PrfExtr_CutOff(TPrfExtrPtr PrfExtrPtr, TErrIndex *ErrIndexPtr)
{
	TCutOffPtr CutOffPtr;
	TScore Score;
	TCutOffLevel Level;
	TText Text;
	TNScoreListPtr NScoreListPtr;
	TBoolean ScoreRead = FALSE;
	TBoolean LevelRead = FALSE;
	TValPtr ValPtr;
	TAssPtr AssPtr;
	TWordPtr AssWordPtr;
	TNScoreIndex NScoreNbr;
	TNScoreIndex NScoreIndex;
	TNormIndex Mode;
	
	/* Recherche de la description */
	if (!PrfExtr_CurrentDesc(PrfExtrPtr)) {
		/* Il n'y a pas de description */
		*ErrIndexPtr = PE_CUTOFF_EXP;
		return NULL;
	}
	/* Controle du mot-cle */
	if (strcmp(PE_CUTOFF_STR, Desc_Keyword(PrfExtr_CurrentDesc(PrfExtrPtr)))) {
		/* Le mot cle n'est pas la valeur de coupure */
		*ErrIndexPtr = PE_CUTOFF_EXP;
		return NULL;
	}
	/* Valeurs par defaut */
	Text = NULL;
	NScoreListPtr = NULL;
	/* Boucle de lecture */
	AssPtr = PrfExtr_CurrentAss(PrfExtrPtr);
	while (AssPtr) {
		AssWordPtr = Ass_Word(AssPtr);
		/* Controle du mot */
		if (!strcmp(PE_SCORE_STR, AssWordPtr)) {
			/* Lecture du score */
			if (ScoreRead) {
				/* Score deja lu */
				if (Text) Free_Text(Text);
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_DBL_SCORE;
				return NULL;
			}
			/* Controle du type de valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_NBR) {
				/* La valeur n'est pas un entier */
				if (Text) Free_Text(Text);
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_INT_EXP;
				return NULL;
			}
			Score = (TScore)Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr));
			/* Controle du score */
			if ((TNbr)Score != Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr))) {
				/* Le score n'est pas un entier */
				if (Text) Free_Text(Text);
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_INT_EXP;
				return NULL;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il existe une valeur de trop */
				if (Text) Free_Text(Text);
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
			/* Score lu */
			ScoreRead = TRUE;
		}
		else if (!strcmp(PE_LEVEL_STR, AssWordPtr)) {
			/* Lecture du niveau */
			if (LevelRead) {
				/* Niveau deja lu */
				if (Text) Free_Text(Text);
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_DBL_LEVEL2;
				return NULL;
			}
			/* Controle de la valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_NBR) {
				/* Ce n'est pas un nombre */
				if (Text) Free_Text(Text);
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_INT_EXP;
				return NULL;
			}
			Level = (TCutOffLevel)Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr));
			/* Controle de la valeur */
			if ((TNbr)(Level) != Val_Nbr(PrfExtr_CurrentVal(PrfExtrPtr))) {
				/* Ce n'est pas un  entier */
				if (Text) Free_Text(Text);
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_INT_EXP;
				return NULL;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il existe une valeur de trop */
				if (Text) Free_Text(Text);
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
			/* Niveau lu */
			LevelRead = TRUE;
		}
		else if (!strcmp(PE_N_SCORE_STR, AssWordPtr)) {
			/* Lecture des scores normalises et des modes */
			if (NScoreListPtr) {
				/* Scores normalises et modes deja lus */
				if (Text) Free_Text(Text);
				Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_DBL_NSCORE;
				return NULL;
			}
			/* Lecture de nombre de scores normalises */
			NScoreNbr = (TNScoreIndex)Ass_ValNbr
			(PrfExtr_CurrentAss(PrfExtrPtr));
			/* Creation de la liste de scores */
			NScoreListPtr = I_NScoreList(NScoreNbr);
			if (!NScoreListPtr) {
				/* Erreur allocation */
				if (Text) Free_Text(Text);
				*ErrIndexPtr = PE_MEM_ERR;
				return NULL;
			}
			/* Lecture des scores normalises */
			for (NScoreIndex = 0; NScoreIndex < NScoreNbr; NScoreIndex++) {
				ValPtr = Ass_ValNth(PrfExtr_CurrentAss(PrfExtrPtr),
				(TValIndex)NScoreIndex);
				/* Controle du type de la valeur */
				if (Val_Type(ValPtr) != PFD_A_NBR) {
					/* Ce n'est pas un nombre */
					if (Text) Free_Text(Text);
					*ErrIndexPtr = PE_NBR_EXP;
					return NULL;
				}
				NScoreList_AddVal(NScoreListPtr, (TNScoreVal)Val_Nbr(ValPtr),
				NScoreIndex);
			}
			/* Assignation suivante */
			AssPtr = PrfExtr_NextAss(PrfExtrPtr);
			if (!AssPtr) {
				/* Il n'y plus d'assignation */
				if (Text) Free_Text(Text);
				Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_NSCORE_MODE_EXP;
				return NULL;
			}
			/* Lecture des modes de normalisations */
			/* Controle de l'assignation */
			if (strcmp(PE_MODE_STR, Ass_Word(AssPtr))) {
				/* Ce n'est pas un mode de normalisation */
				if (Text) Free_Text(Text);
				Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_NSCORE_MODE_EXP;
				return NULL;
			}
			/* Controle du nombre de modes */
			if ((TNScoreIndex)Ass_ValNbr(AssPtr) != NScoreNbr) {
				/* Nombre de score incorrect */
				if (Text) Free_Text(Text);
				Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_NSCORE_NBR_INC;
				return NULL;
			}
			/* Lecture des modes */
			for (NScoreIndex = 0; NScoreIndex < NScoreNbr; NScoreIndex++) {
				ValPtr = Ass_ValNth(AssPtr, NScoreIndex);
				/* Controle de la valeur */
				if (Val_Type(ValPtr) != PFD_A_NBR) {
					/* Ce n'est pas un nombre */
					if (Text) Free_Text(Text);
					Free_NScoreList(NScoreListPtr);
					*ErrIndexPtr = PE_CARD_EXP;
					return NULL;
				}
				Mode = (TNormIndex)Val_Nbr(ValPtr);
				/* Controle du nombre */
				if ((Mode < 1) || ((TNbr)Mode != Val_Nbr(ValPtr))) {
					/* Ce n'est pas un cardinal */
					if (Text) Free_Text(Text);
					Free_NScoreList(NScoreListPtr);
					*ErrIndexPtr = PE_CARD_EXP;
					return NULL;
				}
				NScoreList_AddMode(NScoreListPtr, Mode, NScoreIndex);	
			}
			/* Nombre de valeurs deja controle */
		}
		else if (!strcmp(PE_TEXT_STR, AssWordPtr)) {
			/* Lecture du texte */
			if (Text) {
				/* Texte deja lu */
				Free_Text(Text);
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_DBL_TEXT;
				return NULL;
			}
			/* Controle de la valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_STR) {
				/* Ce n'est pas une chaine */
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_STR_EXP;
				return NULL;
			}
			/* Lecture de la chaine */
			Text = Str_To_Text((char*)Val_Str(PrfExtr_CurrentVal(PrfExtrPtr)));
			if (!Text) {
				/* Erreur d'allocation */
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_MEM_ERR;
				return NULL;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il existe une valeur de trop */
				if (Text) Free_Text(Text);
				if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
		}
		else {
			/* Assignation illegale */
			if (Text) Free_Text(Text);
			if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
			*ErrIndexPtr = PE_ILL_ASS;
			return NULL;
		}
		AssPtr = PrfExtr_NextAss(PrfExtrPtr);
	}	
	/* Controle des valeurs obligatoires */	
	if (!ScoreRead) {
		/* Score non lu */
		if (Text) Free_Text(Text);
		if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
		*ErrIndexPtr = PE_SCORE_EXP;
		return NULL;
	}
	/* Construction de la valeur de coupure */
	CutOffPtr = I_CutOff(Text, NScoreListPtr);
	if (!CutOffPtr) {
		/* Erreur d'allocation */
		if (Text) Free_Text(Text);
		if (NScoreListPtr) Free_NScoreList(NScoreListPtr);
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	CutOff_PutLevel(CutOffPtr, Level);
	CutOff_PutScore(CutOffPtr, Score);
	*ErrIndexPtr = PE_NO_ERROR;
	return CutOffPtr;
}

/*--------------------------------------------------------------------------*/
/* Extraction de la liste de valeurs de coupure a partir de la desc. cour.	*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_CutOffList		| Liste de valeurs de coupure		*/
/* Erreur:	| PrfExtr_CutOffList=NULL	| =>								*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PE_MEM_ERR				| Erreur allocation memoire			*/
/*			| PE_CUTOFF_EXP				| Valeur de coupure manquante		*/
/*			| PE_DBL_SCORE				| Score deja declare				*/
/*			| PE_INT_EXP				| Entier attendu					*/
/*			| PE_ILL_VAL				| Valeur illegale					*/
/*			| PE_DBL_LEVEL2				| Niveau deja declare				*/
/*			| PE_DBL_NSCORE				| Scores norm. deja declares		*/
/*			| PE_NSCORE_MODE_EXP		| Mode du score norm. attendu		*/
/*			| PE_NSCORE_NBR_INC			| Nombre de scores incorrect		*/
/*			| PE_CARD_EXP				| Cardinal attendu					*/
/*			| PE_DBL_TEXT				| Texte deja declare				*/
/*			| PE_STR_EXP				| Chaine attendue					*/
/*			| PE_ILL_ASS				| Assignation illegale				*/
/*			| PE_SCORE_EXP				| Score attendu						*/
/*			| PE_DBL_LEVEL				| Niveau de cut-off a double		*/
/*			| PE_LEVEL_OVF				| Trop de niveaux					*/
/*			| PE_LEVEL_MISS				| Niveau de cut-off manquant		*/
/*--------------------------------------------------------------------------*/
TCutOffListPtr PrfExtr_CutOffList(TPrfExtrPtr PrfExtrPtr,
TErrIndex *ErrIndexPtr)
{
	TCutOffPtr CutOffPtr;
	TCutOffListPtr CutOffListPtr;
	TCutOffListPtr ResCutOffListPtr;
	
	CutOffListPtr = I_CutOffList(PE_MAX_CUTOFF_NBR);
	if (!CutOffListPtr) {
		/* Erreur d'allocation */
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	/* Lecture de la premiere valeur de coupure */
	CutOffPtr = PrfExtr_CutOff(PrfExtrPtr, ErrIndexPtr);
	if (!CutOffPtr) {
		/* Une valeur de coupure est obligatoire */
		Free_CutOffList(CutOffListPtr);
		/* Renvoi de l'erreur */
		return NULL;
	}
	if (CutOffList_Full(CutOffListPtr)) {
		/* Trop de valeurs de coupure */
		Free_CutOffList(CutOffListPtr);
		*ErrIndexPtr = PE_LEVEL_OVF;
		return NULL;
	}
	CutOffList_AddCutOff(CutOffListPtr, CutOffPtr);
	/* Lecture des autres valeurs de coupures */
	PrfExtr_NextDesc(PrfExtrPtr);
	while (TRUE) {
		/* Lecture de la valeur de coupure */
		CutOffPtr = PrfExtr_CutOff(PrfExtrPtr, ErrIndexPtr);
		if (!CutOffPtr) {
			/* Erreur dans la lecture */
			if (*ErrIndexPtr == PE_CUTOFF_EXP) {
				/* Ce n'est pas une valeur de coupure */
				break;
			}
			else {
				/* Renvoi de l'erreur */
				Free_CutOffList(CutOffListPtr);
				return NULL;
			}
		}
		if (CutOffList_Full(CutOffListPtr)) {
			/* Trop de valeurs de coupure */
			Free_CutOffList(CutOffListPtr);
			*ErrIndexPtr = PE_LEVEL_OVF;
			return NULL;
		}
		CutOffList_AddCutOff(CutOffListPtr, CutOffPtr);
		PrfExtr_NextDesc(PrfExtrPtr);
	}
	/* Tri des niveaux */
	ResCutOffListPtr = CutOffList_Sort(CutOffListPtr, ErrIndexPtr);
	if (!ResCutOffListPtr) {
		/* Renvoi de l'erreur*/
		Free_CutOffList(CutOffListPtr);
		return NULL;
	}
	/* CutOffListPtr a ete detruit */
	CutOffListPtr = ResCutOffListPtr;
	*ErrIndexPtr = PE_NO_ERROR;
	/*Resize_CutOffList(CutOffListPtr);*/
	return CutOffListPtr;
}

/*--------------------------------------------------------------------------*/
/* Conversion d'une valeur en score											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ValPtr					| Valeur							*/
/* Sortie:	| Val_Score					| Score								*/
/* Erreur:	| ErrIndex!=PE_NO_ERROR		| Index d'erreur =					*/
/*			| PE_INT_EXP				| Entier attendu					*/
/*--------------------------------------------------------------------------*/
TScore Val_Score(TValPtr ValPtr, TErrIndex *ErrIndexPtr)
{
	TScore Score;
	
	
	if (Val_Type(ValPtr) == PFD_INFINITE) {
		/* Le score est infini */
		*ErrIndexPtr = PE_NO_ERROR;
		return PD_INFINITE;
	}
	if (Val_Type(ValPtr) != PFD_A_NBR) {
		/* Ce n'est pas un nombre */
		*ErrIndexPtr = PE_INT_EXP;
		return 0;
	}
	Score = (TScore)Val_Nbr(ValPtr);
	if ((TNbr)Score != Val_Nbr(ValPtr)) {
		/* Ce n'est pas un entier */
		*ErrIndexPtr = PE_INT_EXP;
		return 0;
	}
	*ErrIndexPtr = PE_NO_ERROR;
	return Score;
}

/*--------------------------------------------------------------------------*/
/* Extraction de la position d'insertion de la description courante			*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/*			| DefaultInsPosPtr			| Position d'insertion par defaut	*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| PrfExtr_InsPos			| Position d'insertion				*/
/* Erreur:	| PrfExtr_InsPos			| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PE_MEM_ERR				| Erreur allocation memoire			*/
/*			| PE_DBL_SYMB				| Symbole deja declare				*/
/*			| PE_SYMB_EXP				| Symbole attendu					*/
/*			| PE_ILL_VAL				| Valeur illegale					*/
/*			| PE_DBL_SCORE				| Score deja declare				*/
/*			| PE_INT_EXP				| Entier attendu					*/
/*			| PE_BAD_SCORE_NBR			| Mauvais nombre de scores			*/
/*			| PE_ILL_WORD				| Mot illegal						*/
/*--------------------------------------------------------------------------*/
TInsPosPtr PrfExtr_InsPos(TPrfExtrPtr PrfExtrPtr, TInsPosPtr DefaultInsPosPtr,
TAlphPtr AlphPtr, TErrIndex *ErrIndexPtr)
{
	TBoolean SymbRead = FALSE;
	TBoolean IRead = FALSE;
	TBoolean B0Read = FALSE;
	TBoolean B1Read = FALSE;
	TBoolean E0Read = FALSE;
	TBoolean E1Read = FALSE;
	TBoolean BMRead = FALSE;
	TBoolean BIRead = FALSE;
	TBoolean BDRead = FALSE;
	TBoolean BERead = FALSE;
	TBoolean MMRead = FALSE;
	TBoolean MIRead = FALSE;
	TBoolean MDRead = FALSE;
	TBoolean MERead = FALSE;
	TBoolean IMRead = FALSE;
	TBoolean IIRead = FALSE;
	TBoolean IDRead = FALSE;
	TBoolean IERead = FALSE;
	TBoolean DMRead = FALSE;
	TBoolean DIRead = FALSE;
	TBoolean DDRead = FALSE;
	TBoolean DERead = FALSE;
	TBoolean I0Read = FALSE;
	TInsPosPtr InsPosPtr;
	TAssPtr AssPtr;
	TWordPtr AssWordPtr;
	TValPtr ValPtr;
	TValIndex ValNbr;
	TValIndex ValIndex;
	TScore Score;
	TAlphSize AlphSize;
	
	/* Creation de la position d'insertion */
	AlphSize = Alph_Size(AlphPtr);
	InsPosPtr = Clone_InsPos(DefaultInsPosPtr, AlphSize);
	if (!InsPosPtr) {
		/* Erreur allocation */
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	/* Boucle de lecture */
	AssPtr = PrfExtr_CurrentAss(PrfExtrPtr);
	while (AssPtr) {
		AssWordPtr = Ass_Word(AssPtr);
		if (!strcmp(PE_SYMB_STR, AssWordPtr)) {
			/* Lecture d'un symbole */
			if (SymbRead) {
				/* Symbole deja lu */
				Free_InsPos(InsPosPtr);
				*ErrIndexPtr = PE_DBL_SYMB;
				return NULL;
			}
			/* Controle du type de la valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_STR) {
				/* Ce n'est pas une chaine */
				Free_InsPos(InsPosPtr);
				*ErrIndexPtr = PE_SYMB_EXP;
				return NULL;
			}
			/* Controle de la longueur de la chaine */
			if (strlen((char*)Val_Str(PrfExtr_CurrentVal(PrfExtrPtr))) != 1) {
				/* La chaine fait plus d'un caractere */
				Free_InsPos(InsPosPtr);
				*ErrIndexPtr = PE_SYMB_EXP;
				return NULL;
			}
			/* Affectation du symbole */
			InsPos_Symb(InsPosPtr) =
			Str_CharNth(Val_Str(PrfExtr_CurrentVal(PrfExtrPtr)), 0);
			/* Prochaine valeur */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				Free_InsPos(InsPosPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
			/* Symbole lu */
			SymbRead = TRUE;
		}
		else if (!strcmp(PE_I_STR, AssWordPtr)) {
			/* Lecture d'un score d'insertion */
			if (IRead) {
				/* Score d'insertion deja lu */
				Free_InsPos(InsPosPtr);
				*ErrIndexPtr = PE_DBL_SCORE;
				return NULL;
			}
			/* Lecture des parametres */
			ValNbr = Ass_ValNbr(AssPtr);
			if (ValNbr == 1) {
				/* Controle du score */
				Score = Val_Score(PrfExtr_CurrentVal(PrfExtrPtr), ErrIndexPtr);
				if (*ErrIndexPtr != PE_NO_ERROR) {
					/* Il y a une erreur de lecture du score */
					Free_InsPos(InsPosPtr);
					/* Renvoi de l'erreur */
					return NULL;
				}
				/* Affectation */
				for (ValIndex = 0; ValIndex < AlphSize; ValIndex++) {
					ScoreVect_PutScore(InsPos_I(InsPosPtr), Score,
					(TAlphSize)ValIndex + 1);
				}
			}
			else if (ValNbr == AlphSize) {
				/* Lecture de tous les parametres */
				for (ValIndex = 0; ValIndex < AlphSize; ValIndex++) {
					Score = Val_Score(
					Ass_ValNth(AssPtr, ValIndex), ErrIndexPtr);
					if (*ErrIndexPtr != PE_NO_ERROR) {
						/* Il y a une erreur de lecture du score */
						Free_InsPos(InsPosPtr);
						/* Renvoi de l'erreur */
						return NULL;
					}
					ScoreVect_PutScore(InsPos_I(InsPosPtr), Score,
					(TAlphSize)ValIndex + 1);
				}
			}
			else {
				/* Le nombre de valeurs est incorrect */
				Free_InsPos(InsPosPtr);
				*ErrIndexPtr = PE_BAD_SCORE_NBR;
				return NULL;
			}
			/* Nombre de valeurs deja controle */
			/* Score d'insertion lu */
			IRead = TRUE;
		}
		else {
			/* Lecture d'un score d'insertion a un parametre */
			Score = Val_Score(PrfExtr_CurrentVal(PrfExtrPtr), ErrIndexPtr);
			if (*ErrIndexPtr != PE_NO_ERROR) {
				/* Il y a une erreur de lecture du score */
				Free_InsPos(InsPosPtr);
				/* Renvoi de l'erreur */
				return NULL;
			}
			/* Affectation */
			if (!strcmp(PE_B0_STR, AssWordPtr)) {
				if (B0Read) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_B0(InsPosPtr) = Score;
				B0Read = TRUE;
			}
			else if (!strcmp(PE_B1_STR, AssWordPtr)) {
				if (B1Read) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_B1(InsPosPtr) = Score;
				B1Read = TRUE;
			}
			else if (!strcmp(PE_E0_STR, AssWordPtr)) {
				if (E0Read) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_E0(InsPosPtr) = Score;
				E0Read = TRUE;
			}
			else if (!strcmp(PE_E1_STR, AssWordPtr)) {
				if (E1Read) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_E1(InsPosPtr) = Score;
				E1Read = TRUE;
			}
			else if (!strcmp(PE_BM_STR, AssWordPtr)) {
				if (BMRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_BM(InsPosPtr) = Score;
				BMRead = TRUE;
			}
			else if (!strcmp(PE_BI_STR, AssWordPtr)) {
				if (BIRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_BI(InsPosPtr) = Score;
				BIRead = TRUE;
			}
			else if (!strcmp(PE_BD_STR, AssWordPtr)) {
				if (BDRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_BD(InsPosPtr) = Score;
				BDRead = TRUE;
			}
			else if (!strcmp(PE_BE_STR, AssWordPtr)) {
				if (BERead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_BE(InsPosPtr) = Score;
				BERead = TRUE;
			}
			else if (!strcmp(PE_MM_STR, AssWordPtr)) {
				if (MMRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_MM(InsPosPtr) = Score;
				MMRead = TRUE;
			}
			else if (!strcmp(PE_MI_STR, AssWordPtr)) {
				if (MIRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_MI(InsPosPtr) = Score;
				MIRead = TRUE;
			}
			else if (!strcmp(PE_MD_STR, AssWordPtr)) {
				if (MDRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_MD(InsPosPtr) = Score;
				MDRead = TRUE;
			}
			else if (!strcmp(PE_ME_STR, AssWordPtr)) {
				if (MERead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_ME(InsPosPtr) = Score;
				MERead = TRUE;
			}
			else if (!strcmp(PE_IM_STR, AssWordPtr)) {
				if (IMRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_IM(InsPosPtr) = Score;
				IMRead = TRUE;
			}
			else if (!strcmp(PE_II_STR, AssWordPtr)) {
				if (IIRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_II(InsPosPtr) = Score;
				IIRead = TRUE;
			}
			else if (!strcmp(PE_ID_STR, AssWordPtr)) {
				if (IDRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_ID(InsPosPtr) = Score;
				IDRead = TRUE;
			}
			else if (!strcmp(PE_IE_STR, AssWordPtr)) {
				if (IERead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_IE(InsPosPtr) = Score;
				IERead = TRUE;
			}
			else if (!strcmp(PE_DM_STR, AssWordPtr)) {
				if (DMRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_DM(InsPosPtr) = Score;
				DMRead = TRUE;
			}
			else if (!strcmp(PE_DI_STR, AssWordPtr)) {
				if (DIRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_DI(InsPosPtr) = Score;
				DIRead = TRUE;
			}
			else if (!strcmp(PE_DD_STR, AssWordPtr)) {
				if (DDRead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_DD(InsPosPtr) = Score;
				DDRead = TRUE;
			}
			else if (!strcmp(PE_DE_STR, AssWordPtr)) {
				if (DERead) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				InsPos_DE(InsPosPtr) = Score;
				DERead = TRUE;
			}
			else if (!strcmp(PE_I0_STR, AssWordPtr)) {
				if (I0Read) {
					Free_InsPos(InsPosPtr);
					*ErrIndexPtr = PE_DBL_SCORE;
					return NULL;
				}
				ScoreVect_PutScore(InsPos_I(InsPosPtr), Score, 0);
				I0Read = TRUE;
			}
			else {
				/* Parametre d'insertion inconnu */
				Free_InsPos(InsPosPtr);
				*ErrIndexPtr = PE_ILL_WORD;
				return NULL;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				Free_InsPos(InsPosPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
		}
		AssPtr = PrfExtr_NextAss(PrfExtrPtr);
	}
	/* Il n'y a pas de parametres obligatoires */
	*ErrIndexPtr = PE_NO_ERROR;
	return InsPosPtr;
}

/*--------------------------------------------------------------------------*/
/* Extraction de la position match de la description courante				*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/*			| DefaultMatchPosPtr		| Position match par defaut			*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| PrfExtr_MatchPos			| Position match					*/
/* Erreur:	| PrfExtr_MatchPos			| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PE_MEM_ERR				| Erreur allocation memoire			*/
/*			| PE_DBL_SYMB				| Symbole deja declare				*/
/*			| PE_SYMB_EXP				| Symbole attendu					*/
/*			| PE_ILL_VAL				| Valeur illegale					*/
/*			| PE_DBL_SCORE				| Score deja declare				*/
/*			| PE_INT_EXP				| Entier attendu					*/
/*			| PE_BAD_SCORE_NBR			| Mauvais nombre de scores			*/
/*			| PE_ILL_WORD				| Mot illegal						*/
/*--------------------------------------------------------------------------*/
TMatchPosPtr PrfExtr_MatchPos(TPrfExtrPtr PrfExtrPtr,
TMatchPosPtr DefaultMatchPosPtr, TAlphPtr AlphPtr, TErrIndex *ErrIndexPtr)
{
	TBoolean SymbRead = FALSE;
	TBoolean MRead = FALSE;
	TBoolean M0Read = FALSE;
	TBoolean DRead = FALSE;
	TMatchPosPtr MatchPosPtr;
	TAssPtr AssPtr;
	TWordPtr AssWordPtr;
	TValPtr ValPtr;
	TValIndex ValNbr;
	TValIndex ValIndex;
	TScore Score;
	TAlphSize AlphSize;
	
	/* Creation de la position match */
	AlphSize = Alph_Size(AlphPtr);
	MatchPosPtr = Clone_MatchPos(DefaultMatchPosPtr, AlphSize);
	if (!MatchPosPtr) {
		/* Erreur allocation */
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	/* Boucle de lecture */
	AssPtr = PrfExtr_CurrentAss(PrfExtrPtr);
	while (AssPtr) {
		AssWordPtr = Ass_Word(AssPtr);
		if (!strcmp(PE_SYMB_STR, AssWordPtr)) {			
			/* C'est un symbole  */
			if (SymbRead) {
				/* Symbole deja lu */
				Free_MatchPos(MatchPosPtr);
				*ErrIndexPtr = PE_DBL_SYMB;
				return NULL;
			}
			/* Controle du type de la valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_STR) {
				/* Ce n'est pas une chaine */
				Free_MatchPos(MatchPosPtr);
				*ErrIndexPtr = PE_SYMB_EXP;
				return NULL;
			}
			/* Controle de la longueur de la chaine */
			if (strlen((char*)Val_Str(PrfExtr_CurrentVal(PrfExtrPtr))) != 1) {
				/* La chaine fait plus d'un caractere */
				Free_MatchPos(MatchPosPtr);
				*ErrIndexPtr = PE_SYMB_EXP;
				return NULL;
			}
			/* Affectation du symbole */
			MatchPos_PutSymb(MatchPosPtr,
			Str_CharNth(Val_Str(PrfExtr_CurrentVal(PrfExtrPtr)), 0));
			/* Prochaine valeur */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				Free_MatchPos(MatchPosPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
			/* Symbole lu */
			SymbRead = TRUE;
		}
		else if (!strcmp(PE_M_STR, AssWordPtr)) {
			/* Lecture d'un score match */
			if (MRead) {
				/* Score match deja lu */
				Free_MatchPos(MatchPosPtr);
				*ErrIndexPtr = PE_DBL_SCORE;
				return NULL;
			}
			ValNbr = Ass_ValNbr(AssPtr);
			/* Lecture des parametres */
			if (ValNbr == 1) {
				/* Controle du score */
				Score = Val_Score(PrfExtr_CurrentVal(PrfExtrPtr), ErrIndexPtr);
				if (*ErrIndexPtr != PE_NO_ERROR) {
					/* Il y a une erreur de lecture du score */
					Free_MatchPos(MatchPosPtr);
					/* Renvoi de l'erreur */
					return NULL;
				}
				/* Affectation */
				for (ValIndex = 0; ValIndex < AlphSize; ValIndex++) {
					ScoreVect_PutScore(MatchPos_M(MatchPosPtr), Score,
					(TAlphSize)ValIndex + 1);
				}
			}
			else if (ValNbr == AlphSize) {
				/* Lecture de tous les parametres */
				for (ValIndex = 0; ValIndex < AlphSize; ValIndex++) {
					Score = Val_Score(
					Ass_ValNth(AssPtr, ValIndex), ErrIndexPtr);
					if (*ErrIndexPtr != PE_NO_ERROR) {
						/* Il y a une erreur de lecture du score */
						Free_MatchPos(MatchPosPtr);
						/* Renvoi de l'erreur */
						return NULL;
					}
					ScoreVect_PutScore(MatchPos_M(MatchPosPtr), Score,
					(TAlphSize)ValIndex + 1);
				}
			}
			else {
				/* Le nombre de valeurs est incorrect */
				Free_MatchPos(MatchPosPtr);
				*ErrIndexPtr = PE_BAD_SCORE_NBR;
				return NULL;
			}
			/* Nombre de valeur deja controle */
			/* Score match lus */
			MRead = TRUE;
		}
		else if (!strcmp(PE_M0_STR, AssWordPtr)) {
			/* Lecture d'un score match pour lettre inconnue */
			if (M0Read) {
				/* Score deja lu */
				Free_MatchPos(MatchPosPtr);
				*ErrIndexPtr = PE_DBL_SCORE;
				return NULL;
			}
			/* Lecture du score */
			Score = Val_Score(PrfExtr_CurrentVal(PrfExtrPtr), ErrIndexPtr);
			if (*ErrIndexPtr != PE_NO_ERROR) {
				/* Il y a une erreur de lecture du score */
				Free_MatchPos(MatchPosPtr);
				/* Renvoi de l'erreur */
				return NULL;
			}
			ScoreVect_PutScore(MatchPos_M(MatchPosPtr), Score, 0);
			/* M0 lu */
			M0Read = TRUE;
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				Free_MatchPos(MatchPosPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
		}	
		else if (!strcmp(PE_D_STR, AssWordPtr)) {
			if (DRead) {
				/* Score deja lu */
				Free_MatchPos(MatchPosPtr);
				*ErrIndexPtr = PE_DBL_SCORE;
				return NULL;
			}
			/* Lecture du score */
			Score = Val_Score(PrfExtr_CurrentVal(PrfExtrPtr), ErrIndexPtr);
			if (*ErrIndexPtr != PE_NO_ERROR) {
				/* Il y a une erreur de lecture du score */
				Free_MatchPos(MatchPosPtr);
				/* Renvoi de l'erreur */
				return NULL;
			}
			MatchPos_PutD(MatchPosPtr, Score);
			/* D lu */
			DRead = TRUE;
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				Free_MatchPos(MatchPosPtr);
				*ErrIndexPtr = PE_ILL_VAL;
				return NULL;
			}
		}	
		else {
			/* Parametre match inconnu */
			Free_MatchPos(MatchPosPtr);
			*ErrIndexPtr = PE_ILL_WORD;
			return NULL;
		}
		AssPtr = PrfExtr_NextAss(PrfExtrPtr);
	}
	/* Il n'y a pas de parametres obligatoires */
	*ErrIndexPtr = PE_NO_ERROR;
	return MatchPosPtr;
}

/*--------------------------------------------------------------------------*/
/* Extraction de la position par defaut de la description courante			*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/*			| DefaultInsPosPtr			| Position d'insertion par defaut	*/
/*			| DefaultMatchPosPtr		| Position match par defaut			*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| PrfExtr_DefaultPos		| Succes							*/
/* Erreurs:	| PrfExtr_DefaultPos		| = FALSE =>						*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PE_DBL_SYMB				| Symbole deja declare				*/
/*			| PE_SYMB_EXP				| Symbole attendu					*/
/*			| PE_ILL_VAL				| Valeur illegale					*/
/*			| PE_DBL_SCORE				| Score deja declare				*/
/*			| PE_INT_EXP				| Entier attendu					*/
/*			| PE_BAD_SCORE_NBR			| Mauvais nombre de scores			*/
/*			| PE_ILL_WORD				| Mot illegal						*/
/*--------------------------------------------------------------------------*/
TBoolean PrfExtr_DefaultPos(TPrfExtrPtr PrfExtrPtr,
TInsPosPtr DefaultInsPosPtr, TMatchPosPtr DefaultMatchPosPtr,
TAlphPtr AlphPtr, TErrIndex *ErrIndexPtr)
{
	TBoolean InsSymbRead = FALSE;
	TBoolean MatchSymbRead = FALSE;
	TBoolean MRead = FALSE;
	TBoolean IRead = FALSE;
	TBoolean B0Read = FALSE;
	TBoolean B1Read = FALSE;
	TBoolean E0Read = FALSE;
	TBoolean E1Read = FALSE;
	TBoolean BMRead = FALSE;
	TBoolean BIRead = FALSE;
	TBoolean BDRead = FALSE;
	TBoolean BERead = FALSE;
	TBoolean MMRead = FALSE;
	TBoolean MIRead = FALSE;
	TBoolean MDRead = FALSE;
	TBoolean MERead = FALSE;
	TBoolean IMRead = FALSE;
	TBoolean IIRead = FALSE;
	TBoolean IDRead = FALSE;
	TBoolean IERead = FALSE;
	TBoolean DMRead = FALSE;
	TBoolean DIRead = FALSE;
	TBoolean DDRead = FALSE;
	TBoolean DERead = FALSE;
	TBoolean I0Read = FALSE;
	TBoolean M0Read = FALSE;
	TBoolean DRead = FALSE;
	TAssPtr AssPtr;
	TWordPtr AssWordPtr;
	TValPtr ValPtr;
	TValIndex ValNbr;
	TValIndex ValIndex;
	TScore Score;
	TAlphSize AlphSize;
	
	AlphSize = Alph_Size(AlphPtr);
	/* Boucle de lecture */
	AssPtr = PrfExtr_CurrentAss(PrfExtrPtr);
	while (AssPtr) {
		AssWordPtr = Ass_Word(AssPtr);
		if (!strcmp(PE_SYMB_I_STR, AssWordPtr)) {			
			/* C'est un symbole d'insertion */
			if (InsSymbRead) {
				/* Symbole deja lu */
				*ErrIndexPtr = PE_DBL_SYMB;
				return FALSE;
			}
			/* Controle du type de la valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_STR) {
				/* Ce n'est pas une chaine */
				*ErrIndexPtr = PE_SYMB_EXP;
				return FALSE;
			}
			/* Controle de la longueur de la chaine */
			if (strlen((char*)Val_Str(PrfExtr_CurrentVal(PrfExtrPtr))) != 1) {
				/* La chaine fait plus d'un caractere */
				*ErrIndexPtr = PE_SYMB_EXP;
				return FALSE;
			}
			/* Affectation du symbole */
			InsPos_PutSymb(DefaultInsPosPtr,
			Str_CharNth(Val_Str(PrfExtr_CurrentVal(PrfExtrPtr)), 0));
			/* Prochaine valeur */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				*ErrIndexPtr = PE_ILL_VAL;
				return FALSE;
			}
			/* Symbole d'insertion lu */
			InsSymbRead = TRUE;
		}
		else if (!strcmp(PE_SYMB_M_STR, AssWordPtr)) {
			/* C'est un symbole match */
			if (MatchSymbRead) {
				/* Symbole deja lu */
				*ErrIndexPtr = PE_DBL_SYMB;
				return FALSE;
			}
			/* Controle du type de la valeur */
			if (Val_Type(PrfExtr_CurrentVal(PrfExtrPtr)) != PFD_A_STR) {
				/* Ce n'est pas une chaine */
				*ErrIndexPtr = PE_SYMB_EXP;
				return FALSE;
			}
			/* Controle de la longueur de la chaine */
			if (strlen((char*)Val_Str(PrfExtr_CurrentVal(PrfExtrPtr))) != 1) {
				/* La chaine fait plus d'un caractere */
				*ErrIndexPtr = PE_SYMB_EXP;
				return FALSE;
			}
			/* Affectation du symbole */
			MatchPos_PutSymb(DefaultMatchPosPtr,
			Str_CharNth(Val_Str(PrfExtr_CurrentVal(PrfExtrPtr)), 0));
			/* Prochaine valeur */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				*ErrIndexPtr = PE_ILL_VAL;
				return FALSE;
			}
			/* Symbole match lu */
			MatchSymbRead = TRUE;
		}
		else if (!strcmp(PE_I_STR, AssWordPtr)) {
			/* C'est un score d'insertion */
			if (IRead) {
				/* Score d'insertion deja lu */
				*ErrIndexPtr = PE_DBL_SCORE;
				return FALSE;
			}
			ValNbr = Ass_ValNbr(AssPtr);
			/* Lecture des parametres */
			if (ValNbr == 1) {
				/* Controle du score */
				Score = Val_Score(PrfExtr_CurrentVal(PrfExtrPtr), ErrIndexPtr);
				if (*ErrIndexPtr != PE_NO_ERROR) {
					/* Il y a une erreur de lecture du score */
					/* Renvoi de l'erreur */
					return FALSE;
				}
				/* Affectation */
				for (ValIndex = 0; ValIndex < AlphSize; ValIndex++) {
					ScoreVect_PutScore(InsPos_I(DefaultInsPosPtr), Score,
					(TAlphSize)ValIndex + 1);
				}
			}
			else if (ValNbr == Alph_Size(AlphPtr)) {
				/* Lecture de tous les parametres */
				for (ValIndex = 0; ValIndex < AlphSize; ValIndex++) {
					Score = Val_Score(
					Ass_ValNth(AssPtr, ValIndex), ErrIndexPtr);
					if (*ErrIndexPtr != PE_NO_ERROR) {
						/* Il y a une erreur de lecture du score */
						/* Renvoi de l'erreur */
						return FALSE;
					}
					ScoreVect_PutScore(InsPos_I(DefaultInsPosPtr), Score,
					(TAlphSize)ValIndex + 1);
				}
			}
			else {
				/* Le nombre de valeurs est incorrect */
				*ErrIndexPtr = PE_BAD_SCORE_NBR;
				return FALSE;
			}
			/* Nombre de valeurs deja controle */
			/* Score d'insertion lu */
			IRead = TRUE;
		}
		else if (!strcmp(PE_M_STR, AssWordPtr)) {
			/* C'est un score match */
			if (MRead) {
				/* Score match deja lu */
				*ErrIndexPtr = PE_DBL_SCORE;
				return FALSE;
			}
			ValNbr = Ass_ValNbr(AssPtr);
			/* Lecture des parametres */
			if (ValNbr == 1) {
				/* Controle du score */
				Score = Val_Score(PrfExtr_CurrentVal(PrfExtrPtr), ErrIndexPtr);
				if (*ErrIndexPtr != PE_NO_ERROR) {
					/* Il y a une erreur de lecture du score */
					/* Renvoi de l'erreur */
					return FALSE;
				}
				/* Affectation */
				for (ValIndex = 0; ValIndex < Alph_Size(AlphPtr); ValIndex++) {
					ScoreVect_PutScore(MatchPos_M(DefaultMatchPosPtr), Score,
					(TAlphSize)ValIndex + 1);
				}
			}
			else if (ValNbr == Alph_Size(AlphPtr)) {
				/* Lecture de tous les parametres */
				for (ValIndex = 0; ValIndex < Alph_Size(AlphPtr); ValIndex++) {
					Score = Val_Score(
					Ass_ValNth(AssPtr, ValIndex), ErrIndexPtr);
					if (*ErrIndexPtr != PE_NO_ERROR) {
						/* Il y a une erreur de lecture du score */
						/* Renvoi de l'erreur */
						return FALSE;
					}
					ScoreVect_PutScore(MatchPos_M(DefaultMatchPosPtr), Score,
					(TAlphSize)ValIndex + 1);
				}
			}
			else {
				/* Le nombre de valeurs est incorrect */
				*ErrIndexPtr = PE_BAD_SCORE_NBR;
				return FALSE;
			}
			/* Nombre de valeur deja controle */
			/* Score match lus */
			MRead = TRUE;
		}
		/* Autres ass. que scores simples avant cette ligne ! */
		else {
			/* Traitement d'un score simple */
			Score = Val_Score(PrfExtr_CurrentVal(PrfExtrPtr), ErrIndexPtr);
			if (*ErrIndexPtr != PE_NO_ERROR) {
				/* Il y a une erreur de lecture du score */
				/* Renvoi de l'erreur */
				return FALSE;
			}
			/* Affectation */
			if (!strcmp(PE_B0_STR, AssWordPtr)) {
				if (B0Read) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutB0(DefaultInsPosPtr, Score);
				/* B0 lu */
				B0Read = TRUE;
			}
			else if (!strcmp(PE_B1_STR, AssWordPtr)) {
				if (B1Read) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutB1(DefaultInsPosPtr, Score);
				/* B1 lu */
				B1Read = TRUE;
			}
			else if (!strcmp(PE_E0_STR, AssWordPtr)) {
				if (E0Read) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutE0(DefaultInsPosPtr, Score);
				/* E0 lu */
				E0Read = TRUE;
			}
			else if (!strcmp(PE_E1_STR, AssWordPtr)) {
				if (E1Read) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutE1(DefaultInsPosPtr, Score);
				/* E1 lu */
				E1Read = TRUE;
			}
			else if (!strcmp(PE_BM_STR, AssWordPtr)) {
				if (BMRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutBM(DefaultInsPosPtr, Score);
				/* BM lu */
				BMRead = TRUE;
			}
			else if (!strcmp(PE_BI_STR, AssWordPtr)) {
				if (BIRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutBI(DefaultInsPosPtr, Score);
				/* BI lu */
				BIRead = TRUE;
			}
			else if (!strcmp(PE_BD_STR, AssWordPtr)) {
				if (BDRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutBD(DefaultInsPosPtr, Score);
				/* BD lu */
				BDRead = TRUE;
			}
			else if (!strcmp(PE_BE_STR, AssWordPtr)) {
				if (BERead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutBE(DefaultInsPosPtr, Score);
				/* BE lu */
				BERead = TRUE;
			}
			else if (!strcmp(PE_MM_STR, AssWordPtr)) {
				if (MMRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutMM(DefaultInsPosPtr, Score);
				/* MM lu */
				MMRead = TRUE;
			}
			else if (!strcmp(PE_MI_STR, AssWordPtr)) {
				if (MIRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutMI(DefaultInsPosPtr, Score);
				/* MI lu */
				MIRead = TRUE;
			}
			else if (!strcmp(PE_MD_STR, AssWordPtr)) {
				if (MDRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutMD(DefaultInsPosPtr, Score);
				/* MD lu */
				MDRead = TRUE;
			}
			else if (!strcmp(PE_ME_STR, AssWordPtr)) {
				if (MERead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutME(DefaultInsPosPtr, Score);
				/* ME lu */
				MERead = TRUE;
			}
			else if (!strcmp(PE_IM_STR, AssWordPtr)) {
				if (IMRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutIM(DefaultInsPosPtr, Score);
				/* IM lu */
				IMRead = TRUE;
			}
			else if (!strcmp(PE_II_STR, AssWordPtr)) {
				if (IIRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutII(DefaultInsPosPtr, Score);
				/* II lu */
				IIRead = TRUE;
			}
			else if (!strcmp(PE_ID_STR, AssWordPtr)) {
				if (IDRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutID(DefaultInsPosPtr, Score);
				/* ID lu */
				IDRead = TRUE;
			}
			else if (!strcmp(PE_IE_STR, AssWordPtr)) {
				if (IERead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutIE(DefaultInsPosPtr, Score);
				/* IE lu */
				IERead = TRUE;
			}
			else if (!strcmp(PE_DM_STR, AssWordPtr)) {
				if (DMRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutDM(DefaultInsPosPtr, Score);
				/* DM lu */
				DMRead = TRUE;
			}
			else if (!strcmp(PE_DI_STR, AssWordPtr)) {
				if (DIRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutDI(DefaultInsPosPtr, Score);
				/* DI lu */
				DIRead = TRUE;
			}
			else if (!strcmp(PE_DD_STR, AssWordPtr)) {
				if (DDRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutDD(DefaultInsPosPtr, Score);
				/* DD lu */
				DDRead = TRUE;
			}
			else if (!strcmp(PE_DE_STR, AssWordPtr)) {
				if (DERead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				InsPos_PutDE(DefaultInsPosPtr, Score);
				/* DE lu */
				DERead = TRUE;
			}
			else if (!strcmp(PE_I0_STR, AssWordPtr)) {
				if (I0Read) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				ScoreVect_PutScore(InsPos_I(DefaultInsPosPtr), Score, 0);
				/* I0 lu */
				I0Read = TRUE;
			}
			else if (!strcmp(PE_M0_STR, AssWordPtr)) {
				if (M0Read) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				ScoreVect_PutScore(MatchPos_M(DefaultMatchPosPtr), Score, 0);
				/* M0 lu */
				M0Read = TRUE;
			}
			else if (!strcmp(PE_D_STR, AssWordPtr)) {
				if (DRead) {
					*ErrIndexPtr = PE_DBL_SCORE;
					return FALSE;
				}
				MatchPos_PutD(DefaultMatchPosPtr, Score);
				/* D lu */
				DRead = TRUE;
			}
			else {
				/* Parametre de score */
				*ErrIndexPtr = PE_ILL_WORD;
				return FALSE;
			}
			/* Valeur suivante */
			ValPtr = PrfExtr_NextVal(PrfExtrPtr);
			if (ValPtr) {
				/* Il y a une valeur de trop */
				*ErrIndexPtr = PE_ILL_VAL;
				return FALSE;
			}
		}
		AssPtr = PrfExtr_NextAss(PrfExtrPtr);
	}
	/* Aucune assignation obligatoire */	
	*ErrIndexPtr = PE_NO_ERROR;
	return TRUE;
}

/*--------------------------------------------------------------------------*/
/* Extraction de la matrice du profil										*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/*			| AlphPtr					| Alphabet							*/
/* Sortie:	| PrfExtr_PrfMatrix			| Matrice du profil					*/
/* Erreur:	| PrfExtr_PrfMatrix			| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PE_MEM_ERR				| Erreur allocation memoire			*/
/*			| PE_DBL_SYMB				| Symbole deja declare				*/
/*			| PE_SYMB_EXP				| Symbole attendu					*/
/*			| PE_ILL_VAL				| Valeur illegale					*/
/*			| PE_DBL_SCORE				| Score deja declare				*/
/*			| PE_INT_EXP				| Entier attendu					*/
/*			| PE_BAD_SCORE_NBR			| Mauvais nombre de scores			*/
/*			| PE_ILL_WORD				| Mot illegal						*/
/*			| PE_PRF_MATR_OVF			| Trop de positions					*/
/*--------------------------------------------------------------------------*/
TPrfMatrixPtr PrfExtr_PrfMatrix(TPrfExtrPtr PrfExtrPtr, TAlphPtr AlphPtr,
TErrIndex *ErrIndexPtr)
{
	typedef unsigned char TState; /* Type de l'etat courant	*/
	
	TScoreVect I;
	TScoreVect M;
	TInsPosPtr DefaultInsPosPtr;
	TMatchPosPtr DefaultMatchPosPtr;
	TInsPosPtr InsPosPtr;
	TMatchPosPtr MatchPosPtr;
	TInsPosPtr ReadInsPosPtr;
	TMatchPosPtr ReadMatchPosPtr;
	TBoolean ReadResult;
	TState State;
	TPrfMatrixPtr PrfMatrixPtr;
	TDescPtr DescPtr;
	
	/* Construction des positions match et d'insertion par defaut */
	/* Position d'insertion */
	/* Construction du vecteur de scores d'insertion */
	I = I_ScoreVect(Alph_Size(AlphPtr));
	if (!I) {
		/* Erreur d'allocation */
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	/* Construction de la position */
	DefaultInsPosPtr = I_InsPos(I);
	if (!DefaultInsPosPtr) {
		/* Erreur d'allocation */
		Free_ScoreVect(I);
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	/* Position match */
	/* Construction du vecteur de scores match */
	M = I_ScoreVect(Alph_Size(AlphPtr));
	if (!M) {
		/* Erreur d'allocation */
		Free_InsPos(DefaultInsPosPtr);
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	/* Construction de la position */	
	DefaultMatchPosPtr = I_MatchPos(M);
	if (!DefaultMatchPosPtr) {
		/* Erreur d'allocation */
		Free_InsPos(DefaultInsPosPtr);
		Free_ScoreVect(M);
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}

	/* Affectation des valeurs par defaut */
	/* Position d'insertion */
	InsPos_B0(DefaultInsPosPtr) = 0;
	InsPos_B1(DefaultInsPosPtr) = 0;
	InsPos_E0(DefaultInsPosPtr) = 0;
	InsPos_E1(DefaultInsPosPtr) = 0;
	InsPos_BM(DefaultInsPosPtr) = 0;
	InsPos_BI(DefaultInsPosPtr) = PD_INFINITE;
	InsPos_BD(DefaultInsPosPtr) = PD_INFINITE;
	InsPos_BE(DefaultInsPosPtr) = PD_INFINITE;
	InsPos_MM(DefaultInsPosPtr) = 0;
	InsPos_MI(DefaultInsPosPtr) = PD_INFINITE;
	InsPos_MD(DefaultInsPosPtr) = PD_INFINITE;
	InsPos_ME(DefaultInsPosPtr) = 0;
	InsPos_IM(DefaultInsPosPtr) = PD_INFINITE;
	InsPos_II(DefaultInsPosPtr) = 0;
	InsPos_ID(DefaultInsPosPtr) = PD_INFINITE;
	InsPos_IE(DefaultInsPosPtr) = PD_INFINITE;
	InsPos_DM(DefaultInsPosPtr) = PD_INFINITE;
	InsPos_DI(DefaultInsPosPtr) = PD_INFINITE;
	InsPos_DD(DefaultInsPosPtr) = 0;
	InsPos_DE(DefaultInsPosPtr) = PD_INFINITE;
	/* Les scores d'insertion sont deja a 0 */
	InsPos_Symb(DefaultInsPosPtr) = '-';

	/* Position match */
	/* Les score match sont deja a 0 */
	MatchPos_D(DefaultMatchPosPtr) = 0;
	MatchPos_Symb(DefaultMatchPosPtr) = 'X';

	/* Construction de la matrice */
	PrfMatrixPtr = I_PrfMatrix(PE_MAX_POS_NBR);
	if (!PrfMatrixPtr) {
		/* Erreur d'allocation */
		Free_InsPos(DefaultInsPosPtr);
		Free_MatchPos(DefaultMatchPosPtr);
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}

	/* Lecture de la matrice */
	State = PE_WAIT_I;
	DescPtr = PrfExtr_CurrentDesc(PrfExtrPtr);
	while (DescPtr) {
		if (!strcmp(PE_DFT_STR, Desc_Keyword(DescPtr))) {
			/* C'est une description de parametres par defaut */
			ReadResult = PrfExtr_DefaultPos(PrfExtrPtr, DefaultInsPosPtr,
			DefaultMatchPosPtr, AlphPtr, ErrIndexPtr);
			if (!ReadResult) {
				/* Une erreur s'est produite */
				Free_InsPos(DefaultInsPosPtr);
				Free_MatchPos(DefaultMatchPosPtr);
				Free_PrfMatrix(PrfMatrixPtr);
				if (State == PE_WAIT_M) {
					/* Une position match a ete lue */
					Free_InsPos(InsPosPtr);
				}
				/* Renvoi de l'erreur */
				return NULL;
			}
		}
		else if (!strcmp(PE_I_STR, Desc_Keyword(DescPtr))) {
			/* C'est une description de position d'insertion */
			ReadInsPosPtr = PrfExtr_InsPos(PrfExtrPtr, DefaultInsPosPtr,
			AlphPtr, ErrIndexPtr);
			if (!ReadInsPosPtr) {
				/* Une erreur s'est produite */
				Free_InsPos(DefaultInsPosPtr);
				Free_MatchPos(DefaultMatchPosPtr);
				Free_PrfMatrix(PrfMatrixPtr);
				if (State == PE_WAIT_M) {
					/* Une position match a ete lue */
					Free_InsPos(InsPosPtr);
				}
				/* Renvoi de l'erreur */
				return NULL;
			}
			/* Position d'insertion lue */
			switch (State) {
				case PE_WAIT_I:
					/* Position d'insertion attendue */
					/* Attente de la position match */
					InsPosPtr = ReadInsPosPtr;
					State = PE_WAIT_M;
					break;
				case PE_WAIT_M:
					/* Position match attendue */
					/* Creation de la position match par defaut */
					MatchPosPtr = Clone_MatchPos(DefaultMatchPosPtr,
					Alph_Size(AlphPtr));
					if (!MatchPosPtr) {
						/* Erreur d'allocation */
						Free_InsPos(DefaultInsPosPtr);
						Free_MatchPos(DefaultMatchPosPtr);
						Free_PrfMatrix(PrfMatrixPtr);
						Free_InsPos(InsPosPtr);
						*ErrIndexPtr = PE_MEM_ERR;
						return NULL;
					}
					/* Ajout des positions dans la matrice */
					if (PrfMatrix_Full(PrfMatrixPtr)) {
						/* Matrice pleine */
						Free_InsPos(DefaultInsPosPtr);
						Free_MatchPos(DefaultMatchPosPtr);
						Free_PrfMatrix(PrfMatrixPtr);
						Free_InsPos(InsPosPtr);
						Free_MatchPos(MatchPosPtr);
						*ErrIndexPtr = PE_PRF_MATR_OVF;
						return NULL;
					}
					PrfMatrix_AddPos(PrfMatrixPtr, InsPosPtr, MatchPosPtr);
					InsPosPtr = ReadInsPosPtr;
					break;
			}
		}
		else if (!strcmp(PE_M_STR, Desc_Keyword(DescPtr))) {
			/* C'est une description de position match */
			ReadMatchPosPtr = PrfExtr_MatchPos(PrfExtrPtr,
			DefaultMatchPosPtr, AlphPtr, ErrIndexPtr);
			if (!ReadMatchPosPtr) {
				/* Une erreur s'est produite */
				Free_InsPos(DefaultInsPosPtr);
				Free_MatchPos(DefaultMatchPosPtr);
				Free_PrfMatrix(PrfMatrixPtr);
				if (State == PE_WAIT_M) {
					Free_InsPos(InsPosPtr);
				}
				/* Renvoi de l'erreur */
				return NULL;
			}
			/* Position match lue */
			switch (State) {
				case PE_WAIT_I:
					/* Position d'insertion attendue */
					/* Creation de la position d'insertion par defaut */
					InsPosPtr = Clone_InsPos(DefaultInsPosPtr,
					Alph_Size(AlphPtr));
					if (!InsPosPtr) {
						/* Erreur d'allocation */
						Free_InsPos(DefaultInsPosPtr);
						Free_MatchPos(DefaultMatchPosPtr);
						Free_PrfMatrix(PrfMatrixPtr);
						*ErrIndexPtr = PE_MEM_ERR;
						return NULL;
					}
					MatchPosPtr = ReadMatchPosPtr;
					/* Ajout des positions dans la matrice */
					if (PrfMatrix_Full(PrfMatrixPtr)) {
						/* Matrice pleine */
						Free_InsPos(DefaultInsPosPtr);
						Free_MatchPos(DefaultMatchPosPtr);
						Free_PrfMatrix(PrfMatrixPtr);
						Free_InsPos(InsPosPtr);
						Free_MatchPos(MatchPosPtr);
						*ErrIndexPtr = PE_PRF_MATR_OVF;
						return NULL;
					}
					PrfMatrix_AddPos(PrfMatrixPtr, InsPosPtr, MatchPosPtr);
					break;
				case PE_WAIT_M:
					/* Position match attendue */
					MatchPosPtr = ReadMatchPosPtr;
					/* Ajout des positions dans la matrice */
					if (PrfMatrix_Full(PrfMatrixPtr)) {
						/* Matrice pleine */
						Free_InsPos(DefaultInsPosPtr);
						Free_MatchPos(DefaultMatchPosPtr);
						Free_PrfMatrix(PrfMatrixPtr);
						Free_InsPos(InsPosPtr);
						Free_MatchPos(MatchPosPtr);
						*ErrIndexPtr = PE_PRF_MATR_OVF;
						return NULL;
					}
					PrfMatrix_AddPos(PrfMatrixPtr, InsPosPtr, MatchPosPtr);
					/* Attente de la position d'insertion */
					State = PE_WAIT_I;
					break;
			}
		}
		DescPtr = PrfExtr_NextDesc(PrfExtrPtr);
	}
	/* Ajout de la derniere position d'insertion */
	if (State == PE_WAIT_I) {
		/* Creation d'une position d'insertion */
		InsPosPtr = Clone_InsPos(DefaultInsPosPtr, Alph_Size(AlphPtr));
		if (!InsPosPtr) {
			/* Erreur d'allocation */
			Free_InsPos(DefaultInsPosPtr);
			Free_MatchPos(DefaultMatchPosPtr);
			Free_PrfMatrix(PrfMatrixPtr);
			*ErrIndexPtr = PE_MEM_ERR;
			return NULL;
		}
	}
	PrfMatrix_AddLastPos(PrfMatrixPtr, InsPosPtr)
	Free_InsPos(DefaultInsPosPtr);
	Free_MatchPos(DefaultMatchPosPtr);
	/*Resize_PrfMatrix(PrfMatrixPtr);*/
	*ErrIndexPtr = PE_NO_ERROR;
	return PrfMatrixPtr;
}

/*--------------------------------------------------------------------------*/
/* Extraction des donnees du profil											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_PrfData			| Donnees du profil					*/
/* Erreur	| PrfExtr_PrfData			| = NULL =>							*/
/*			| ErrIndex					| Index d'erreur =					*/
/*			| PE_MEM_ERR				| Erreur allocation memoire			*/
/*			| PE_GEN_SPEC_EXP			| Specifications generales att.		*/
/*			| PE_DBL_ALPH				| Alphabet deja defini				*/
/*			| PE_STR_EXP				| Chaine attendue					*/
/*			| PE_ILL_VAL				| Valeur illegale					*/
/*			| PE_DBL_LENGTH				| Longueur deja declaree			*/
/*			| PE_CARD_EXP				| Entier positif attendu			*/
/*			| PE_DBL_TOPO				| Topologie deja declaree			*/
/*			| PE_WORD_EXP				| Mot attendu						*/
/*			| PE_ILL_WORD				| Mot illegale						*/
/*			| PE_ILL_ASS				| Assignation illegale				*/
/*			| PE_ALPH_EXP				| Alphabet attendu					*/
/*			| PE_DISJ_EXP				| Exclusion attendue				*/
/*			| PE_DBL_DEF				| Definition deja declaree			*/
/*			| PE_PAR_EXP				| Parametre attendu					*/
/*			| PE_DEF_EXP				| Definition attendue				*/
/*			| PE_DBL_FCT				| Fonction deja declaree			*/
/*			| PE_NBR_EXP				| Nombre attendu					*/
/*			| PE_DBL_MODE				| Mode deja defini					*/
/*			| PE_DBL_PRTY2				| Priorite deja declaree			*/
/*			| PE_DBL_TEXT				| Texte deja declare				*/
/*			| PE_FCT_EXP				| Fonction de norm. attendue		*/
/*			| PE_NORM_MODE_ILL			| Mode de normalisation illegal		*/
/*			| PE_NORM_PRTY_ILL			| Priorite de normalisation ill.	*/
/*			| PE_DBL_NORM_MODE			| Mode de normalisation a double	*/
/*			| PE_NORM_MODE_OVF			| Trop de modes de normalisation	*/
/*			| PE_NORM_MODE_MISS			| Il manque un mode de norm.		*/
/*			| PE_OUT_PRTY				| Priorite hors rangee				*/
/*			| PE_DBL_PRTY				| Priorite deja utilisee			*/
/*			| PE_NORM_MISS_PRTY			| Priorite manquante				*/
/*			| PE_CUTOFF_EXP				| Valeur de coupure manquante		*/
/*			| PE_DBL_SCORE				| Score deja declare				*/
/*			| PE_INT_EXP				| Entier attendu					*/
/*			| PE_DBL_LEVEL2				| Niveau deja declare				*/
/*			| PE_POS_EXP				| Entier positif attendu			*/
/*			| PE_DBL_NSCORE				| Scores norm. deja declares		*/
/*			| PE_NSCORE_MODE_EXP		| Mode du score norm. attendu		*/
/*			| PE_NSCORE_NBR_INC			| Nombre de scores incorrect		*/
/*			| PE_SCORE_EXP				| Score attendu						*/
/*			| PE_DBL_LEVEL				| Niveau de cut-off a double		*/
/*			| PE_LEVEL_OVF				| Trop de niveaux					*/
/*			| PE_LEVEL_MISS				| Niveau de cut-off manquant		*/
/*			| PE_DBL_SYMB				| Symbole deja declare				*/
/*			| PE_SYMB_EXP				| Symbole attendu					*/
/*			| PE_BAD_SCORE_NBR			| Mauvais nombre de scores			*/
/*			| PE_PRF_MATR_OVF			| Trop de positions					*/
/*--------------------------------------------------------------------------*/
TPrfDataPtr PrfExtr_PrfData(TPrfExtrPtr PrfExtrPtr, TErrIndex *ErrIndexPtr)
{
	TId Id;
	TNbrAc NbrAc;
	TDe De;
	TGenSpecPtr GenSpecPtr;
	TDisjointPtr DisjointPtr;
	TNormListPtr NormListPtr;
	TCutOffListPtr CutOffListPtr;
	TPrfMatrixPtr PrfMatrixPtr;
	TPrfDataPtr PrfDataPtr;
	TDescPtr DescPtr;
	TCutOffIndex CutOffIndex;
	TCutOffPtr CutOffPtr;
	TNScoreIndex NScoreIndex;
	TNScoreListPtr NScoreListPtr;
	TPosIndex StartMatchPos;
	TPosIndex EndMatchPos;

	/* Extraction de l'identificateur */	
	Id = PrfExtr_Id(PrfExtrPtr);
	if (!Id) {
		/* Erreur d'allocation */
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	/* Extraction de la description */
	if (PrfFileData_De(PrfExtr_PrfFileData(PrfExtrPtr))) {
		De = PrfExtr_De(PrfExtrPtr);
		if (!De) {
			/* Erreur d'allocation */
			*ErrIndexPtr = PE_MEM_ERR;
			Free_Id(Id);
			return NULL;
		}
	}
	else {
		De = NULL;
	}
	/* Extraction du nombre Prosite */
	NbrAc = PrfExtr_NbrAc(PrfExtrPtr);
	if (!NbrAc) {
		/* Erreur d'allocation */
		*ErrIndexPtr = PE_MEM_ERR;
		Free_Id(Id);
		if (De) Free_De(De);
		return NULL;		
	}
	/* Extraction des specifications generales */
	GenSpecPtr = PrfExtr_GenSpec(PrfExtrPtr, ErrIndexPtr);
	if (!GenSpecPtr) {
		/* Une erreur de lecture est survenue */
		/* Renvoi de l'erreur */
		Free_Id(Id);
		if (De) Free_De(De);
		Free_NbrAc(NbrAc);
		return NULL;
	}
	/* Description suivante */
	DescPtr = PrfExtr_NextDesc(PrfExtrPtr);
	/* Extraction de l'exclusion */
	DisjointPtr = PrfExtr_Disjoint(PrfExtrPtr, ErrIndexPtr);
	if (!DisjointPtr) {
		/* Une erreur de lecture est survenue */
		Free_Id(Id);
		if (De) Free_De(De);
		Free_NbrAc(NbrAc);
		Free_GenSpec(GenSpecPtr);
		/* Renvoi de l'erreur */
		return NULL;
	}
	/* Description suivante */
	DescPtr = PrfExtr_NextDesc(PrfExtrPtr);
	/* Extraction de la liste des normalisations */
	NormListPtr = PrfExtr_NormList(PrfExtrPtr, ErrIndexPtr);
	if (!NormListPtr) {
		/* Une erreur de lecture est survenue */
		Free_Id(Id);
		if (De) Free_De(De);
		Free_NbrAc(NbrAc);
		Free_GenSpec(GenSpecPtr);
		Free_Disjoint(DisjointPtr);
		/* Renvoi de l'erreur */
		return NULL;
	}
	/* Extraction de la liste des valeurs de coupure */
	CutOffListPtr = PrfExtr_CutOffList(PrfExtrPtr, ErrIndexPtr);
	if (!CutOffListPtr) {
		/* Une erreur de lecture est survenue */
		Free_Id(Id);
		Free_De(De);
		Free_NbrAc(NbrAc);
		Free_GenSpec(GenSpecPtr);
		Free_Disjoint(DisjointPtr);
		Free_NormList(NormListPtr);
		/* Renvoi de l'erreur */
		return NULL;
	}
	/* Extraction de la matrice de profil */
	PrfMatrixPtr = PrfExtr_PrfMatrix(PrfExtrPtr, GenSpec_Alph(GenSpecPtr),
	ErrIndexPtr);
	if (!PrfMatrixPtr) {
		/* Une erreur de lecture est survenue */
		Free_Id(Id);
		if (De) Free_De(De);
		Free_NbrAc(NbrAc);
		Free_GenSpec(GenSpecPtr);
		Free_Disjoint(DisjointPtr);
		Free_NormList(NormListPtr);
		Free_CutOffList(CutOffListPtr);
		/* Renvoi de l'erreur */
		return NULL;
	}
	
	if (GenSpec_PosNbr(GenSpecPtr) != 0) {
		if (GenSpec_PosNbr(GenSpecPtr) != PrfMatrix_PosNbr(PrfMatrixPtr)) {
			/* Longeur lue et longueur reelles differentes */
			Free_Id(Id);
			if (De) Free_De(De);
			Free_NbrAc(NbrAc);
			Free_GenSpec(GenSpecPtr);
			Free_Disjoint(DisjointPtr);
			Free_NormList(NormListPtr);
			Free_CutOffList(CutOffListPtr);
			Free_PrfMatrix(PrfMatrixPtr);
			*ErrIndexPtr = PE_BAD_PRF_LENGTH;
			return NULL;
		}
	}
	else {
		GenSpec_PutPosNbr(GenSpecPtr, PrfMatrix_PosNbr(PrfMatrixPtr));
	}
	
	/* Verification des modes dans les cut-off */
	
	/* Parcours des valeurs de coupure */
	for (CutOffIndex = 0; CutOffIndex < CutOffList_CutOffNbr(CutOffListPtr);
	CutOffIndex++) {
		CutOffPtr = CutOffList_CutOffNth(CutOffListPtr, CutOffIndex);
		/* Parcours des scores normalises */
		if (!(NScoreListPtr = CutOff_NScoreList(CutOffPtr))) {
			/* Pas de scores normalise */
			/* Prochaine valeur de coupure */
			continue;
		}
		for (NScoreIndex = 0; NScoreIndex <
		NScoreList_NScoreNbr(NScoreListPtr); NScoreIndex++) {
			if (NScoreList_Mode(NScoreListPtr, NScoreIndex) >
			NormList_NormNbr(NormListPtr)) {
				/* Mode inexistant */
				Free_Id(Id);
				if (De) Free_De(De);
				Free_NbrAc(NbrAc);
				Free_GenSpec(GenSpecPtr);
				Free_Disjoint(DisjointPtr);
				Free_NormList(NormListPtr);
				Free_CutOffList(CutOffListPtr);
				Free_PrfMatrix(PrfMatrixPtr);
				*ErrIndexPtr = PE_OUT_MODE;
				return NULL;
			}
		}
	}
	
	/* Verification de la coherence des parametres d'exclusion */
	if (Disjoint_Def(DisjointPtr) == PD_PROTECT) {
		/* L'exclusion est definie par region protegee */
		StartMatchPos = DisjointParList_ParNth(
		Disjoint_ParList(DisjointPtr), 1);
		EndMatchPos = DisjointParList_ParNth(
		Disjoint_ParList(DisjointPtr), 2);
		if (StartMatchPos > EndMatchPos) {
			/* Region prot. mal definie */
			Free_Id(Id);
			if (De) Free_De(De);
			Free_NbrAc(NbrAc);
			Free_GenSpec(GenSpecPtr);
			Free_Disjoint(DisjointPtr);
			Free_NormList(NormListPtr);
			Free_CutOffList(CutOffListPtr);
			Free_PrfMatrix(PrfMatrixPtr);
			*ErrIndexPtr = PE_BAD_PROT_RGN;
			return NULL;
		}
		if  (EndMatchPos > GenSpec_PosNbr(GenSpecPtr)) {
			/* Region prot. hors profil */
			Free_Id(Id);
			if (De) Free_De(De);
			Free_NbrAc(NbrAc);
			Free_GenSpec(GenSpecPtr);
			Free_Disjoint(DisjointPtr);
			Free_NormList(NormListPtr);
			Free_CutOffList(CutOffListPtr);
			Free_PrfMatrix(PrfMatrixPtr);
			*ErrIndexPtr = PE_OUT_PROT_RGN;
			return NULL;
		}
	}

	PrfDataPtr = I_PrfData(Id, De, NbrAc, GenSpecPtr, DisjointPtr,
	NormListPtr, CutOffListPtr, PrfMatrixPtr);
	if (!PrfDataPtr) {
		/* Erreur d'allocation */
		Free_Id(Id);
		if (De) Free_De(De);
		Free_NbrAc(NbrAc);
		Free_GenSpec(GenSpecPtr);
		Free_Disjoint(DisjointPtr);
		Free_NormList(NormListPtr);
		Free_CutOffList(CutOffListPtr);
		Free_PrfMatrix(PrfMatrixPtr);
		*ErrIndexPtr = PE_MEM_ERR;
		return NULL;
	}
	return PrfDataPtr;
}
