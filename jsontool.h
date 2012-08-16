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

  class TypeAdapter {
  
    public:
  
    virtual boolean toBoolean(var);
    virtual number  toNumber(var);
    virtual cstring const toString(var);
    virtual Object  toObject(var);
    virtual Array   toArray(var);
    
  };

  class NullAdapter: public TypeAdapter { };
  
  class BooleanAdapter: public TypeAdapter {
  
    public:
  
    number  toNumber(var);
    cstring const toString(var);
    
  };
  class NumberAdapter: public TypeAdapter {
  
    public:
  
    boolean toBoolean(var);
    cstring const toString(var);
    
  };
  class StringAdapter: public TypeAdapter {
  
    public:
  
    boolean toBoolean(var);
    number  toNumber(var);
    
  };
  class ObjectAdapter: public TypeAdapter {
  
    public:
  
    boolean toBoolean(var);
    number  toNumber(var);
    cstring const toString(var);
    // Object  toObject(var);
    // Array   toArray(var);
  
  };
  class ArrayAdapter: public TypeAdapter {
  
    public:
  
    boolean toBoolean(var);
    number  toNumber(var);
    cstring const toString(var);
    // Object  toObject(var);
    // Array   toArray(var);
    
  };
  
  #include "var.h"
  #include "TypeAdapter.h"
  
  ostream& operator<<(ostream &os, const var &value) {
    return os << value.toString();
  }

}
  
#endif

