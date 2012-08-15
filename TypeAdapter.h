class TypeAdapter {

  public:
  
  boolean toBoolean(var value) {
  
    return value.booleanValue;
  
  }
  
  number toNumber(var value) {
  
    return value.numberValue;
  
  }

  string toString(var value) {
  
    return value.stringValue;
  
  }
  
  Object toObject(var value) {
  
    return value.objectValue;
  
  }
  
  Array toArray(var value) {
  
    return value.arrayValue;
  
  }

};

