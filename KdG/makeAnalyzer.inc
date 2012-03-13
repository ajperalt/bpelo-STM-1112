
ANALYZER_APP=Analyzer

CFLAGS += #DTESTMODE


LIBS_ANALYZER = $(AUDIOLIBS)
LIBS_ANALYZER += -lrt -ldl -lm -lpthread 
LIBS_ANALUZER+= -LAppAnalyzer/arm_audio -lasound -ljack -lportaudio

FILES_APPANALYZER=AppAnalyzer/main.c
FILES_ANALYZER_AUDIO=$(wildcard AppAnalyzer/AUDIO/*.c)
FILES_ANALYZER=$(FILES_APPANALYZER) $(FILES_ANALYZER_AUDIO)
ANALYZER_OBJS=$(FILES_ANALYZER:.c=.o)

analyzer : analyzer_release
analyzer_release: $(ANALYZER_APP)

$(ANALYZER_APP): Directories $(ANALYZER_OBJS)
	@echo Compiling  Analyzer
	@echo -------------------
	@$(LC) $(LFLAGS) -o $(OUTDIR)/$(ANALYZER_APP) $(ANALYZER_OBJS) $(LIBS_ANALYZER)
	@rm $(ANALYZER_OBJS)
   
clean_analyzer:
	rm $(ANALYZER_OBJS)
	rm -r output
