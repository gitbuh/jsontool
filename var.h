class var {

  public:
  
  TypeAdapter* adapter;
  
  boolean booleanValue;
  
  number numberValue;
  
  string stringValue;
  
  shared_ptr<Object> objectValue;
  
  shared_ptr<Array> arrayValue;
  
  //
  
  Object tempKeys;
  
  var* parent;
  
  bool isTempArrayMember;
  
  bool isTempObjectMember;
  
  unsigned tempArrayKey;
  
  string tempObjectKey;
  
  //
  
  
  // initializers
  
  
  void reset() {
  
    booleanValue = false;
    numberValue = 0;
    stringValue = "null"; // "undefined";
    objectValue = shared_ptr<Object>(new Object());
    arrayValue = shared_ptr<Array>(new Array());
  }
  
  void init() {
    
    isTempArrayMember = false;
    isTempObjectMember = false;
    //adapter = new TypeAdapter();
    adapter = getAdapter(TYPE_UNDEFINED);
  }
  
  void setFromVariant(const var &value) {
  
    reset();
    adapter = getAdapter(TYPE_UNDEFINED);
    copy(value);
    
  }
  
  void setFromUndefined() {
  
    reset();
    adapter = getAdapter(TYPE_UNDEFINED);
    
  }
  
  void setFromNull() {
  
    reset();
    stringValue = "null";
    adapter = getAdapter(TYPE_NULL);
    
  }
  
  void setFromBoolean(boolean value) {
  
    reset();
    booleanValue = value;
    adapter = getAdapter(TYPE_BOOLEAN);
    
  }
  
  void setFromNumber(number value) {
  
    reset();
    numberValue = value;
    adapter = getAdapter(TYPE_NUMBER);
    
  }
  
  void setFromString(string value) {
  
    reset();
    stringValue = value;
    adapter = getAdapter(TYPE_STRING);
    
  }
  
  void setFromObject(Object value) {
  
    reset();
    objectValue = shared_ptr<Object>(new Object(value));
    adapter = getAdapter(TYPE_OBJECT);
    
  }
  
  void setFromArray(Array value) {
  
    reset();
    Array v = value;
    arrayValue = shared_ptr<Array>(new Array(value));
    adapter = getAdapter(TYPE_ARRAY);
    
  }
  
  // adapter wrappers
  
  string toString() {
  
    return adapter->toString(this);
  
  }
  
  number toNumber() {
  
    return adapter->toNumber(this);
  
  }
  
  
  // cast operators
  
  operator number() const { 
    return numberValue;
  }
  
  operator string()  { 
    return toString();
  }
  
  operator Object() const { 
    return *objectValue;
  }
  
  operator Array() const { 
    return *arrayValue;
  }
  
  // operators
  
  void checkTempMember() {
  
      if (isTempArrayMember) {
        isTempArrayMember = false;
        parent->arrayValue->resize(tempArrayKey + 1);
        (*parent->arrayValue)[tempArrayKey] = *this;
        parent->tempKeys.erase((string)(var)tempArrayKey);
      } else if (isTempObjectMember) {
        isTempObjectMember = false;
        (*parent->objectValue)[tempObjectKey] = *this;
        parent->tempKeys.erase(tempObjectKey);
      }
      
  }
  
  void copy(var source) {
  
      adapter = source.adapter;
  
      booleanValue = source.booleanValue;
      
      numberValue = source.numberValue;
      
      stringValue = source.stringValue;
      
      objectValue = source.objectValue;
      
      arrayValue = source.arrayValue;
      
  }
  
  template <typename T>
  bool operator == (T val) {
       
    var rhs = val;
     
    // debug
    cout << " ==: " << rhs << " : " << rhs.adapter->type << endl;
    
    // ES5 11.9.3 The Abstract Equality Comparison Algorithm
    // The comparison x == y, where x and y are values, produces true or false. Such a comparison is performed as follows:

    // 1. If Type(x) is the same as Type(y), then
    if (adapter->type == rhs.adapter->type) {
    
      // debug
      cout << " ==: operands are the same type" << endl;
    
      // 1. If Type(x) is Undefined, return true.
      if (isUndefined()) return true;
      
      // 2. If Type(x) is Null, return true.
      if (isNull()) return true;
      
      // 3. If Type(x) is Number, then
      if (isNumber()) {
    
        // 1. If x is NaN, return false.
        // 2. If y is NaN, return false.
        
        // (TODO: NaN checks?)
        
        // 3. If x is the same Number value as y, return true.
        if (numberValue == rhs.numberValue) return true;
        
        // 4. If x is +0 and y is -0, return true.
        if (numberValue == +0 && rhs.numberValue == -0) return true;
        
        
        // 5. If x is -0 and y is +0, return true.
        if (numberValue == -0 && rhs.numberValue == +0) return true;
        
        // 6. Return false.
        return false;
        
      }
      
	    // 4. If Type(x) is String, then return true if x and y are exactly the same sequence of characters 
	    //    (same length and same characters in corresponding positions). Otherwise, return false.
      if (isString()) return stringValue == rhs.stringValue;
      
	    // 5. If Type(x) is Boolean, return true if x and y are both true or both false. Otherwise, return false.
      if (isBoolean()) return booleanValue == rhs.booleanValue;
	    
	    // 6. Return true if x and y refer to the same object. Otherwise, return false.
      if (isObject()) return objectValue == rhs.objectValue;
      if (isArray()) return arrayValue == rhs.arrayValue;
      
      return false;
    
    }
    // 2. If x is null and y is undefined, return true.
    if (isNull() && rhs.isUndefined()) return true;
      
    // 3. If x is undefined and y is null, return true.
    if (isUndefined() && rhs.isNull()) return true;
    
    // 4. If Type(x) is Number and Type(y) is String, return the result of the comparison x == ToNumber(y).
    if (isNumber() && rhs.isString()) return numberValue == rhs.toNumber();
    
    
    // 5. If Type(x) is String and Type(y) is Number, return the result of the comparison ToNumber(x) == y.
    if (isString() && rhs.isNumber()) return toNumber() == rhs;
    
    
    // 6. If Type(x) is Boolean, return the result of the comparison ToNumber(x) == y.
    if (isBoolean()) return toNumber() == rhs;
    
    // 7. If Type(y) is Boolean, return the result of the comparison x == ToNumber(y).
    if (rhs.isBoolean()) return toNumber() == rhs.toNumber();
    
    
    // 8. If Type(x) is either String or Number and Type(y) is Object, return the result of the comparison x == ToPrimitive(y).
    if ((isString() || isNumber()) && (rhs.isObject() || rhs.isArray())) return toString() == rhs.toString();
    
    
    // 9. If Type(x) is Object and Type(y) is either String or Number, return the result of the comparison ToPrimitive(x) == y.
    if ((isObject() || isArray()) && (rhs.isString() || rhs.isNumber())) return toString() == rhs.toString();
    
    // 10. Return false.
    return false;
      
  }
  
  template <typename T>
  bool operator != (T val) {
    return !(*this == val);
  }
  
  var operator = (var rhs) {
    
      copy(rhs);
      
      checkTempMember();
    
    return *this;
  }
  
  var operator += (var rhs) {
    numberValue += rhs.numberValue;
    stringValue += rhs.stringValue;
    return *this;
  }
  
  var operator -= (var rhs) {
    numberValue -= rhs.numberValue;
    return *this;
  }
  
  var operator *= (var rhs) {
    numberValue *= rhs.numberValue;
    return *this;
  }
  
  var operator /= (var rhs) {
    numberValue /= rhs.numberValue;
    return *this;
  }
  
  var &operator [] (const string key) {
  
    if (!objectValue->count(key)) {
    
      tempKeys[key] = var();
      tempKeys[key].isTempObjectMember = true;
      tempKeys[key].parent = this;
      tempKeys[key].tempObjectKey = key;
      
      return tempKeys[key];
      
    }
    
    return (*objectValue)[key];
  }
  
  var &operator [] (const int key) {
    
    if ((unsigned)key >= arrayValue->size()) {
    
      string k = (var)key;
      tempKeys[k] = var();
      tempKeys[k].isTempArrayMember = true;
      tempKeys[k].parent = this;
      tempKeys[k].tempArrayKey = key;
      
      return tempKeys[k];
      
    }
    
    return (*arrayValue)[key];
    
  }
  
  TypeAdapter* getAdapter(ValueType type) {

    static map<ValueType, TypeAdapter*> adapters;
    
    if (adapters.empty()) {
    
      static TypeAdapter a;
      static NullAdapter b;
      static BooleanAdapter c;
      static NumberAdapter d;
      static StringAdapter e;
      static ObjectAdapter f;
      static ArrayAdapter g;

      adapters[TYPE_UNDEFINED] = &a;
      adapters[TYPE_NULL] = &b;
      adapters[TYPE_BOOLEAN] = &c;
      adapters[TYPE_NUMBER] = &d;
      adapters[TYPE_STRING] = &e;
      adapters[TYPE_OBJECT] = &f;
      adapters[TYPE_ARRAY] = &g;
        
    }
    
    return adapters[type];
    
  }
  
  // ctors

  var() {
  
    init();
    reset();
  
  }

  var(Null) {
  
    init();
    reset();
  
  }
  
  var(bool value) {
  
    init();
    setFromBoolean(value);
  
  }
  
  var(long double value) {
  
    init();
    setFromNumber(value);
  
  }
  
  var(double value) {
    
    init();
    setFromNumber(value);
  
  }
  
  var(long value) {
    
    init();
    setFromNumber(value);
  
  }
  
  var(int value) {
  
    init();
    setFromNumber(value);
  
  }
  
  var(unsigned value) {
  
    init();
    setFromNumber(value);
  
  }
  
  var(unsigned long value) {
  
    init();
    setFromNumber(value);
  
  }
  
  var(cstring value) {
   
    init();
    setFromString(value);
  
  }
  
  var(Object value) {
    
    init();
    setFromObject(value);
  
  }
  
  var(Array value) {
    
    init();
    setFromArray(value);
  
  }
  
  
  // type checks (for convenience)
  
  inline bool isUndefined() {
  
    return adapter->type == TYPE_UNDEFINED;
    
  }
  inline bool isNull() {
  
    return adapter->type == TYPE_NULL;
  
  }
  inline bool isBoolean() {
  
    return adapter->type == TYPE_BOOLEAN;
  
  }
  inline bool isNumber() {
  
    return adapter->type == TYPE_NUMBER;
  
  }
  inline bool isString() {
  
    return adapter->type == TYPE_STRING;
  
  }
  inline bool isObject() {
  
    return adapter->type == TYPE_OBJECT;
  
  }
  inline bool isArray() {
  
    return adapter->type == TYPE_ARRAY;
  
  }

};

