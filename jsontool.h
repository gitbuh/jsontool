/**

jsontool

*/

#ifndef jsontool_h
#define jsontool_h 1

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

namespace jsontool {

  using namespace std;

  class var;

  typedef map<string, var> Object;
  typedef vector<var> Array;
  typedef bool boolean;
  typedef long double number;
  typedef string string;
  typedef const char * cstring;

  enum ValueType { TYPE_UNDEFINED, TYPE_NULL, TYPE_BOOLEAN, TYPE_NUMBER, TYPE_STRING, TYPE_OBJECT, TYPE_ARRAY };

  #include "var.h"
  #include "TypeAdapter.h"
  #include "TypeAdapter/BooleanAdapter.h"
  #include "TypeAdapter/NumberAdapter.h"
  #include "TypeAdapter/StringAdapter.h"
  #include "TypeAdapter/ObjectAdapter.h"
  #include "TypeAdapter/ArrayAdapter.h"
  
  ostream& operator<<(ostream &os, const var &value) {
    return os << value.stringValue;
  }

}

#endif

