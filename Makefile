# jsontool build targets

all : tests dist

dist : dist/jsontool.h

dist/jsontool.h :
	cd include; ../build.sh

tests :
	cd test; $(MAKE) $(MFLAGS)

update : # update the test harness
	cd test; $(MAKE) $(MFLAGS) update
	
clean : clean-dist clean-test

clean-dist :
	rm -f dist/*
	
clean-test :
	cd test; $(MAKE) $(MFLAGS) clean
	