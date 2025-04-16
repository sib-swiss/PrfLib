/****************************************************************************/
/*																			*/
/*	But: Alignement entre une sequence et une collection de profils			*/
/*																			*/
/****************************************************************************/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/

#ifdef _SUN_
#include <floatingpoint.h>
#endif
#include <stddef.h>
#include <stdio.h>
#include <float.h>
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

/**********/
/* MACROS */
/**********/

/*--------------------------------------------------------------------------*/
/* Impression du format d'appel												*/
/*--------------------------------------------------------------------------*/
void Print_Format()\
{
	fprintf(stderr, "\
	Usage:\nsrch4prf -s seq_library_file  [-p profile_file] [-i profile_ID]\n\
[-l cut_off_level] [-o output_file] [-f] [-a] [-b] [-y] [-u] [-t] [-x]\n\n");
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
	TScore CutOff;					/* Valeur de coupure					*/
	TBoolean SelectAll;				/* Parametre de selection				*/
	TBoolean ReportAlign;			/* Reporte les alignements				*/
	TBoolean ReportCoord;			/* Reporte les coordonnees d'align.		*/
	TBoolean Unique;				/* Trouve seulement le meill. ali.		*/
	TBoolean UniqueForced;			/* Unique force							*/
	TBoolean FASTA;					/* Format FASTA ou non					*/
	TBoolean ComplStr;				/* Teste les sequences complementaires	*/
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
	
	TPrfAlignPtr PrfAlignPtr;				/* Donnee d'alignation			*/
	TAlignListPtr AlignListPtr;				/* Liste des alignements		*/
	TPrfAlignPtr PrfAlignResPtr;			/* Resultat de l'algorithme		*/
	TPathMatrixPtr PathMatrixPtr;			/* Matrice de chemin			*/
	TAlignPtr AlignPtr;						/* Alignement particulier		*/
	TAlignIndex AlignIndex;					/* Index d'alignement			*/
	TCoordVectPtr CoordVectPtr;				/* Vecteur de coordonnees		*/
	TCoordVectPtr TempCoordVectPtr;			/* Vecteur de coordonnees		*/
	TAliStrPtr AliStrPtr;					/* Chaine d'alignement			*/
	TAliStrPtr TempAliStrPtr;				/* Chaine d'alignement			*/

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
	TDisjointDef DisjointDef;		/* Definition de l'exclusion			*/
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
	PrfId = NULL;
	CutOffLevelDouble = DBL_MIN;
	CutOffLevel = 0;
	SelectAll = FALSE;
	ReportAlign = FALSE;
	ReportCoord = FALSE;
	UniqueForced = FALSE;
	TestProt = FALSE;
	FASTA = FALSE;
	ComplStr = FALSE;
	OutPutFile = stdout;

	if (argc < 2) {
		ParFile = fopen("srch4prf.par", "r");
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
				CutOffLevel = (TCutOffIndex)CutOffLevelDouble;
				if ((double)CutOffLevel != CutOffLevelDouble) {
					/* Erreur de format */
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
			case 'x':
				/* Report des coordonnees */
				if ((ParStr) || (ReportCoord)) {
					/* Erreur de format */
					Print_Format();
					exit(1);
				}
				ReportCoord = TRUE;
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
		/* Erreur de format */
		Print_Format();
		exit(1);
	}

	/* Verification utilite de la valeur de coupure */
	if (SelectAll && Unique && (CutOffLevelDouble != DBL_MIN)) {
		Print_Format();
		exit(1);
	}

	/* Exclusion affichage alignement et coordonnees */
	if (ReportCoord && ReportAlign) {
		Print_Format();
		exit(1);
	}

	/* Exclusion test des alignements et exclusion = unique */
	if ((TestProt) && (UniqueForced)) {
		Print_Format();
		exit(1);
	}
		
	for (TestIndex = 0; TestIndex < TEST_NBR; TestIndex++) {
	
	/*========================*/
	/* Lecture de la sequence */
	/*========================*/

	/*---------------------------------------*/
	/* Initialisation des donnees de lecture */
	/*---------------------------------------*/

	if (FASTA) ReadFilePtr = (TReadFilePtr)I_ReadFASTAFile(
	SeqFilename, &ErrIndex);
	else ReadFilePtr = (TReadFilePtr)I_ReadSeqFile(SeqFilename, &ErrIndex);

	if (!ReadFilePtr) {
		fprintf(stderr, "Sequences file reading initialization error:\n");
		Print_ErrStr(ErrTable_ErrStrNth(RSF_ErrTable, ErrIndex));
		fprintf(stderr, "\n");
		exit(1);
	}

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
		fprintf(stderr, "Sequences file reading error:\n");
		if (FASTA) {
			Print_ErrStr(ErrTable_ErrStrNth(RFF_ErrTable, ErrIndex));
		}
		else {
			Print_ErrStr(ErrTable_ErrStrNth(RSF_ErrTable, ErrIndex));
		}
		fprintf(stderr, "\n");
		return;
	}
	Free_ReadFile(ReadFilePtr);
	
	/*=================================================*/
	/* Initialisation des donnees de lecture du profil */
	/*=================================================*/
	
	ReadPrfFilePtr = I_ReadPrfFile(PrfFilename, &ErrIndex);
	if (!ReadPrfFilePtr) {
		fprintf(stderr, "Profile file reading initialization error:\n");
		Print_ErrStr(ErrTable_ErrStrNth(RPF_ErrTable, ErrIndex));
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
	printf("Program:      srch4prf\n");
	printf("Version:      v1.00\n");
	printf("Author:       Nicolas Moeri\n");
	printf("Description:  Compares a sequence against a profiles database\n");
	printf("\n");
	printf("Infinite negative score is %d\n", PD_INFINITE);
	printf("\n");
	fflush(stdout);

	/*------------------------*/
	/* Parametres utilisateur */	
	/*------------------------*/
	
	fprintf(OutPutFile, "Profiles database:    %s\n", PrfFilename);
	fprintf(OutPutFile, "Sequences database:   %s\n", SeqFilename);
	fprintf(OutPutFile, "Sequence name:        ");
	Out_SeqId(OutPutFile, SeqFileData_Id(SeqFileDataPtr));
	fprintf(OutPutFile, "\n");
	fprintf(OutPutFile, "Sequence description: ");
	Out_Sent20(OutPutFile, SeqFileData_De((SeqFileDataPtr)));
	fprintf(OutPutFile, "\n\n");
	
	/*---------------------*/
	/* En-tete du resultat */
	/*---------------------*/

	fprintf(OutPutFile, "Alignments results\n");
	fprintf(OutPutFile, "==================\n");
	if ((!ReportAlign) && (!ReportCoord)) {
		fprintf(OutPutFile,
		"\nProfile name           Description                 Hits  Score  Position       \n");
		fprintf(OutPutFile,
		  "-------------------------------------------------------------------------------\n");
	}
	fflush(OutPutFile);
	
	/*===================*/
	/* Boucle de lecture */
	/*===================*/

	while(TRUE) {

		/*====================*/
		/* Lecture du profil */
		/*====================*/

		/*------------------------------------------*/	
		/* Lecture des donnees du fichier de profil */
		/*------------------------------------------*/	

		PrfFileDataPtr = ReadPrfFile_PrfFileData(ReadPrfFilePtr, PrfId,
		&ErrIndex);
		if (!PrfFileDataPtr) {
			if (!PrfId && (ErrIndex == RPF_ID_EXP_UEOF)) {
                /* Fin du fichier: on sort de la boucle */
                break;
			}
			fprintf(stderr, "Profile file reading error:\n");
			Print_ErrStr(ErrTable_ErrStrNth(RPF_ErrTable, ErrIndex));
			fprintf(stderr, "\n");
			exit(1);
		}

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
		Free_PrfFileData(PrfFileDataPtr);
		Free_PrfExtr(PrfExtrPtr);
		
		/*-------------------------*/
		/* Recherche de l'alphabet */
		/*-------------------------*/
	
		AlphPtr = GenSpec_Alph(PrfData_GenSpec(PrfDataPtr));

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
	
		/*-----------------------------------*/
		/* Recherche de la valeur de coupure */
		/*-----------------------------------*/

		/* Controle du debordement du niveau de valeur de coupure */
		CutOffListPtr = PrfData_CutOffList(PrfDataPtr);
		if (CutOff_Level(CutOffList_CutOffNth(CutOffListPtr, 0)) >
		CutOffLevel) {
			CutOffLevelUsed =
			CutOff_Level(CutOffList_CutOffNth(CutOffListPtr, 0));
		}
		else if (CutOff_Level(CutOffList_CutOffNth(CutOffListPtr,
		CutOffList_CutOffNbr(CutOffListPtr) - 1)) < CutOffLevel) {
			CutOffLevelUsed = CutOff_Level(CutOffList_CutOffNth(CutOffListPtr,
			CutOffList_CutOffNbr(CutOffListPtr) - 1));
		}
		else {
			CutOffLevelUsed = CutOffLevel;
		}
		CutOff = CutOff_Score(CutOffList_CutOffNth(PrfData_CutOffList
		(PrfDataPtr), CutOffLevelUsed));
	
		/*=========================*/
		/* Creation de la sequence */
		/*=========================*/

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
				Print_ErrStr("Alignments flow");
				fprintf(stderr, "\n");
				exit(1);
			}
			/* Ajout */
			AlignList_AddAlign(AlignListPtr, BestCplAlignPtr);
		}

		/* Affichage */
		if ((ReportAlign) || (ReportCoord)) {
			if (ComplStr) {
				/* Retour a la sequence initiale */
				MolSeqPtr = MolSeq_CplStrand(SeqData_MolSeq(SeqDataPtr),
				SeqData_Alph(SeqDataPtr));
			}
			fprintf(OutPutFile, "\n");
			Out_PrfId(OutPutFile, PrfData_Id(PrfDataPtr));
			fprintf(OutPutFile, ", ");
			Out_De45(OutPutFile, SeqData_De(SeqDataPtr));
			fprintf(OutPutFile, ", Hits: ");
			Out_AlignIndex(OutPutFile, HitNbr);
			fprintf(OutPutFile,
			"\n-------------------------------------------------------------------------------\n");
		}
		else {
			Out_PrfId(OutPutFile, PrfData_Id(PrfDataPtr));
			fprintf(OutPutFile, "  ");
			Out_De26(OutPutFile, SeqData_De(SeqDataPtr));
			fprintf(OutPutFile, "  ");
			Out_AlignIndex(OutPutFile, HitNbr);
			fprintf(OutPutFile, "  ");
		}
			
		for (AlignIndex = 0; AlignIndex < AlignList_AlignNbr(AlignListPtr);
		AlignIndex++) {
			AlignPtr = AlignList_AlignNth(AlignListPtr, AlignIndex);
			
			if ((ReportAlign) || (ReportCoord)) {
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
			}
			if (ReportAlign) {
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
			else if (ReportCoord) {

				/* Construction du vecteur de coordonnees */
				CoordVectPtr = I_CoordVect(PathMatrix_RowNbr(PathMatrixPtr)
				+ PathMatrix_ColumnNbr(PathMatrixPtr) - 1);
				if (!CoordVectPtr) {
					/* Erreur d'allocation */
					fprintf(stderr, "Coordinates vector allocation error\n");
					exit(1);
				}

				/* Calcul du vecteur de coordonnees */
				TempCoordVectPtr = CoordVect_FromPathMatrix(
				CoordVectPtr, PathMatrixPtr, &ErrIndex);
				if (!TempCoordVectPtr) {
					/* Erreur dans le calcul du vecteur de coord. */
					fprintf(stderr,
					"Coordinates vector calculation error:\n");
					Print_ErrStr(ErrTable_ErrStrNth(PA_ErrTable, ErrIndex));
					fprintf(stderr, "\n");
					exit(1);
				}

				/* Affichage du vecteur de coordonnees */
				Out_CoordVect(OutPutFile, CoordVectPtr);
			
				/* Destruction du vecteur de coordonnees */
				Free_CoordVect(CoordVectPtr);
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
		Free_PrfData(PrfDataPtr);
		Free_SeqData(SeqDataPtr);
		if (PrfId) {
			/* On ne test qu'un seul profil */
			break;
		}

	}	
	Free_ReadPrfFile(ReadPrfFilePtr);
	Free_SeqFileData(SeqFileDataPtr);

	}
	
	if (OutPutFile != stdout) {
		fclose(OutPutFile);
	}
	exit(0);
}
