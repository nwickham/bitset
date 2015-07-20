# Top level makefile

default: all

.DEFAULT:
	cd src && $(MAKE) $@