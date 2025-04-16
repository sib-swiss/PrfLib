/****************************************************************************/
/*																			*/
/*	But: definition des routines d'extraction des donnees d'un profil		*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	TValPtr								| 	Val_Score						*/
/*--------------------------------------------------------------------------*/
/*	TPrfExtrPtr							|	I_PrfExtr						*/
/*										|	Free_PrfExtr					*/
/*										|	PrfExtr_Prf						*/
/*										|	PrfExtr_PrfFileData				*/
/*										|	PrfExtr_CurrentDesc				*/
/*										|	PrfExtr_CurrentAss				*/
/*										|	PrfExtr_CurrentVal				*/
/*										|	PrfExtr_DescNth					*/
/*										|	PrfExtr_AssNth					*/
/*										|	PrfExtr_ValNth					*/
/*										|	PrfExtr_Id						*/
/*										|	PrfExtr_NbrAc					*/
/*										|	PrfExtr_NextDesc				*/
/*										|	PrfExtr_NextAss					*/
/*										|	PrfExtr_NextVal					*/
/*										|	PfrExtr_GenSpec					*/
/*										|	PfrExtr_Disjoint				*/
/*										|	PrfExtr_Norm					*/
/*										|	PrfExtr_NormList				*/
/*										|	PrfExtr_CutOff					*/
/*										|	PrfExtr_CutOffList				*/
/*										|	PrfExtr_InsPos					*/
/*										|	PrfExtr_MatchPos				*/
/*										|	PrfExtr_DefaultPos				*/
/*										|	PrfExtr_PrfMatrix				*/
/*										|	PrfExtr_PrfData					*/
/****************************************************************************/

#ifndef _PRFEXTR_
#define _PRFEXTR_

#include "error.h"
#include "PrfData.h"
#include "PrfFileData.h"

/*****************************/
/* DEFINITION DES CONSTANTES */
/*****************************/

/*================*/
/* Index d'erreur */
/*================*/

#define PE_NO_ERROR			0				/* Pas d'erreur				*/
#define PE_MEM_ERR			1				/* Allocation memoire		*/
#define PE_OUT_PRTY			PD_OUT_PRTY
#define PE_DBL_PRTY			PD_DBL_PRTY
#define PE_NORM_PRTY_MISS	PD_PRTY_MISS
#define PE_DBL_LEVEL		PD_DBL_LEVEL
#define PE_LEVEL_MISS		PD_LEVEL_MISS
#define PE_ZERO_LEVEL_MISS	PD_ZERO_LEVEL_MISS
#define PE_GEN_SPEC_EXP		8	/* Specifications generales attendues	*/
#define PE_ALPH_EXP			9	/* Alphabet attendu						*/
#define PE_STR_EXP			10	/* Chaine attendue						*/
#define PE_ILL_VAL			11	/* Valeur illegale						*/
#define PE_POS_EXP			12	/* Entier positif attendu				*/
#define PE_ILL_ASS			13	/* Assignation illegale					*/
#define PE_WORD_EXP			14	/* Mot attendu							*/
#define PE_ILL_WORD			15	/* Mot illegal							*/
#define PE_DISJ_EXP			16	/* Exclusion attendue					*/
#define PE_DEF_EXP			17	/* Definition de l'exclusion attendue	*/
#define PE_PAR_EXP			18	/* Parametre attendu					*/
#define PE_NBR_EXP			19	/* Nombre attendu						*/
#define PE_NORM_EXP			20	/* Normalisation attendue				*/
#define PE_FCT_EXP			21	/* Fonction de normalisation attendue	*/
#define PE_CARD_EXP			22	/* Cardinal attendu						*/
#define PE_DBL_NORM_MODE	23	/* Mode deja existant					*/
#define PE_NORM_MODE_ILL	24	/* Mode illegale						*/
#define PE_NORM_PRTY_ILL	25	/* Priorite illegale					*/
#define PE_NORM_MODE_OVF	26	/* Mode de normalisation trop grand		*/
#define PE_NORM_MODE_MISS	27	/* Mode normalisation manquant			*/
#define PE_CUTOFF_EXP		28	/* Valeur de coupure attendue			*/
#define PE_SCORE_EXP		29	/* Score attendue						*/
#define PE_INT_EXP			30	/* Entier attendu						*/
#define PE_NSCORE_MODE_EXP	31	/* Mode attendu							*/
#define PE_NSCORE_NBR_INC	32	/* Inc. entre le nbr de mode et de sco.	*/
#define PE_LEVEL_OVF		33	/* Niveau trop grand					*/
#define PE_SYMB_EXP			34	/* Symbole attendu						*/
#define PE_BAD_SCORE_NBR	35	/* Mauvais nombre de parametres			*/
#define PE_PRF_MATR_OVF		36	/* Trop de positions					*/
#define PE_TEXT_EXP			37	/* Texte attendu						*/
#define PE_DBL_ALPH			38	/* Alphabet deja defini					*/
#define PE_DBL_TOPO			39	/* Topologie deja definie				*/
#define PE_DBL_LENGTH		40	/* Longueur deja definie				*/
#define PE_DBL_DEF			41	/* Type d'exclusion deja defini			*/
#define PE_DBL_FCT			42	/* Fonction de norm. deja definie		*/
#define PE_DBL_MODE			43	/* Mode de norm. deja lu				*/
#define PE_DBL_TEXT			44	/* Texte deja lu						*/
#define PE_DBL_PRTY2		45	/* Priorite deja lue					*/
#define PE_DBL_SCORE		46	/* Score deja lu						*/
#define PE_DBL_LEVEL2		47	/* Niveau de la val. de coupure deja lu	*/
#define PE_DBL_NSCORE		48	/* Scores normalises deja lus 			*/
#define PE_DBL_SYMB			49	/* Symbole deja lu						*/
#define PE_BAD_PRF_LENGTH	50	/* Mauvaise longueur de profil			*/
#define PE_OUT_MODE			51	/* Mode hors rangee						*/
#define PE_BAD_PROT_RGN		52	/* Region protegee mal definie			*/
#define PE_OUT_PROT_RGN		53	/* Region protegee hors profil			*/

