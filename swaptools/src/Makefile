# Project: swaptools
include $(TOPDIR)/config.mk

BINOUT		=	../build/bin/swaptools

SRCFILES	=	$(wildcard *.c)
OBJFILES	=	$(SRCFILES:.c=.o)
.PHONY: all clean

all: $(OBJFILES)
	@echo " [ LD ] $(BINOUT)"
	@$(CC) -o $(BINOUT) $(OBJFILES) $(LDFLAGS)
	@echo "Done."
	@echo 

clean:
	@echo
	@echo " [ RM ] $(OBJFILES)"
	@$(RM) $(OBJFILES)
	@echo " [ RM ] $(BINOUT)"
	@$(RM) $(BINOUT)
	@echo "Done."
	@echo 

%.o: %.c %.h
	@echo " [ CC ] src/$<"
	@$(CC) $(CFLAGS) -c -o $@ $<
