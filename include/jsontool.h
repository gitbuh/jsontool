/**

 jsontool

 */

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cstdarg>
#include <memory>

namespace jsontool {

using namespace std;

class var;

class Null {
};

static const Null null;

static const Null undefined;

typedef bool boolean;
typedef long double number;
typedef const char* cstring;
typedef string string;

typedef map<string, var> Object;
typedef vector<var> Array;
typedef Object O_;
typedef Array A_;

static inline var parse(string str);
static inline string stringify(var value);

enum ValueType {
  TYPE_UNDEFINED,
  TYPE_NULL,
  TYPE_BOOLEAN,
  TYPE_NUMBER,
  TYPE_STRING,
  TYPE_OBJECT,
  TYPE_ARRAY
};

#include "adapter.h"
#include "compare.h"
#include "variant.h"
#include "parseerror.h"
#include "parser.h"

#include "../src/adapter.cpp"
#include "../src/adapter/array.cpp"
#include "../src/adapter/boolean.cpp"
#include "../src/adapter/null.cpp"
#include "../src/adapter/number.cpp"
#include "../src/adapter/object.cpp"
#include "../src/adapter/string.cpp"
#include "../src/adapter/undefined.cpp"
#include "../src/compare.cpp"
#include "../src/parser.cpp"

static Parser parser;

static inline var parse(string json) {

  return parser.parse(json);

}

static inline string stringify(var value) {

  return value.toJSON();

}

ostream& operator<<(ostream &os, var value) {

  return os << (string)value;

}

}
