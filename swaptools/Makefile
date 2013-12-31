# Project: swaptools 
include config.mk
MAKEFLAGS	+=	--no-print-directory

TOPDIR		=	$(shell pwd)
export TOPDIR

.PHONY: all install strip clean

all:
	@echo " [INIT] build/"
	@$(MKDIR) build/share/locale
	@$(MKDIR) build/bin
	@echo " [ CD ] src/"
	+@make -C src/
	@echo " [ CD ] po/"
	+@make -C po/
	
	@echo "Build complete."
	@echo 

clean:
	@echo " [ RM ] build/"
	+@rm -Rf bin/
	@echo " [ CD ] po/"
	+@make -C po/ clean
	@echo " [ CD ] src/"
	+@make -C src/ clean
	@echo
	@echo "Source tree cleaned."
	@echo

strip:
	@echo " [STRP] bin/"
	@strip $(LIB)
	@strip bin/darnit-*
	
install: $(INSTARG)
	@$(MKDIR) $(PREFIX)/share/locale
	@$(MKDIR) $(PREFIX)/bin
	@echo
	@echo "Swaptools installed."
	@echo 
