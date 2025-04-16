/****************************************************************************/
/*																			*/
/*	But: definition des tables d'erreurs									*/
/*																			*/
/****************************************************************************/
/*																			*/
/*	Resume:																	*/
/*																			*/
/*==========================================================================*/
/*	Donnees:							|	Routines						*/
/*==========================================================================*/
/*	RPF_ErrTable						| 	-								*/
/*--------------------------------------------------------------------------*/
/*	PE_ErrTable							|	-								*/
/*--------------------------------------------------------------------------*/
/*	RSF_ErrTable						| 	-								*/
/*--------------------------------------------------------------------------*/
/*	PA_ErrTable							| 	-								*/
/****************************************************************************/

#include "error.h"

#ifndef _ERRTABLE_
#define _ERRTABLE_

/****************************/
/* DEFINITION DES VARIABLES */
/****************************/

/*==================*/
/* Tables d'erreurs */
/*==================*/

/*--------------------------------*/
/* Lecture d'un fichier de profil */
/*--------------------------------*/

TErrTable RPF_ErrTable = {
    "No error",
    "Allocation error",
    "Opening error",
    "Positive integer expected",
    "Number expected",
    "Word expected",
    "Start ' expected",
    "End ' expected",
    "/ expected",
    ": expected",
    "= expected, unexpected end of file",
    "= expected, unexpected end of profile",
    "= expected",
    "Value expected, unexpected end of file",
    "Value expected, unexpected end of profile",
    "Value expected",
    ", or ; expected, unexpected end of file",
    ", or ; expected, unexpected end of profile",
    ", or ; expected",
    "Values number overflow",
    "Assignments number overflow",
    "Descriptions number overflow",
    "Empty profile",
    "Not a profile ID",
    "Word expected, unexpected end of line",
    "Word expected, unexpected end of file",
    ", or ; expected, unexpected end of line",
    "AC number expected, unexpected end of line",
    "AC number expected, unexpected end of file",
    "ID line expected, unexpected end of file",
    "AC line expected, unexpected end of file",
    "AC line expected",
    "MA line expected",
    "MA line expected, unexpected end of profile",
    "MA line expected, unexpected end of file",
	"Description expected, unexpected end of profile",
    "Description expected, unexpected end of file",
	"DE line expected, unexpected end of profile",
    "DE line expected, unexpected end of file",
	"DE line expected"
};

/*------------------------*/
/* Extraction d'un profil */
/*------------------------*/

TErrTable PE_ErrTable = {
	"No error",
	"Allocation error",
	"Priority out of range",
	"Already existing priority",
	"Missing priority",
	"Already existing level",
	"Missing level",
	"Missing zero level",
	"General specifications expected",
	"Alphabet expected",
	"String expected",
	"Illegal value",
	"Positive integer expected",
	"Illegal assignment",
	"Word expected",
	"Illegal word",
	"Disjoint description expected",
	"Disjoint definition expected",
	"Parameter expected",
	"Number expected",
	"Normalization expected",
	"Normalization function expected",
	"Cardinal expected",
	"Already existing normalization mode",
	"Illegal normalization mode",
	"Illegal priority",
	"Normalization mode overflow",
	"Missing normalization mode",
	"Cut-off value expected",
	"Score expected",
	"Integer expected",
	"Normalized score mode expected",
	"Bad normalized scores number",
	"Level overflow",
	"Symbol expected",
	"Bad scores number",
	"Positions overflow",
	"Text expected",
	"Alphabet already defined",
	"Topology already defined",
	"Length already defined",
	"Exclusion already defined",
	"Normalization function already defined",
	"Normalization mode already defined",
	"Text already defined",
	"Priority already defined",
	"Score already defined",
	"Cutoff level already defined",
	"Normalized score already defined",
	"Symbol already defined",
	"Bad profil length",
	"Mode out of range",
	"Protected region bad defined",
	"Protected region out of the profile"
};

/*-----------------------------------*/
/* Lecture d'un fichier de sequences */
/*-----------------------------------*/

TErrTable RSF_ErrTable = {
	"No error",
	"Allocation error",
	"Opening error",
	"Positive integer expected",
	"Number expected",
	"Word expected",
    "Start ' expected",
    "End ' expected",
	"Word expected, unexpected end of line",
	"Word expected, unexpected end of file",
	"Positive integer expected, unexpected end of line",
	"Positive integer expected, unexpected end of file",
	"Bad sequence length",
	"ID line expected, unexpected end of file",
	"SQ line expected, unexpected end of file",
	"SQ line expected",
	"SEQUENCE expected",
	"Description expected, unexpected end of profile",
    "Description expected, unexpected end of file",
	"DE line expected, unexpected end of profile",
    "DE line expected, unexpected end of file",
	"DE line expected",
	"DE lines overflow"
};

/*----------------------------*/
/* Lecture d'un fichier FASTA */
/*----------------------------*/

TErrTable RFF_ErrTable = {
	"No error",
	"Allocation error",
	"Opening error",
	"Positive integer expected",
	"Number expected",
	"Word expected",
    "Start ' expected",
    "End ' expected",
	"Sequence length overflow",
	"ID line expected, unexpected end of file",
	"Sequence expected, unexpected end of file"
};

/*----------------------*/
/* Alignement de profil */
/*----------------------*/

TErrTable PA_ErrTable = {
	"No error",
	"Allocation error",
	"Alignments overflow",
	"Bad disjoint definition",
	"Not protected alignment over the cut-off",
	"Coordinates overflow",
	"Characters overflow"
};

#endif
