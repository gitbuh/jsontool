# Build targets.
all : tests

tests :
	cd test; $(MAKE) $(MFLAGS)
