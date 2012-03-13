
OUTDIR=../output_igep
BINARY_GUI=Gui

CFLAGS += # -DDEBUG_CONTAINER=2 -DDEBUG=1 -DDEBUG_STATES=2
GUI_LIBS=

FILES_GUI=$(wildcard AppGui/*/*.c) AppGui/gui.c
FILES_GUI+=SerialLib/serial.c
FILES_GUI+=GuiLib/draw.c GuiLib/parameters.c GuiLib/button/button.c GuiLib/component/component.c GuiLib/container/container.c GuiLib/label/label.c GuiLib/spinner/spinner.c GuiLib/circle/circle.c GuiLib/rectangle/rectangle.c GuiLib/oval/oval.c GuiLib/roundrect/roundrect.c
FILES_GUI+=KeysLib/keys.c
FILES_GUI+=IoLib/io.c
FILES_GUI+=EnableLib/enable.c

OBJS_GUI=$(FILES_GUI:.c=.o)

gui: gui_release
gui_release: $(BINARY_GUI)

$(BINARY_GUI): Directories $(OBJS_GUI)
	@echo Compiling  Gui
	@echo --------------k
	@echo $(LFLAGS)
	@$(LC) $(LFLAGS) -o $(OUTDIR)/$(BINARY_GUI) $(OBJS_GUI) $(GUI_LIBS)
	@rm $(OBJS_GUI)

	
clean_gui:
	rm $(OBJS_GUI)
