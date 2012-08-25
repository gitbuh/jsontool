# Make and run unit tests.

# Flags passed to the preprocessor.
CPPFLAGS += -I..

# Flags passed to the C++ compiler.
CXXFLAGS += -std=c++0x

# Build targets.
all : test

test : clean-tests catch.hpp unittests
	./unittests

clean-tests :
	rm -f unittests
	
clean : clean-tests
	rm -f catch.hpp

update : clean catch.hpp

catch.hpp :
	wget https://raw.github.com/philsquared/Catch/master/single_include/catch.hpp

unittests :
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) alltests.cpp -o unittests
