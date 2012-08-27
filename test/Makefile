# Make and run unit tests.

# Flags passed to the preprocessor.
CPPFLAGS += -I..

# Flags passed to the C++ compiler.
CXXFLAGS += -std=c++0x -g

# URL to pull catch.hpp from if not present.
# TODO: change this to point to a particular commit.
CATCHURL = https://raw.github.com/philsquared/Catch/master/single_include/catch.hpp

# Build targets.
all : test

test : clean-tests catch.hpp unittests
	valgrind ./unittests

clean-tests :
	rm -f unittests
	
clean : clean-tests
	rm -f catch.hpp

update : clean catch.hpp

catch.hpp :
	wget $(CATCHURL)

unittests :
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) alltests.cpp -o unittests
