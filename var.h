class var {

  public:

  ValueType type;
  
  TypeAdapter *adapter;
  
  boolean booleanValue;
  
  string stringValue;
  
  number numberValue;
  
  Object objectValue;
  
  Array arrayValue;
  
  
  // initializers
  
  
  void setFromBoolean(boolean value) {
  
    type = TYPE_BOOLEAN;
    booleanValue = value;
    adapter = new BooleanAdapter();
    
  }
  
  void setFromNumber(number value) {
  
    type = TYPE_NUMBER;
    numberValue = value;
    // delete adapter;
    adapter = new NumberAdapter();
    
  }
  
  void setFromString(string value) {
  
    type = TYPE_STRING;
    stringValue = value;
    adapter = new StringAdapter();
    
  }
  
  void setFromObject(Object value) {
  
    type = TYPE_OBJECT;
    objectValue = value;
    adapter = new ObjectAdapter();
    
  }
  
  void setFromArray(Array value) {
  
    type = TYPE_ARRAY;
    arrayValue = value;
    adapter = new ArrayAdapter();
    
  }
  
  cstring toString() const {
  
    return adapter->toString(*this);
  
  }
  
  // cast to other types
  
  operator number() const { 
    return numberValue;
  }
  
  operator string() const { 
    return toString();
  }
  
  operator cstring() const { 
    return toString();
  }
  
  operator Object() const { 
    return objectValue;
  }
  
  operator Array() const { 
    return arrayValue;
  }
  
  // operators
  
  var operator += (const var &rhs) {
    if (isNumber())
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
    stringValue = "undefined";
  
  }
  
  var(bool value) {
  
    setFromBoolean(value);
  
  }
  
  var(long double value) {
  
    setFromNumber(value);
  
  }
  
  var(double value) {
  
    setFromNumber(value);
  
  }
  
  var(long value) {
  
    setFromNumber(value);
  
  }
  
  var(int value) {
  
    setFromNumber(value);
  
  }
  
  var(unsigned value) {
  
    setFromNumber(value);
  
  }
  
  var(unsigned long value) {
  
    setFromNumber(value);
  
  }
  
  var(cstring value) {
    
    setFromString(value);
  
  }
  
  var(Object value) {
    
    setFromObject(value);
  
  }
  
  var(Array value) {
    
    setFromArray(value);
  
  }
  
  var(initializer_list<var> value) {
  
    cout << "initializer_list" << endl;
    
    setFromArray((vector<var>)value);
  
  }
  
  
  // type checks (for convenience)
  
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
