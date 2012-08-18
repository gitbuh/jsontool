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
  typedef pair<string, var> property;
  typedef bool boolean;
  typedef long double number;
  typedef string string;
  typedef const char* cstring;

  enum ValueType { 
    TYPE_UNDEFINED, 
    TYPE_NULL, 
    TYPE_BOOLEAN, 
    TYPE_NUMBER, 
    TYPE_STRING, 
    TYPE_OBJECT, 
    TYPE_ARRAY 
  };

  class TypeAdapter {
  
    public:
    
    var* value;
    
    ValueType type;
  
    virtual boolean toBoolean(var);
    virtual number  toNumber(var);
    virtual cstring const toString(var);
    virtual Object  toObject(var);
    virtual Array   toArray(var);
    
    TypeAdapter() { type = TYPE_UNDEFINED; }
    
  };

  class NullAdapter: public TypeAdapter { 
    
    public:
  
    NullAdapter(): TypeAdapter() { type = TYPE_NULL; };
    
  };
  
  class BooleanAdapter: public TypeAdapter {
  
    public:
  
    number toNumber(var);
    cstring const toString(var);
    BooleanAdapter(): TypeAdapter() { type = TYPE_BOOLEAN; };
    
  };
  class NumberAdapter: public TypeAdapter {
  
    public:
  
    boolean toBoolean(var);
    cstring const toString(var);
    
    NumberAdapter(): TypeAdapter() { type = TYPE_NUMBER; };
    
  };
  class StringAdapter: public TypeAdapter {
  
    public:
  
    boolean toBoolean(var);
    number toNumber(var);
    
    StringAdapter(): TypeAdapter() { type = TYPE_STRING; };
    
  };
  class ObjectAdapter: public TypeAdapter {
  
    public:
  
    boolean toBoolean(var);
    number toNumber(var);
    cstring const toString(var);
    
    ObjectAdapter(): TypeAdapter() { type = TYPE_OBJECT; };
  
  };
  class ArrayAdapter: public TypeAdapter {
  
    public:
  
    boolean toBoolean(var);
    number toNumber(var);
    cstring const toString(var);
    
    ArrayAdapter(): TypeAdapter() { type = TYPE_ARRAY; };
    
  };
  
  #include "var.h"
  #include "TypeAdapter.h"
  
  ostream& operator<<(ostream &os, const var &value) {
    return os << value.toString();
  }

}
  
#endif

