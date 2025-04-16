/****************************************************************************/
/*																			*/
/*	But: Alignement entre un profil et une collection de sequences			*/
/*																			*/
/****************************************************************************/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/


#ifdef _SUN_
#include <floatingpoint.h>
#endif
#include <stddef.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "error.h"
#include "ReadPrfFile.h"
#include "PrfExtr.h"
#include "ReadSeqFile.h"
#include "ReadFASTAFile.h"
#include "SeqExtr.h"
#include "PrfAlign.h"
#include "ErrTable.h"
#include "ReadPar.h"

/**************/
/* CONSTANTES */
/**************/

/*=========================*/
/* Constantes du programme */
/*=========================*/

#define TEST_NBR		1

/*--------------------------------------------------------------------------*/
/* Impression du format d'appel												*/
/*--------------------------------------------------------------------------*/
void Print_Format()\
{
	fprintf(stderr, "\
	Usage:\nscan4prf -s seq_library_file  [-p profile_file] [-i profile_ID]\n\
[-l cut_off_level] [-c cut_off_value] [-n normalization_mode]\
 [-o output_file]\n[-f] [-a] [-b] [-y] [-u] [-t]\n\n");
	fflush(stderr);
}

void main(int argc, char *argv[])
{
	/*****************************/
	/* DECLARATION DES VARIABLES */
	/*****************************/

	/*=========================*/
	/* Parametres du programme */
	/*=========================*/
	
	char *SeqFilename;				/* Nom du fichier de sequences			*/
	char *PrfFilename;				/* Nom du fichier de profils			*/
	char *PrfId;					/* Identificateur du profil				*/
	double CutOffLevelDouble;		/* Niveau de val. de coupure en double	*/
	TCutOffLevel CutOffLevel;		/* Niveau de la valeur de coupure		*/
	TCutOffLevel CutOffLevelUsed;	/* Niveau utilise						*/
	double CutOffDouble;			/* Valeur de coupure donnee				*/
	TScore CutOff;					/* Valeur de coupure					*/
	double NormModeDouble;			/* Mode de normalisation en double		*/
	TNormIndex NormMode;			/* Mode de normalisation				*/
	TBoolean SelectAll;				/* Parametre de selection				*/
	TBoolean ReportAlign;			/* Reporte les alignements				*/
	TBoolean Unique;				/* Trouve seulement le meill. ali.		*/
	TBoolean UniqueForced;			/* Unique force							*/
	TBoolean FASTA;					/* Format FASTA ou non					*/
	TBoolean ComplStr;				/* Teste la sequence complementaire		*/
	FILE *OutPutFile;				/* Fichier de sortie					*/
	TBoolean TestProt;				/* Test ou pas les align. prot.			*/
	
	/*===================*/
	/* Donnees du profil */
	/*===================*/
	
	TReadPrfFilePtr ReadPrfFilePtr;	/* Donnees de lecture d'un profil		*/
	TPrfFileDataPtr PrfFileDataPtr;	/* Donnees d'un fichier de profil		*/
	TPrfExtrPtr PrfExtrPtr;			/* Donnees d'extraction d'un profil		*/
	TPrfDataPtr PrfDataPtr;			/* Donnees d'un profil					*/
	TAlphPtr AlphPtr;				/* Alphabet du profil					*/
	
	/*========================*/
	/* Donnees de la sequence */
	/*========================*/
	
	TReadFilePtr ReadFilePtr;		/* Donnees de lecture d'une sequence	*/
	TSeqFileDataPtr SeqFileDataPtr;	/* Donnees d'un fichier de sequence		*/
	TSeqExtrPtr SeqExtrPtr;			/* Donnees d'extraction d'une sequence	*/
	TSeqDataPtr SeqDataPtr;			/* Donnees d'une sequence				*/
	
	/*======================================*/
	/* Donnees de l'algorithme d'alignement */
	/*======================================*/
	
	TPrfAlignPtr PrfAlignPtr;		/* Donnee d'alignation					*/
	TAlignListPtr AlignListPtr;		/* Liste des alignements				*/
	TPrfAlignPtr PrfAlignResPtr;	/* Resultat de l'algorithme				*/
	TPathMatrixPtr PathMatrixPtr;	/* Matrice de chemin					*/
	TAlignPtr AlignPtr;				/* Alignement particulier				*/
	TAlignIndex AlignIndex;			/* Index d'alignement					*/
	TAliStrPtr AliStrPtr;			/* Chaine d'alignement					*/
	TAliStrPtr TempAliStrPtr;		/* Chaine d'alignement					*/

	/*======================*/
	/* Donnees du programme */
	/*======================*/

	TErrIndex ErrIndex;				/* Index d'erreur						*/
	char ParChar;					/* Caractere du type de parametre		*/
	char *ParStr;					/* Chaine parametre						*/
	char *EndStr;					/* Ptr sur chaine apres conversion		*/
	TScore Score;					/* Score d'alignement					*/
	char *CharPtr;					/* Ptr sur un caractere					*/
	char ParLine[UCHAR_MAX];		/* Ligne de lecture de fichier			*/
	FILE *ParFile;					/* Fichier de parametres				*/
	TMolSeqPtr MolSeqPtr;			/* Sequence de molecules				*/
	TAlignIndex FirstCplAlign;		/* Index du 1er alignement compl.		*/
	TBoolean AccAlign;				/* Temoin de calcul des align.			*/
	TBoolean AccCplAlign;			/* Temoin de calcul des align. cpl.		*/
	TAlignPtr BestAlignPtr;			/* Meilleur alignement					*/
	TAlignPtr BestCplAlignPtr;		/* Meilleur alignement cpl.				*/
	TAlignIndex HitNbr;				/* Nbr d'alignements acceptes			*/
	TNormFct NormFct;				/* Fonction de normalisation			*/
	TNormPar R[5];					/* Parametre de normalisation			*/
	TBoolean CutOffNorm;			/* Indique si le cutoff donne est nor.	*/
	TNormParListPtr NormParListPtr;	/* Liste des parametres de norm.		*/
	TNormParIndex ParNbr;			/* Nombre de par. de norm.				*/
	TNormParIndex ParIndex;			/* Index des par. de norm.				*/
	TBoolean NegCutOff;				/* Indique si le cutoff est negatif		*/
	double Frac;					/* Partie fractionnaire du cut-off		*/
	TDisjointDef DisjointDef;		/* Definition de l'exclusion			*/
	double Double;					/* Double temporaire					*/
	TCutOffListPtr CutOffListPtr;	/* Liste de valeurs de coupure			*/
	unsigned int TestIndex;
	
	/********/
	/* CODE */
	/********/

	/*=====================================*/
	/* Lecture des parametres du programme */
	/*=====================================*/
	
	/*-------------------------------*/
	/* Initialisation des parametres */
	/*-------------------------------*/

	SeqFilename = NULL;
	PrfFilename = NULL;
	CutOff = PD_INFINITE;
	CutOffDouble = DBL_MIN;
	PrfId = NULL;
	CutOffLevelDouble = DBL_MIN;
	NormModeDouble = DBL_MIN;
	CutOffLevel = 0;
	NormMode = 1;
	SelectAll = FALSE;
	ReportAlign = FALSE;
	UniqueForced = FALSE;
	TestProt = FALSE;
	FASTA = FALSE;
	ComplStr = FALSE;
	CutOffNorm = FALSE;
	OutPutFile = stdout;

	if (argc < 2) {
		ParFile = fopen("scan4prf.par", "r");
		if (!ParFile) {
			/* Erreur de format */
			Print_Format();
			exit(1);
		}
		CharPtr = fgets(ParLine, UCHAR_MAX, ParFile);
		if (!CharPtr) {
			/* Erreur de format */
			Print_Format();
			exit(1);
		}
		printf("%s\n", ParLine);
		fflush(stdout);
		argc = 0;
		CharPtr = strtok(ParLine, " \n");
		while (CharPtr) {
			argv[argc++] = CharPtr;
			CharPtr = strtok(NULL, " \n");
		}
	}
		
	ParChar = ProgPar(argc, argv, &ParStr, &ErrIndex);
	while (ErrIndex == RP_NO_ERROR) {
		switch (ParChar) {
			case 's':
				/* Nom du fichier de sequences */
				if ((!ParStr) || (SeqFilename)) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				SeqFilename = ParStr;
				break;
			case 'p':
				/* Nom du fichier de profils */
				if ((!ParStr) || (PrfFilename)) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				PrfFilename = ParStr;
				break;
			case 'i':
				/* ID du profil */
				if ((!ParStr) || (PrfId)) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				PrfId = ParStr;
				break;
			case 'l':
				/* Niveau de la valeur de coupure */
				if ((!ParStr) || (CutOffLevelDouble != DBL_MIN)) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				CutOffLevelDouble = strtod(ParStr, &EndStr);
				if (*EndStr != 0) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				CutOffLevel = (TCutOffLevel)CutOffLevelDouble;
				if ((double)CutOffLevel != CutOffLevelDouble) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				break;
			case 'c':
				/* Entree d'une valeur de coupure */
				if ((!ParStr) || (CutOffDouble != DBL_MIN))  {
					Print_Format();
					exit(1);
				}
				CutOffDouble = strtod(ParStr, &EndStr);
				if (*EndStr != 0) {
					Print_Format();
					exit(1);
				}
				if (strchr(ParStr, '.')) CutOffNorm = TRUE;
				break;
			case 'n':
				/* Normalisation */
				if ((!ParStr) || (NormModeDouble != DBL_MIN)) {
					Print_Format();
					exit(1);
				}
				NormModeDouble = strtod(ParStr, &EndStr);
				if (*EndStr != 0) {
					Print_Format();
					exit(1);
				}
				NormMode = (TNormIndex)NormModeDouble;
				if (((double)NormMode != NormModeDouble) ||
				(NormMode < 1)) {
					Print_Format();
					exit(1);
				}
				break;
			case 'a':
				/* Parametre de selection */
				if ((ParStr) || (SelectAll)) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				SelectAll = TRUE;
				break;
			case 'y':
				/* Report des alignements */
				if ((ParStr) || (ReportAlign)) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				ReportAlign = TRUE;
				break;
			case 'u':
				/* Meilleur alignement */
				if ((ParStr) || (UniqueForced)) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				UniqueForced = TRUE;
				break;
			case 'f':
				/* Format FASTA */
				if ((ParStr) || (FASTA)) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				FASTA = TRUE;
				break;
			case 'b':
				/* Teste la sequence complementaire */
				if ((ParStr) || (ComplStr)) {
					Print_Format();
					exit(1);
				}
				ComplStr = TRUE;
				break;
			case 'o':
				/* Nom du fichier de sortie */
				if ((!ParStr) || (OutPutFile != stdout)) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				OutPutFile = fopen((char*)ParStr, "w");
				if (!OutPutFile) {
					/* Erreur d'ouverture */
					fprintf(stderr, "Output file opening error");
					fprintf(stderr, "\n");
					exit(1);			
				}
				break;
			case 't':
				/* Teste les align. prot. */
				if ((ParStr) || (TestProt)) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				TestProt = TRUE;
				break;
			default:
				/* Erreur de format */
				Print_Format();
				exit(1);
		}
		ParChar = ProgPar(argc, argv, &ParStr, &ErrIndex);
	}
	
	/*-------------------------*/
	/* Controle des parametres */
	/*-------------------------*/
	
	if (!PrfFilename) PrfFilename = "PROSITE.DAT";

	/* Nom du fichier de sequence obligatoire */
	if (!SeqFilename) {
		Print_Format();
		exit(1);
	}
	
	/* Exclusion valeur de coupure  et niveau de coupure */
	if ((CutOffDouble != DBL_MIN) && (CutOffLevelDouble != DBL_MIN)) {
		Print_Format();
		exit(1);
	}

	/* Verification utilite de la valeur de coupure */
	if (SelectAll && Unique && ((CutOffDouble != DBL_MIN) ||
	(CutOffLevelDouble != DBL_MIN))) {
		Print_Format();
		exit(1);
	}
	
	/* Si mode de normalisation alors cut-off normalise obligatoire */
	if ((NormModeDouble != DBL_MIN) && (!CutOffNorm)) {
		Print_Format();
		exit(1);
	}
	
	/* Exclusion test des alignements et exclusion = unique */
	if ((TestProt) && (UniqueForced)) {
		Print_Format();
		exit(1);
	}
	
	for (TestIndex = 0; TestIndex < TEST_NBR; TestIndex++) {
	
	/*===================*/
	/* Lecture du profil */
	/*===================*/

	/*---------------------------------------*/	
	/* Initialisation des donnees de lecture */
	/*---------------------------------------*/	

	ReadPrfFilePtr = I_ReadPrfFile(PrfFilename, &ErrIndex);
	if (!ReadPrfFilePtr) {
		fprintf(stderr, "Profile file reading initialization error:\n");
		Print_ErrStr(ErrTable_ErrStrNth(RPF_ErrTable, ErrIndex));
		fprintf(stderr, "\n");
		exit(1);
	}
	
	/*------------------------------------------*/	
	/* Lecture des donnees du fichier de profil */
	/*------------------------------------------*/	

	PrfFileDataPtr = ReadPrfFile_PrfFileData(ReadPrfFilePtr, PrfId,
	&ErrIndex);
	if (!PrfFileDataPtr) {
		fprintf(stderr, "Profile file reading error:\n");
		Print_ErrStr(ErrTable_ErrStrNth(RPF_ErrTable, ErrIndex));
		fprintf(stderr, "\n");
		exit(1);
	}
	Free_ReadPrfFile(ReadPrfFilePtr);
	
	/*----------------------------------*/
	/* Extraction des donnees du profil */
	/*----------------------------------*/

	PrfExtrPtr = I_PrfExtr(PrfFileDataPtr);
	if (!PrfExtrPtr) {
		fprintf(stderr, "Profile extraction initialization error:\n");
		fprintf(stderr, "Allocation error\n");
		exit(1);
	}
	PrfDataPtr = PrfExtr_PrfData(PrfExtrPtr, &ErrIndex);
	if (!PrfDataPtr) {
		fprintf(stderr, "Profile extraction error:\n");
		Print_ErrStr(ErrTable_ErrStrNth(PE_ErrTable, ErrIndex));
		fprintf(stderr, "\n");
		exit(1);
	}
	Free_PrfExtr(PrfExtrPtr);
	Free_PrfFileData(PrfFileDataPtr);
	/* Print_PrfData(PrfDataPtr); */
	
	/*------------------------------------*/
	/* Definition utilisee de l'exclusion */
	/*------------------------------------*/
	
	if (!UniqueForced) {
		DisjointDef = Disjoint_Def(PrfData_Disjoint(PrfDataPtr));
		if (DisjointDef == PD_UNIQUE) {
			Unique = TRUE;
		}
		else if (DisjointDef == PD_PROTECT) {
			Unique = FALSE;
		}
		else {
			fprintf(stderr, "Program error:\n");
			Print_ErrStr("Unknow disjoint definition");
			fprintf(stderr, "\n");
			exit(1);
		}
	}
	else {
		Unique = TRUE;
	}
	
	/*---------------*/
	/* Normalisation */
	/*---------------*/

	if (CutOffNorm) {
		if (NormList_NormNbr(PrfData_NormList(PrfDataPtr)) >= NormMode) {
			NormFct = Norm_Fct(NormList_NormNth(
			PrfData_NormList(PrfDataPtr), NormMode));
		}
		else {
			/* Erreur: il n'y a pas de fct de normalisation */
			fprintf(stderr, "Parameter error:\n");
			Print_ErrStr("Normalization function missing");
			fprintf(stderr, "\n");
			exit(1);
		}
		/* Affectation des parametres */
		NormParListPtr = Norm_ParList(
		NormList_NormNth(PrfData_NormList(PrfDataPtr), NormMode));
		ParNbr = NormParList_ParNbr(NormParListPtr);
		if (NormFct == PD_NORM_LINEAR) {
			if (ParNbr != 2) {
				/* Mauvais nombre de parametres */
				fprintf(stderr, "Parameter error:\n");
				Print_ErrStr("Bad normalization parameters number");
				fprintf(stderr, "\n");
				exit(1);
			}
		}
		else if (NormFct == PD_NORM_GRIB) {
			if (ParNbr != 5) {
				/* Mauvais nombre de parametres */
				fprintf(stderr, "Parameter error:\n");
				Print_ErrStr("Bad normalization parameters number");
				fprintf(stderr, "\n");
				exit(1);
			}
		}
		else {
			/* Fonction non connue */
			fprintf(stderr, "Program error:\n");
			Print_ErrStr("Unknown normalization function");
			fprintf(stderr, "\n");
			exit(1);
		}
		for (ParIndex = 1; ParIndex <= ParNbr; ParIndex++)
		R[ParIndex - 1] = NormParList_ParNth(NormParListPtr, ParIndex);
	}
	
	/*-------------------------*/
	/* Recherche de l'alphabet */
	/*-------------------------*/
	
	AlphPtr = GenSpec_Alph(PrfData_GenSpec(PrfDataPtr));
	
	/*-----------------------------------*/
	/* Recherche de la valeur de coupure */
	/*-----------------------------------*/

	if (!CutOffNorm) {
		/* La valeur de coupure n'est pas normalisee */
		if (CutOffDouble != DBL_MIN) {
			/* Elle est donnee en parametre */
			CutOff = (TScore)CutOffDouble;
		}
		else {
			/* Elle est donne dans le fichier de profil */
			/* Controle du debordement du niveau de valeur de coupure */
			CutOffListPtr = PrfData_CutOffList(PrfDataPtr);
			/*Print_CutOffList(CutOffListPtr);*/
			if ((CutOff_Level(CutOffList_CutOffNth(CutOffListPtr, 0)) >
			CutOffLevel) || (CutOff_Level(CutOffList_CutOffNth(CutOffListPtr,
			CutOffList_CutOffNbr(CutOffListPtr) - 1)) < CutOffLevel)) {
				/* Le niveau specifie n'existe pas */
				fprintf(stderr, "Parameter error:\n");
				fprintf(stderr, "Cut-off level inexistent\n");
				exit(1);
			}
			else {
				CutOffLevelUsed = CutOffLevel;
			}
			CutOff = CutOff_Score(CutOffList_CutOffLevelNth(
			PrfData_CutOffList(PrfDataPtr), CutOffLevelUsed));
		}
	}
	
	/*====================================================*/
	/* Initialisation des donnees de lecture de sequences */
	/*====================================================*/

	if (FASTA) ReadFilePtr = (TReadFilePtr)I_ReadFASTAFile(
	SeqFilename, &ErrIndex);
	else ReadFilePtr = (TReadFilePtr)I_ReadSeqFile(SeqFilename, &ErrIndex);

	if (!ReadFilePtr) {
		fprintf(stderr, "Sequences file reading initialization error:\n");
		Print_ErrStr(ErrTable_ErrStrNth(RSF_ErrTable, ErrIndex));
		fprintf(stderr, "\n");
		exit(1);
	}

	/*====================================*/
	/* Affichage des donnees du programme */
	/*====================================*/
	
	/*-----------------*/
	/* Donnees general */
	/*-----------------*/
	
	printf("\n");
	printf("Program:      scan4prf\n");
	printf("Version:      v1.00\n");
	printf("Author:       Nicolas Moeri\n");
	printf("Description:  Compares a profile against a sequences database\n");
	printf("\n");
	printf("Infinite negative score is %d\n", PD_INFINITE);
	printf("\n");
	fflush(stdout);

	/*------------------------*/
	/* Parametres utilisateur */	
	/*------------------------*/
	
	fprintf(OutPutFile, "Sequences database:  %s\n", SeqFilename);
	fprintf(OutPutFile, "Profiles database:   %s\n", PrfFilename);
	fprintf(OutPutFile, "Profile name:        ");
	Out_PrfId(OutPutFile, PrfData_Id(PrfDataPtr));
	fprintf(OutPutFile, "\n");
	fprintf(OutPutFile, "Profile description: ");
	Out_De21(OutPutFile, PrfData_De(PrfDataPtr));
	fprintf(OutPutFile, "\n");
	fprintf(OutPutFile, "Cut-off value:       ");
	if (!CutOffNorm) {
		Out2_Score(OutPutFile, CutOff);
	}
	else {
		fprintf(OutPutFile, "normalized");
	}
	fprintf(OutPutFile, "\n\n");
	
	/*---------------------*/
	/* En-tete du resultat */
	/*---------------------*/

	fprintf(OutPutFile, "Alignments results\n");
	fprintf(OutPutFile, "==================\n");
	if (!ReportAlign) {
		fprintf(OutPutFile,
		"\nSequence name  Description                         Hits  Score  Position       \n");
		fprintf(OutPutFile,
		  "-------------------------------------------------------------------------------\n");
	}
	fflush(OutPutFile);
	
	/*===================*/
	/* Boucle de lecture */
	/*===================*/

	while(TRUE) {

		/*----------------------------------*/
		/* Lecture de la prochaine sequence */
		/*----------------------------------*/

		if (FASTA) {
			SeqFileDataPtr = ReadFASTAFile_SeqFileData(
			(TReadFASTAFilePtr)ReadFilePtr, &ErrIndex);
		}
		else {
			SeqFileDataPtr = ReadSeqFile_SeqFileData(
			(TReadSeqFilePtr)ReadFilePtr, &ErrIndex);
		}
		if (!SeqFileDataPtr) {
            if (((!FASTA) && (ErrIndex == RSF_ID_EXP_UEOF)) ||
			((FASTA) && (RFF_ID_EXP_UEOF))) {
                /* Fin du fichier: on sort de la boucle */
                break;
            }
			fprintf(stderr, "Sequences file reading error:\n");
			if (FASTA) {
				Print_ErrStr(ErrTable_ErrStrNth(RFF_ErrTable, ErrIndex));
			}
			else {
				Print_ErrStr(ErrTable_ErrStrNth(RSF_ErrTable, ErrIndex));
			}
			fprintf(stderr, "\n");
			exit(1);
		}
	
		/*-----------------------------------------*/
		/* Initialisation des donnees d'extraction */
		/*-----------------------------------------*/

		SeqExtrPtr = I_SeqExtr(SeqFileDataPtr, AlphPtr);
		if (!SeqExtrPtr) {
			fprintf(stderr, "Sequence extraction initialization error:\n");
			fprintf(stderr, "Allocation error\n");
			exit(1);
		}
		
		/*------------------------*/
		/* Extraction des donnees */
		/*------------------------*/

		SeqDataPtr = SeqExtr_SeqData(SeqExtrPtr);
		if (!SeqDataPtr) {
			fprintf(stderr, "Sequence extraction error\n");
			fprintf(stderr, "Allocation error\n");
			exit(1);
		}
		Free_SeqExtr(SeqExtrPtr);
		Free_SeqFileData(SeqFileDataPtr);
		
		/*Print_SeqData(SeqDataPtr);*/
		
		/*-----------------------------------------------------*/
		/* Calcul d'un valeur de coupure donnee non normalisee */
		/*-----------------------------------------------------*/

		if (CutOffNorm) {
			/* La valeur de coupure donnee est normalisee */
			/* Choix de la 1ere normalisation */
			if (NormFct == PD_NORM_LINEAR) {
				Double = (CutOffDouble - R[0])/R[1];
			}
			else if (NormFct == PD_NORM_GRIB) {
				Double = (R[4]*CutOffDouble + R[3])*(R[0]*(1.0 -
				exp(R[1]*MolSeq_MolNbr(SeqData_MolSeq(SeqDataPtr)) - R[2])));
			}
			/* Conversion -> entier */
			if (Double < 0.0) {
				Double = -Double;
				NegCutOff = TRUE;
			}
			else NegCutOff = FALSE;
			Frac = modf(Double, &Double);
			CutOff = (TScore)Double;
			if (Frac > 0.5) CutOff++;
			if (NegCutOff) CutOff = -CutOff;
		}

		/*============*/
		/* Alignement */
		/*============*/
		
		/*-------------------------*/
		/* Selection des sequences */
		/*-------------------------*/
		
		BestAlignPtr = PrfAlign_BestAlign(PrfData_PrfMatrix(PrfDataPtr),
		SeqData_MolSeq(SeqDataPtr), &ErrIndex);
		if (!BestAlignPtr) {
			/* Erreur */
			fprintf(stderr, "Best alignment algorithme error:\n");
			Print_ErrStr(ErrTable_ErrStrNth(PA_ErrTable, ErrIndex));
			fprintf(stderr, "\n");
			exit(1);
		}
		if (Align_Score(BestAlignPtr) >= CutOff) AccAlign = TRUE;
		else AccAlign = FALSE;
		if (ComplStr) {
			/* Sequence complementaire */
			MolSeqPtr = MolSeq_CplStrand(SeqData_MolSeq(SeqDataPtr),
			SeqData_Alph(SeqDataPtr));
			BestCplAlignPtr  = PrfAlign_BestAlign(PrfData_PrfMatrix(
			PrfDataPtr), SeqData_MolSeq(SeqDataPtr), &ErrIndex);
			if (!BestCplAlignPtr) {
				/* Erreur */
				fprintf(stderr, "Best alignment algorithme error:\n");
				Print_ErrStr(ErrTable_ErrStrNth(PA_ErrTable, ErrIndex));
				fprintf(stderr, "\n");
				exit(1);
			}
			/* Retour a la sequence originelle */
			MolSeqPtr = MolSeq_CplStrand(SeqData_MolSeq(SeqDataPtr),
			SeqData_Alph(SeqDataPtr));
			if (Align_Score(BestCplAlignPtr) >= CutOff) AccCplAlign = TRUE;
			else AccCplAlign = FALSE;
		}
		else AccCplAlign = FALSE;

		if ((!AccAlign) && (!AccCplAlign) && (!SelectAll)) {
			/* Continue */
			continue;
		}
		
		/*-----------------------------------------*/
		/* Initialisation des donnees d'alignement */
		/*-----------------------------------------*/

		PrfAlignPtr = I_PrfAlign(SeqDataPtr, PrfDataPtr,
		MolSeq_MolNbr(SeqData_MolSeq(SeqDataPtr)));
		if (!PrfAlignPtr) {
			/* Erreur d'allocation */
			fprintf(stderr, "Alignment data contruction:\n");
			fprintf(stderr, "Allocation error\n");
			exit(1);
		}
		AlignListPtr = PrfAlign_AlignList(PrfAlignPtr);

		/*-------------------------*/
		/* Algorithme d'alignement */
		/*-------------------------*/

		if ((AccAlign) && (!Unique)) {
			PrfAlignResPtr = PrfAlign_Align(PrfAlignPtr, CutOff, TestProt,
			&ErrIndex);
			if (!PrfAlignResPtr) {
				/* Erreur */
				fprintf(stderr, "Alignment algorithme error:\n");
				Print_ErrStr(ErrTable_ErrStrNth(PA_ErrTable, ErrIndex));
				fprintf(stderr, "\n");
				exit(1);
			}
		}

		/*-------------------------*/
		/* Sequence complementaire */
		/*-------------------------*/

		if ((AccCplAlign) && (!Unique)) {
			/* Index du 1ere alignment compl. */
			FirstCplAlign = AlignList_AlignNbr(AlignListPtr);
			/* Conversion de la sequence */
			MolSeqPtr = MolSeq_CplStrand(SeqData_MolSeq(SeqDataPtr),
			SeqData_Alph(SeqDataPtr));
			/* Alignement */
			PrfAlignResPtr = PrfAlign_Align(PrfAlignPtr, CutOff, TestProt,
			&ErrIndex);
			if (!PrfAlignResPtr) {
				/* Erreur */
				fprintf(stderr, "Alignment algorithme error:\n");
				Print_ErrStr(ErrTable_ErrStrNth(PA_ErrTable, ErrIndex));
				fprintf(stderr, "\n");
				exit(1);
			}
		}
		
		/*---------------------------------------*/
		/* Affichage du resultat de l'alignement */
		/*---------------------------------------*/

		/*Print_AlignList(PrfAlign_AlignList(PrfAlignPtr));*/
		
		/*----------------------------------*/
		/* Stockage du nombre d'occurrences */
		/*----------------------------------*/
		
		HitNbr = AlignList_AlignNbr(AlignListPtr);
		
		if ((Unique) && (AccAlign)) HitNbr++;
		if ((Unique) && (AccCplAlign)) HitNbr++;

		/*----------------------------------------------*/
		/* Ajout des meilleurs alignments si necessaire */
		/*----------------------------------------------*/
		
		if (((SelectAll) && (!AccAlign)) || ((Unique) && (AccAlign))) {
			if (AlignList_Full(AlignListPtr)) {
				/* Liste d'alignement pleine */
				fprintf(stderr, "Program error:\n");
				Print_ErrStr("Alignments overflow");
				fprintf(stderr, "\n");
				exit(1);
			}
			/* Ajout */
			AlignList_AddAlign(AlignListPtr, BestAlignPtr);
		}
		
		if (((SelectAll) && (!AccCplAlign) && (ComplStr)) ||
		((Unique) && (AccCplAlign))) {
			if (AlignList_Full(AlignListPtr)) {
				/* Liste d'alignement pleine */
				fprintf(stderr, "Program error:\n");
				Print_ErrStr("Alignments overflow");
				fprintf(stderr, "\n");
				exit(1);
			}
			/* Ajout */
			AlignList_AddAlign(AlignListPtr, BestCplAlignPtr);
		}
		
						
		/* Affichage */
		if (ReportAlign) {
			if (ComplStr) {
				/* Retour a la sequence initiale */
				MolSeqPtr = MolSeq_CplStrand(SeqData_MolSeq(SeqDataPtr),
				SeqData_Alph(SeqDataPtr));
			}
			fprintf(OutPutFile, "\n");
			Out_SeqId(OutPutFile, SeqData_Id(SeqDataPtr));
			fprintf(OutPutFile, ", ");
			Out_De53(OutPutFile, SeqData_De(SeqDataPtr));
			fprintf(OutPutFile, ", Hits: ");
			Out_AlignIndex(OutPutFile, HitNbr);
			fprintf(OutPutFile,
			"\n-------------------------------------------------------------------------------\n");
		}
		else {			
			Out_SeqId(OutPutFile, SeqData_Id(SeqDataPtr));
			fprintf(OutPutFile, "  ");
			Out_De34(OutPutFile, SeqData_De(SeqDataPtr));
			fprintf(OutPutFile, "  ");
			Out_AlignIndex(OutPutFile, HitNbr);
			fprintf(OutPutFile, "  ");
		}
		
		for (AlignIndex = 0; AlignIndex < AlignList_AlignNbr(AlignListPtr);
		AlignIndex++) {
			AlignPtr = AlignList_AlignNth(AlignListPtr, AlignIndex);
			if (ReportAlign) {
				if ((AccCplAlign) && (AlignIndex == FirstCplAlign)) {
					/* Retour a la sequence complementaire */
					MolSeqPtr = MolSeq_CplStrand(SeqData_MolSeq(SeqDataPtr),
					SeqData_Alph(SeqDataPtr));
				}
				fprintf(OutPutFile, "\nScore: ");
				Out_Score(OutPutFile, Align_Score(AlignPtr));
				fprintf(OutPutFile, "  Position: ");
				if ((ComplStr) && (AlignIndex >= FirstCplAlign)) {
					Align_OutCplRange(OutPutFile, AlignPtr,
					MolSeq_MolNbr(SeqData_MolSeq(SeqDataPtr)));
				}
				else {
					Align_OutRange(OutPutFile, AlignPtr);
				}
				fprintf(OutPutFile, "\n");
				/* Allocation de la matrice de chemins */
				PathMatrixPtr = I_PathMatrix(Coord_PosIndex(
				&Align_EndCoord(AlignPtr)) - Coord_PosIndex(
				&Align_StartCoord(AlignPtr)) + 1, Coord_MolIndex(&
				Align_EndCoord(AlignPtr)) - Coord_MolIndex(
				&Align_StartCoord(AlignPtr)) + 1, &Align_StartCoord(
				AlignPtr));
				if (!PathMatrixPtr) {
					/* Erreur d'allocation */
					fprintf(stderr, "Path matrix allocation error\n");
					exit(1);
				}
			
				/* Calcul de matrice de chemin */
				if (Coord_PosIndex(&Align_InCoord(AlignPtr)) ==
				PD_POS_IDX_NOT_DEF) {				
					Score = PathMatrix_BestCalc(PathMatrixPtr, AlignPtr,
					PrfData_PrfMatrix(PrfDataPtr),
					SeqData_MolSeq(SeqDataPtr));
				}
				else {
					Score = PathMatrix_Calc(PathMatrixPtr, AlignPtr,
					PrfData_PrfMatrix(PrfDataPtr),
					SeqData_MolSeq(SeqDataPtr));
				}

				/* Construction de la chaine d'alignement */
				AliStrPtr = I_AliStr(PathMatrix_RowNbr(PathMatrixPtr) +
				PathMatrix_ColumnNbr(PathMatrixPtr) - 1);
				if (!AliStrPtr) {
					/* Erreur d'allocation */
					fprintf(stderr, "Alignment string allocation error\n");
					exit(1);
				}
			
				/* Calcul de la chaine d'alignement */
				TempAliStrPtr = AliStr_FromPathMatrix(AliStrPtr,
				PathMatrixPtr, PrfData_PrfMatrix(PrfDataPtr), SeqDataPtr,
				&ErrIndex);
			
				if (!TempAliStrPtr) {
					/* Erreur dans le calcul de la chaine d'alignement */
					fprintf(stderr,
					"Alignment string calculation error:\n");
					Print_ErrStr(ErrTable_ErrStrNth(PA_ErrTable,
					ErrIndex));
					fprintf(stderr, "\n");
					exit(1);
				}
				
				/* Affichage de la chaine d'alignement */
				fprintf(OutPutFile, "\n");
				Out_AliStr(OutPutFile, AliStrPtr);
					
				/* Destruction de la chaine d'alignement */
				Free_AliStr(AliStrPtr);

				/* Destruction de la matrice de chemin */
				Free_PathMatrix(PathMatrixPtr);
			}
			else {
				Out_Score(OutPutFile, Align_Score(AlignPtr));
				fprintf(OutPutFile, "  ");
				if ((ComplStr) && (AlignIndex >= FirstCplAlign)) {
					Align_OutCplRange(OutPutFile, AlignPtr,
					MolSeq_MolNbr(SeqData_MolSeq(SeqDataPtr)));
				}
				else {
					Align_OutRange(OutPutFile, AlignPtr);
				}
					fprintf(OutPutFile, "\n");
				if (AlignIndex < AlignList_AlignNbr(AlignListPtr) - 1) {
					fprintf(OutPutFile,
					"                                                        ");
				}
			}
			fflush(OutPutFile);
		}
		
		Free_PrfAlign(PrfAlignPtr);
		Free_SeqData(SeqDataPtr);

	}
	
	if (FASTA) Free_ReadFASTAFile((TReadFASTAFilePtr)ReadFilePtr);
	else Free_ReadSeqFile((TReadSeqFilePtr)ReadFilePtr);

	Free_PrfData(PrfDataPtr);

	}
	
	if (OutPutFile != stdout) {
		fclose(OutPutFile);
	}
	exit(0);
}
