
BINARY_RECORD=Recorder

CFLAGS += # -DTESTMODE -DSTATETESTMODE


RECORD_LIBS = $(AUDIOLIBS)
RECORD_LIBS += -lrt -ldl -lm -lpthread 
RECORD_LIBS += -LAppRecord/arm_audio -lasound -ljack -lportaudio

FILES_RECORD=AppRecord/main.c
FILES_RECORD+=$(wildcard AppRecord/AUDIO/*.c)
OBJS_RECORD=$(FILES_RECORD:.c=.o)

record : record_release
record_release: $(BINARY_RECORD)

$(BINARY_RECORD): Directories $(OBJS_RECORD)
	@echo Compiling  Record
	@echo -----------------
	@$(LC) $(LFLAGS) -o $(OUTDIR)/$(BINARY_RECORD) $(OBJS_RECORD) $(RECORD_LIBS)
	@rm $(OBJS_RECORD)
   
clean:
	rm $(OBJS_RECORD)
	rm -r output
