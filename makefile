CC		=	gcc
OBJS	= 	Alphabet.o \
			GeneralTypes.o \
			PrfAlign.o \
			PrfData.o \
			PrfExtr.o \
			PrfFileData.o \
			ReadFile.o \
			ReadFASTAFile.o \
			ReadPar.o \
			ReadPrfFile.o \
			ReadSeqFile.o \
			SeqData.o \
			SeqExtr.o \
			SeqFileData.o

INC	= /usr/include
CFLAGS  = -g -c -I$(INC) # -D_SUN_ # Uncomment -D_SUN_ for SunOS

LIB     = -lm

all:	scan4prf srch4prf

scan4prf:		$(OBJS) scan4prf.o
				$(CC) $(OBJS) scan4prf.o -o scan4prf -g -L/usr/lib $(LIB)

srch4prf:		$(OBJS) srch4prf.o
				$(CC) $(OBJS) srch4prf.o -o srch4prf -g -L/usr/lib $(LIB)

Alphabet.o:			Alphabet.c
					$(CC) $(CFLAGS) Alphabet.c
GeneralTypes.o:		GeneralTypes.c
					$(CC) $(CFLAGS) GeneralTypes.c
PrfAlign.o:			PrfAlign.c
					$(CC) $(CFLAGS) PrfAlign.c
PrfData.o:			PrfData.c
					$(CC) $(CFLAGS) PrfData.c
PrfExtr.o:			PrfExtr.c
					$(CC) $(CFLAGS) PrfExtr.c
PrfFileData.o:		PrfFileData.c
					$(CC) $(CFLAGS) PrfFileData.c
ReadFASTAFile.o:	ReadFASTAFile.c
					$(CC) $(CFLAGS) ReadFASTAFile.c
ReadFile.o:			ReadFile.c
					$(CC) $(CFLAGS) ReadFile.c
ReadPar.o:			ReadPar.c
					$(CC) $(CFLAGS) ReadPar.c
ReadPrfFile.o:		ReadPrfFile.c
					$(CC) $(CFLAGS) ReadPrfFile.c
ReadSeqFile.o:		ReadSeqFile.c
					$(CC) $(CFLAGS) ReadSeqFile.c
SeqData.o:			SeqData.c
					$(CC) $(CFLAGS) SeqData.c
SeqExtr.o:			SeqExtr.c
					$(CC) $(CFLAGS) SeqExtr.c
SeqFileData.o:		SeqFileData.c
					$(CC) $(CFLAGS) SeqFileData.c
scan4prf.o:			scan4prf.c
					$(CC) $(CFLAGS) scan4prf.c
srch4prf.o:			srch4prf.c
					$(CC) $(CFLAGS) srch4prf.c

# DO NOT DELETE THIS LINE -- make depend depends on it.
