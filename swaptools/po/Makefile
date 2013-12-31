include $(TOPDIR)/config.mk

.PHONY: all clean

all:
	@echo " Compiling translations..."
	@xgettext -k_ -d swaptools -s -o swaptools.pot ../src/*.c
	@$(MKDIR) sv/LC_MESSAGES
	@msgfmt -o sv/LC_MESSAGES/swaptools.mo sv.po
	
	
	@cp -a */ ../build/share/locale/

clean:
	@rm -Rf */
