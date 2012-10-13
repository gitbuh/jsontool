# Make and run unit tests.

# Flags passed to the preprocessor.
CPPFLAGS += -I../include -I. -Isrc

# Flags passed to the C++ compiler.
CXXFLAGS += -std=c++0x -g

# URL to pull Catch test harness from if not present.
# TODO: change this to point to a particular commit.
CATCHURL = https://raw.github.com/philsquared/Catch/master/single_include/catch.hpp

# Build targets.
all : test

test : catch.hpp unittests
	valgrind --leak-check=full ./unittests	

catch.hpp :
	wget $(CATCHURL)

unittests :
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) src/all.cpp -o unittests

update : clean-catch catch.hpp

clean-tests :
	rm -f unittests

clean-catch :
	rm -f catch.hpp
	
clean : clean-tests