/**************************/
/* DEFINITION DES DONNEES */
/**************************/

/*======================================*/
/* Structure d'une extraction de profil */
/*======================================*/

typedef struct TPrfExtr {
	TPrfFileDataPtr PrfFileDataPtr;	/* Donnees de profil traitee				*/
	TPrfPtr PrfPtr;					/* Profil traite							*/
	TDescPtr CurrentDescPtr;		/* Description courante						*/
	TAssPtr CurrentAssPtr;			/* Assignation courante						*/
	TValPtr CurrentValPtr;			/* Valeur courante							*/
	TDescIndex DescNth;				/* Index de la desc. courante a partir de 1	*/
	TAssIndex AssNth;				/* Index de l'ass. courante a partir de 1	*/
	TValIndex ValNth;				/* Index de la val. courante a partir de 1	*/
} TPrfExtr;
typedef TPrfExtr *TPrfExtrPtr;

/***************************/
/* DEFINITION DES ROUTINES */
/***************************/

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
TPrfExtrPtr I_PrfExtr(TPrfFileDataPtr PrfFileDataPtr);

/*--------------------------------------------------------------------------*/
/* Destruction des donnees d'extractions d'un profil						*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| -							| -									*/
/* Erreur:	| -							| -									*/
/*--------------------------------------------------------------------------*/
void Free_PrfExtr(TPrfExtrPtr PrfExtrPtr);

/*------------*/
/* Selecteurs */
/*------------*/

