class BooleanAdapter: public TypeAdapter {

  public:
  
  number toNumber(var value) {
  
    return value.booleanValue ? 1 : 0;
  
  }
  
  string toString(var value) {
    
    return value.booleanValue ? "true" : "false";
    
  }

};

