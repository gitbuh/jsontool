


#include "jsontool.h"

#include <iostream>


using namespace jsontool;

int main(int argc, char *argv[])
{
  
  var testValue = 5.5;
  
  testValue += 5;
  
  Object myMap = {{"fee", 4}, {"foe", 5}};
  
  var testValue2 = {"asdf", 9}; 
  
  var lmno = "dfg";
  
  lmno += "hjkl";
  
  // var myVal = (Object){{"fee", 4}, {"foe", 5}};
  
  var myArray = { lmno, 8, false, testValue, { "asdfsdf", 19 } };
  
  var myObject = (Object){{"fee", 4}, {"foe", {"sdgsdg", 123}}};
  
  // var baz = ;
  
  float foo = testValue;
  
  const char * bar = testValue;

	cout << "Test: " << myArray << "..." << myObject << endl;
	
	cout << myObject["fee"] << endl;
	
	cout << myArray[4] << endl;
	
	return 0;
}


