CC=gcc
LC=$(CC)

CFLAGS = -c -Wall -DLINUX

OUTDIR=../output_igep

include makeGui.inc
include makeMechanics.inc
include makeAnalyzer.inc
include makeRecord.inc

all: Directories gui mechanics analyzer record


Directories:
	@test -d $(OUTDIR) || mkdir $(OUTDIR)


%.o: %.c
	@$(CC) $(CFLAGS) $< -o $@
	
clean: clean_gui clean_mechanics clean_record clean_analyzer
