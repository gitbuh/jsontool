class var {
  
  public:

  ValueType type;
  
  boolean booleanValue;
  
  string stringValue;
  
  number numberValue;
  
  Object objectValue;
  
  Array arrayValue;
  
  long length;
  
  // string builders
  
  string numberToString(number value) {
    ostringstream ss;
    if (!(ss << value))
      return "NaN";
    return ss.str();
  }
  
  string arrayToString(Array value) {
  
    ostringstream ss;
    
    long size = value.size();
    
    ss << "[";
      
    for (Array::iterator it = value.begin(); it != value.end(); ++it) {
    
      cstring item = *it;
    
      if (it != value.begin())
        ss << ", ";
    
      if (it->isString()) {
      
        ss << "\"" << item << "\"";
      
      }
      
      else {
      
        ss << item;
      
      }
    
    } 
    
    ss << "]";
    
    return ss.str();
  
  }
  
  string objectToString(Object value) {
  
    ostringstream ss;
    
    ss << "{";

    // show content:
    
    for (Object::iterator it = value.begin(); it != value.end(); ++it) {
    
      if (it != value.begin())
        ss << ", ";
        
      ss << "\"" << it->first << "\":" << (cstring)(it->second);
    }
    
    
    ss << "}";
    
    return ss.str();
  
  }
  
  // initializers
  
  
  void setFromBoolean(boolean value) {
  
    type = TYPE_BOOLEAN;
    booleanValue = value;
    numberValue = value ? 1 : 0;
    stringValue = value ? "true" : "false";
    length = 0;
    
  }
  
  void setFromNumber(number value) {
  
    type = TYPE_NUMBER;
    booleanValue = value == 0 ? true : false;
    numberValue = value;
    stringValue = numberToString(value);
    length = 0;
    
  }
  
  void setFromString(string value) {
  
    type = TYPE_STRING;
    stringValue = value;
    
    istringstream in(value);
    in >> numberValue;
    
    booleanValue = numberValue == 0 ? true : false;
    length = stringValue.length();
    
  }
  
  void setFromObject(Object value) {
  
    type = TYPE_OBJECT;
    objectValue = value;
    arrayValue.clear();
    booleanValue = true;
    numberValue = 1.0;
    length = 0;
    stringValue = objectToString(value);
    
  }
  
  void setFromArray(Array value) {
  
    type = TYPE_ARRAY;
    arrayValue = value;
    objectValue.clear();
    booleanValue = true;
    numberValue = 1.0;
    length = value.size();
    stringValue = arrayToString(value);
    
  }
  
  string toString() {
    return stringValue;
  }
  
  // cast to other types
  
  operator number() const { 
    return numberValue;
  }
  
  operator string() const { 
    return stringValue;
  }
  
  operator cstring() const { 
    return stringValue.c_str();
  }
  
  operator Object() const { 
    return objectValue;
  }
  
  operator Array() const { 
    return arrayValue;
  }
  
  // operators
  
  var operator += (const var &rhs) {
    if (type == TYPE_NUMBER)
      setFromNumber(numberValue + rhs.numberValue);
    else
      setFromString(stringValue + rhs.stringValue);
    return *this;
  }
  
  var operator -= (const var &rhs) {
    setFromNumber(numberValue - rhs.numberValue);
    return *this;
  }
  
  var operator *= (const var &rhs) {
    setFromNumber(numberValue * rhs.numberValue);
    return *this;
  }
  
  var operator /= (const var &rhs) {
    setFromNumber(numberValue / rhs.numberValue);
    return *this;
  }
  
  var operator [] (const cstring key) {
    return objectValue[key];
  }
  
  var operator [] (const int key) {
    return arrayValue[key];
  }
  
  
  // ctors

  
  var() {
  
    type = TYPE_UNDEFINED;
    booleanValue = false;
    numberValue = 0;
    stringValue = "undefined";
    length = 0;
  
  }
  
  var(bool value) {
  
    cout << "bool: " << value << endl;
  
    setFromBoolean(value);
  
  }
  
  var(long double value) {
  
    cout << "long double: " << value << endl;
  
    setFromNumber(value);
  
  }
  
  var(double value) {
  
    cout << "double: " << value << endl;
  
    setFromNumber(value);
  
  }
  
  var(long value) {
  
    cout << "long: " << value << endl;
  
    setFromNumber(value);
  
  }
  
  var(int value) {
  
    cout << "int: " << value << endl;
  
    setFromNumber(value);
  
  }
  
  var(unsigned value) {
  
    cout << "unsigned: " << value << endl;
  
    setFromNumber(value);
  
  }
  
  var(unsigned long value) {
  
    cout << "unsigned long: " << value << endl;
  
    setFromNumber(value);
  
  }
  
  var(cstring value) {
  
    cout << "cstring: " << value << endl;
    
    setFromString(value);
  
  }
  
  var(Object value) {
  
    cout << "Object" << endl;
    
    setFromObject(value);
  
  }
  
  var(Array value) {
  
    cout << "Array" << endl;
    
    setFromArray(value);
  
  }
  
  var(initializer_list<var> value) {
  
    cout << "initializer_list" << endl;
    
    setFromArray((vector<var>)value);
  
  }
  
  
  // type checks
  
  bool isNull() {
  
    return type == TYPE_NULL;
  
  }
  bool isBoolean() {
  
    return type == TYPE_BOOLEAN;
  
  }
  bool isNumber() {
  
    return type == TYPE_NUMBER;
  
  }
  bool isString() {
  
    return type == TYPE_STRING;
  
  }
  bool isObject() {
  
    return type == TYPE_OBJECT;
  
  }
  bool isArray() {
  
    return type == TYPE_ARRAY;
  
  }

};

