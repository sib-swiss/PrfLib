#   File:       all.make
#   Target:     all
#   Sources:    Alphabet.c
#               GeneralTypes.c
#               PrfAlign.c
#               PrfData.c
#               PrfExtr.c
#               PrfFileData.c
#               ReadFASTAFile.c
#               ReadFile.c
#               ReadPar.c
#               ReadPrfFile.c
#               ReadSeqFile.c
#               srch4prf.c
#				scan4prf.c
#               SeqData.c
#               SeqExtr.c
#               SeqFileData.c
#   Created:    Friday, July 26, 1996 05:13:50 PM

MAKEFILE     = all.make
¥MondoBuild¥ = #{MAKEFILE}  # Make blank to avoid rebuilds when makefile is modified
Includes     =
Sym¥PPC      = -sym on 
ObjDir¥PPC   =

PPCCOptions  = {Includes} {Sym¥PPC} 

Objects¥PPC  = ¶
		"{ObjDir¥PPC}Alphabet.c.x" ¶
		"{ObjDir¥PPC}GeneralTypes.c.x" ¶
		"{ObjDir¥PPC}PrfAlign.c.x" ¶
		"{ObjDir¥PPC}PrfData.c.x" ¶
		"{ObjDir¥PPC}PrfExtr.c.x" ¶
		"{ObjDir¥PPC}PrfFileData.c.x" ¶
		"{ObjDir¥PPC}ReadFASTAFile.c.x" ¶
		"{ObjDir¥PPC}ReadFile.c.x" ¶
		"{ObjDir¥PPC}ReadPar.c.x" ¶
		"{ObjDir¥PPC}ReadPrfFile.c.x" ¶
		"{ObjDir¥PPC}ReadSeqFile.c.x" ¶
		"{ObjDir¥PPC}SeqData.c.x" ¶
		"{ObjDir¥PPC}SeqExtr.c.x" ¶
		"{ObjDir¥PPC}SeqFileData.c.x"

all ÄÄ srch4prf srch4prf.appl scan4prf scan4prf.appl

srch4prf Ä {¥MondoBuild¥} {Objects¥PPC} srch4prf.c.x
	PPCLink ¶
		-o srch4prf {Sym¥PPC} ¶
		{Objects¥PPC} srch4prf.c.x ¶
		-t 'MPST' ¶
		-c 'MPS ' ¶
		-mf ¶
		"{SharedLibraries}InterfaceLib" ¶
		"{SharedLibraries}StdCLib" ¶
		"{SharedLibraries}MathLib" ¶
		"{PPCLibraries}StdCRuntime.o" ¶
		"{PPCLibraries}PPCCRuntime.o" ¶
		"{PPCLibraries}PPCToolLibs.o"

srch4prf.appl Ä {¥MondoBuild¥} {Objects¥PPC} srch4prf.c.x
	PPCLink ¶
		-o srch4prf.appl {Sym¥PPC} ¶
		{Objects¥PPC} srch4prf.c.x ¶
		-t 'APPL' ¶
		-c '????' ¶
		-mf ¶
		"{SharedLibraries}InterfaceLib" ¶
		"{SharedLibraries}StdCLib" ¶
		"{SharedLibraries}MathLib" ¶
		"{PPCLibraries}StdCRuntime.o" ¶
		"{PPCLibraries}PPCCRuntime.o" ¶
		"{PPCLibraries}PPCToolLibs.o"
		
scan4prf Ä {¥MondoBuild¥} {Objects¥PPC} scan4prf.c.x
	PPCLink ¶
		-o scan4prf {Sym¥PPC} ¶
		{Objects¥PPC} scan4prf.c.x ¶
		-t 'MPST' ¶
		-c 'MPS ' ¶
		-mf ¶
		"{SharedLibraries}InterfaceLib" ¶
		"{SharedLibraries}StdCLib" ¶
		"{SharedLibraries}MathLib" ¶
		"{PPCLibraries}StdCRuntime.o" ¶
		"{PPCLibraries}PPCCRuntime.o" ¶
		"{PPCLibraries}PPCToolLibs.o"

scan4prf.appl Ä {¥MondoBuild¥} {Objects¥PPC} scan4prf.c.x
	PPCLink ¶
		-o srch4prf.appl {Sym¥PPC} ¶
		{Objects¥PPC} scan4prf.c.x ¶
		-t 'APPL' ¶
		-c '????' ¶
		-mf ¶
		"{SharedLibraries}InterfaceLib" ¶
		"{SharedLibraries}StdCLib" ¶
		"{SharedLibraries}MathLib" ¶
		"{PPCLibraries}StdCRuntime.o" ¶
		"{PPCLibraries}PPCCRuntime.o" ¶
		"{PPCLibraries}PPCToolLibs.o"