/*--------------------------------------------------------------------------*/
/* Macro retournant le profil traite										*/
/*--------------------------------------------------------------------------*/
#define PrfExtr_Prf(PrfExtrPtr)\
((PrfExtrPtr)->PrfPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant les donnees de profil traitees							*/
/*--------------------------------------------------------------------------*/
#define PrfExtr_PrfFileData(PrfExtrPtr)\
((PrfExtrPtr)->PrfFileDataPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la description courante									*/
/*--------------------------------------------------------------------------*/
#define PrfExtr_CurrentDesc(PrfExtrPtr)\
((PrfExtrPtr)->CurrentDescPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant l'assignation courante									*/
/*--------------------------------------------------------------------------*/
#define PrfExtr_CurrentAss(PrfExtrPtr)\
((PrfExtrPtr)->CurrentAssPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant la valeur courante										*/
/*--------------------------------------------------------------------------*/
#define PrfExtr_CurrentVal(PrfExtrPtr)\
((PrfExtrPtr)->CurrentValPtr)

/*--------------------------------------------------------------------------*/
/* Macro retournant le No de la description courante a partir de 1			*/
/*--------------------------------------------------------------------------*/
#define PrfExtr_DescNth(PrfExtrPtr)\
((PrfExtrPtr)->DescNth)

/*--------------------------------------------------------------------------*/
/* Macro retournant le No de l'assignation courante a partir de 1			*/
/*--------------------------------------------------------------------------*/
#define PrfExtr_AssNth(PrfExtrPtr)\
((PrfExtrPtr)->AssNth)

/*--------------------------------------------------------------------------*/
/* Macro retournant le No de la valeur courante a partir de 1				*/
/*--------------------------------------------------------------------------*/
#define PrfExtr_ValNth(PrfExtrPtr)\
((PrfExtrPtr)->ValNth)

/*--------------------------------------------------------------------------*/
/* Extraction de l'identificateur du profil									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_Id				| Identificateur					*/
/* Erreur:	| PrfExtr_Id=NULL			| Allocation memoire				*/
/*--------------------------------------------------------------------------*/
TId PrfExtr_Id(TPrfExtrPtr PrfExtrPtr);

/*--------------------------------------------------------------------------*/
/* Extraction du nombre Prosite du profil									*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_NbrAc				| Nombre Prosite					*/
/* Erreur:	| PrfExtr_NbrAc=NULL		| Erreur allocation					*/
/*--------------------------------------------------------------------------*/
TNbrAc PrfExtr_NbrAc(TPrfExtrPtr PrfExtrPtr);

/*--------------------------------------------------------------------------*/
/* Saute a la prochaine description	du profil								*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_NextDesc			| Description						*/
/* Erreur:	| PrfExtr_NextDesc=NULL		| Plus de descriptions				*/
/*--------------------------------------------------------------------------*/
TDescPtr PrfExtr_NextDesc(TPrfExtrPtr PrfExtrPtr);

/*--------------------------------------------------------------------------*/
/* Saute a la prochaine assignation											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_NextAss			| Assignation						*/
/* Erreur:	| PrfExtr_NextAss=NULL		| Plus d'assignations				*/
/*--------------------------------------------------------------------------*/
TAssPtr PrfExtr_NextAss(TPrfExtrPtr PrfExtrPtr);

/*--------------------------------------------------------------------------*/
/* Saute a la prochaine valeur												*/
/*--------------------------------------------------------------------------*/
/* Entree:	| PrfExtrPtr				| Donnees d'extraction				*/
/* Sortie:	| PrfExtr_NextVal			| Valeur							*/
/* Erreur:	| PrfExtr_NextVal=NULL		| Plus de valeurs					*/
/*--------------------------------------------------------------------------*/
TValPtr PrfExtr_NextVal(TPrfExtrPtr PrfExtrPtr);

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
TGenSpecPtr PrfExtr_GenSpec(TPrfExtrPtr PrfExtrPtr, TErrIndex *ErrIndexPtr);

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
TDisjointPtr PrfExtr_Disjoint(TPrfExtrPtr PrfExtrPtr, TErrIndex *ErrIndexPtr);

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
TBoolean *ModePresPtr, TBoolean *PrtyPresPtr, TErrIndex *ErrIndexPtr);

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
TNormListPtr PrfExtr_NormList(TPrfExtrPtr PrfExtrPtr, TErrIndex *ErrIndexPtr);

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
TCutOffPtr PrfExtr_CutOff(TPrfExtrPtr PrfExtrPtr, TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

/*--------------------------------------------------------------------------*/
/* Conversion d'une valeur en score											*/
/*--------------------------------------------------------------------------*/
/* Entree:	| ValPtr					| Valeur							*/
/* Sortie:	| Val_Score					| Score								*/
/* Erreur:	| ErrIndex!=PE_NO_ERROR		| Index d'erreur =					*/
/*			| PE_INT_EXP				| Entier attendu					*/
/*--------------------------------------------------------------------------*/
TScore Val_Score(TValPtr ValPtr, TErrIndex *ErrIndexPtr);

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
TAlphPtr AlphPtr, TErrIndex *ErrIndexPtr);

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
TMatchPosPtr DefaultMatchPosPtr, TAlphPtr AlphPtr, TErrIndex *ErrIndexPtr);

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
TAlphPtr AlphPtr, TErrIndex *ErrIndexPtr);

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
TErrIndex *ErrIndexPtr);

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
TPrfDataPtr PrfExtr_PrfData(TPrfExtrPtr PrfExtrPtr, TErrIndex *ErrIndexPtr);

#endif
