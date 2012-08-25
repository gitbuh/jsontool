class var {

  public:
  
  TypeAdapter *adapter;
  
  boolean booleanValue;
  
  number numberValue;
  
  string stringValue;
  
  Object objectValue;
  
  Array arrayValue;
  
  //
  
  Object tempKeys;
  
  var *parent;
  
  bool isTempArrayMember;
  
  bool isTempObjectMember;
  
  unsigned tempArrayKey;
  
  string tempObjectKey;
  
  
  // initializers
  
  
  void reset() {
  
    booleanValue = false;
    numberValue = 0;
    stringValue = "null"; // "undefined";
    objectValue = Object();
    arrayValue = Array();
  }
  
  void init() {
    isTempArrayMember = false;
    isTempObjectMember = false;
    reset();
    adapter = new TypeAdapter();
  }
  
  void setFromVariant(const var &value) {
  
    reset();
    delete adapter;
    adapter = new TypeAdapter();
    copy(value);
    
  }
  
  void setFromUndefined() {
  
    reset();
    delete adapter;
    adapter = new TypeAdapter();
    
  }
  
  void setFromNull() {
  
    reset();
    stringValue = "null";
    delete adapter;
    adapter = new NullAdapter();
    
  }
  
  void setFromBoolean(boolean value) {
  
    reset();
    booleanValue = value;
    delete adapter;
    adapter = new BooleanAdapter();
    
  }
  
  void setFromNumber(number value) {
  
    reset();
    numberValue = value;
    delete adapter;
    adapter = new NumberAdapter();
    
  }
  
  void setFromString(string value) {
  
    reset();
    stringValue = value;
    delete adapter;
    adapter = new StringAdapter();
    
  }
  
  void setFromObject(Object value) {
  
    reset();
    objectValue = value;
    delete adapter;
    adapter = new ObjectAdapter();
    
  }
  
  void setFromArray(Array value) {
  
    reset();
    arrayValue = value;
    delete adapter;
    adapter = new ArrayAdapter();
    
  }
  
  // adapter wrappers
  
  string toString() const {
  
    return adapter->toString(*this);
  
  }
  
  number toNumber() const {
  
    return adapter->toNumber(*this);
  
  }
  
  // cast operators
  
  operator number() const { 
    return numberValue;
  }
  
  operator string() const { 
    return toString();
  }
  /*
  operator cstring() const { 
    return toString().c_str();
  }
  */
  operator Object() const { 
    return objectValue;
  }
  
  operator Array() const { 
    return arrayValue;
  }
  
  // operators
  
  
  void checkTempMember() {
  
      if (isTempArrayMember) {
        isTempArrayMember = false;
        parent->arrayValue.resize(tempArrayKey + 1);
        parent->arrayValue[tempArrayKey] = *this;
        parent->tempKeys.erase((string)(var)tempArrayKey);
      } else if (isTempObjectMember) {
        isTempObjectMember = false;
        parent->objectValue[tempObjectKey] = *this;
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
  
    if (!objectValue.count(key)) {
    
      tempKeys[key] = var();
      tempKeys[key].isTempObjectMember = true;
      tempKeys[key].parent = this;
      tempKeys[key].tempObjectKey = key;
      
      return tempKeys[key];
      
    }
    
    return objectValue[key];
  }
  
  var &operator [] (const int key) {
    
    if ((unsigned)key >= arrayValue.size()) {
    
      string k = (var)key;
      tempKeys[k] = var();
      tempKeys[k].isTempArrayMember = true;
      tempKeys[k].parent = this;
      tempKeys[k].tempArrayKey = key;
      
      return tempKeys[k];
      
    }
    
    return arrayValue[key];
    
  }
  
  
  // ctors

  
  var() {
  
    init();
  
  }

  var(Null) {
  
    init();
  
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
  
  bool isUndefined() {
  
    return adapter->type == TYPE_UNDEFINED;
    
  }
  bool isNull() {
  
    return adapter->type == TYPE_NULL;
  
  }
  bool isBoolean() {
  
    return adapter->type == TYPE_BOOLEAN;
  
  }
  bool isNumber() {
  
    return adapter->type == TYPE_NUMBER;
  
  }
  bool isString() {
  
    return adapter->type == TYPE_STRING;
  
  }
  bool isObject() {
  
    return adapter->type == TYPE_OBJECT;
  
  }
  bool isArray() {
  
    return adapter->type == TYPE_ARRAY;
  
  }

};
