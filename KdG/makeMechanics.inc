
OUTDIR=../output_igep
BINARY_MECHANICS=Mechanics

CFLAGS += # 
MECHANICS_LIBS=-lm

MECHANICS_FILES=$(wildcard MECH/*.c)

OBJS_MECHANICS=$(MECHANICS_FILES:.c=.o)

mechanics: mechanics_release
mechanics_release: $(BINARY_MECHANICS)

$(BINARY_MECHANICS): Directories $(OBJS_MECHANICS)
	@echo Compiling  Mechanics
	@echo --------------------
	@$(LC) $(LFLAGS) -o $(OUTDIR)/$(BINARY_MECHANICS) $(OBJS_MECHANICS) $(MECHANICS_LIBS)
	@rm $(OBJS_MECHANICS)

	
clean_mechanics:
	rm $(OBJS_MECHANICS)