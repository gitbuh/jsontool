
#include "jsontool.h"
#include "macro.h"

#define A_ jsontool_array
#define O_ jsontool_object

using namespace jsontool;


int main(int argc, char *argv[]) {
  
  
  var myArray = A_("lmno", 8, false, 1);
  
  myArray[1] = 35;
  
  myArray[6] = 2;

  myArray[1] += 4.5;
  
  var grua = myArray[12];
  
	cout << "myArray: " << myArray << endl;

	
  var myObject = O_({"lmno", 8}, {"false", 1});
	
	myObject["boo"] = "asd";
	
	var blah = myObject["blah"];
	
	cout << "myObject: " << myObject << endl;
  
  
	
	return 0;
}


